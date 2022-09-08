#ifndef TREE_H
#define TREE_H
#include "node.h"
#include <iostream>
#include <vector>
using namespace std;

class tree{
    Node *root;
    int tree_size;
    public:
    tree();
    tree(const tree& copy);
    ~tree();

    void tree::insert(string token, int digits,int prevPriority);
    bool remove(string name);

    std::string to_string();
    int level(int key);

    unsigned size();
    unsigned depth();
    void print();

    tree& operator=(const tree &rhs);
    friend std::ostream& operator<<(std::ostream& stream, tree& rhs);

};
#endif