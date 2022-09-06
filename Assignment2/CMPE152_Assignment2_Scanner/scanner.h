#ifndef SCANNER_H
#define SCANNER_H

using namespace std;

class scanner {
public:
    string nexttoken();
    bool isIdentifier(char*);
    bool isSpecialSymbol(char);
private:

};
#endif
