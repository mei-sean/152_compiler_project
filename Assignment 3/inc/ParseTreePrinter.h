#include <iostream>
#include <string>
#include <vector>
#include "../NEW_FILES/node.h"
#include "tree.h"

namespace intermediate {
    using namespace std;
    // New namespace, which is part of the intermediate of the parser. 

    class ParseTreePrinter {
    private: 
        string indent; // Indentation in the line. 
        string line; // Output of the line. 

    public:
        ParseTreePrinter() : indent(""), line("") {}; // ParseTreePrinter function with definitions of indent and line variables. 
        void print(Node *); // Print the tree. Will take the root node as the parameter. 
        void printChildren(vector<Node *>); // Print the children of a given node. 
        void printOutputLine(); // Print an output line. 
    };
}

