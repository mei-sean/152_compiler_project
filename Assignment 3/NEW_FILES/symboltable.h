#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <string>
#include <vector>

using namespace std;

class Symboltable {    
private:
	vector<string>symtab;    //store variable entries in symbol table
public:
	void addSymbol(string newEntry);
	string symbolTableLookup(string name);
};

#endif SYMBOLTABLE_H
