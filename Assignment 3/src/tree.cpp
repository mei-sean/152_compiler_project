#include "../inc/tree.h"
#include <iostream>

using namespace std;

tree::tree() {
    root = nullptr;
    tree_size = 0;

}

tree::tree(const tree &copy) {
    root = copy.root;
    tree_size = copy.tree_size;
}

void tree::insert(string token, int digits,int prevPriority) {
    if(!root){
        Node* temp;
        temp->name = token;
        temp->value = digits;
        temp->firstchild = nullptr;
        root = temp;
    }
    if(root->firstchild->priority < prevPriority){
        root = root->firstchild;
        //insert();
    }
}
