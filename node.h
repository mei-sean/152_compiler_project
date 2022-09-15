#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

class Node{
    public:
    Node *firstchild;
    Node *nextsibling;
    Node *parent;
    Node *left;
    Node *right;
    string name;
    int value;
    int priority;
    Node* newNode (string name,int value);
    void adopt();
};

enum class NodeType {
    PROGRAM, COMPOUND, ASSIGN, LOOP, TEST, WRITE, WRITELN,
    ADD, SUBTRACT, MULTIPLY, DIVIDE, EQ, LT, VARIABLE, 
    INTEGER_CONSTANT, REAL_CONSTANT, STRING_CONSTANT
};
#endif