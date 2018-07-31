/*
 * Copyright (c) 2018, Kelvin W Sherlock
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <Files.h>
#include <ErrMgr.h>

#include "FileCommon.h"
#include "Rename-flags.h"

/*
Rename          # rename files and directories
Rename [-y | -n | -c] oldName newName
    -resolve                # resolve leaf aliases in oldName
    -y                      # overwrite existing file (avoids dialog)
    -n                      # don't overwrite existing file (avoids dialog)
    -c                      # cancel if conflict occurs (avoids dialog)
*/




static char error_message[255];


/*
 * -1: cancel
 * 0: no
 * 1: yes
 */
int check(const unsigned char *pname) {
	int m = mode(pname, NULL);
	if (m <= 0) return 1; /* error or does not exist */

	if (flags._y) return 1;
	if (flags._n) return 0;
	if (flags._c) return -1;

	return prompt(pname, "overwrite");
}

int do_rename(const unsigned char *src, const unsigned char *dest) {

	/* n.b. - does not move into a directory (use Move for that) */
	int st;
	OSErr err;

	st = mode(src, &err);
	if (st <= 0) {

		fprintf(stderr, "### Rename - unable to rename %s to %s\n", src+1, dest+1);
		fprintf(stderr, "# %s\n", GetSysErrText(err, error_message));

		if (err == fnfErr) return 2;
		return 3;
	}

	st = check(dest);
	if (st < 0) return 4;
	if (st == 0) return 1;

	err = FSDelete((const unsigned char *)dest, 0);
	if (err && err != fnfErr) {
		fprintf(stderr, "### Rename - unable to delete %s\n", dest+1);
		fprintf(stderr, "# %s\n", GetSysErrText(err, error_message));
		return 2;
	}
	err = Rename((const unsigned char *)src, 0, (const unsigned char *)dest);
	if (err) {
		fprintf(stderr, "### Rename - unable to rename %s to %s\n", src+1, dest+1);
		fprintf(stderr, "# %s\n", GetSysErrText(err, error_message));
		return 3;
	}
	return 0;
}

int main(int argc, char **argv) {

	unsigned char *src;
	unsigned char *dest;
	int status;

	pascalStrings = false;
	InitErrMgr(NULL, NULL, true);

	argc = FlagsParse(argc, argv);

	if (flags._c + flags._n + flags._y > 1) {
		fprintf(stderr, "### Rename - Conflicting options were specified.\n");
		FlagsHelp();
		return 1;
	}


	if (argc != 3) {
		FlagsHelp();
		return 1;
	}


	src = c2p(argv[1]);
	dest = c2p(argv[2]);
	status = do_rename(src, dest);
	free(src);
	free(dest);
	CloseErrMgr();

	return status;
}
