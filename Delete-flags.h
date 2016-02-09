
#ifndef __flags_h__
#define __flags_h__

typedef struct Flags {

    unsigned _y:1;
    unsigned _n:1;
    unsigned _c:1;
    unsigned _i:1;
    unsigned _p:1;

} Flags;


extern struct Flags flags;

int FlagsParse(int argc, char **argv);

void FlagsHelp(void);

#endif

