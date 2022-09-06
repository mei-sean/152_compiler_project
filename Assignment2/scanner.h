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

