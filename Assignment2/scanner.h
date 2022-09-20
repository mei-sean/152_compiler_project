#ifndef SCANNER_H
#define SCANNER_H

#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Scanner {
public:
    char nexttoken(ifstream& in);        //Retreive next character from input file stream
    bool isAlpha(char ch);               //Check if current character is a letter
    bool isDigit(char ch);               //Check if current character is a digit
    bool isSpecialSymbol(char ch);       //Check if current character is a symbol
    bool isDoubleSymbol(char ch);        //Check if current character has two symbols
    string convertToken(string token);   //Convert a symbol to its abreviated name EX. + -> PLUSOP
    string searchTable(string word);     //Search table contained all reserved words and symbols
    string str_upper(string word);
    void callScanner(ifstream &ifs, ofstream &ofs);

private:
    vector<string> table = { "AND", "ARRAY", "ASM", "BEGIN", "BREAK", "CASE",
     "CONST", "CONSTRUCTOR", "CONTINUE", "DESTRUCTOR", "DIV", "DO", "DOWNTO",
    "ELSE", "END", "FALSE", "FILE", "FOR", "FUNCTION", "GOTO", "IF", "IMPLEMENTATION",
    "IN", "INLINE", "INTERFACE", "LABEL", "MOD", "NIL", "NOT", "OBJECT", "OF", "ON", "OPERATOR",
    "OR", "PACKED", "PROCEDURE", "PROGRAM", "RECORD", "REPEAT", "SET", "SHL", "SHR",
    "STRING", "THEN", "TO", "TRUE", "TYPE", "UNIT", "UNTIL", "USES", "VAR", "WHILE", "WITH",
    "XOR", "INTEGER", "REAL", "IDENTIFIER", "+", "-", "*", "/", ":=",
    "=", "<>", "<=", ">=", "<", ">", "+=", "-=", "*=",
    "/=", "^", ";", ",", "(", ")", "[", "]", "{", "}", "(*", "*)", "."};
};
#endif
