/*
EXCERCISE
IMPLEMENT A PROGRAM THAT: 
on -h/--help displays help and quits
on -v/--verbose prints all arguments passed
on -f=N calculates N*N and verifies if 2^N-1 is prime

*/

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    
    string arg = "";
    cout << "Print command: " << endl;
    cin >> arg;

        if (arg == "-h" || arg == "--help") 
        {
            cout << "HELP: Display information about builtin commands.\n";
        }
        else if (arg == "-v" || arg == "--verbose") 
        {
            cout << "VERBOSE\n";
        } 
        else if (arg == "-f")
        {
            cout << "F\n";
        }

    return 0;
}