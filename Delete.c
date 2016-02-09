/*
 * Delete          # delete files and directories
 * Delete [-y | -n | -c] [-i] [-p] name...
 *     -y                      # delete directory contents (avoids dialog)
 *     -n                      # don't delete directory contents (avoids dialog)
 *     -c                      # cancel if a directory is to be deleted (avoids dialog)
 *     -i                      # ignore errors (no diagnostics)
 *     -p                      # write progress information to diagnostics
 */

/*
 * return value:
 * 0 - all ok
 * 1 - syntax error
 * 2 - delete error
 * 4 - canceled.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Files.h>
#include <ErrMgr.h>

#include "Delete-flags.h"
 
char *c2p(const char *cp)
{
	int length;
	char *p;

	if (!cp) return NULL;
	length = strlen(cp);
	if (length > 255)
	{
		fprintf(stderr, "Error: Pathname is too long.\n");
		exit(1);
		return NULL;
	}

	p = malloc(length + 2); // + 2 for \0 and length.
	if (!p)
	{
		fprintf(stderr, "Error: unable to allocate memory.\n");
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
int mode(const char *pname)
{
	//char *pname;
	CInfoPBRec rec;
	OSErr status;

	memset(&rec, 0, sizeof(rec));

	//pname = c2p(path);
	//if (!pname) return -1;

	rec.hFileInfo.ioNamePtr = (unsigned char *)pname;
	status = PBGetCatInfo(&rec, false);
	//free(pname);

	if (status) return 0;
	if (rec.hFileInfo.ioFlAttrib & kioFlAttribDirMask)
		return 2;

	return 1;
}

int prompt(const char *file) {
	char ch;
	char first;

	fprintf(stderr, "remove %s? ", file);
	fflush(stderr);

	first = ch = getchar();
	while (ch != '\n' && ch != EOF) ch = getchar();
	if (first == 'y' || first == 'Y') return 1;
	return 0;
}

static char error_message[255];

int main(int argc, char **argv) {
	int i;
	int status = 0;

	argc = FlagsParse(argc, argv);

	if (flags._c + flags._n + flags._y > 1) {
		fprintf(stderr, "### Delete - Conflicting options were specified.\n");
		FlagsHelp();
		return 1;
	}

	if (argc == 1)
	{
		FlagsHelp();
		return 1;
	}



	pascalStrings = false;
	InitErrMgr(NULL, NULL, true);

	for (i = 1 ; i < argc; ++i) {
		OSErr err;
		int m;

		char *file = argv[i];
		char *p = c2p(file);
		// todo -- y/n/c flags.

		m = mode(p);
		if (m == 2 && !flags._y) {
			// directory...
			if (flags._n) continue;
			if (flags._c) { status = 4; break; }
			
			if (!prompt(file)) continue;
		}

		err = FSDelete((unsigned char *)p, 0);
		if (err && !flags._i) {
			fprintf(stderr, "### Delete - unable to delete %s\n", file);
			fprintf(stderr, "# %s\n", GetSysErrText(err, error_message));
			status = 2;
			break;
		}
		if (!err && flags._p) {
			fprintf(stderr, "%s deleted.\n", file);
		}
		free(p);
	}
	CloseErrMgr();
	return status;
}
