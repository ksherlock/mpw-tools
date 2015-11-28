#include <stdio.h>
/*
 * Echo [-n] ...
 */


int main(int argc, char **argv) {
	
	int i;
	int space = 0;
	int n = 0;

	for (i = 1; i < argc; ++i) {

		char *cp = argv[i];
		if (cp[0] == '-' && cp[1] == 'n' && cp[2] == 0) {
			n = 1;
			continue;
		}
		if (space) fputc(' ', stdout);
		fputs(cp, stdout);
		space = 1;
	}

	if (space && n) fputc(' ', stdout);
	if (!n) fputc('\n', stdout);
	return 0;
}
