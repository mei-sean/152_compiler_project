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
	parseStatementList(compoundNode, "END", ifs);
	if (currentToken->tokenType == "END") {
		*currentToken = scan.nextToken(ifs);
	}
	else {
		cout << "Expecting END" << endl;
	}
	return compoundNode;
}

void Parser::parseStatementList(Node* parentNode, string terminalType, ifstream &ifs) {
	while ((currentToken->tokenType!=terminalType) && (currentToken->tokenType != "END_OF_FILE")) {
		Node* statementNode = parseStatement();
		if (statementNode != nullptr) {
			parentNode->adopt(statementNode);
		}
		if (currentToken->tokenType == "SEMICOLON") {
			while (currentToken->tokenType == "SEMICOLON") {
				*currentToken = scan.nextToken(ifs);
			}
		}
	}
}
Node* Parser::parseStatement() {
	Node* statementNode = nullptr;
	int saveLineNumber = currentToken->tokenLine;

	if (currentToken->tokenType == "IDENTIFIER") {
		statementNode = parseAssignmentStatement();
	}
	else if(currentToken->tokenType == "BEGIN") {
		statementNode = parseCompoundStatement();
	}
	else if (currentToken->tokenType == "REPEAT") {
		statementNode = parseRepeatStatement();
	}
	else if (currentToken->tokenType == "WHILE") {
		statementNode = parseWhileStatement();
	}
	else if (currentToken->tokenType == "IF") {
		statementNode = parseIfStatement();
	}
	else if (currentToken->tokenType == "FOR") {
		statementNode = parseForStatement();
	}
	else if (currentToken->tokenType == "WRITE") {
		statementNode = parseWriteStatement();
	}
	else if (currentToken->tokenType == "WRITELN") {
		parseWritelnStatement();
	}
	else if (currentToken->tokenType == "SEMICOLON") {
		statementNode = nullptr;
	}
	else {
		syntaxError("Unrecognized Token");
	}
	if (statementNode != nullptr) {
		statementNode->lineNumber = saveLineNumber;
	}
	return statementNode;
}

Node* Parser::parseForStatement(ifstream& ifs) {
	Node* compoundNode = new Node("COMPOUND");
	Node* newValue = new Node("INTEGER_CONSTANT");

	string symtabentry;
	Node* oldVariable = new Node("VARIABLE");
	if (currentToken->tokenType == "FOR") {
		*currentToken = scan.nextToken(ifs);
		oldVariable->text = currentToken->tokenValue;
		string variableName = currentToken->tokenName;

		compoundNode->adpot(parseAssignmentStatement());
		symtabentry = symtab.symbolTableLookup(variableName);
	}
	else {
		syntaxError("EXPECTING FOR");
	}
	if (currentToken->tokenType == "TO" || currentToken->tokenType == "DOWNTO") {
		Node* gtltNode;
		if (currentToken->tokenType == "TO") {
			gtltNode = new Node("GT");
		}
		else {
			gtltNode = new Node("LT");
		}
		Node* addNode;
		if (currentToken->tokenType == "TO") {
			addNode = new Node("ADD");
		}
		else {
			addNode = new Node("SUBTRACT");
		}
		*currentToken = scan.nextToken(ifs);
		newValue->text = currentToken->tokenValue;

		*currentToken = scan.nextToken(ifs);

		gtltNode->adopt(oldVariable);
		gtltNode->adopt(newValue);

		Node* testNode = new Node("TEST");
		testNode->adopt(gtltNode);

		Node* loopNode = new Node("LOOP");
		loopNode->adopt(testNode);

		*currentToken = scan.nextToken(ifs);

		loopNode->adopt(parseStatement());
		addNode->adopt(oldVariable);

		int constant = 1;
		Node* Constant = new Node("INTEGER_CONSTANT");
		Constant->text = constant;
		addNode->adopt(Constant);

		Node* assignNode = new Node("ASSIGN");
		compoundNode->adopt(loopNode);
		assignNode->adopt(oldVariable);
		loopNode->adopt(assignNode);
		assignNode->adopt(addNode);
	}
}
/*
Node* Parser::parseWhileStatement(ifstream& ifs) {
	Node* newNode = new Node("LOOP"); //create node for while loop
	currentToken = scan->nexttoken(in); //move to next token

	Node* test = newNode("TEST"); //create node for tests
	lineNumber = currentToken.tokenLine;//FIX: maybe need setLineNumber funct?
	test->lineNumber = lineNumber; //FIX: need get lineNumber

	if (currentToken.tokenType == "DO") {
		newNode->adopt(parseCompoundStatement());
	}
	else {
		newNode->adopt(parseStatement());
	}
	return newNode;

}
*/
/*
Node* Parser::parseIfStatement(ifstream& ifs) {
	Node* newNode = new Node("IF");
	int lineNum = currentToken.tokenLine; //FIX: might need setLineNumber funct?
	currentToken = scan->nexttoken(ifs);

	newNode->adopt(parseExpression());

	if (currentToken.tokenType == "THEN") {
		currentToken = scanner->nexttoken(in);
	}
	else {
		syntaxError("Expected THEN");
	}
	if (currentToken.tokenType == "BEGIN") {
		newNode->adopt(parseCompoundStatement());
	}
	else {
		newNode->adopt(parseStatement());
	}
	if (currentToken.tokenType == "ELSE") {
		currentToken = scanner->nexttoken();
		if (currentToken.tokenType == "BEGIN") {
			newNode->adopt(parseCompoundStatement());
		}
		else {
			newNode->adopt(parseStatement());
		}
	}
	return newNode;
}

Node* Parser::parseWriteArguments() {
	Node* writeNode = new Node("WRITE");
	currentToken = scanner->nexttoken();

	parseWriteArguments(writeNode);
	if (writeNode->children.size() == 0) { //no children
		syntaxError("Invalid WRITE statement");
	}
}

Node* Parser::parseWritelnStatement() {
	Node* writelnNode = new Node("WRITELN");
	currentToken = scanner->nextToken();

	if (currentToken.tokenType == "LPAREN") {
		parseWriteArguments(writelnNode); //goes through WriteArgument if statements to parse
	}
	return writelnNode;

}

void Parser::parseWriteArguments(Node* node) {
	bool argument = false; //use to check argument presence
	if (currentToken.tokenType == "LPAREN") {
		currentToken = scanner->nextToken(in);
	}
	else syntaxError("Missing (");
	if (currentToken.tokenType == "IDENTIFIER") {
		node->adopt(parseVariable());
		argument = true;
	}
	else if (currentToken.tokenType == "STRING") {
		node->adopt(parseStringConstant());
		argument = true;
	}
	else if (currentToken.tokenType == "CHARACTER") {
		node->adopt(parseCharacterConstant());
	}
	else syntaxError("Invalid WRITE or WRITELN");

	if (argument) {
		if (currentToken.tokenType == "COLON") {
			currentToken = scanner->nexttoken(in); //get rid of the colon and read next
			if (currentToken.tokenType == "INTEGER") {
				node->adopt(parseIntegerConstant()); //if integer found then parse sole integer
				if (currentToken.tokenType == "COLON") {//repeat
					currentToken.tokenType = scanner->nextToken(in);
					if (currentToken.tokenType == "INTEGER") {
						node->adopt(parseIntegerConstant());
					}
					else syntaxError("INTEGER")
				}
			}
		}
	}
}
*/
Node* Parser::parseTerm() {
	Node* termNode = parseFactor();
	while()
}
/*
Node* Parser::parsefactor() {
	Node* factor = nullptr;
	Node* negativeSign = nullptr;
	if (currentToken.tokenType == "MINUS") { //looking for minus signs for negative integers
		negativeSign = new Node("NEGATE"); //store
		currentToken = scanner->nexttoken(in); //move to next token
	}
	if (currentToken.tokenType == "IDENTIFIER") { //check if factor type is an identifier
		factor = parseVariable();
	}
	else if (currentToken.tokenType == "INTEGER") {//check if factor is an integer
		factor = parseIntegerConstant();
	}
	else if (currentToken.tokenType == "REAL") {
		factor = parseRealConstant();
	}
	else if (currentToken.tokenType == "LPAREN") {
		currentToken = scanner->nexttoken(in);
		//factor = parseExpression(); //uncomment when parseExpression() exists
		if (currentToken.tokenType == "RPAREN") {
			currentToken = scanner->nexttoken(in);
		}
		else syntaxError("Expected )"); //missing end paren
	}
	else syntaxError("Unexpected token received");
	if (negativeSign != nullptr) { //if negative sign exists
		negativeSign->adopt(factor); //add the rest of the factor to the negative symbol
		return negativeSign; //return the full term
	}
	return factor; //return "positive" term
}
Node* Parser::parseVariable() {
	string variableName = currentToken.tokenName; //store name of token into variable
	//check variable name for valid symtab token and call syntax or semantic error if one exists
	entry* vID = Symboltable::symbolTableLookup(variableName); //FIX: creating entry variable to store the existence of entry or not
	Node* newnode = new Node("VARIABLE"); //set type within new node
	newnode->text = variableName; //storing the name into the node's text

	currentToken = scanner->nexttoken(in); //change this to something that actually works
	return newnode;

}

Node* Parser::parseIntegerConstant(ifstream &ifs)
{
	// The current token should now be a number.

	Node* integerNode = new Node("INTEGER_CONSTANT");
	integerNode->value = currentToken->tokenValue;

	currentToken = scanner->nexttoken(in);  // consume the number
	return integerNode;
}

Node* Parser::parseRealConstant()
{
	// The current token should now be a number.

	Node* realNode = new Node(REAL_CONSTANT);
	realNode->text = currentToken->tokenValue;

	currentToken = scanner->nexttoken(in);  // consume the number
	return realNode;
}

Node* Parser::parseStringConstant()
{
	Node* stringNode = new Node(STRING_CONSTANT);
	stringNode->value = currentToken;

	currentToken = scanner->nexttoken(in);  // This will consume the string
	return stringNode;
}

Node* Parser::parseCharacterConstant() {
	Node* characterNode = new Node(CHARACTER_CONSTANT);
	characterNode->value = currentToken;

	currentToken = scanner->nexttoken(in); // This will consume the character
	return characterNode;
}
void Parser::semanticError(string data) {
	errorCount++;
	int errorNum = getErrorCount();
	printf("ERROR #%d! Semantic Error found on line %d. %s at %s\n", errorNum, currentToken.tokenLine, data, currentToken.tokenName, currentToken.tokenType);
}*/
void Parser::syntaxError(string message) {
	cout << "SYNTAX ERROR at line " << currentToken->tokenLine << message << " at " << currentToken->tokenName << endl;
	errorCount++;
}        
string Parser::searchVector(vector<string>myVector, string target) {
	int max = myVector.size();   //right bound of vector search
	for (int i = 0; i < max; i++) {
		if (target == myVector[i]) {
			return myVector[i];
		}
	}
	string emptyString = "";
	return emptyString;
}