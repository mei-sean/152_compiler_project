#include <iostream>
#include <cstring>
#include "scanner.h"
using namespace std;

bool Scanner::isSpecialSymbol(char ch) {
    // Check if there is a special character in the input stream. 
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == '.' || ch == ';' ||
        ch == ':=' || ch == '(' || ch == ')' || ch == '=' ||
        ch == '<' || ch == '>' || ch == '{' || ch == '}' ||
        ch == '[' || ch == ']')
    {
        return true;
    }
    return false;
}
bool Scanner::isAlpha(char ch) {
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
        return true;
    }
    return false;
}
bool Scanner::isDoubleSymbol(char ch) {
    if (ch == ':' || ch == '<' || ch == '>' ||
        ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '(') {
        return true;
    }
    return false;
}
bool Scanner::isDigit(char ch) {
    // Not an identifier if the first character is an int or a special symbol.
    if (ch == '0' || ch == '1' || ch == '2' ||
        ch == '3' || ch == '4' || ch == '5' ||
        ch == '6' || ch == '7' || ch == '8' ||
        ch == '9')
    {
        return true;
    }
    return false;
}
string Scanner::searchTable(string word) {    //implemented with linear Search O(n)
    int max = table.size();   //right bound of vector search
    for (int i = 0; i < max; i++) {
        if (word == table[i]) {
            return table[i];
        }
    }
    string emptyString = "";
    return emptyString;
}
char Scanner::nexttoken(ifstream& in) {
    char next_ch;
    in.get(next_ch);
    return next_ch;
}