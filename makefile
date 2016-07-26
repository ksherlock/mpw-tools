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

TARGETS = Help GetEnv Delete Duplicate SetFile OverlayIIgs ListRez ListRezIIgs\
	LSeg MakeEnums ReadGlobal Parameters Echo md5

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

# GetEnv: GetEnv.c.o
# 	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 

# Help: Help.c.o
# 	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 


# Duplicate: Duplicate.c.o
# 	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 


Delete: Delete.c.o Delete-flags.c.o $(LIBRARIES)
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 


SetFile: SetFile.c.o SetFile-flags.c.o $(LIBRARIES)
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 


OverlayIIgs: OverlayIIgs.c.o OverlayIIgs-flags.c.o $(LIBRARIES)
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 

# ListRez: ListRez.c.o lib/libtomcrypt
# 	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 

# ListRezIIgs: ListRezIIgs.c.o
# 	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 

# LSeg: LSeg.c.o lib/libc
# 	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 


# MakeEnums: MakeEnums.c.o 
# 	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 

# ReadGlobal: ReadGlobal.c.o 
# 	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 

# Parameters: Parameters.c.o
# 	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 

# Echo: Echo.c.o
# 	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 


#md5 : md5.c.o lib/libtomcrypt
#	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 



LTC_H = libtomcrypt/src/hashes/
lib/libtomcrypt : $(LTC_H)/md2.c.o $(LTC_H)/md4.c.o $(LTC_H)/md5.c.o $(LTC_H)/sha1.c.o | lib
	$(MPW) Lib $(LIBFLAGS) -o $@ $^ 


$(LTC_H)%.c.o : $(LTC_H)%.c
	$(MPW) SC $(SCFLAGS)  $< -o $@

#SetFile.c : SetFile.rl
#	ragel -G2 -p -m -o $@ $<

#ReadGlobal.c : ReadGlobal.rc
#	re2c -o $@ $<


%.c.o : %.c
	$(MPW) SC $(SCFLAGS) $< -o $@

% : %.c.o $(LIBRARIES)
	$(MPW) Link $(LDFLAGS) -o $@ $^ $(LIBS) 
