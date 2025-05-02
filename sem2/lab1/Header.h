#pragma once

#ifndef RBTREE_HEADER_H
#define RBTREE_HEADER_H

#include <iostream>
#include <string>

struct node {
    int data;
    node* parent;
    node* left;
    node* right;
    bool color; // true - black, false - red
    node(int val);
};

class RBTree {
private:
    node* root;

    void LEFT_ROTATE(node* x);
    void RIGHT_ROTATE(node* x);
    void RB_INSERT_FIXUP(node* z);
    void RB_TRANSPLANT(node* u, node* v);
    void RB_DELETE_FIXUP(node* x);

public:
    RBTree();
    node* most_right(node* z);
    node* most_left(node* z);
    node* search(int inf);
    node* maximum(node* z);
    node* minimum(node* z);
    void RB_INSERT(int inf);
    void RB_DELETE(int inf);
    void printTree(node* r, int space = 0, int height = 10);
    void print_2(node* r, std::string indent, bool last);
    node* getRoot() { return root; }
    void test_f();
};
//
// Created by aleks on 02.05.2025.
//

#endif //RBTREE_HEADER_H
