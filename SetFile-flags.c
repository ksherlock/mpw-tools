
#ifdef __ORCAC__
#pragma optimize 79
#pragma noroot
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SetFile-flags.h"

void FlagsHelp(void)
{
  fputs("SetFile [options] file...\n", stdout);
  fputs("-c creator   set the creator\n", stdout);
  fputs("-t type      set the file type\n", stdout);
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
        break;
      case 'c':
        // -xarg or -x arg
        ++j;  
        if (cp[j])
        {
          optarg = cp + j;
        }
        else
        {
          if (++i >= argc)
          {
            fputs("option requires an argument -- c\n", stderr); 
            exit(1);
          }
          optarg = argv[i];
        }
        flags._c = optarg;

        break;
      case 't':
        // -xarg or -x arg
        ++j;  
        if (cp[j])
        {
          optarg = cp + j;
        }
        else
        {
          if (++i >= argc)
          {
            fputs("option requires an argument -- t\n", stderr); 
            exit(1);
          }
          optarg = argv[i];
        }
        flags._t = optarg;

        break;
      case 'm':
        // -xarg or -x arg
        ++j;  
        if (cp[j])
        {
          optarg = cp + j;
        }
        else
        {
          if (++i >= argc)
          {
            fputs("option requires an argument -- m\n", stderr); 
            exit(1);
          }
          optarg = argv[i];
        }
        flags._m = optarg;

        break;

      default:
        fprintf(stderr, "illegal option -- %c\n", c);
        exit(1); 
      }
            
      if (optarg) break;
    }    
  }

  return mindex;
}
