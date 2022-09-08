#ifndef PARSER_H
#define PARSER_H
#include "node.h"
#include "tree.h"
#include <iostream>
using namespace std;

class Parser {
    public:
    
    Node parseProgram();
    tree outputTree(Node);
    //Symbol? outputSymbolTable();
    int priorityAssign(std::string operator_in);

};
#endif