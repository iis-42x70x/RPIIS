#include "Node.h"

Node::Node(int value) {
	info = value;
	right = nullptr;
	left = nullptr;
}

Node* Node::Leaf(int value) {
	Node* a = new Node(value);
	a->info = value;
	a->left = a->right = nullptr;
	return a;
}

Node* Node::Show(Node* a, int b) {
	if (a == nullptr) return a;

	Show(a->right, b + 1);
	cout << setw(b* 4) << " " << a->info << endl;
	Show(a->left, b + 1);

	return a;
}

Node* Node::Pop(Node* root, int value) {
	Node* r = nullptr, * prev_r = nullptr, * del = root, * prev_del = nullptr;

	while (del != nullptr && del->info != value) {
		prev_del = del;
		if (del->info < value) del = del->right;
		else del = del->left;
	}
	if (del == nullptr) {
		cout << "\n\nThe element is missing!\n\n";
		exit(EXIT_FAILURE);
		return root;
	}
	if (del->right == nullptr && del->left != nullptr) r = del->left;
	else if (del->left == nullptr && del->right != nullptr) r = del->right;
	else if (del->left == nullptr && del->right == nullptr) {
		Node* a = del;
		if (del = prev_del->left) {
			delete a;
			prev_del->left = nullptr;
			return root;
		}
		else if (del = prev_del->right) {
			delete a;
			prev_del->right = nullptr;
			return root;
		}
	}
	else {
		prev_r = del;
		r = del->left;
		while (r->right != nullptr) {
			prev_r = r;
			r = r->right;
		}
		if (prev_r == del) r->right = del->right;
		else {
			r->right = del->right;
			prev_r->right = r->left;
			r->left = prev_r;
		}
	}
	if (del == root) root = r;
	else if (del->info < prev_del->info) prev_del->left = r;
	else prev_del->right = r;
	delete del;
	return root;
}

bool Node::Sort(Node* root, int value) {
	Node* a = root;
	bool isTrue = true;
	while (a != nullptr && a->info != value) {
		if (value > a->info) a = a->right;
		else a = a->left;
	}
	if (a != nullptr) {
		isTrue = false;
		return isTrue;
	}
	return isTrue;
}

Node* Node::Delete(Node* root) {
	if (root = nullptr) {
		cout << "\n\nThe memory is clear!\n\n";
		return nullptr;
	}
	else {
		while (root != nullptr) {
			Delete(root->left);
			Delete(root->right);
			delete root;
		}
	}
	return nullptr;
}

void Node::Bypass(Node* root) {
	Node* a = root;
	if (a == nullptr) return;

	Bypass(a->left);
	cout << "[" << a->info << "]" << " ";
	Bypass(a->right);

	return;
}