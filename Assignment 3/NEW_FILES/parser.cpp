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
Node *Parser::parseWhileStatement(){
	Node *newNode = new Node("LOOP"); //create node for while loop
	currentToken = scanner->nexttoken(in); //move to next token

	Node *test = newNode("TEST"); //create node for tests
	lineNumber = currentToken.tokenLine;//FIX: maybe need setLineNumber funct?
	test->lineNumber = lineNumber; //FIX: need get lineNumber

	if(currentToken.tokenType == "DO"){
		newNode->adopt(parseCompoundStatement());
	}
	else{
		newNode->adopt(parseStatement());
	}
	return newNode;

}

Node *Parser::parseForStatement(){


}

Node *Parser::parseIfStatement(){
	Node* newNode = new Node("IF");
	int lineNum = currentToken.tokenLine; //FIX: might need setLineNumber funct?
	currentToken =  scanner->nexttoken(in);

	newNode->adopt(parseExpression());

if(currentToken.tokenType == "THEN"){
	currentToken = scanner->nexttoken(in);
}
else{
	syntaxError("Expected THEN");
}
if(currentToken.tokenType == "BEGIN"){
	newNode->adopt(parseCompoundStatement());
}
else{
	newNode->adopt(parseStatement());
}
if(currentToken.tokenType == "ELSE"){
	currentToken = scanner->nexttoken();
	if (currentToken.tokenType == "BEGIN"){
		newNode->adopt(parseCompoundStatement());
	}
	else{
		newNode->adopt(parseStatement());
	}
}
return newNode;
}

Node *Parser::parseWriteArguments(){
	Node *writeNode = new Node("WRITE");
	currentToken = scanner->nexttoken();

	parseWriteArguments(writeNode);
	if(writeNode->children.size() == 0){ //no children
		syntaxError("Invalid WRITE statement");
	}
}

Node *Parser::parseWritelnStatement(){
	Node *writelnNode = new Node("WRITELN");
	currentToken = scanner->nextToken();

	if (currentToken.tokenType == "LPAREN"){
		parseWriteArguments(writelnNode); //goes through WriteArgument if statements to parse
	}
	return writelnNode;

}

void Parser::parseWriteArguments(Node *node){
	bool argument = false; //use to check argument presence
	if (currentToken.tokenType == "LPAREN"){
		currentToken = scanner->nextToken(in);
	}
	else syntaxError("Missing (");
	if(currentToken.tokenType == "IDENTIFIER"){
		node->adopt(parseVariable());
		argument = true;
	}
	else if(currentToken.tokenType == "STRING"){
		node->adopt(parseStringConstant());
		argument = true;
	}
	else if (currentToken.tokenType == "CHARACTER"){
		node->adopt(parseCharacterConstant());
	}
	else syntaxError("Invalid WRITE or WRITELN");

	if(argument){
		if(currentToken.tokenType == "COLON"){
			currentToken = scanner->nexttoken(in); //get rid of the colon and read next
			if (currentToken.tokenType == "INTEGER"){
				node->adopt(parseIntegerConstant()); //if integer found then parse sole integer
				if(currentToken.tokenType == "COLON"){//repeat
					currentToken.tokenType = scanner->nextToken(in);
					if(currentToken.tokenType == "INTEGER"){
						node->adopt(parseIntegerConstant());
					}
					else syntaxError("INTEGER")
				}
			}
		}
	}
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
		return negativeSign; //return the full term
	}
	return factor; //return "positive" term
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

