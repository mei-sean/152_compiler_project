#include <iostream>
using namespace std; 

class Scanner {
public:
    string nexttoken(); 
    bool isIdentifier(char*);
    bool isSpecialSymbol(char);
    bool isNumber(char*);
    bool isReservedWord(char*);
    bool isMiscellaneousToken(char*); 
private: 

};

#ifndef SCANNER_H
#define SCANNER_H

#include <vector>
#include <string>
using namespace std;

class Scanner {
public:
    char nexttoken(istream& in);
    bool isAlpha(char ch);
    bool isDigit(char ch);
    bool isSpecialSymbol(char);
    bool isNumber(char*);
    bool isReservedWord(char*);
    bool isMiscellaneousToken(char*);
    string searchTable(string word);

private:
    vector<string> table = { "AND", "ARRAY", "ASM", "BEGIN", "BREAK", "CASE",
     "CONST", "CONSTRUCTOR", "CONTINUE", "DESTRUCTOR", "DIV", "DO", "DOWNTO",
    "ELSE", "END", "FALSE", "FILE", "FOR", "FUNCTION", "GOTO", "IF", "IMPLEMENTATION",
    "IN", "INLINE", "INTERFACE", "LABEL", "MOD", "NIL", "NOT", "OBJECT", "OF", "ON", "OPERATOR",
    "OR", "PACKED", "PROCEDURE", "PROGRAM", "RECORD", "REPEAT", "SET", "SHL", "SHR",
    "STRING", "THEN", "TO", "TRUE", "TYPE", "UNIT", "UNTIL", "USES", "VAR", "WHILE", "WITH",
    "XOR", "INTEGER", "REAL", "IDENTIFIER", "PLUSOP", "MINUSOP", "MULTOP", "DIVOP", "ASSIGN",
    "EQUAL", "NE", "LTEQ", "GTEQ", "LT", "GT", "PLUSEQUAL", "MINUSEQUAL", "MULTEQUAL",
    "DIVEQUAL", "CARAT" }; //Table has IDENTIFIER spelled as INDENTIFIER?? mistake i dunno lmao
};
#endif

