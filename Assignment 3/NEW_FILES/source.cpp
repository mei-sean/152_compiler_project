#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <fstream>

#include "scanner.h"
using namespace std;
int main()
{
    Scanner scan;    //scanner object
    ifstream ifs;
    string word;
    ofstream ofs;


    ifs.open("test-in.txt");    //input file stream
    if (ifs.fail()) {    //check if input file opened properly
        cout << "<ERROR> input file opening failure" << endl;
        exit(1);
    }
    ofs.open("test-out.txt");    //check if output file opened properly.
    if (ofs.fail()) {
        cout << "<ERROR> output file opening failure" << endl;
        exit(1);
    }
    while (!ifs.eof()) {    //continue input file stream if not at end of file
        scan.callScanner(ifs, ofs);
    }
    ifs.close();    //close input file
    ofs.close();
}

