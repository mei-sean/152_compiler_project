#include<iostream>
#include<vector>
#include "symboltable.h"
using namespace std;

entry::entry(string name, int value) {
	this->name = name;
	this->value = value;
}
string entry::getEntryName() {    //gets entry name
    return this->name;
}
void Symboltable::addSymbol(entry newEntry) {    //appends new entry to vector 
	symtab.push_back(newEntry);
}
entry Symboltable::symbolTableLookup(string name) {     //find if variable exists in symbol table
    int max = symtab.size();   //right bound of vector search
    for (int i = 0; i < max; i++) {    //search iteratively
        if (name == symtab[i].getEntryName()) {
            return symtab[i];
            break;
        }
    }
    return entry(" ", 0);     //return signal that no entry exists
}
