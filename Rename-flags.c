
#ifdef __ORCAC__
#pragma optimize 79
#pragma noroot
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Rename-flags.h"

void FlagsHelp(void)
{
  fputs("Rename [options] oldName newName\n", stdout);
  fputs("-y    overwrite existing files (avoids dialog)\n", stdout);
  fputs("-n    don't overwrite existing file (avoids dialog)\n", stdout);
  fputs("-c    cancel if conflict occurs (avoids dialog)\n", stdout);
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

  for (i = 1, mindex = 1, eof = 0; i < argc; ++i)
  {    
    cp = argv[i];
    c = cp[0];
      
    if (c != '-' || eof)
    {
      if (i != mindex) argv[mindex] = argv[i];
      mindex++;
      continue;    	
    }
      
    // -- = end of options.
    if (cp[1] == '-' && cp[2] == 0)
    {
      eof = 1;
      continue;
    }
   
    // now scan all the flags in the string...
    optarg = NULL;
    for (j = 1; ; ++j)
    {          
      c = cp[j];
      if (c == 0) break;
          
      switch (c)
      {
      case 'h':
        FlagsHelp();
        exit(0);
      case 'y':
      case 'Y':
        flags._y = 1;
        break;
      case 'n':
      case 'N':
        flags._n = 1;
        break;
      case 'c':
      case 'C':
        flags._c = 1;
        break;

      default:
        fprintf(stderr, "### Rename - \"-%c\" is not an option.\n", c);
        exit(1); 
      }
            
      if (optarg) break;
    }    
  }

  return mindex;
}
