#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "symboltable.h"
#include "node.h"
#include <vector>

namespace frontend {
	using namespace std;
	class Parser {
	private:
		Scanner* scanner;
		char currentToken; 
		Symboltable *symboltable;
		int lineNumber;
		int errorCount;
		vector<string>statementStarters = { "BEGIN", "IDENTIFIER", "REPEAT", "WHILE",
		"WRITE", "WRITELN" };
		vector<string>statementFollowers = { ";", "END", "UNTIL", "DO", "OF" };
		vector<string>relationalOperators = { "=", "!=", "<", "<=", ">", ">=" };

		Node *parseCharacterConstant();
		Node *parseStringConstant();
		Node *parseRealConstant();
		Node *parseIntegerConstant();
		Node *parseVariable();
	};
}
#endif 