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
#include "FileCommon.h"

int check(const unsigned char *pname) {
	int m = mode(pname, NULL);
	if (m != 2 || flags._y) return 1;

	// directory.
	if (flags._n) return 0;
	if (flags._c) return -1;

	return prompt(pname, "remove");
}

static char error_message[255];


int do_delete(const unsigned char *file) {
	OSErr err;
	int st;

	st = check(file);
	if (st < 0) return 4;

	err = FSDelete(file, 0);
	if (err) {
		if (flags._i) return 0;
		fprintf(stderr, "### Delete - unable to delete %s\n", file+1);
		fprintf(stderr, "# %s\n", GetSysErrText(err, error_message));
		return 2;
	}

	if (flags._p) {
		fprintf(stderr, "%s deleted.\n", file+1);
	}

	return 0;
}

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

		char *file = argv[i];
		unsigned char *p = c2p(file);
		status  = do_delete(p);
		free(p);
		if (status) break;
	}
	CloseErrMgr();
	return status;
}
