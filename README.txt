PROBLEM
=======
You have a preferred integrated development environment for software development, that supports makefile projects.
You have reason to favour makefiles. For example you need to exercise full control explicitly over the build process, you are doing cross platform development etc.
Your build process (Eg make or nmake) uses compilers etc. that generate error output streams that your IDE cannot interpret. This impacts your core-process productivity.
You are constantly being slowed down by having to manually open the source file and scroll to the line number of warnings and errors to deal with every correction.

ROOT CAUSE
==========
Nearly all IDE's have a one click 'jump-to-line' feature when you click on an error in the build output window. 
This feature can break if assumptions about error message format are invalidated by your build tooling choices.

SOLUTION
========
Assuming the compiler emits source and line number with errors and warnings then it is easy to fix.
It is just a matter of filtering the output stream (from compiler, assembler etc.) so that the IDE recognizes the format once more. 
The IDE can then find and open a source file edit window, jump to the line number, when you click on an error shown in the output window. Just as you want it to.
This simple approach works for most IDE's. By adding a filter, you will be able use your preferred IDE _effectively again_ during development.

DESCRIPTION OF DELIVERABLE
==========================
This is an EXAMPLE NOT A GENERAL SOLUTION. The solution has two stages:

     i) "configuring" a filter to do what you need 
    ii) "inserting" the filter into the build chain

Configuring is achieved with a custom program. 
Check and if necessary change armccOutputFilter.cpp supplied in this solution, and use visual studio to build a custom armccOutputFilter.exe.

Inserting is achieved with a command in the makefile, but you won't find the syntax in the nmake reference. It works by redirecting the compiler's stdout and stderr 
through a pipe to the filter's stdin. Here's an example make/nmake line typical of what you might need:

	armcc {copts} sourcefilename 2>&1 | armccOutputFilter

The stdout of the filter is then used by the IDE instead of the raw data (in this case compiler output).
This little "repair" makes IDE development a lot more comfortable and efficient. 

CAPABILITIES
============
The armccOutputFilter is a command line program built to solve exactly this problem specifically when using Norcroft's arm C compiler, and assembler. 
It works with Visual Studio and Eclipse, and has been co-opted and used in other contexts (without source change) simply because it happens to match.

It can be used in cygwin (make) or microsoft (nmake) makefiles. 

For this to work armccOutputFilter.exe must be placed in the program path. (I'd suggest that you just drop it into the same directory as your compiler).

LIMITATIONS
===========
You may use this material in part or in whole, and change it at will, entirely at your own risk. 
The author and other third parties accept no liability whatsoever for losses of any kind.

This assumes that you know how to build a single source cpp file into a native command line program for the build platform of you choice.
As delivered, the project is Visual Studio 2019 (32 & 64 bit selecting multibyte character set, static linked to runtime) 
The code should easily port anywhere.

 The construct " 2>&1 | filter " appended to the compiler invokation line is the key to integration of 'your_filter.exe' within a makefile (or batch).
 This construct is supported across many platforms and shells, including windows and cygwin. Some shells have an equivalent capability with another syntax. 

Every situation is different, and you may need to change the code to match your compiler (or other build tool), or you might need more than one filter.
To this end the code has been kept trivially simple and is very short (just 8 lines inside the loop that you might need to 'tweak').

Take care to test stuff that you get for free! If your compiler can emit an error/warning as its last line of output, 
and if it terminates with <eof> (instead of <eol><eof>) then a filter based on this (simple) example might "eat" the last error! etc.
