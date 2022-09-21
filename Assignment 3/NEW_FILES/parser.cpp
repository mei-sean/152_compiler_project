#include <iostream>
#include "parser.h"
#include "node.h"
#include <fstream>

using namespace std;

Scanner scan;    //instantiate scanner class
token current;

Node parseProgram(){
	Node* program = new Node("PROGRAM");
	currentToken  = 
}


Node *Parser::parseVariable(){
	token current;//need actual currentToken
	string variableName = current.tokenName; //store name of token into variable
	//check variable name for valid symtab token and call syntax or semantic error if one exists
	Node *newnode = new Node("VARIABLE"); //set type within new node
	newnode->text = variableName; 

	current = scanner->nexttoken(); //change this to something that actually works


}

void Parser::semanticError(string data){
	//token current = scan.buildToken();//replace
	errorCount++;
	int errorNum = getErrorCount();
	printf("ERROR #%d! Semantic Error found on line %d. %s at %s\n",errorNum,current.tokenLine,current.tokenName,current.tokenType);
}

void Parser::syntaxError(string data){
	char current;
	//token current=scan.buildToken();//replace
	errorCount++;
	int errorNum = getErrorCount();
	printf("ERROR #%d! Syntax Error found on line %d. %s at %s\n",errorNum,current.tokenLine,current.tokenName,current.tokenType);
	while (current.tokenType == statementFollowers){ //compare token type with all follower statements until new
		current = scan.nexttoken(ifs);
	}
}

