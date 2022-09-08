#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

class Node{
    public:
    Node *firstchild;
    Node *nextsibling;
    Node *parent;
    string name;
    int value;
    int priority;
    Node* newNode (string name,int value);
};
#endif