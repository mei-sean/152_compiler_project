#include <iostream>
#include "parser.h"
#include "node.h"
#include "symboltable.h"
#include "scanner.h"
#include <fstream>

using namespace std;

Scanner scan;    //instantiate scanner class

Node* Parser::parseProgram(ifstream& ifs) {
	Node *programNode = new Node("PROGRAM");    //head node of parse tree 
	*currentToken = scan.nextToken(ifs);        //pointer dereferenced to copy values of next token in file

	if (currentToken->tokenType == "PROGRAM") { //check if program keyword is found
		*currentToken = scan.nextToken(ifs);
	}
	else {
		syntaxError("Expecting PROGRAM");
	}
	if (currentToken->tokenType == "IDENTIFIER") {
		programNode->text = currentToken->tokenName;
		symtab.addSymbol(currentToken->tokenName);     //store name into symbol table
		*currentToken = scan.nextToken(ifs);
	}
	else {
		syntaxError("Expecting program name");
	}
	if (currentToken->tokenType == "SEMICOLON") {
		*currentToken = scan.nextToken(ifs);
	}
	else {
		syntaxError("Missing ;");
	}
	if (currentToken->tokenType != "BEGIN") {
		syntaxError("Expecting BEGIN");
	}
	programNode->adopt(parseCompoundStatement(ifs));
	if (currentToken->tokenType == "SEMICOLON") {
		syntaxError("Expecting .");
		return programNode;
	}
}
Node* Parser::parseCompoundStatement(ifstream& ifs) {
	Node* compoundNode = new Node("COMPOUND");
	compoundNode->lineNumber = scan.line;
	*currentToken = scan.nextToken(ifs);
	parseStatementList(compoundNode, "END");
	if (currentToken->tokenType == "END") {
		*currentToken = scan.nextToken(ifs);
	}
	else {
		cout << "Expecting END" << endl;
	}
	return compoundNode;
}
void Parser::parseStatementList(Node* parentNode, string tokenType){

}
void Parser::syntaxError(string message) {
	cout << "SYNTAX ERROR at line " << currentToken->tokenLine << message << " at " << currentToken->tokenName << endl;
	errorCount++;
}        
