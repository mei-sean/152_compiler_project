#include <iostream>
#include "ParseTreePrinter.h"
using namespace std;
string ParseTreePrinter::indentSize = "      "; // Tab. 
void ParseTreePrinter::print(Node* node) {
    line = line + indent;
    line += "<" + node->nodeType; // Opening for the xml format. 

    if (node->nodeType == "PROGRAM") line += " " + node->text;
    else if (node->nodeType == "VARIABLE") line += " " + node->text;
    else if (node->nodeType == "INTEGER_CONSTANT") line += " " + node->text;
    else if (node->nodeType == "REAL_CONSTANT") line += " " + node->text;
    else if (node->nodeType == "STRING_CONSTANT" || node->nodeType == "CHARACTER_CONSTANT") line += " '" + node->text + "'";
    if (node->lineNumber > 0) line += " Line " + to_string(node->lineNumber);

    vector<Node*> childrenVector = node->children; // Store children in a vector. 

    if (node->children.size() > 0) {
        // Print the children nodes. 
        line += ">";
        OutputLine();
        printChildren(node->children);
        line += indent;
        line += "</" + node->nodeType + ">";
    }
    else line += " />"; // Closing tag. 
    OutputLine();
}

void ParseTreePrinter::printChildren(vector<Node*> children) {
    // Will print all the children nodes of a given node in the vector. 
    string indentation = indent;
    indent = indent + indentSize;
    for (Node* child : children) print(child);
    indent = indentation; // Save the indentation. 
}
void ParseTreePrinter::OutputLine() {
    // Only outputs a line for xml format. 
    cout << line << endl;
    line = "";
}
