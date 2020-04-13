// armccOutputFilter.cpp : Defines the entry point for the console application.
//
// History
// -------
//    Author     Version  Comments
//   Jack Heeley   2.0    Initial CPP release (v1.0 & v1.1 were C prototypes)
//   Jack Heeley   2.1    Removal of unneccessary sample code
//   Jack Heeley   3.0    Modernizing portability (ansi std cpp)
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
        cout << "Output Filter " << VERSION << " (for Norcroft armcc v4.76 and armasm 2.40)" << endl << endl;
        cout << "  Converts compiler output to \"Visual Studio 2005-2015\"/\"Eclipse CDT\" style." << endl;
        cout << "  Use in Visual Studio 2005 makefile Nmake compile commands or" << endl;
        cout << "  Cygwin make compile commands." << endl << endl;
        cout << "  Usage (nmake or cygwin make): armcc {copts} file.c 2>&1 | armccOutputFilter" << endl << endl;
        cout << "  This provides the expected behaviour for the IDE by supporting the" << endl;
        cout << "  usual compiler error/warning 'Go To Location' feature (as available" << endl;
        cout << "  in visual studio projects using the built-in compiler) but also for" << endl;
        cout << "  makefile projects that use the armcc 4.76 compiler instead." << endl << endl;
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
