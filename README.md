MPW Tools
=========

This is a collection of tools for use with the MPW emulator.

Some of them are replacements for built-in MPW commands.  Some of them are 
replacements (the original Duplicate, for example, has a graphical 
confirmation box). Some are just handy to use.

These are tested under the MPW emulator.  They may or may not actually work
with a real MPW installation due to implementation differences.

The tools are:

* Delete: replacement for the Delete command.

* Echo: replacement for the Echo command.

* Duplicate: replacement for the Duplicate command.

* GetEnv: new command to extract environment variables for use in makefiles.

* Help: replacement for the Help command.  This version looks for individual
file in the `$MPW:Help:` directory rather than searching through a single 
monolithic help file.

* ListRez: List the resources in a Macintosh resource file.

* ListRezIIgs: List the resources in a IIgs resource file.

* LSegIIgs: List segments in a IIgs OMF File (borrowed from gno/me). 

* MakeEnums: Print struct offsets for various records (for use with MPW development).

* md5: Print md5 checksum for a file (data and resource fork).

* OverlayIIgs: replacement for the OverlayIIgs command. 
(This has been tested under MPW.)

* Parameters: replacement for the Parameters command.

* ReadGlobal: Display a global value.

* SetFile: replacement for the SetFile command.  Currently only filetype and
creator type are supported.

