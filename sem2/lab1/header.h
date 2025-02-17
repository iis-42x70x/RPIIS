#pragma once
#include <vector>
using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;

	Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

struct BinarySearchTree {
	Node* root;

	BinarySearchTree();
	~BinarySearchTree();

	void Insert(int value);
	bool Search(int value) const;
	void Remove(int value);
	void InOrderTraversal() const;
	void PreOrderTraversal() const;
	void PostOrderTraversal() const;
	void BuildFromArray(const vector<int>& values);
	void Clear();

private:
	void Insert(Node*& node, int value);
	bool Search(Node* node, int value) const;
	Node* Remove(Node* node, int value);
	Node* FindMin(Node* node) const;
	void InOrderTraversal(Node* node) const;
	void PreOrderTraversal(Node* node) const;
	void PostOrderTraversal(Node* node) const;
	void DestroyTree(Node* node);
};
#pragma once
