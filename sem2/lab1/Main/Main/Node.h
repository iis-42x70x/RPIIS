#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

struct Node {
	int info;
	Node* left;
	Node* right;
	Node(int value);
	static Node* Leaf(int value);
	static Node* Show(Node* a, int b);
	static Node* Pop(Node* root, int value);
	static bool Sort(Node* root,int value);
	static Node* Delete(Node* root);
	static void Bypass(Node* root);
};
