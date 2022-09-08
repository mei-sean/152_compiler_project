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


bool Scanner::isNumber(char* str) {
    int numOfDecimal = 0;

    if (strlen(str) == 0) {
        return false;
    }

    else {
        for (int i = 0; i < strlen(str); i++) {
            if (numOfDecimal > 1 && str[i] == '.') {
                return false;
            }
            else if (numOfDecimal <= 1) {
                numOfDecimal++;
            }
            if (str[i] != '0' && str[i] != '1' && str[i] != '2' &&
                str[i] != '3' && str[i] != '4' && str[i] != '5' &&
                str[i] != '6' && str[i] != '7' && str[i] != '8' &&
                str[i] != '9' || (str[i] == '-' && i > 0)) {
                return false;
            }
        }
        return true;
    }
}

bool Scanner::isReservedWord(char* str) {
    if (!strcmp(str, "PROGRAM") || !strcmp(str, "BEGIN") ||
        !strcmp(str, "END") || !strcmp(str, "REPEAT") ||
        !strcmp(str, "UNTIL") || !strcmp(str, "WRITE") ||
        !strcmp(str, "WRITELN") || !strcmp(str, "THEN") ||
        !strcmp(str, "IF") || !strcmp(str, "WHILE") ||
        !strcmp(str, "FOR"))
    {
        return true;
    }
    else {
        return false;
    }
}

bool Scanner::isMiscellaneousToken(char* str) {
    if (!strcmp(str, "END_OF_FILE") || !strcmp(str, "ERROR")) {
        return true;
    }
    else {
        return false;
    }
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
char Scanner::nexttoken(istream& in) {
    char next_ch;
    in >> next_ch;
    return next_ch;
}