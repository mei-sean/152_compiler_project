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
    Scanner scan;    //scanner object
    ifstream ifs;
    string word;
    ofstream ofs;

    int line = 1;    //line to track which line we are in the input file
    char ch;         //char to store next character in file

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
        word = "";    //string to store current word
        ch = scan.nexttoken(ifs);    //scan the first character in file 
        if (scan.isAlpha(ch)) {    //check if char is a letter
            //This block indicates word must be identifier or keyword
            word.push_back(ch);    //append letter to current word
            ch = scan.nexttoken(ifs);    //get next character
            while (ch != '\n' && ch != '\t' && ch != ' ') {
                if (!scan.isAlpha(ch)) {    //if not letter print error message
                    cout << "TOKEN ERROR at line " << line << ": Invalid  at " << ch << endl;
                    ofs << "TOKEN ERROR at line " << line << ": Invalid  at " << ch << endl;
                    break;
                }
                word.push_back(ch);    
                ch = scan.nexttoken(ifs);    
            }
            string token = (str_upper(word));    //convert token to all uppercase
            if (scan.searchTable(token) == token) {    //check if token matches any keyword in table
                cout << token << " : " << word << endl;
                ofs << token << " : " << word << endl;
            }
            else {
                cout << "IDENTIFIER : " << word << endl;
                ofs << "IDENTIFIER : " << word << endl;
            }
        }
        else if (scan.isDigit(ch)) {    //check if first char is a digit
            bool hasDecimal = false;
            bool invalid = false;
            word.push_back(ch);
            while (ch != '\n' && ch != '\t' && ch != ' ') {
                ch = scan.nexttoken(ifs);
                if (ch == '.' && !hasDecimal) {    //if first decimal found
                    hasDecimal = true;
                    word.push_back(ch);
                }
                else if (ch == '.' && hasDecimal) {    //if another decimal is found
                    invalid = true;                    //number is invalid 
                }
                else {
                    word.push_back(ch);
                }
            }
            if (!invalid) {
                cout << "INTEGER : " << word << endl;
                ofs << "INTEGER : " << word << endl;
            }
            else {
                cout << "TOKEN ERROR at line " << line <<": Invalid number at "<<word;
                ofs << "TOKEN ERROR at line " << line << ": Invalid number at " << word;
            }
        }
        else if (scan.isSpecialSymbol(ch)) {    //check if first char is an operator
            //This block indicates word must be a operator 
            word.push_back(ch);    //append letter to current word 
            while (ch != '\n' && ch != '\t' && ch != ' ') {    //while not end of word
                if (scan.isDoubleSymbol(ch)) {    //check if operator can have two characters
                    ch = scan.nexttoken(ifs);
                    string tempWord = word;    //create two character operator
                    tempWord.push_back(ch);
                    string token = scan.searchTable(tempWord);    //check if operator is in table
                    if (token != "") {    //if operator is in table
                        cout << scan.convertToken(token) << " : " << tempWord << endl;    //print the 2 character operator 
                        ofs << scan.convertToken(token) << " : " << tempWord << endl;
                        word = "";
                    }
                    else {
                        cout << scan.convertToken(word) << " : " << word << endl;
                        ofs << scan.convertToken(word) << " : " << word << endl;
                        word = "";
                    }
                }
                else {
                    string token = scan.searchTable(word);
                    cout << scan.convertToken(token) << " : " << word << endl;
                    ofs << scan.convertToken(token) << " : " << word << endl;
                    word = "";
                }
                ch = scan.nexttoken(ifs);
                if (ch != ' ' && ch != '\n' && ch != '\t') {
                    word.push_back(ch);
                }
            }
        }
        else if (ch == '\'') {    //must be a string or character
            word.push_back(ch);
            bool endOfStr = false;
            while (ch != '\n' && ch != '\t') {
                ch = scan.nexttoken(ifs);
                if (ch == '\'') {
                    endOfStr = true;
                }
                word.push_back(ch);
                if (endOfStr) {
                    if (word.length() == 3) {
                        cout << "CHARACTER : " << word << endl;
                        ofs << "CHARACTER : " << word << endl;
                    }
                    else {
                        cout << "STRING : " << word << endl;
                        ofs << "STRING : " << word << endl;
                    }
                    break;
                }
            }
            if (!endOfStr) {
                cout << "TOKEN ERROR at line " << line << endl;
                ofs << "TOKEN ERROR at line " << line << endl;
            }
        }
        word = "";
        if (ch == '\n') {
            line++;
        }
    }
    ifs.close();    //close input file
    ofs.close();
}
string str_upper(string word) {    //converts a string to all uppercase 
    string new_word = word;
    for (int i = 0; i < new_word.size(); i++) {
        new_word.at(i) = toupper(new_word.at(i));
    }
    return new_word;
}

