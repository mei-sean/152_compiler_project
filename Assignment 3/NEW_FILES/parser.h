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
	vector<string>statementFollowers = { "SEMICOLON", "END", "UNTIL", "END_OF_FILE", "DO", "OF"};
	vector<string>operators = { "=", "!=", "<", "<=", ">", ">=" };
	vector<string>boolOperators = {"!", "&", "|"};
public:
	Node* parseProgram(ifstream& ifs);
	Node* parseCompoundStatement(ifstream& ifs);
	void parseStatementList(Node* parentNode, string tokenType, ifstream &ifs);
	Node* parseStatement();
	Node* parseForStatement(ifstream& ifs);
	Node* parseWhileStatement(ifstream& ifs);
	Node* parseIfStatement();
	Node* parseWriteArguments();
	Node* parseWritelnStatement();
	void parseWriteArguments(Node* node);
	Node* parseSimpleExpression();
	Node* parseTerm();
	Node* parsefactor();
	Node* parseVariable();
	Node* parseIntegerConstant();
	Node* parseRealConstant();

	void syntaxError(string data);
	void syntaxError(string message);
	string searchVector(vector<string>myVector, string target);

};
#endif 