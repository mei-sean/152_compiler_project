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
    int line = 1;
    char ch;
    bool error;

    ifs.open("masterTestCase.txt");    //input file stream
    if (ifs.fail()) {
        cout << "<ERROR> input file opening failure" << endl;
        exit(1);
    }
    while (!ifs.eof()) {    //continue input file stream if not at end of file
        word = "";    //string to store current word
        error = false;     //beginning of scan no error
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
                string token = (str_upper(word));
                if (scan.searchTable(token) == token) {
                    cout << token << " : " << word << endl;
                }
                else {
                    cout << "Identifier : " << word << endl;
                }
            }
            if (ch == '\n') {
                line++;
            }
        }
        else if (scan.isDigit(ch)) {    //check if first char is a digit
            //This block indicates word must be a integer or real

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
                        cout << token << " : " << tempWord << endl;    //print the 2 character operator 
                    }
                }
                else {
                    string token = scan.searchTable(word);
                    cout << token << " : " << word << endl;
                }
                ch = scan.nexttoken(ifs);
                if (ch == '\n') {
                    line++;
                }
            }
        }
        else if(ch == 

    }
    ifs.close();    //close input file
}
string str_upper(string word) {
    string new_word = word;
    for (int i = 0; i < new_word.size(); i++) {
        new_word.at(i) = toupper(new_word.at(i));
    }
    return new_word;
}
