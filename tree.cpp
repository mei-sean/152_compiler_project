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

int tree::size(Node *root) {
    if (root == 0) return 0;
    else {
        return 1 + tree::size(root->left) + tree::size(root->right);
    }
}

// We might need height of the tree instead. 
int tree::depth(Node *node) {
    if (node == NULL) return -1;
    else {
        // Recursively compute the depth of the tree.
        int ldepth = depth(node->left);
        int rdepth = depth(node->right);

         if (ldepth > rdepth)
            return(ldepth + 1);
        else return(rdepth + 1);
    }
}

/*
int tree::height() {

}
*/
// We also need a function to create the parse tree. 

// Should be a treewalker function to print in XML format. 
void tree::print() {

}