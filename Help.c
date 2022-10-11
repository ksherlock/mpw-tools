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

/*
 * MPW Help utility.
 * 
 * help topic
 * does a cat of $ShellDirectory:Help:topic
 */

 /*
  * MPW 3.2
  *
  * C Help.c -o Help.c.o -r {SymOptions}
  *
  * Link {SymOptions} -w -c 'MPS ' -t MPST Help.c.o
  * -sn STDIO=Main
  * -sn INTENV=Main
  * -sn %A5Init=Main
  * "{Libraries}"Stubs.o
  * "{CLibraries}"StdCLib.o
  * "{Libraries}"Interface.o
  * "{Libraries}"Runtime.o
  * "{Libraries}"ToolLibs.o
  * -o Help
  *
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *base(char *str)
{
	char *rv = str;
	char *tmp = str;

	if (!str) return str;

	for (tmp = str; *tmp; ++tmp)
	{
		char c = *tmp;
		if (c == ':' || c == '/') rv = tmp + 1;
	}
	return rv;

}
void help(char *root, char *topic)
{
	int l;
	char *path;
	FILE *fp;


	// todo -- check if they're being stupid or malicious and 
	// handle / or : chars.

	topic = base(topic);
	if (!topic || !*topic)
	{
		return;
	}
	l = strlen(root) + strlen("Help:") + strlen(topic) + 1;
	path = malloc(1);
	if (!path)
	{
		fprintf(stderr, "### Help - Memory allocation failure.\n");
		return;
	}

	sprintf(path, "%sHelp:%s", root, topic);
	fp = fopen(path, "r");
	free(path);
	if (!fp)
	{
		fprintf(stderr, "### Help - \"%s\" was not found.\n", topic);
		return;
	}

	for(;;)
	{
		char buffer[512];
		int count;

		count = fread(buffer, 1, sizeof(buffer), fp);
		if (count == 0) break;

		fwrite(buffer, 1, count, stdout);
	}
	fwrite("\r", 1, 1, stdout);
	fclose(fp);
}
int main(int argc, char **argv)
{
	char *root;

	root = getenv("ShellDirectory");
	if (!root || !*root)
	{
		fprintf(stderr, "### Help - $ShellDirectory is not defined.\n");
		return 1;
	}
	if (argc == 1)
	{
		help(root, "MPW");
	}
	else
	{
		int i;
		for (i = 1; i < argc; ++i)
		{
			help(root, argv[i]);
		}
	}

	return 0;
}