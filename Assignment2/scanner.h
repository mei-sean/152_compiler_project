#ifndef SCANNER_H
#define SCANNER_H

#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Scanner {
public:
    char nexttoken(ifstream& in);
    bool isAlpha(char ch);
    bool isDigit(char ch);
    bool isSpecialSymbol(char ch);
    bool isDoubleSymbol(char ch);
    string convertToken(string token);
    string searchTable(string word);

private:
    vector<string> table = { "AND", "ARRAY", "ASM", "BEGIN", "BREAK", "CASE",
     "CONST", "CONSTRUCTOR", "CONTINUE", "DESTRUCTOR", "DIV", "DO", "DOWNTO",
    "ELSE", "END", "FALSE", "FILE", "FOR", "FUNCTION", "GOTO", "IF", "IMPLEMENTATION",
    "IN", "INLINE", "INTERFACE", "LABEL", "MOD", "NIL", "NOT", "OBJECT", "OF", "ON", "OPERATOR",
    "OR", "PACKED", "PROCEDURE", "PROGRAM", "RECORD", "REPEAT", "SET", "SHL", "SHR",
    "STRING", "THEN", "TO", "TRUE", "TYPE", "UNIT", "UNTIL", "USES", "VAR", "WHILE", "WITH",
    "XOR", "INTEGER", "REAL", "IDENTIFIER", "+", "-", "*", "/", ":=",
    "=", "<>", "<=", ">=", "<", ">", "+=", "-=", "*=",
    "/=", "^", ";", ",", "(", ")", "[", "]", "{", "}", "(*", "*)"}; //Table has IDENTIFIER spelled as INDENTIFIER?? mistake i dunno lmao
};
#endif
