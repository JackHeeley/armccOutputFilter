PROBLEM
=======
You have a preferred integrated development environment for software development, that supports makefile projects.
You have reason to favour makefiles. For example you need to exercise full control explicitly over the build process etc.
Your build process (Eg make or nmake) uses compilers etc. that generate error output streams that your IDE cannot interpret. 
This impacts your core-process productivity, as you are constantly being slowed down by having to manually open source files
and scroll to the line number of warnings and errors, when dealing with every correction.

ROOT CAUSE
==========
Nearly all IDE's have a one click 'jump-to-line' feature when you click on an error in the build output window. 
This feature can break if assumptions about error message format are invalidated by your build tooling choices.

SOLUTION
========
Assuming the compiler emits source and line number with errors and warnings then it is easy to fix.
It is just a matter of filtering the (compiler, assembler etc.) output stream so that the IDE recognizes the format once more. 
The IDE can then find/open a source file edit window move the cursor to the error/warning you clicked - just as it should do.
This simple approach works for most IDE's. By adding a filter, you can restore the expected level of service this IDE feature.

DESCRIPTION OF DELIVERABLE
==========================
This is an EXAMPLE NOT A GENERAL SOLUTION. The solution has two stages:

     i) "configuring" a filter to do what you need 
    ii) "inserting" the filter into the build chain

Configuring is achieved with a custom program. 
Check and if necessary change armccOutputFilter.cpp supplied in this VS2019 solution. 
Then use VS2019 to build (a custom) armccOutputFilter.exe.

Inserting the filter is achieved with a command in the makefile, but you won't find the syntax in the nmake reference. 
It works by redirecting the compiler's stdout and stderr through a pipe to the filter's stdin. 

Here's an example make/nmake line typical of what you might need:

	armcc {copts} sourcefilename 2>&1 | armccOutputFilter

The stdout of the filter is then used by the IDE instead of the raw data (in this case compiler output).
This little "repair" makes IDE development a lot more comfortable and efficient. 

CAPABILITIES
============
The armccOutputFilter was originally built to support VS2005 nmake projects using Norcroft's armcc C compiler, and assembler.
It works as-is with Visual Studio and Eclipse, and some other build tools where by chance, the filtering needs happen to match.
It can be used in cygwin (make) or microsoft (nmake) makefiles. 
Note: armccOutputFilter.exe must be placed in the program path, or just drop it into the same directory as your compiler.

LIMITATIONS
===========

Copyright (c) 2006-2020 Jack Heeley, all rights reserved. https://github.com/JackHeeley/armccOutputFilter

    This program is free software : you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see < http://www.gnu.org/licenses/ >.
 
This material assumes that you can use VS2019 to build a native command line program to target your development platform.
As delivered, the project is Visual Studio 2019 static-linked to use windows c++ runtime support.
The code should easily port anywhere.

The construct " 2>&1 | filter " appended to the compiler invokation line will integrate 'filter.exe' in a makefile/batch build.
This construct is supported across many platforms and shells, including windows and cygwin. 
Some shells have an equivalent capability with another syntax. 

Every situation is different, and you may need to change the code to suit the compiler/build tool in use.
For this reason the code has been kept very short and simple so it is easy to 'tweak'.