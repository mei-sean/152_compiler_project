#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "node.h"
#include "symboltable.h"
#include <vector>
using namespace std;
class Parser {
private:
	Symboltable symtab;
	Scanner scan;
	int lineNumber;
	int errorCount;
	token* currentToken;
	vector<string>statementStarters = { "BEGIN", "IDENTIFIER", "REPEAT", "WHILE",
	"WRITE", "WRITELN" };
	vector<string>statementFollowers = { ";", "END", "UNTIL", "DO", "OF" };
	vector<string>operators = { "=", "!=", "<", "<=", ">", ">=" };
	vector<string>boolOperators = {"!", "&", "|"};
public:
	Node* parseProgram(ifstream& ifs);
	Node* parseCompoundStatement(ifstream& ifs);
	void parseStatementList(Node* parentNode, string tokenType);
	void syntaxError(string message);

};
#endif 