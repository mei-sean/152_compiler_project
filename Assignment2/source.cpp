#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "scanner.h"
using namespace std;
int main()
{
    Scanner scan;
    ifstream ifs;
    string word;
    int line = 0;
    char ch;
    bool error = false;

    ifs.open("masterTestCase.txt");    //input file stream
    if (ifs.fail()) {
        cout << "<ERROR> input file opening failure" << endl;
        exit(1);
    }
    while (!ifs.eof()) {
        word = "";
        ch = scan.nexttoken(ifs);
        if (scan.isAlpha(ch)) {
            word.push_back(ch);
            ch = scan.nexttoken(ifs);
            while (ch != '\n' || ch != '\t' || ch != ' ') {
                word.push_back(ch);
                ch = scan.nexttoken(ifs);
                if (scan.isDigit(ch) || scan.isSpecialSymbol(ch)) {
                    error = true;
                }
                else {
                    word.push_back(ch);
                }
            }
            if (error) {
                //print error and line number
            }
            if (ch == '\n') {
                line++;
            }
            //table lookup on word 
            //if returns print keyword
            //otherwise print that it is a identifier
        }
        //check table 
    }
    ifs.close();    //close input file
}
