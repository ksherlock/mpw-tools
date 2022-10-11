# makefile

.SUFFIXES:            # Delete the default suffixes

MPW ?= mpw

# MPW 3.2
# LIBS = \
# 	{Libraries}Stubs.o \
# 	{CLibraries}StdCLib.o \
# 	{Libraries}Interface.o \
# 	{Libraries}Runtime.o \
# 	{Libraries}ToolLibs.o

LDFLAGS = -w -c 'MPS ' -t MPST \
	-sn STDIO=Main -sn INTENV=Main -sn %A5Init=Main

LIBFLAGS = -P
SCFLAGS = -P -I include/ -I libtomcrypt/src/headers/

# MPW 3.5

LIBRARIES = lib/libc lib/libtomcrypt

LIBS = \
	{CLibraries}StdCLib.o \
	{Libraries}Stubs.o \
	{Libraries}IntEnv.o \
	{Libraries}MacRuntime.o \
	{Libraries}Interface.o \
	{Libraries}ToolLibs.o

# LDFLAGS = -d -c 'MPS ' -t MPST

TARGETS = Help GetEnv Delete Duplicate Files SetFile OverlayIIgs ListRez ListRezIIgs\
	LSegIIgs MakeEnums ReadGlobal Parameters Echo md5 Rename

all: $(TARGETS)

clean:
	rm -f *.o
	rm -f  $(TARGETS)
	rm -f lib/libc libc/*.o
	rm -f lib/*
	rm -f libtomcrypt/src/hashes/*.o


dist/Tools.tgz: $(TARGETS)
	cp $^ dist/Tools/
	rm -f $@
	cd dist; tar cfz Tools.tgz Tools/
	#zip -r  Tools.zip Tools

install: $(TARGETS)
	cp $^ ~/mpw/Tools/

lib:
	mkdir lib

lib/libc: libc/strcasecmp.c.o libc/_getprogname.c.o libc/err.c.o libc/getopt.c.o libc/basename.c.o | lib
	$(MPW) Lib $(LIBFLAGS) -o $@ $^ 



Delete: Delete.c.o Delete-flags.c.o FileCommon.c.o $(LIBRARIES)
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 


SetFile: SetFile.c.o SetFile-flags.c.o $(LIBRARIES)
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 


OverlayIIgs: OverlayIIgs.c.o OverlayIIgs-flags.c.o $(LIBRARIES)
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 


Rename: Rename.c.o Rename-flags.c.o FileCommon.c.o $(LIBRARIES)
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 


Date : Date.c.o Date-flags.c.o $(LIBRARIES)
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 



LTC_H = libtomcrypt/src/hashes/
lib/libtomcrypt : \
	$(LTC_H)/md2.c.o $(LTC_H)/md4.c.o $(LTC_H)/md5.c.o \
	$(LTC_H)/sha1.c.o $(LTC_H)/blake2s.c.o \
	$(LTC_H)/rmd128.c.o $(LTC_H)/rmd160.c.o $(LTC_H)/rmd256.c.o $(LTC_H)/rmd320.c.o  \
	$(LTC_H)/sha2/sha224.c.o $(LTC_H)/sha2/sha256.c.o $(LTC_H)/sha2/sha384.c.o \
	| lib
	$(MPW) Lib $(LIBFLAGS) -o $@ $^ 


# $(LTC_H)%.c.o : $(LTC_H)%.c
# 	$(MPW) --stack=0x10000 SC $(SCFLAGS)  $< -o $@


%.c.o : %.c
	$(MPW) --stack=0x10000 SC $(SCFLAGS) $< -o $@

% : %.c.o $(LIBRARIES)
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 
