#include <iostream>
#include "parser.h"
#include "node.h"
#include <fstream>

using namespace std;

Scanner scan;    //instantiate scanner class
token currentToken; //placeholder


Node parseProgram(){
	Node* program = new Node("PROGRAM");
	currentToken  = 
}

Node *Parser::parsefactor(){
	Node* factor = nullptr;
	Node *negativeSign = nullptr;
	if(currentToken.tokenType == "MINUS"){ //looking for minus signs for negative integers
		negativeSign = new Node("NEGATE"); //store
		currentToken = scanner->nexttoken(in); //move to next token
	}
	if(currentToken.tokenType == "IDENTIFIER"){ //check if factor type is an identifier
		factor = parseVariable();
	}
	else if(currentToken.tokenType == "INTEGER"){//check if factor is an integer
		factor = parseIntegerConstant(); 
	}
	else if (currentToken.tokenType == "REAL"){
		factor = parseRealConstant();
	}
	else if (currentToken.tokenType == "LPAREN"){
		currentToken = scanner->nexttoken(in);
		//factor = parseExpression(); //uncomment when parseExpression() exists
		if (currentToken.tokenType == "RPAREN"){
			currentToken = scanner->nexttoken(in);
		}
		else syntaxError("Expected )"); //missing end paren
	}
	else syntaxError("Unexpected token received");
	if (negativeSign != nullptr){ //if negative sign exists
		negativeSign->adopt(factor); //add the rest of the factor to the negative symbol
		return negativeSign; //return the combined node
	}
	return factor; //return "positive" factor
}
Node *Parser::parseVariable(){
	string variableName = currentToken.tokenName; //store name of token into variable
	//check variable name for valid symtab token and call syntax or semantic error if one exists
	entry *vID = Symboltable::symbolTableLookup(variableName); //FIX: creating entry variable to store the existence of entry or not
	Node *newnode = new Node("VARIABLE"); //set type within new node
	newnode->text = variableName; //storing the name into the node's text

	currentToken = scanner->nexttoken(in); //change this to something that actually works
	return newnode;

}

void Parser::semanticError(string data){
	errorCount++;
	int errorNum = getErrorCount();
	printf("ERROR #%d! Semantic Error found on line %d. %s at %s\n",errorNum,currentToken.tokenLine,data,currentToken.tokenName,currentToken.tokenType);
}

void Parser::syntaxError(string data){
	errorCount++;
	int errorNum = getErrorCount();
	printf("ERROR #%d! Syntax Error found on line %d. %s.\n %s at %s\n",errorNum,currentToken.tokenLine,data,currentToken.tokenName,currentToken.tokenType);
	while (currentToken.tokenType == statementFollowers){ //compare token type with all follower statements until new
		currentToken = scanner->nexttoken(in);
	}
}

