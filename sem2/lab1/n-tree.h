#pragma once
#include <vector>
#include <iostream>
using namespace std;
struct Treenode {
	int data;
	std::vector <Treenode*> children;
};
void menu();
void addChild(Treenode*& parent, int n);
void deleteNode(Treenode* parent, Treenode* nodeToDelete);
void findtodelete(Treenode* parent);
void printTree(Treenode* root, int depth = 0);
void deleteTree(Treenode*& parent);
void choice(int n);
