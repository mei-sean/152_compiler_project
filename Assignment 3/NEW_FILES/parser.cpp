#include <iostream>
#include "parser.h"
#include "node.h"

using namespace std;

Scanner scan;    //instantiate scanner class

Node* Parser::parseProgram() {
	Node* program = new Node("PROGRAM");
	return program;
}