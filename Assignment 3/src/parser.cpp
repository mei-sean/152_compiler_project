#include <iostream>
#include <cstring>
#include "../NEW_FILES/parser.h"
#include "../NEW_FILES/node.h"
#include <fstream>
using namespace std;

namespace frontend {
    Node parseProgram(){

    }

    int priorityAssign(std::string operator_in){
    }


    Node *Parser::parseIntegerConstant()
    {
        // The current token should now be a number.

        Node *integerNode = new Node(INTEGER_CONSTANT);
        integerNode->value = currentToken;

        currentToken = scanner->nexttoken(in);  // consume the number
        return integerNode;
    }

    Node *Parser::parseRealConstant()
    {
        // The current token should now be a number.

        Node *realNode = new Node(REAL_CONSTANT);
        realNode->value = currentToken;

        currentToken = scanner->nexttoken(in);  // consume the number
        return realNode;
    }

    Node *Parser::parseStringConstant()
    {

        Node *stringNode = new Node(STRING_CONSTANT);
        stringNode->value = currentToken;

        currentToken = scanner->nexttoken(in);  // This will consume the string
        return stringNode;
    }

    Node *Parser::parseCharacterConstant() {
        Node * characterNode = new Node(CHARACTER_CONSTANT);
        characterNode->value = currentToken;

        currentToken = scanner->nexttoken(in); // This will consume the character
        return characterNode;
    }
}
