#ifndef PARSER_H
#define PARSER_H
#include "node.h"
#include "scanner.h"
#include <vector>
using namespace std;
class Parser {
private:
	Scanner *scanner;
	int lineNumber;
	int errorCount;
	vector<string>statementStarters = { "BEGIN", "IDENTIFIER", "REPEAT", "WHILE",
	"WRITE", "WRITELN" };
	vector<string>statementFollowers = { ";", "END", "UNTIL", "DO", "OF" };
	vector<string>operators = { "=", "!=", "<", "<=", ">", ">=" };
	vector<string>boolOperators = {"!", "&", "|"};
	
	Node *Parser::parseWhileStatement();
	Node *Parser::parseIfStatement();
	Node *Parser::parseWriteArguments();
	Node *Parser::parseWritelnStatement();
	void parseWriteArguments(Node *node);
	Node *parseSimpleExpression();
	Node *parseTerm();
	Node *parsefactor();
	Node *parseVariable();
	Node *parseIntegerConstant();
	Node *parseRealConstant();

	void syntaxError(string data);
	void semanticError(string data);
public:
	Node* parseProgram();
	int getErrorCount() const{
		return errorCount;
	}

};
#endif 