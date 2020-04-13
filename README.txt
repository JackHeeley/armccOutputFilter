PROBLEM
=======
You want explicit control of build metadata and might be working on cross platform development.
You have a powerful integrated development environment, that supports makefile projects, and a preference to use it.
Your build processs (Eg make or nmake) generates an error output stream that your IDE cannot put into context.
During coding, you are delayed by constantly having to manually open the file and scroll to the line number of warnings and errors.


SOLUTION
========
Most IDE's support 'jump-to-line' when you click on an error in the build output window.
So filter the output stream (from compiler, assembler etc.) so that the IDE recognizes the format (can find the source file and line number).
This is simply a matter of massaging the output format to match that of the native tools of the IDE manufacturer. This works for most IDE's.
Now you can use your preferred IDE effectively during code development.


DESCRIPTION OF DELIVERABLE
==========================
This is an EXAMPLE NOT A GENERAL SOLUTION.

The armccOutputFilter is a command line program built to solve exactly this problem when using Norcroft's arm C compiler, and assembler. 
It works with Visual Studio and Eclipse, and has been co-opted and used in other contexts (without source change) simply because it happens to match.

It can be used in cygwin (make) or microsoft (nmake) makefiles. 

It works by redirecting compiler's stdout and stderr through a pipe to the filter's stdin. Here's an example make/nmake line that you need:

	armcc {copts} sourcefilename 2>&1 | armccOutputFilter

The stdout of the filter is then used by the IDE instead of the raw data (in this case compiler output).
This tool makes IDE development a lot more attractive.


LIMITATIONS
===========
You may use this material in part or in whole, and change it at will, entirely at your own risk. 
The author and other third parties accept no liability whatsoever for losses of any kind.

This assumes that you know how to build a single source ansi cpp file into a native command line program for the platform of you choice.
As delivered, the project is Visual Studio 2015 (32 & 64 bit selecting multibyte character set, static linked to runtime) 
The code should easily port anywhere.

 The construct " 2>&1 | filter " appended to the compiler invokation line is the key to integration of 'filter.exe' within a makefile (or batch).
 This construct is supported across many platforms and shells, including windows and cygwin. Some shells have an equivalent capability with another syntax. 

Every situation is different, and you may need to change the code to match your compiler (or other build tool), or you might need more than one filter.
To this end the code has been kept trivially simple and is very short (just 8 lines inside the loop that you might need to 'tweak').

Take care to test stuff that you get for free! If your compiler can emit an error/warning as its last line of output, 
and terminates with <eol> instead of <eof><eol> then this (simple) code might well lead you to miss it! etc.

