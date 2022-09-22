#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <fstream>

#include "scanner.h"
#include "parser.h"
#include "parseTreePrinter.h"

using namespace std;
int main(int argc, char*argv[])
{
    if (argc != 3) {
        cout << "Format: -scan parse fileName" << endl;
        exit(-1);
    }
    Scanner scan;    //scanner object
    Parser parse;
    ParseTreePrinter printer;
    ifstream ifs;
    string word;
    ofstream ofs;
    string fileName = argv[2];
    string option = argv[1];
    token newToken;

    while (!ifs.eof()) {    //continue input file stream if not at end of file
        newToken = scan.nextToken(ifs);
        if (newToken.tokenValue == " " && newToken.tokenType != " ") {
            cout << newToken.tokenType << " : " << newToken.tokenName << endl;
        }
        else if (newToken.tokenValue != " ") {
            cout << newToken.tokenType << " : " << newToken.tokenValue << endl;
        }
        else {
            //do nothing
        }
    }

    ifs.open(fileName);    //input file stream
    if (ifs.fail()) {    //check if input file opened properly
        cout << "<ERROR> input file opening failure" << endl;
        exit(1);
    }
    ofs.open("test-out.txt");    //check if output file opened properly.
    if (ofs.fail()) {
        cout << "<ERROR> output file opening failure" << endl;
        exit(1);
    }
    if (option == "-scan") {
        while (!ifs.eof()) {    //continue input file stream if not at end of file
            newToken = scan.nextToken(ifs);
            if (newToken.tokenValue == " " && newToken.tokenType != " ") {
                cout << newToken.tokenType << " : " << newToken.tokenName << endl;
            }
            else if (newToken.tokenValue != " ") {
                cout << newToken.tokenType << " : " << newToken.tokenValue << endl;
            }
            else {
                //do nothing
            }
        }
    }
    else if (option == "-parse") {
        printer.print(parse.parseProgram(ifs), ofs);
    }
    else {
        cout << "Not a valid option choose -scan or -parse" << endl;
        exit(1);
    }
   
    ifs.close();    //close input file
    ofs.close();

}

