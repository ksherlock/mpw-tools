/*
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <unistd.h>
#include <err.h>

#include <Files.h>
#include <ErrMgr.h>
#include <DateTimeUtils.h>

static char error_message[255];

char *_x = NULL;
int _d = 0;
int _n = 0;
int _i = 0;
OSType _c = 0;
OSType _t = 0;
int _m = 1;
int _o = 0;
int _r = 0;
int _s = 0;
int _q = 0;
int _filter = 0;


char *creator(OSType c) {
	static char buffer[5];

	memcpy(buffer, &c, 4);
	buffer[4] = 0;
	if (isprint(buffer[0]) && isprint(buffer[1]) && isprint(buffer[2]) && isprint(buffer[3]))
		return buffer;
	return "????";
}

char *date(unsigned long tm) {
	static char buffer[20];
	DateTimeRec dt;
	char am;

	if (tm == 0) return "";

	SecondsToDate(tm, &dt);

	am = 'A';
	if (dt.hour >= 12) { dt.hour -= 12; am = 'P'; }
	if (dt.hour == 0) dt.hour = 12;

	sprintf(buffer, "%u/%u/%04u %2u:%02u %cM",
		dt.month, dt.day, dt.year, 
		dt.hour, dt.minute, am);	

	return buffer;
}

/*

Name                                 Flags       Finder Comments    Data Sz   Rsrc Sz  Crtr     Creation-Date    Size      Last-Mod-Date   Type       Owner             Group        Privileges
-------------------------------  ------------- ------------------- --------- --------- ---- ------------------- ------ ------------------- ---- ----------------- ----------------- -----------


*/
void header(const char *fmt) {
	int c;
	int i;

	fputs("Name                            ", stdout);

	for (i = 0; c = fmt[i]; ++i) {
		switch (c) {
			case 'b':
				fputs("  Data Sz ", stdout);
				break;
			case 'r':
				fputs("  Rsrc Sz ", stdout);
				break;
			case 'c':
				fputs(" Crtr", stdout);
				break;
			case 't':
				fputs(" Type", stdout);
				break;
			case 'k':
				fputs("  Size ", stdout);
				break;
			case 'm':
				fputs("     Last-Mod-Date  ", stdout);
				break;
			case 'd':
				fputs("     Creation-Date  ", stdout);
				break;
		}
	}

	fputc('\n', stdout);
	fputs("------------------------------- ", stdout);
	for (i = 0; c = fmt[i]; ++i) {
		switch (c) {
			case 'b':
			case 'r':
				fputs(" ---------", stdout);
				break;
				break;
			case 'c':
			case 't':
				fputs(" ----", stdout);
				break;
			case 'k':
				fputs(" ------", stdout);
				break;
			case 'd':
			case 'm':
				fputs(" -------------------", stdout);
				break;
		}
	}
	fputc('\n', stdout);
}

void format(const char *name, CInfoPBRec *pb, const char *fmt) {
	int c;
	int dir;
	int i;

	//if (!pb || !fmt) return;


	printf("%-31s ", name);
	dir = pb->hFileInfo.ioFlAttrib & (1<<4) ? 1 : 0;
	for (i = 0; c = fmt[i]; ++i) {

		switch (c) {

		case 'b': /* logical size of data fork */
			printf(" %8ub", dir ? 0 : pb->hFileInfo.ioFlLgLen);
			break;
		case 'r': /* logical size of resource fork */
			printf( " %8ub", dir ? 0 : pb->hFileInfo.ioFlRLgLen);
			break;
		case 'c': /* file creator */
			printf(" %s", dir ? "Fldr" : creator(pb->hFileInfo.ioFlFndrInfo.fdCreator));
			break;
		case 't': /* file type */
			printf(" %s", dir ? "Fldr" : creator(pb->hFileInfo.ioFlFndrInfo.fdType));
			break;
		case 'd': /* creation date */
			printf(" %19s", date(dir ? pb->dirInfo.ioDrCrDat : pb->hFileInfo.ioFlCrDat));
			break;
		case 'm': /* modification date */
			printf(" %19s", date(dir ? pb->dirInfo.ioDrMdDat : pb->hFileInfo.ioFlMdDat));
			break;
		case 'k': /* data + resource blocks */
			printf(" %5uK", dir ? 0 : 
				((pb->hFileInfo.ioFlPyLen + 1023) >> 10) +  ((pb->hFileInfo.ioFlRPyLen + 1023) >> 10)
			);
			break;

		case 'a': /* attributes */
			break;
		case 'f': /* finder comments */
			break;
		case 'o': /* owner */
			break;
		case 'g': /* group */
			break;
		case 'p': /* priveleges */
			break;
		}
	}
	fputc('\n', stdout);
}

void validate_format(const char *fmt) {
	int c;
	int i;
	for (i = 0; (c = fmt[i]); ++i) {
		switch (c) {
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'f':
			case 'g':
			case 'k':
			case 'm':
			case 'o':
			case 'p':
			case 'r':
			case 't':
				break;
			default:
				fprintf(stderr, "# Files -%c is not a valid format character.\n");
				exit(1);
		}
	}
}




char *c2p(const char *cp)
{
	int length;
	char *p;

	if (!cp) return NULL;
	length = strlen(cp);
	if (length > 255)
		errx(2, "Pathname too long.");

	p = malloc(length + 2); // + 2 for \0 and length.
	if (!p) err(2, "malloc");

	p[0] = length;
	memcpy(p + 1, cp, length + 1);
	return p;
}

const char *ct(unsigned char *cp) {
	static char table[] = "0123456789abcdef";
	static char buffer[12];

	int i, j;
	for (i = 0; i < 4; ++i) {
		if (!isprint(cp[i])) break;
		buffer[i+1] = cp[i];
	}
	if (i == 4) {
		buffer[0] = '\'';
		buffer[5] = '\'';
		buffer[6] = 0;
		return buffer;
	}

	for (i = 0, j = 1; i < 4; ++i) {
		unsigned x = cp[i];
		buffer[j++] = table[x >> 4];
		buffer[j++] = table[x & 0x0f];
	}

	buffer[0] = '$';
	buffer[j] = 0;
	return buffer;
}

// return 
int exclude(CInfoPBRec *pb) {

	OSType ctype = 0;
	OSType ftype = 0;
	int dir = pb->hFileInfo.ioFlAttrib & (1<<4) ? 1 : 0;

	if (dir && _s) return 1;
	if (!dir && _d) return 1;

	if (!dir) ctype = pb->hFileInfo.ioFlFndrInfo.fdCreator;
	if (!dir) ftype = pb->hFileInfo.ioFlFndrInfo.fdType;

	if ((_filter & 0x01) && (ctype != _c)) return 1;
	if ((_filter & 0x02) && (ftype != _t)) return 1;
	return 0;
} 

void dir(int dirID) {
	unsigned char buffer[256+1];
	OSErr err;
	CInfoPBRec pb;
	int i, l;

	memset(&pb, 0, sizeof(pb));
	pb.hFileInfo.ioNamePtr = buffer;
	//pb.hFileInfo.ioVRefNum = 0;

	for(i = 1; ;++i) {
		pb.hFileInfo.ioFDirIndex = i;
		pb.hFileInfo.ioDirID = dirID; // PBGetCatInfo resets to file id.
		err = PBGetCatInfoSync(&pb);
		if (err == fnfErr) break;
		if (err != 0)
		{
			fprintf(stderr, "# GetCatInfo: %s\n", GetSysErrText(err, error_message));		
			break;
		}
		if (exclude(&pb)) continue;

		l = buffer[0];
		buffer[l+1] = 0;
		if (_x) {
			format((char *)buffer+1, &pb, _x);
		}
		else {
			// _m, etc.
			fprintf(stdout, "%s\n", buffer+1);
		}
	}
}

void one_file(const char *name) {

	CInfoPBRec pb;
	OSErr err;

	char *pstr = c2p(name);

	memset(&pb, 0, sizeof(pb));
	pb.hFileInfo.ioNamePtr = (unsigned char *)pstr;
	err = PBGetCatInfoSync(&pb);
	free(pstr);
	if (err != 0)
	{
		fprintf(stderr, "### Files - unable to get information on \"%s\"\n", name);
		fprintf(stderr, "# %s\n", GetSysErrText(err, error_message));		
		return;
	}

	if (exclude(&pb)) return;

	// todo -- if directory, etc.
	if (_x) {
		format(name, &pb, _x);
	}
	else {
		// _m, etc.
		fprintf(stdout, "%s\n", name);
	}
}

void usage(status) {
	fputs("# Usage: Files [options] [files...]\n", stderr);
	exit(status);
}

int tox(char c)
{
	c |= 0x20;
	if (c >='0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	return 0;
}



long hex(const char *in)
{
	long rv = 0;

	int i;
	for (i = 0; ; ++i)
	{
		long tmp;
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

long dec(const char *in)
{
	long rv = 0;

	int i;
	for (i = 0; ; ++i)
	{
		long tmp;
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

long parse_num(const char *cp)
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

OSType parse_ostype(const char *cp) {
	OSType rv = 0;
	unsigned char c;

	if ((c = *cp)) {
		rv |= c << 24;
		cp++;
	}

	if ((c = *cp)) {
		rv |= c << 16;
		cp++;
	}

	if ((c = *cp)) {
		rv |= c << 8;
		cp++;
	}

	if ((c = *cp)) {
		rv |= c << 0;
		cp++;
	}

	return rv;
}

int main(int argc, char **argv) {

	int c;
	unsigned i;

	// -y4, -fr, -af
	while ((c = getopt(argc, argv, "c:dfhilm:noqrst:x:")) != -1) {
		switch(c) {
			case '?':
			case ':':
			default:
				usage(1);
				break;
			case 'c':
				_c = parse_ostype(optarg);
				_filter |= 1;
				break;
			case 'd':
				_d = 1;
				break;
			case 'h':
				usage(0);
				break;
			case 'i':
				_i = 1;
				break;
			case 'l':
				_x = "tckamd";
				break;
			case 'm':
				_m = parse_num(optarg);
				if (_m < 1 ) {
					fprintf(stderr, "# Files - Illegal number, %s, specified with the \"-m\" option.\n", optarg);
					exit(1);
				}
				break;
			case 'n':
				_n = 1;
				break;
			case 'o':
				_o = 1;
				break;
			case 'q':
				_q = 1;
				break;
			case 'r':
				_r = 1;
				break;
			case 's':
				_s = 1;
				break;
			case 't':
				_t = parse_ostype(optarg);
				_filter |= 2;
				break;
			case 'x':
				_x = optarg;
				break;
		}
	}

	argc -= optind;
	argv += optind;


	if (_d && _s) {
		fprintf(stderr, "### Files - Conflicting options were specified.\n");
		usage(1);
	}

	if (_x) validate_format(_x);

	pascalStrings = false;
	InitErrMgr(NULL, NULL, true);

	if (_x && !_n) header(_x);


	if (argc == 0) dir(0);

	for (i = 0; i < argc; ++i) {
		one_file(argv[i]);
	}

	CloseErrMgr();


	return 0;
}