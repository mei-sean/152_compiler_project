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

string Scanner::nexttoken() {

}