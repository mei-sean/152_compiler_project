#include <iostream>
#include "parser.h"
#include "node.h"
#include "parseTreePrinter.h"
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
	}
	return programNode;
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
		Node* statementNode = parseStatement(ifs);
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
Node* Parser::parseStatement(ifstream& ifs) {
	Node* statementNode = nullptr;
	int saveLineNumber = currentToken->tokenLine;

	if (currentToken->tokenType == "IDENTIFIER") {
		statementNode = parseAssignmentStatement(ifs);
	}
	else if(currentToken->tokenType == "BEGIN") {
		statementNode = parseCompoundStatement(ifs);
	}
	else if (currentToken->tokenType == "REPEAT") {
		statementNode = parseRepeatStatement(ifs);
	}
	else if (currentToken->tokenType == "WHILE") {
		statementNode = parseWhileStatement(ifs);
	}
	else if (currentToken->tokenType == "IF") {
		statementNode = parseIfStatement(ifs);
	}
	else if (currentToken->tokenType == "FOR") {
		statementNode = parseForStatement(ifs);
	}
	else if (currentToken->tokenType == "WRITE") {
		statementNode = parseWriteStatement(ifs);
	}
	else if (currentToken->tokenType == "WRITELN") {
		parseWritelnStatement(ifs);
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
Node* Parser::parseWriteStatement(ifstream& ifs) {
	Node* writeNode = new Node("WRITE");
	*currentToken = scan.nextToken(ifs);
	parseWriteArguments(writeNode, ifs);
	if (writeNode->children.size() == 0) {
		syntaxError("Invalid WRITE statement");
	}
	return writeNode;
}
Node *Parser::parseAssignmentStatement(ifstream& ifs) {
	Node *assignmentNode = new Node("ASSIGN"); // Create the assign node. 
	Node *lhsNode = new Node("VARIABLE"); // Adopt the variable node as the first child.
	string variableName = currentToken->tokenName;

	lhsNode->text = variableName;
	assignmentNode->adopt(lhsNode);

	*currentToken = scan.nextToken(ifs);  // consume the LHS variable;

	if (currentToken->tokenType == "COLON_EQUALS")
	{
		*currentToken = scan.nextToken(ifs);  // consume :=
	}
	else syntaxError("Missing :=");

	// Adopt expression node as the second child. 
	Node *rhsNode = parseExpression(ifs);
	assignmentNode->adopt(rhsNode);

	return assignmentNode;
}

Node *Parser::parseRepeatStatement(ifstream& ifs) {
	// Parses the repeat token. 
	Node *loopNode = new Node("LOOP");
	*currentToken = scan.nextToken(ifs);  // consume REPEAT

	parseStatementList(loopNode, "UNTIL", ifs);

	if (currentToken->tokenType == "UNTIL")
	{
		// Will adopt the test expression node. 
		Node *testNode = new Node("TEST");
		lineNumber = currentToken->tokenLine;
		testNode->lineNumber = lineNumber;
		*currentToken = scan.nextToken(ifs);  // consume UNTIL

		testNode->adopt(parseExpression(ifs));

		// Adopts the TEST node as the final child. 
		loopNode->adopt(testNode);
	}
	else syntaxError("Expecting UNTIL");

	return loopNode;

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

		compoundNode->adopt(parseAssignmentStatement(ifs));
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

		loopNode->adopt(parseStatement(ifs));
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
	return compoundNode;
}

Node* Parser::parseWhileStatement(ifstream& ifs) {
	Node* newNode = new Node("LOOP"); //create node for while loop
	*currentToken = scan.nextToken(ifs); //move to next token

	Node* test = new Node("TEST"); //create node for tests
	lineNumber = currentToken->tokenLine;//FIX: maybe need setLineNumber funct?
	test->lineNumber = lineNumber; //FIX: need get lineNumber

	if (currentToken->tokenType == "DO") {
		newNode->adopt(parseCompoundStatement(ifs));
	}
	else {
		newNode->adopt(parseStatement(ifs));
	}
	return newNode;

}

Node* Parser::parseIfStatement(ifstream& ifs) {
	Node* newNode = new Node("IF");
	int lineNum = currentToken->tokenLine; //FIX: might need setLineNumber funct?
	*currentToken = scan.nextToken(ifs);

	newNode->adopt(parseExpression(ifs));

	if (currentToken->tokenType == "THEN") {
		*currentToken = scan.nextToken(ifs);
	}
	else {
		syntaxError("Expected THEN");
	}
	if (currentToken->tokenType == "BEGIN") {
		newNode->adopt(parseCompoundStatement(ifs));
	}
	else {
		newNode->adopt(parseStatement(ifs));
	}
	if (currentToken->tokenType == "ELSE") {
		*currentToken = scan.nextToken(ifs);
		if (currentToken->tokenType == "BEGIN") {
			newNode->adopt(parseCompoundStatement(ifs));
		}
		else {
			newNode->adopt(parseStatement(ifs));
		}
	}
	return newNode;
}

Node* Parser::parseWritelnStatement(ifstream &ifs) {
	Node* writelnNode = new Node("WRITELN");
	*currentToken = scan.nextToken(ifs);

	if (currentToken->tokenType == "LPAREN") {
		parseWriteArguments(writelnNode, ifs); //goes through WriteArgument if statements to parse
	}
	return writelnNode;

}
void Parser::parseWriteArguments(Node* node, ifstream& ifs) {
	bool argument = false; //use to check argument presence
	if (currentToken->tokenType == "LPAREN") {
		*currentToken = scan.nextToken(ifs);
	}
	else syntaxError("Missing (");
	if (currentToken->tokenType == "IDENTIFIER") {
		node->adopt(parseVariable(ifs));
		argument = true;
	}
	else if (currentToken->tokenType == "STRING") {
		node->adopt(parseStringConstant(ifs));
		argument = true;
	}
	else if (currentToken->tokenType == "CHARACTER") {
		node->adopt(parseCharacterConstant(ifs));
	}
	else syntaxError("Invalid WRITE or WRITELN");

	if (argument) {
		if (currentToken->tokenType == "COLON") {
			*currentToken = scan.nextToken(ifs);//get rid of the colon and read next
			if (currentToken->tokenType == "INTEGER") {
				node->adopt(parseIntegerConstant(ifs)); //if integer found then parse sole integer
				if (currentToken->tokenType == "COLON") {//repeat
					*currentToken = scan.nextToken(ifs);
					if (currentToken->tokenType == "INTEGER") {
						node->adopt(parseIntegerConstant(ifs));
					}
					else syntaxError("INTEGER");
				}
			}
		}
	}
}
Node* Parser::parseExpression(ifstream& ifs) {
	Node* expressionNode = parseSimpleExpression(ifs);
	Node* opNode = new Node("");
	while ((findVector(operators, currentToken->tokenType) || 
		(findVector(boolOperators, currentToken->tokenType)))){
		if (currentToken->tokenType == "EQUALS") {
			opNode->nodeType = "EQ";
		}
		else if (currentToken->tokenType == "NOT_EQUALS") {
			opNode->nodeType = "NEQ";
		}
		else if (currentToken->tokenType == "LESS_THAN") {
			opNode->nodeType = "LT";
		}
		else if (currentToken->tokenType == "LESS_THAN_EQUALS") {
			opNode->nodeType = "LTEQ";
		}
		else if (currentToken->tokenType == "GREATER_THAN") {
			opNode->nodeType = "GT";
		}
		else if (currentToken->tokenType == "GREATER_THAN_EQUALS") {
			opNode->nodeType = "GTEQ";
		}
		else if (currentToken->tokenType == "AND") {
			opNode->nodeType = "AND";
		}
		else if (currentToken->tokenType == "OR") {
			opNode->nodeType = "OR";
		}
		else {
			Node* opNode = nullptr;
		}
	}
	*currentToken = scan.nextToken(ifs);
	if (opNode != nullptr) {
		opNode->adopt(expressionNode);
		opNode->adopt(parseSimpleExpression(ifs));
		expressionNode = opNode;
	}
	return expressionNode;
}
Node* Parser::parseSimpleExpression(ifstream& ifs) {
	Node* notNode = nullptr;
	if (currentToken->tokenType == "NOT") {
		*currentToken = scan.nextToken(ifs);
		notNode = new Node("NOT");
	}
	Node* simpleExpressionNode = parseTerm(ifs);
	while (findVector(simpleExpressionOperators, currentToken->tokenType)) {
		if (currentToken->tokenType == "PLUS") {
			Node* opNode = new Node("ADD");
		}
		else {
			Node* opNode = new Node("SUBTRACT");
		}
		*currentToken = scan.nextToken(ifs);
	}
	if (notNode != nullptr) {
		notNode->adopt(simpleExpressionNode);
		simpleExpressionNode = notNode;
	}
	return simpleExpressionNode;
}
Node* Parser::parseTerm(ifstream& ifs) {
	Node* termNode = parseFactor(ifs);
	while (findVector(termOperators, currentToken->tokenType)) {
		Node* opNode = nullptr;
		if (currentToken->tokenType == "STAR") {
			opNode = new Node("MULTIPLY");
		}
		else if ((currentToken->tokenType == "SLASH") || (currentToken->tokenType == "DIV")) {
			opNode = new Node("DIVIDE");
		}
		else if (currentToken->tokenType == "MOD") {
			opNode = new Node("MOD");
		}
		*currentToken = scan.nextToken(ifs);
		opNode->adopt(termNode);
		opNode->adopt(parseFactor(ifs));
		termNode = opNode;
	}
	return termNode;
}
Node* Parser::parseFactor(ifstream &ifs) {
	Node* factor = nullptr;
	Node* negativeSign = nullptr;
	if (currentToken->tokenType == "MINUS") { //looking for minus signs for negative integers
		negativeSign = new Node("NEGATE"); //store
		*currentToken = scan.nextToken(ifs); //move to next token
	}
	if (currentToken->tokenType == "IDENTIFIER") { //check if factor type is an identifier
		factor = parseVariable(ifs);
	}
	else if (currentToken->tokenType == "INTEGER") {//check if factor is an integer
		factor = parseIntegerConstant(ifs);
	}
	else if (currentToken->tokenType == "REAL") {
		factor = parseRealConstant(ifs);
	}
	else if (currentToken->tokenType == "LPAREN") {
		*currentToken = scan.nextToken(ifs);
		//factor = parseExpression(); //uncomment when parseExpression() exists
		if (currentToken->tokenType == "RPAREN") {
			*currentToken = scan.nextToken(ifs);
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
Node* Parser::parseVariable(ifstream& ifs) {
	string variableName = currentToken->tokenName; //store name of token into variable
	//check variable name for valid symtab token and call syntax or semantic error if one exists
	if (symtab.symbolTableLookup(variableName) == "") {
		semanticError("Undeclared identifier");
	}

	Node* newnode = new Node("VARIABLE"); //set type within new node
	newnode->text = variableName; //storing the name into the node's text

	*currentToken = scan.nextToken(ifs); //change this to something that actually works
	return newnode;

}

Node* Parser::parseIntegerConstant(ifstream &ifs)
{
	// The current token should now be a number.

	Node* integerNode = new Node("INTEGER_CONSTANT");
	integerNode->text = currentToken->tokenValue;

	*currentToken = scan.nextToken(ifs);  // consume the number
	return integerNode;
}

Node* Parser::parseRealConstant(ifstream& ifs)
{
	// The current token should now be a number.

	Node* realNode = new Node("REAL_CONSTANT");
	realNode->text = currentToken->tokenValue;

	*currentToken = scan.nextToken(ifs);  // consume the number
	return realNode;
}

Node* Parser::parseStringConstant(ifstream& ifs)
{
	Node* stringNode = new Node("STRING_CONSTANT");
	stringNode->text = currentToken->tokenName;

	*currentToken = scan.nextToken(ifs);  // This will consume the string
	return stringNode;
}

Node* Parser::parseCharacterConstant(ifstream& ifs) {
	Node* characterNode = new Node("CHARACTER_CONSTANT");
	characterNode->text = currentToken->tokenName;

	*currentToken = scan.nextToken(ifs); // This will consume the character
	return characterNode;
}
void Parser::semanticError(string message) {
	cout << "SEMANTIC ERROR at line " << currentToken->tokenLine << message << " at " << currentToken->tokenName << endl;
	errorCount++;
}
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
bool Parser::findVector(vector<string>myVector, string target) {
	int max = myVector.size();   //right bound of vector search
	for (int i = 0; i < max; i++) {
		if (target == myVector[i]) {
			return true;
		}
	}
	return false;
}