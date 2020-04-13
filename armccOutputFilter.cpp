// armccOutputFilter.cpp : Defines the entry point for the console application.
//          compiles with Visual Studio 2019 v16.5.3 /std:c++latest, the current probably final, working draft C++20
//          builds and runs on x86 & x64 architectures
//
// FULL DOCUMENTATION AT https://github.com/JackHeeley/Challenges/wiki
//
// Copyright (c) 2006-2020 Jack Heeley, all rights reserved. https://github.com/JackHeeley/armccOutputFilter
//
//    This program is free software : you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.If not, see < http://www.gnu.org/licenses/ >.
// 

#include <iostream>
#include <sstream>

using namespace std;

const string VERSION = "3.0";

//
// main   - filter Norcroft ARMCC 4.76 compiler & ARMASM 2.40 assembler output streams.
//          Changes errors and warnings to Visual Studio 2005-2015 / Eclipse CDT style. 
//          Absorbs all other output lines silently. Very probably suitable for 
//          all versions of the Norcroft build tools.
//
int main( int argc, char* argv[] )
{
    const string KEY = ", line ";
    const string NUMERICS = "0123456789";

    if (argc > 1)
    {
        cout << "This program comes with ABSOLUTELY NO WARRANTY; for details refer to GPL 3.0.\n";
        cout << "This is free software, and you are welcome to redistribute it\n";
        cout << "under certain conditions; refer to GPL 3.0 for details.\n\n";

        cout << "You should have received a copy of the GNU General Public License (GPL 3.0)\n";
        cout << "along with this program. If not, see < http://www.gnu.org/licenses/" << " >.\n\n";

        cout << "Output Filter " << VERSION << " (for Norcroft armcc v4.76 and armasm 2.40)\n\n";
        cout << "  Converts compiler output to \"Visual Studio 2005-2019\"/\"Eclipse CDT\" style.\n";
        cout << "  Use in Visual Studio 2005 makefile Nmake compile commands or\n";
        cout << "  Cygwin make compile commands.\n\n";

        cout << "  Usage (nmake or cygwin make): armcc {copts} file.c 2>&1 | armccOutputFilter\n\n";
        cout << "  This provides the expected behaviour for the IDE by supporting the\n";
        cout << "  usual compiler error/warning 'Go To Location' feature (as available\n";
        cout << "  in visual studio projects using the built-in compiler) but also for\n";
        cout << "  makefile projects that use the armcc 4.76 compiler instead.\n" <<  endl;
        return 1;
    }

    while (!cin.eof() && !cin.fail()) 
    {
        string line;
        getline(cin, line);
        try
        {
            if (line.find(KEY) != string::npos) 
            {
                size_t start = line.find_first_of("\"", 0);
                size_t end = line.find_first_of("\"", start+1);
                const string fileName = line.substr(start+1,end-1);

                start = line.find_first_of(NUMERICS, end+1);
                end = line.find_first_not_of(NUMERICS, start);
                const string lineNumber = line.substr(start, end-start);

                const string details = line.substr(end);

                cout << ".\\" << fileName << "(" << lineNumber << ") " << details << endl;
            }
        }
        catch (...)
        {
            // (unsupported/unexpected line format) Quietly echo original line (and carry on)
            cout << line << endl;
        }
    }
}
