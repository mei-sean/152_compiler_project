#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <string>
#include <vector>

using namespace std;
class entry {
private:
	string name;    //store name of variable
	int value;      //store value of variable
public:
	entry(string name, int value);    //constructor for entry
	string getEntryName();
};
class Symboltable {    
private:
	vector<entry>symtab;    //store variable entries in symbol table
public:
	void addSymbol(entry newEntry);
	entry symbolTableLookup(string name);
};

#endif SYMBOLTABLE_H
