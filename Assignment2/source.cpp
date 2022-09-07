#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <fstream>

#include "scanner.h"
using namespace std;
string str_upper(string word);
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
    while (!ifs.eof()) {    //continue input file stream if not at end of file
        word = "";    //string to store current word
        ch = scan.nexttoken(ifs);    //scan the first character in file 
        if (scan.isAlpha(ch)) {    //check if char is a letter
            //This block indicates word must be identifier or keyword
            word.push_back(ch);    //append letter to current word
            ch = scan.nexttoken(ifs);    //get next character
            while (ch != '\n' && ch != '\t' && ch != ' ') {
                word.push_back(ch);
                if (scan.isDigit(ch) || scan.isSpecialSymbol(ch)) {
                    error = true;
                }
                else {
                    word.push_back(ch);
                }
                ch = scan.nexttoken(ifs);
            }
            if (error) {
                cout << "TOKEN ERROR at line " << line << endl;
            }
            else {

            }
            if (ch == '\n') {
                line++;
            }
            //table lookup on word 
            //if returns print keyword
            //otherwise print that it is a identifier
        }
        else if (scan.isDigit(ch)) {    //check if first char is a digit
            //This block indicates word must be a integer or real
        }
        else if (scan.isSpecialSymbol(ch)) {
            //This block indicates word must be a operator 
        }
        //check table 
    }
    ifs.close();    //close input file
}
string str_upper(string word) {
    string new_word = word;
    for (int i = 0; i < new_word.size(); i++) {
        new_word.at(i) = toupper(new_word.at(i));
    }
}
