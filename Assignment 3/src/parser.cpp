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



    Node *Parser::parseCharacterConstant() {
        Node * characterNode = new Node(CHARACTER_CONSTANT);
        characterNode->value = currentToken->value;

        currentToken = scanner->nexttoken(in); // This will consume the character
        return characterNode;
    }
}
