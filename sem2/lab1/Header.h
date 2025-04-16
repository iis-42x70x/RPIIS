#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

struct Node;

Node* insert(Node* root, int key);
void split(Node* root, int key, Node*& left, Node*& right);
Node* merge(Node* left, Node* right);
Node* remove(Node* root, int key);
bool search(Node* root, int key);
void collectKeys(Node* root, vector<int>& keys);
Node* unionTreaps(Node* treap1, Node* treap2);
Node* intersectionTreaps(Node* treap1, Node* treap2);
void inorder(Node* root);
void printMenu();