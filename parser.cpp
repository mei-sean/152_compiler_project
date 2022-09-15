#include <iostream>
#include <cstring>
#include "../inc/parser.h"
#include "../inc/node.h"
#include "../inc/tree.h"
#include <fstream>
using namespace std;

Node parseProgram(){

}

int priorityAssign(std::string operator_in){
}

void Parser::parseCompoundStatements(Node *node) {
    if (node == NULL) {
        node = new Node;
        node->firstchild = NULL;
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        node->nextsibling = NULL;
    }
    // I created the node, but idk how to give it type COMPOUND. 
}

void Parser::parseAssignmentStatement(Node *node1, Node *node2) {
    
    node1 = new Node; // Assign node. 
    node2 = new Node; // variable node. 
    node1->firstchild = node2;
    
}

void Parser::parseExpression() {

}