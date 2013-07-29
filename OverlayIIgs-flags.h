
#ifndef __flags_h__
#define __flags_h__

typedef struct Flags {
    char *_a;

    unsigned _p:1;

} Flags;


extern struct Flags flags;

int FlagsParse(int argc, char **argv);

void FlagsHelp(void);

#endif

