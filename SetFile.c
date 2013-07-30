/*
 * Copyright (c) 2013, Kelvin W Sherlock
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
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <Finder.h>
#include <Files.h>

#include "SetFile-flags.h"



int tox(char c)
{
	c |= 0x20;
	if (c >='0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	return 0;
}

int hex(const char *in, char *out, int length)
{
	int i;
	for (i = 0; i < length; ++i)
	{
		int tmp = 0;
		char c;

		c = *in++;
		if (!isxdigit(c)) return -1;
		tmp |= tox(c) << 4;

		c = *in++;
		if (!isxdigit(c)) return -1;
		tmp |= tox(c);

		*out++ = tmp;
	}	
	return 0;
}

// convert the file/creators...
// format:
// 0x \xdigit{8}
// $ \xdigit{8}
// 4-cc code
int checkcode(const char *in, char *out)
{
	int length;

	length = strlen(in);

	if (length == 4)
	{
		// 4 cc code.
		int i;
		for (i = 0; i < 4; ++i)
			out[i] = in[i];
		return 0;
	}

	if (length == 9 && in[0] == '$')
		return hex(in + 1, out, 4);

	if (length ==10 && in[0] == '0' && in[1] == 'x')
		return hex(in + 2, out, 4);

	return -1;
}

int main(int argc, char **argv)
{

	FInfo newFI;
	int optind;
	int ok;
	int i;


	argc = FlagsParse(argc, argv);

	if (argc == 1)
	{
		FlagsHelp();
		return 0;
	}


	memset(&newFI, 0, sizeof(newFI));

	// todo - m  sets the mod date (. = now)
	if (!flags._t && !flags._c) return 0;

	if (flags._t)
	{
		ok = checkcode(flags._t, (char *)&newFI.fdType);
		if (ok < 0)
		{
			fprintf(stderr, "SetFile: invalid file type: `%s`\n", flags._t);
			exit(1);
		}
	}

	if (flags._c)
	{
		ok = checkcode(flags._c, (char *)&newFI.fdCreator);
		if (ok < 0)
		{
			fprintf(stderr, "SetFile: invalid creator type: `%s`\n", flags._c);
			exit(1);
		}
	}

	for (i = 1; i < argc; ++i)
	{
		FInfo fi;
		char buffer[256];
		char *cp;
		int l;

		cp = argv[i];
		l = strlen(cp);
		if (l > 255)
		{
			fprintf(stderr, "SetFile: %s: file name too long.\n", cp);
			continue;
		}

		buffer[0] = l;
		memcpy(buffer + 1, cp, l);

		memset(&fi, 0, sizeof(fi));

		ok = GetFInfo((unsigned char *)buffer, 0, &fi);
		
		if (flags._t) fi.fdType = newFI.fdType;
		if (flags._c) fi.fdCreator = newFI.fdCreator;

		ok = SetFInfo((unsigned char *)buffer, 0, &fi);
		if (ok != 0)
		{
			fprintf(stderr, "SetFile: %s: unable to set finder info: %d\n", cp, ok);
		}
	}

	exit(0);
	return 0;
}