# makefile

MPW ?= mpw

# MPW 3.2
LIBS = \
	{Libraries}Stubs.o \
	{CLibraries}StdCLib.o \
	{Libraries}Interface.o \
	{Libraries}Runtime.o \
	{Libraries}ToolLibs.o

LDFLAGS = -w -c 'MPS ' -t MPST \
	-sn STDIO=Main -sn INTENV=Main -sn %A5Init=Main

# MPW 3.5

# LIBS = \
# 	{CLibraries}StdCLib.o \
# 	{Libraries}Stubs.o \
# 	{Libraries}IntEnv.o \
# 	{Libraries}MacRuntime.o \
# 	{Libraries}Interface.o \
# 	{Libraries}ToolLibs.o

# LDFLAGS = -d -c 'MPS ' -t MPST

all: Help GetEnv Duplicate SetFile OverlayIIgs ListRez ListRezIIgs MakeEnums ReadGlobal

clean:
	rm -f *.c.o
	rm -f Help GetEnv Duplicate SetFile OverlayIIgs MakeEnums

GetEnv: GetEnv.c.o
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 

Help: Help.c.o
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 


Duplicate: Duplicate.c.o
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 


SetFile: SetFile.c.o SetFile-flags.c.o
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 


OverlayIIgs: OverlayIIgs.c.o OverlayIIgs-flags.c.o
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 

ListRez: ListRez.c.o
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 

ListRezIIgs: ListRezIIgs.c.o
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 

MakeEnums: MakeEnums.c.o
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 

ReadGlobal: ReadGlobal.c.o
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 

#SetFile.c : SetFile.rl
#	ragel -G2 -p -m -o $@ $<

#ReadGlobal.c : ReadGlobal.rc
#	re2c -o $@ $<


%.c.o : %.c
	$(MPW) SC -p $< -o $@
