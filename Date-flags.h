
#ifndef __flags_h__
#define __flags_h__

typedef struct Flags {
    char *_c;
    char *_x;

    unsigned _a:1;
    unsigned _d:1;
    unsigned _n:1;
    unsigned _s:1;
    unsigned _s4:1;
    unsigned _st:1;
    unsigned _t:1;
    unsigned _u:1;
    unsigned _utc:1;

} Flags;


extern struct Flags flags;

int FlagsParse(int argc, char **argv);

void FlagsHelp(void);

#endif

