#pragma once
class Node; // Предварительное объявление класса Node
extern Node* leaf;
class Node {
public:
	int key;
	int info;
	bool color;
	Node* left;
	Node* right;
	Node* parent;

	Node(int key, int info) {
		std::cout << "sozdan uzel: " << key << std::endl;
		this->key = key;
		this->info = info;
		this->color = 1;
		this->left = leaf;
		this->right = leaf;
		this->parent = leaf;
	}
	~Node() {
		std::cout << "udalen uzel: " << key << std::endl;
	}
};
class Tree {
public:
	Node* root;
	Tree() {
		tree.root = leaf;
	}
	~Tree() {
		deleteTree(root);
		delete leaf;
	}

private:
	void deleteTree(Node* node) {
		if (node == leaf||node==NULL||node==nullptr) return;
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
}tree;
void Insert(Tree &tree, int key, int info);
//void CreateNode(Node* node, int key, int info);
bool NodeExists(Node* node);
void balanceTree(Tree &tree, Node* newNode);
void swapN(Node* &a, Node* &b);
void leftRotate(Tree &tree, Node* &Nodet);
void rightRotate(Tree &tree, Node* &newNode);
Node* search(Node* node, int key);
void removeN(Tree &tree, int key);
int getChildrenCount(Node* node);
Node* getmin(Node* node);
Node* getmax(Node* node);
void transplantNode(Tree &tree, Node* &toNode, Node* &fromNode);
Node* getChildorMock(Node* node);
void fixRulesAfterRemoval(Tree &tree, Node* node);
void keymass(Node* node, int*& mass, int &kolvo);
void kolvoNodes(Node* node, int& kolvo);
int searchfor(Node* node, int key, int kakoi);
void printTree(Node* node);
