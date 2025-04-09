#include "Binary Tree.h"

Tree::Tree() {
	root = nullptr;
}

void Tree::insert(int value) {
	Node* a = nullptr, * prev = nullptr;
	bool isTrue = true;
	
	if (root == nullptr) {
		root = Node::Leaf(value);
		return;
	}

	a = root;
	while (a && isTrue) {
		prev = a;
		if (a == nullptr) {
			cout << "\n\nError! Root = nullptr!\n\n";
			exit(EXIT_FAILURE);
		}
		else {
			if (value < a->info) a = a->left;
			else a = a->right;
		}
	}
	if (isTrue) {
		if(Node::Sort(root, value) == true) {
			Node* newNode = Node::Leaf(value);
			if (newNode->info < prev->info) prev->left = newNode;
			else prev->right = newNode;
		}
	}
}

void Tree::print() {
	Node* b = root;
	if (root == nullptr) {
		cout << "\n\nMemory clear!\n\n";
		return;
	}
	else {
		Node::Show(b, 0);
	}
}

void Tree::pop(int value) {
	root = Node::Pop(root, value);
}

void Tree::search(int value) {
	Node* a = root;
	while (a != nullptr && a->info != value) {
		if (value > a->info) a = a->right;
		else a = a->left;
	}
	if (a == nullptr) {
		cout << "\n\nThe element is missing!\n\n";
		exit(EXIT_FAILURE);
		return;
	}
	else cout << "\n\nYour element has been found: " << a->info << "\n\n";
}

void Tree::build(int arr[], int a) {
	int b = 0;

	if (root != nullptr) {
		root = Node::Delete(root);
	}
	for (int j = 0; j < a; j++) {
		b = arr[j];
		insert(b);
	}
	return;
}

void Tree::del_comp() {
	if (root != nullptr) {
		root = Node::Delete(root);
	}
	cout << "\n\nMemory cleared!";
	return;
}

void Tree::bypass() {
	Node::Bypass(root);
	return;
}