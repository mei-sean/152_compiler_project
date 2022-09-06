#include <iostream>
#include <cstring>
#include "scanner.h"
using namespace std;

bool Scanner::isSpecialSymbol(char ch) {
    // Check if there is a special character in the input stream. 
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == '.' || ch == ';' ||
        ch == ':=' || ch == '(' || ch == ')' || ch == '=' ||
        ch == '<' || ch == '>' || ch == '{' || ch == '}' ||
        ch == '[' || ch == ']')
    {
        return true;
    }
    return false;
}

bool Scanner::isIdentifier(char* str) {
    // Not an identifier if the first character is an int or a special symbol.
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isSpecialSymbol(str[0]) == true)
    {
        return false;
    }
    // If string length is one, it's already an identifier. 
    if (strlen(str) == 1) return true;
    // Otherwise, check for special symbols. 
    else {
        for (int i = 1; i < strlen(str); i++) {
            if (isSpecialSymbol(str[i] == true)) return false;
        }
    }
    // Return true by default. 
    return true;
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

string Scanner::searchTable(string word) {    //implemented with Binary Search O(log n)
    int left = 0;    //left bound of vector search
    int right = table.size() - 1;   //right bound of vector search
    int mid = (right + left) / 2;    //index of middle bounded search

    while (mid > left) {
        int i = 0;
        while (word[i] == table[mid][i]) {
            i++;
        }
        if (word[i] > table[mid][i]) {
            left = mid + 1;
        }
        else if (word[i] < table[mid][i]) {
            right = mid - 1;
        }
        else {
            return table[mid];
        }
    }
}
char Scanner::nexttoken(string line, int i) {
    while (line[i] != ' ' || line[i] != '\n' || line[i] != '\t') {

    }
    char token;
    return token;
}