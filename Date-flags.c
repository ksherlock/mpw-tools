
#ifdef __ORCAC__
#pragma optimize 79
#pragma noroot
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Date-flags.h"

void FlagsHelp(void)
{
  fputs("Date [options]\n", stdout);
  fputs("-a                      abbreviated date (e.g. Wed, Jun 14, 1995)\n", stdout);
  fputs("-s                      short date (e.g. 6/14/95)\n", stdout);
  fputs("-s4                     short date, using 4-digit year (e.g. 6/14/1995)\n", stdout);
  fputs("-u                      uniform output format, \1YYYY-MM-DD HH:MM:SS\1\n", stdout);
  fputs("-st                     omit seconds from time format\n", stdout);
  fputs("-d                      write date only\n", stdout);
  fputs("-t                      write time only\n", stdout);
  fputs("-c seconds              write date corresponding to seconds\n", stdout);
  fputs("-x date                 write seconds corresponding to date\n", stdout);
  fputs("-n                      write seconds since January 1, 1904\n", stdout);
  fputs("-utc                    write output converted to Universal Time Coordinates\n", stdout);
  fputs("\n", stdout);
  exit(0);
}

struct Flags flags;
int FlagsParse(int argc, char **argv)
{
  char *cp;
  char *optarg;

  char c;
  int i;
  int j;
  int eof; // end-of-flags
  int mindex; // mutation index.

  memset(&flags, 0, sizeof(flags));

  for (i = 1, mindex = 1, eof = 0; i < argc; ++i) {
    cp = argv[i];
    c = cp[0];
      
    if (c != '-' || eof) {
      if (i != mindex) argv[mindex] = argv[i];
      mindex++;
      continue;    	
    }
      
    // -- = end of options.
    if (cp[1] == '-' && cp[2] == 0) {
      eof = 1;
      continue;
    }
    if (!strcasecmp("s4", cp+1)) {
        flags._s4 = 1;
        continue;
    }
    if (!strcasecmp("st", cp+1)) {
        flags._st = 1;
        continue;
    }
    if (!strcasecmp("utc", cp+1)) {
        flags._utc = 1;
        continue;
    }
   
    // now scan all the flags in the string...
    optarg = NULL;
    for (j = 1; ; ++j) {
      c = cp[j];
      if (c == 0) break;
          
      switch (c) {
      case 'h':
        FlagsHelp();
        exit(0);
      case 'a':
      case 'A':
        flags._a = 1;
        break;
      case 'c':
      case 'C':
        // -xarg or -x arg
        ++j;  
        if (cp[j]) {
          optarg = cp + j;
        }
        else {
          if (++i >= argc) {
            fputs("### Date - \"-c\" requires an argument.\n", stderr); 
            exit(1);
          }
          optarg = argv[i];
        }
        flags._c = optarg;

        break;
      case 'd':
      case 'D':
        flags._d = 1;
        break;
      case 'n':
      case 'N':
        flags._n = 1;
        break;
      case 's':
      case 'S':
        flags._s = 1;
        break;
      case 't':
      case 'T':
        flags._t = 1;
        break;
      case 'u':
      case 'U':
        flags._u = 1;
        break;
      case 'x':
      case 'X':
        // -xarg or -x arg
        ++j;  
        if (cp[j]) {
          optarg = cp + j;
        }
        else {
          if (++i >= argc) {
            fputs("### Date - \"-x\" requires an argument.\n", stderr); 
            exit(1);
          }
          optarg = argv[i];
        }
        flags._x = optarg;

        break;

      default:
        fprintf(stderr, "### Date - \"-%c\" is not an option.\n", c);
        exit(1); 
      }
            
      if (optarg) break;
    }    
  }

  return mindex;
}
