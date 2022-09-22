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
	int errorCount = 0;
	token* currentToken;
	vector<string>statementStarters = { "BEGIN", "IDENTIFIER", "REPEAT", "WHILE",
	"WRITE", "WRITELN" };
	vector<string>statementFollowers = { "SEMICOLON", "END", "UNTIL", "END_OF_FILE", "DO", "OF"};
	vector<string>operators = { "EQUALS", "NOT_EQUALS", "LESS_THAN", "LESS_THAN_EQUALS", "GREATER_THAN", "GREATER_THAN_EQUALS" };
	vector<string>boolOperators = {"NOT", "AND", "OR"};
	vector<string>simpleExpressionOperators = { "PLUS", "MINUS" };
	vector<string>termOperators = { "STAR", "SLASH", "DIV", "MOD" };
public:
	Node* parseProgram(ifstream& ifs);
	Node* parseCompoundStatement(ifstream& ifs);
	void parseStatementList(Node* parentNode, string tokenType, ifstream &ifs);
	Node* parseStatement();
	Node* parseForStatement(ifstream& ifs);
	Node* parseWhileStatement(ifstream& ifs);
	Node* parseIfStatement(ifstream& ifs);
	void parseWriteArguments(Node* node, ifstream& ifs);
	Node* parseWritelnStatement(ifstream& ifs);
	void parseWriteArguments(Node* node);
	Node* parseSimpleExpression();
	Node* parseTerm();
	Node* parsefactor(ifstream &ifs);
	Node* parseVariable(ifstream &ifs);
	Node* parseIntegerConstant(ifstream &ifs);
	Node* parseCharacterConstant(ifstream& ifs);
	Node* parseStringConstant(ifstream& ifs);
	Node* parseRealConstant(ifstream &ifs);

	void semanticError(string message);
	void syntaxError(string message);
	string searchVector(vector<string>myVector, string target);

};
#endif 