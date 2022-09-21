#include <iostream>
#include "../inc/ParseTreePrinter.h"

namespace intermediate {
    using namespace std;

    void ParseTreePrinter::print(Node *node) {
        line = line + indent;
        line += "<" + NodeTypes[(int) node->type]; // Opening for the xml format. 

        if (node->type == PROGRAM) line+=" " + node->text;
        else if (node->type == VARIABLE) line += " " + node->text;
        else if (node->type == INTEGER_CONSTANT) line += " " + to_string(node->Lvalue);
        else if (node->type == REAL_CONSTANT) line += " " + to_string(node->Dvalue);
        else if (node->type == STRING_CONSTANT || node->type == CHARACTER_CONSTANT) line += " '" + node->Svalue + "'";
        if (node->lineNumber > 0) line += " Line " + to_string(node->lineNumber);

        

    }
}

