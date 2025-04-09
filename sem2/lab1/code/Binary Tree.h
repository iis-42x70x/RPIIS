#pragma once
#include <iostream>
#include "Node.h"

using namespace std;

struct Tree {
public:
	Tree();
	void insert(int value);
	void pop(int value);
	void print();
	void search(int value);
	void build(int arr[], int a);
	void del_comp();
	void bypass();
private:
	Node* root;
};