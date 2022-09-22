#include <iostream>
#include "../inc/ParseTreePrinter.h"

namespace intermediate {
    using namespace std;

    string ParseTreePrinter::indentSize = "      "; // Tab. 
    void ParseTreePrinter::print(Node *node) {
        line = line + indent;
        line += "<" + NodeTypes[(int) node->type]; // Opening for the xml format. 

        if (node->type == PROGRAM) line+=" " + node->text;
        else if (node->type == VARIABLE) line += " " + node->text;
        else if (node->type == INTEGER_CONSTANT) line += " " + to_string(node->Lvalue);
        else if (node->type == REAL_CONSTANT) line += " " + to_string(node->Dvalue);
        else if (node->type == STRING_CONSTANT || node->type == CHARACTER_CONSTANT) line += " '" + node->Svalue + "'";
        if (node->lineNumber > 0) line += " Line " + to_string(node->lineNumber);

        vector<Node *> childrenVector = node->children; // Store children in a vector. 

        if (node->children.size() > 0) {
            // Print the children nodes. 
            line += ">";
            OutputLine();
            printChildren(node->children);
            line += indent;
            line += "</" + NodeTypes[(int) node->type] + ">";
        }
        else line += " />"; // Closing tag. 
        OutputLine(); 
    }

    void ParseTreePrinter::printChildren(vector<Node *> children) {
        // Will print all the children nodes of a given node in the vector. 
        string indentation = indent; 
        indent = indent + indentSize;
        for (Node *child : children) print(child);
        indent = indentation; // Save the indentation. 
    }

    void ParseTreePrinter::OutputLine() {
        // Only outputs a line for xml format. 
        cout << line << endl;
        line = "";
    }
}

