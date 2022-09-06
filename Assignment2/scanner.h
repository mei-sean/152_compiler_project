#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
using namespace std;

class Scanner {
public:
    string nexttoken();
    bool isIdentifier(char*);
    bool isSpecialSymbol(char);

private:

};
#endif

