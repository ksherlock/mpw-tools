#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Files.h>

#include "FileCommon.h"

unsigned char *c2p(const char *cp)
{
	int length;
	unsigned char *p;

	if (!cp) return NULL;
	length = strlen(cp);
	if (length > 255)
	{
		fprintf(stderr, "# Error: Pathname is too long.\n");
		exit(1);
		return NULL;
	}

	p = malloc(length + 2); // + 2 for \0 and length.
	if (!p)
	{
		fprintf(stderr, "# Error: unable to allocate memory.\n");
		exit(1);
		return NULL;
	}

	p[0] = length;
	memcpy(p + 1, cp, length + 1);
	return p;
}

// -1 - error.
// 0 - no file
// 1 - regular file
// 2 - directory.
int mode(const unsigned char *pname, OSErr *ec)
{
	//char *pname;
	CInfoPBRec rec;
	OSErr err;

	memset(&rec, 0, sizeof(rec));

	rec.hFileInfo.ioNamePtr = (unsigned char *)pname;
	err = PBGetCatInfo(&rec, false);
	if (ec) *ec = err;
	if (err) return err = fnfErr ? 0 : -1;

	if (rec.hFileInfo.ioFlAttrib & kioFlAttribDirMask)
		return 2;

	return 1;
}

int prompt(const unsigned char *pname, const char *verb) {
	char ch;
	char first;

	fprintf(stderr, "%s %s? ", verb, pname+1);
	fflush(stderr);

	first = ch = getchar();
	while (ch != '\n' && ch != EOF) ch = getchar();
	if (first == 'y' || first == 'Y') return 1;
	if (first == 'c' || first == 'C') return -1;
	return 0;
}


