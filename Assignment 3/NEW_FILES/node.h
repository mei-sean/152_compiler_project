#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>

using namespace std;


// Types of parse tree nodes. 
enum class NodeType {
	PROGRAM, COMPOUND, ASSIGN, LOOP, TEST, IF, WRITE, WRITELN, NEGATE,
    ADD, SUBTRACT, MULTIPLY, DIVIDE, MOD, EQ, NEQ, LT, LTEQ, GT, GTEQ,
    NOT, AND, OR, VARIABLE, INTEGER_CONSTANT, REAL_CONSTANT, STRING_CONSTANT,
    CHARACTER_CONSTANT
};

// String of the parse tree node types. 
static const string NodeTypes[] = {
	"PROGRAM", "COMPOUND", "ASSIGN", "LOOP", "TEST", "IF", "WRITE", "WRITELN", "NEGATE",
    "ADD", "SUBTRACT", "MULTIPLY", "DIVIDE", "MOD", "EQ", "NEQ", "LT", "LTEQ", "GT", "GTEQ",
    "NOT", "AND", "OR", "VARIABLE", "INTEGER_CONSTANT", "REAL_CONSTANT", "STRING_CONSTANT",
    "CHARACTER_CONSTANT"
};

class Node {
public:

	NodeType type;
	string nodeType; 
	int lineNumber;
	string text;
	long Lvalue;
	int Dvalue;
	string Svalue;
	vector<Node*>children;

	Node(string nt) :nodeType(nt), lineNumber(0) {};
	void adopt(Node* child) {
		children.push_back(child);
	}
};

#endif