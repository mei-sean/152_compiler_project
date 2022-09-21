#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "node.h"
#include <vector>
using namespace std;
class Parser {
private:
	Scanner scan;
	int lineNumber;
	int errorCount;
	vector<string>statementStarters = { "BEGIN", "IDENTIFIER", "REPEAT", "WHILE",
	"WRITE", "WRITELN" };
	vector<string>statementFollowers = { ";", "END", "UNTIL", "DO", "OF" };
	vector<string>operators = { "=", "!=", "<", "<=", ">", ">=" };
	vector<string>boolOperators = {"!", "&", "|"};
public:
	Node* parseProgram();

};
#endif 