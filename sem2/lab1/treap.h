#pragma once

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int key, priority;
    Node* l = nullptr, * r = nullptr;
    Node(int k);
};

//Операции с деревом
Node* merge(Node* a, Node* b);
void split(Node* root, int key, Node*& a, Node*& b);
void insert(Node*& root, int key);
Node* search(Node* root, int key);
void remove(Node*& root, int key);
void buildTree(Node*& root, vector<int>& arr);
void printTree(Node* root, int level = 0);
Node* mergeTrees(Node* tree1);
Node* intersection(Node* left, Node* right);
Node* intersectionTrees(Node* tree1);
void runMenu();

#endif
