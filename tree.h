#ifndef TREE_H
#define TREE_H
#include "node.h"
#include <iostream>
#include <vector>
using namespace std;

class tree{
    
    int tree_size;
public:
    Node *root;
    tree();
    tree(const tree& copy);
    ~tree();

    void tree::insert(string token, int digits,int prevPriority);
    bool remove(string name);

    string to_string();
    int level(int key);

    int size(Node *);
    int depth(Node *);
    //int height();
    void print();

    tree& operator=(const tree &rhs);
    friend std::ostream& operator<<(std::ostream& stream, tree& rhs);

};
#endif