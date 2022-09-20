#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include <vector>
using namespace std;
class Parser {
private:
	Scanner* scanner;
	int lineNumber;
	int errorCount;
	vector<string>statementStarters = { "BEGIN", "IDENTIFIER", "REPEAT", "WHILE",
	"WRITE", "WRITELN" };
	vector<string>statementFollowers = { ";", "END", "UNTIL", "DO", "OF" };
	vector<string>relationalOperators = { "=", "!=", "<", "<=", ">", ">=" };

};
#endif 