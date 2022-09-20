#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>

using namespace std;

class Node {
public:
	string nodeType;
	int lineNumber;
	string text;
	vector<Node*>children;

	Node(string nt) :nodeType(nt), lineNumber(0) {};
	void adopt(Node* child) {
		children.push_back(child);
	}
};
#endif