#include "BinarySearchTree.h"
#include <iostream>

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
	DestroyTree(root);
}

void BinarySearchTree::Insert(int value) {
	Insert(root, value);
}

bool BinarySearchTree::Search(int value) const {
	return Search(root, value);
}

void BinarySearchTree::Remove(int value) {
	root = Remove(root, value);
}

void BinarySearchTree::InOrderTraversal() const {
	InOrderTraversal(root);
	cout << endl;
}

void BinarySearchTree::PreOrderTraversal() const {
	PreOrderTraversal(root);
	cout << endl;
}

void BinarySearchTree::PostOrderTraversal() const {
	PostOrderTraversal(root);
	cout << endl;
}

void BinarySearchTree::BuildFromArray(const vector<int>& values) {
	for (int value : values) {
		Insert(value);
	}
}

void BinarySearchTree::Clear() {
	DestroyTree(root);
	root = nullptr;
}

void BinarySearchTree::Insert(Node*& node, int value) {
	if (!node) {
		node = new Node(value);
	}
	else if (value < node->data) {
		Insert(node->left, value);
	}
	else {
		Insert(node->right, value);
	}
}

bool BinarySearchTree::Search(Node* node, int value) const {
	if (!node) {
		return false;
	}
	else if (node->data == value) {
		return true;
	}
	else if (value < node->data) {
		return Search(node->left, value);
	}
	else {
		return Search(node->right, value);
	}
}

Node* BinarySearchTree::Remove(Node* node, int value) {
	if (!node) return nullptr;

	if (value < node->data) {
		node->left = Remove(node->left, value);
	}
	else if (value > node->data) {
		node->right = Remove(node->right, value);
	}
	else {
		if (!node->left) {
			Node* temp = node->right;
			delete node;
			return temp;
		}
		else if (!node->right) {
			Node* temp = node->left;
			delete node;
			return temp;
		}
		else {
			Node* temp = FindMin(node->right);
			node->data = temp->data;
			node->right = Remove(node->right, temp->data);
		}
	}
	return node;
}

Node* BinarySearchTree::FindMin(Node* node) const {
	while (node && node->left) {
		node = node->left;
	}
	return node;
}

void BinarySearchTree::InOrderTraversal(Node* node) const {
	if (node) {
		InOrderTraversal(node->left);
		cout << node->data << " ";
		InOrderTraversal(node->right);
	}
}

void BinarySearchTree::PreOrderTraversal(Node* node) const {
	if (node) {
		cout << node->data << " ";
		PreOrderTraversal(node->left);
		PreOrderTraversal(node->right);
	}
}

void BinarySearchTree::PostOrderTraversal(Node* node) const {
	if (node) {
		PostOrderTraversal(node->left);
		PostOrderTraversal(node->right);
		cout << node->data << " ";
	}
}

void BinarySearchTree::DestroyTree(Node* node) {
	if (node) {
		DestroyTree(node->left);
		DestroyTree(node->right);
		delete node;
	}
}
