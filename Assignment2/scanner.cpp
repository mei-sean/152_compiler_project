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
        ch == '[' || ch == ']' || ch == '^')
    {
        return true;
    }
    return false;
}
bool Scanner::isAlpha(char ch) {
    //check if character is a letter
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
string Scanner::convertToken(string token) {    //convert string into its keyword
    string returnToken;
    if (token == "+") {
        returnToken = "PLUSOP";
    }
    else if (token == "-") {
        returnToken = "MINUSOP";
    }
    else if (token == "*") {
        returnToken = "MULTOP";
    }
    else if (token == "/") {
        returnToken = "DIVOP";
    }
    else if (token == ":=") {
        returnToken = "ASSIGN";
    }
    else if (token == "=") {
        returnToken = "EQUAL";
    }
    else if (token == "<>") {
        returnToken = "NE";
    }
    else if (token == "<=") {
        returnToken = "LTEQ";
    }
    else if (token == ">=") {
        returnToken = "GTEQ";
    }
    else if (token == "<") {
        returnToken = "LT";
    }
    else if (token == ">") {
        returnToken = "GT";
    }
    else if (token == "+=") {
        returnToken = "PLUSEQUAL";
    }
    else if (token == "-=") {
        returnToken = "MINUSEQUAL";
    }
    else if (token == "*=") {
        returnToken = "MULTEQUAL";
    }
    else if (token == "/=") {
        returnToken = "DIVEQUAL";
    }
    else if (token == "^") {
        returnToken = "CARAT";
    }
    else if (token == ";") {
        returnToken = "SEMICOLOR";
    }
    else if (token == ",") {
        returnToken = "COMMA";
    }
    else if (token == "(") {
        returnToken = "LPAREN";
    }
    else if (token == ")") {
        returnToken = "RPAREN";
    }
    else if (token == "[") {
        returnToken = "LBRACKET";
    }
    else if (token == "]") {
        returnToken = "RBRACKET";
    }
    else if (token == "{") {
        returnToken = "LBRACE";
    }
    else if (token == "}") {
        returnToken = "RBRACE";
    }
    else if (token == "(*") {
        returnToken = "LCOMMENT";
    }
    else if (token == "*)") {
        returnToken = "RCOMMENT";
    }
    return returnToken;
}

char Scanner::nexttoken(ifstream& in) {    //get next character in input stream from file
    char next_ch;
    in.get(next_ch);
    return next_ch;
}