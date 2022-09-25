#include <iostream>
#include <fstream>
#include "antlr4-runtime.h"
#include "ExprLexer.h"

using namespace antlrcpp;
using namespace antlr4;
using namespace std;

int main(int argc, const char *incoming[]){
	ifstream in;
	in.open(incoming[1]);
	ANTLRInputStream input(in);
	ExprLexer lexer(&input);
	CommonTokenStream tokens(&lexer)

	cout << "Tokens:\n";
	tokens.fill();
	for (Token *token : tokens.getTokens()){
		std::cout << token->toString() << std::endl;
	}
}