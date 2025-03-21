#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

struct Node {
    int l, r;       
    int max;        
    int add;       
    Node* left;    
    Node* right;   
};


Node* createNode(int l, int r);
Node* buildTree(int l, int r, int* initialValues);
void modify(Node* node, int l, int r, int val);
int query(Node* node, int l, int r);
void collectValues(Node* root, int start, int end, int* output);

#endif 
