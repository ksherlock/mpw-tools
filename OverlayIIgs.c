#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#include <errno.h>
#include <string.h>

#include "OverlayIIgs-flags.h"

int tox(char c)
{
	c |= 0x20;
	if (c >='0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	return 0;
}


off_t hex(const char *in)
{
	off_t rv = 0;

	int i;
	for (i = 0; ; ++i)
	{
		off_t tmp;
		char c;

		c = *in++;
		if (!c) break;

		if (!isxdigit(c)) return -1;


		tmp = rv;
		rv <<= 4;
		rv |= tox(c);

		// numver too large.
		if (rv < tmp)
		{
			return -1;
		}
	}	

	if (i == 0) return -1;

	return rv;
}

off_t dec(const char *in)
{
	off_t rv = 0;

	int i;
	for (i = 0; ; ++i)
	{
		off_t tmp;
		char c;

		c = *in++;
		if (!c) break;

		if (!isdigit(c)) return -1;


		tmp = rv;
		rv = rv * 10;
		rv += c - '0';

		// numver too large.
		if (rv < tmp)
		{
			return -1;
		}
	}	

	if (i == 0) return -1;

	return rv;
}

off_t getnum(const char *cp)
{
	if (!cp) return -1;

	if (cp[0] == '$')
	{
		return hex(cp + 1);
	}
	
	if (cp[0] == '0' && cp[1] == 'x')
	{
		return hex(cp + 2);
	}
	return dec(cp);
}


int seek_to(int fd, off_t address)
{
	// posix lseek(2) will seek past the eof and zero-fill
	// when a write occurs.

	// mpw lseek will fail (ENXIO) in such situations.
	// SetEOF will not zero-fill.

	// to compensate, manually zero-fill to the address
	// if address > eof.

	off_t eof;

	eof = lseek(fd, 0, SEEK_END);
	if (eof < 0)
		return -1;

	while (eof < address)
	{
		static char buffer[512] = { 0 };

		off_t size = address - eof;
		if (size > 512) size = 512;

		size = write(fd, buffer, size);
		if (size < 0) return -1;
		eof += size;
	}

	eof = lseek(fd, address, SEEK_SET);
	if (eof < 0)
		return -1;

	return 0;
}

int main(int argc, char **argv)
{
	char *src;
	char *dest;

	int srcFD, destFD;
	off_t address;
	int rv;


	argc = FlagsParse(argc, argv);

	if (argc != 3)
	{
		FlagsHelp();
		return 1;
	}

	if (!flags._a)
	{
		FlagsHelp();
		return 1;
	}

	address = getnum(flags._a);
	if (address == -1)
	{

		fprintf(stderr, "#OverlayIIgs: Invalid address: %s\n", flags._a);
		return 1;
	}

	src = argv[1];
	dest = argv[2];

	srcFD = open(src, O_RDONLY | O_BINARY);
	if (srcFD < 0)
	{
		fprintf(stderr, "#OverlayIIgs: Unable to open input file %s: %s", 
			src, strerror(errno));
		return 1;
	}

	destFD = open(dest, O_WRONLY | O_CREAT | O_BINARY);
	if (destFD < 0)
	{
		fprintf(stderr, "#OverlayIIgs: Unable to open output file %s: %s", 
			dest, strerror(errno));
		close(srcFD);
		return 1;
	}


	//if (lseek(destFD, address, SEEK_SET) < 0)
	if (seek_to(destFD, address) < 0)
	{
		fprintf(stderr, "#OverlayIIgs: Error seeking %s: %s", 
			dest, strerror(errno));
		close(srcFD);
		close(destFD);
		return 1;
	}

	// copy it
	rv = 0;

	for (;;)
	{

		unsigned char buffer[4096];
		ssize_t rsize;
		ssize_t wsize;

		rsize = read(srcFD, buffer, 4096);

		if (rsize == 0) break;

		if (rsize < 0)
		{
			fprintf(stderr, "#OverlayIIgs: Error reading %s: %s\n", 
				src, strerror(errno));
			rv = 1;
			break;
		}

		wsize = write(destFD, buffer, rsize);
		if (wsize < 0 || wsize != rsize)
		{
			fprintf(stderr, "#OverlayIIgs: Error writing %s: %s\n", 
				dest, strerror(errno));
			rv = 1;
			break;	
		}
	}

	close(srcFD);
	close(destFD);


	return rv;
}