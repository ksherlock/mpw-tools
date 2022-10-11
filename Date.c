#include <stdio.h>
#include <stdlib.h>

#include <DateTimeUtils.h>
#include "Date-flags.h"

/*

Date            # write the date and time
Date ([-a | -s | -s4 | -u] [-st] [-d | -t] [-c seconds | -utc]) | ([-n] [-utc]) | [-x date] > date
    -a                      # abbreviated date (e.g. Wed, Jun 14, 1995)
    -s                      # short date (e.g. 6/14/95)
    -s4                     # short date, using 4-digit year (e.g. 6/14/1995)
    -u                      # uniform output format, "YYYY◊MM◊DD HH:MM:SS"
    -st                     # omit seconds from time format
    -d                      # write date only
    -t                      # write time only
    -c seconds              # write date corresponding to seconds
    -x date                 # write seconds corresponding to date
    -n                      # write seconds since January 1, 1904
    -utc                    # write output converted to Universal Time Coordinates

*/

void conflict(void) {
	fprintf(stderr, "### Date - Conflicting options were specified.\n");
	FlagsHelp();
	exit(1);
}
unsigned long parse_seconds(const char *cp) {
	unsigned long rv;
	char *end = NULL;

	rv = strtoul(cp, &end, 10);
	if (!end || *end) {
		fprintf(stderr, "### Date - illegal number, %s, specified with the \"-c\" option\n", cp);
		exit(1);
	}
	return rv;
}

unsigned long parse_date(const char *cp) {

	/* easter egg? bug?  return 42316544 on bad input
	 accepts mm/dd/yy hh:mm:ss
	 accepts yyyy-mm-dd hh:mm:ss as well,
	but option-shift-v diamond instead of -
	*/
	// should use StringToDate, StringToTime....

	fputs("### Date -x not supported (yet)\n", stderr);
	return 0;
}

int main(int argc, char **argv) {

	unsigned type = 0;
	unsigned long now;
	DateForm df = longDate;
	unsigned i;

	unsigned char ds[256+1];
	unsigned char ts[256+1];
	const char *sep;


	argc = FlagsParse(argc, argv);

	if (argc > 1) {
		fputs("### Date - Too many parameters were specified.\n", stderr);
		FlagsHelp();
		return 1;		
	}

	// ([-a | -s | -s4 | -u] [-st] [-d | -t] [-c seconds | -utc])
	// ([-n] [-utc])
	// [-x date]
	if (flags._a + flags._s + flags._s4 + flags._u > 1) conflict();
	if (flags._d + flags._t > 1) conflict();
	if (flags._c && flags._utc) conflict();
	if (flags._utc + flags._n > 1) conflict();
	// utc allowed in 1 or 2, not 3.
	if (flags._utc && flags._x) conflict();

	type = 0;
	if (flags._a | flags._s | flags._s4 | flags._u | flags._st | flags._d | flags._t)
		type |= 1;
	if (flags._c) type |= 1;
	if (flags._n) type |= 2;
	if (flags._x) type |= 4;

	switch(type) {
		case 0:
		case 1:
		case 2:
		case 4:
			break;
		default:
			conflict();
	}

	if (flags._x) {
		printf("%lu", parse_date(flags._x));
		return 0;
	}

	if (flags._c) {
		now = parse_seconds(flags._c);
	} else {
		ReadDateTime(&now);
	}

	if (flags._n) {
		/* just print seconds */
		printf("%lu\n", now);
		return 0;
	}

	if (flags._u) {
		/* uniform format .... */
	}

	if (flags._a) df = abbrevDate;
	if (flags._s) df = shortDate;

	// SecondsToDate(now, &dt);

	IUDateString(now, df, ds);
	IUTimeString(now, flags._st ? 0 : 1, ts);


	i = ds[0];
	if (flags._t) i = 0;
	ds[i+1] = 0;

	i = ts[0];
	if (flags._d) i = 0;
	ts[i+1] = 0;

	if (flags._d | flags._t) sep = "";
	else sep = " ";

	printf("%s%s%s\n", ds+1, sep, ts+1);

	return 0;
}
