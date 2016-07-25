#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include <tomcrypt.h>


const char *unhash(const unsigned char *hash) {
	static char buffer[33];
	static char table[] = "0123456789abcdef";

	unsigned i, j;

	for (i = 0, j = 0; i < 16; ++i) {
		unsigned char c = hash[i];
		buffer[j++] = table[c >> 4];
		buffer[j++] = table[c & 0x0f];
	}
	buffer[j] = 0;
	return buffer;
}

int process(int fd, const char *name, int fork) {

	static unsigned char buffer[4096];
	hash_state md;
	unsigned char hash[16];

	md5_init(&md);


	for(;;) {
		long l = read(fd, buffer, sizeof(buffer));
		if (l == 0) break;
		if (l < 0) {
			if (errno == EINTR) continue;
			perror("read");
			return -1;
		}
		md5_process(&md, buffer, l);
	}


	md5_done(&md, hash);
	fprintf(stdout, "MD5 (%s%s) = %s\n",
		name, fork ? "+" : "", unhash(hash));
	return 0;
}

// from md5_test
int test() {

	static const struct {
		char *msg;
		unsigned char hash[16];
	} tests[] = {
		{ "",
			{ 0xd4, 0x1d, 0x8c, 0xd9, 0x8f, 0x00, 0xb2, 0x04, 
			0xe9, 0x80, 0x09, 0x98, 0xec, 0xf8, 0x42, 0x7e } },
		{ "a",
			{0x0c, 0xc1, 0x75, 0xb9, 0xc0, 0xf1, 0xb6, 0xa8, 
			0x31, 0xc3, 0x99, 0xe2, 0x69, 0x77, 0x26, 0x61 } },
		{ "abc",
			{ 0x90, 0x01, 0x50, 0x98, 0x3c, 0xd2, 0x4f, 0xb0, 
			0xd6, 0x96, 0x3f, 0x7d, 0x28, 0xe1, 0x7f, 0x72 } },
		{ "message digest", 
			{ 0xf9, 0x6b, 0x69, 0x7d, 0x7c, 0xb7, 0x93, 0x8d, 
			0x52, 0x5a, 0x2f, 0x31, 0xaa, 0xf1, 0x61, 0xd0 } }, 
		{ "abcdefghijklmnopqrstuvwxyz",
			{ 0xc3, 0xfc, 0xd3, 0xd7, 0x61, 0x92, 0xe4, 0x00, 
			0x7d, 0xfb, 0x49, 0x6c, 0xca, 0x67, 0xe1, 0x3b } },
		{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
			{ 0xd1, 0x74, 0xab, 0x98, 0xd2, 0x77, 0xd9, 0xf5, 
			0xa5, 0x61, 0x1c, 0x2c, 0x9f, 0x41, 0x9d, 0x9f } },
		{ "12345678901234567890123456789012345678901234567890123456789012345678901234567890",
			{ 0x57, 0xed, 0xf4, 0xa2, 0x2b, 0xe3, 0xc9, 0x55, 
			0xac, 0x49, 0xda, 0x2e, 0x21, 0x07, 0xb6, 0x7a } }, 
		{ NULL, { 0 } }
	};


	unsigned i;
	unsigned ok;
	hash_state md;
	unsigned char hash[16];

	for (i = 0; tests[i].msg != NULL; i++) {
		md5_init(&md);
		md5_process(&md, (unsigned char *)tests[i].msg, (unsigned long)strlen(tests[i].msg));
		md5_done(&md, hash);

		ok = !memcmp(hash, tests[i].hash, 16);

		printf("MD5 (\"%s\") = %s - %s\n",
			tests[i].msg, unhash(hash),
			ok ? "verified correct" : "INCORRECT RESULT!");

		if (!ok) return -1;
	}


	return 0;
}

void help() {
	fputs("Usage: MD5 [-x] files...\n", stdout);
}

int main(int argc, char **argv) {


	int rv;
	int i;

	for (i = 1; i < argc; ++i) {
		char *cp = argv[i];
		if (*cp != '-') {
			break;
		}
		if (strcmp(cp, "--")) {
			++i;
			break;
		}
		if (!strcmp(cp, "-h")) {
			help();
			exit(0);
		}
		if (!strcmp(cp, "-x")) {
			return test();
		}
	}

	argv += i;
	argc -= i;

	if (argc == 0) {
		help();
		return 1;
	}

	rv = 0;
	for ( i = 0; i < argc; ++i) {

		int fd;
		int tmp;

		char *cp = argv[i];

		fd = open(cp, O_RDONLY | O_BINARY);
		if (fd < 0) {
			perror(cp);
			rv = 1;
			continue;
		}

		tmp = process(fd, cp, 0);
		if (tmp) rv = 1;
		close(fd);

		// flag for resource fork...

		fd = open(cp, O_RDONLY | O_BINARY | O_RSRC);
		if (fd < 0) {
			perror(cp);
			rv = 1;
			continue;
		}
		tmp = process(fd, cp, 1);
		if (tmp) rv = 1;
		close(fd);
	}

	return rv;
}