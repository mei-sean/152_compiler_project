#include<iostream>
#include<vector>
#include "symboltable.h"
using namespace std;

void Symboltable::addSymbol(string newEntry) {    //appends new entry to vector 
	symtab.push_back(newEntry);
}
string Symboltable::symbolTableLookup(string name) {     //find if variable exists in symbol table
    int max = symtab.size();   //right bound of vector search
    for (int i = 0; i < max; i++) {    //search iteratively
        if (name == symtab[i]) {
            return symtab[i];
            break;
        }
    }
    return "";    //return signal that no entry exists
}
