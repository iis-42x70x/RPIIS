#include <iostream>
#include "КЧД.h"
//class Tree {
//public:
//	Node* root;
//	~Tree() {
//		deleteTree(root); 
//		delete leaf;
//	}
//
//private:
//	void deleteTree(Node* node) {
//		if (node == leaf) return; 
//		deleteTree(node->left);  
//		deleteTree(node->right); 
//		delete node;             
//	}
//}tree;
//class Node {
//public:
//	int key;
//	int info;
//	bool color;
//	Node* left;
//	Node* right;
//	Node* parent;
//
//	Node(int key, int info) {
//		this->key = key;
//		this->info = info;
//		this->color = 1;
//		this->left = leaf;
//		this->right = leaf;
//		this->parent = tree.root;
//	}
//	~Node() {
//		if (left != leaf) {
//			delete left; // Рекурсивно вызываем деструктор для левого поддерева
//		}
//		if (right != leaf) {
//			delete right; // Рекурсивно вызываем деструктор для правого поддерева
//		}
//		}
//};
////
////
//Node* leaf = new Node();//!!!!!!!!!!!!!!!!
////
////


Node* leaf = new Node(0, 0);


void Insert(Tree &tree, int key, int info) {
	if (tree.root == leaf) {
		Node* newNode = new Node(key, info);
		/*CreateNode(newNode, key, info);*/
		tree.root = newNode;
	}	
	else {
		Node* currentNode = tree.root;
		Node* parentIN = leaf;

		while (NodeExists(currentNode)) {
			parentIN = currentNode;
			if (key < currentNode->key)currentNode = currentNode->left;
			else currentNode = currentNode->right;
		}
		Node* newNode = new Node(key, info);
		/*CreateNode(newNode, key, info);*/
		newNode->parent = parentIN;
		if (key < parentIN->key)parentIN->left = newNode;
		else parentIN->right = newNode;
		balanceTree(tree, newNode);
	}
}
//void CreateNode(Node* node, int key, int info) {
//	node->parent = leaf;
//	node->left = leaf;
//	node->right = leaf;
//	node->key = key;
//	node->info = info;
//	node->color = 1;
//}
bool NodeExists(Node* node) {
	return node != leaf;
}
void balanceTree(Tree &tree, Node* newNode) {
	if (newNode == leaf || newNode == nullptr)return;
	Node* uncle;
	if(NodeExists(newNode->parent))
		if (NodeExists(newNode->parent->parent)) {
			while (newNode->parent->color == 1) {
				if (NodeExists(newNode->parent))
					if (NodeExists(newNode->parent->parent)) {
						if (newNode->parent == newNode->parent->parent->left) {
							uncle = newNode->parent->parent->right;
							if (uncle->color == 1) {
								newNode->parent->color = 0;
								uncle->color = 0;
								newNode->parent->parent->color = 1;
								newNode = newNode->parent->parent;
							}
							else {
								if (newNode == newNode->parent->right) {
									newNode= newNode->parent;
									leftRotate(tree, newNode);
								}
								newNode->parent->color = 0;
								newNode->parent->parent->color = 1;
								rightRotate(tree, newNode);
							}
						}
						else {
							uncle = newNode->parent->parent->left;
							if (uncle->color == 1) {
								newNode->parent->color = 0;
								uncle->color = 0;
								newNode->parent->parent->color = 1;
								newNode = newNode->parent->parent;
							}
							else {
								if (newNode == newNode->parent->left) {
									newNode= newNode->parent;
									rightRotate(tree, newNode);
								}
								newNode->parent->color = 0;
								newNode->parent->parent->color = 1;
								leftRotate(tree, newNode->parent->parent);
							}
						}

					}
					else break;
			}
		}
	tree.root->color = 0;
	return;
}
void swapN(Node* &a, Node* &b) {
	int a_key = a->key;
	a->key = b->key;
	b->key = a_key;
	int a_info = a->info;
	a->info = b->info;
	b->info = a_info;
}
void leftRotate(Tree &tree, Node* &newNode) {
	//Node* pivot = n->right;

	//pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
	//if (n->parent != leaf) {
	//	if (n->parent->left == n)
	//		n->parent->left = pivot;
	//	else
	//		n->parent->right = pivot;
	//}

	//n->right = pivot->left;
	//if (pivot->left != leaf)
	//	pivot->left->parent = n;

	//n->parent = pivot;
	//pivot->left = n;
	if(NodeExists(newNode->left))
	swapN(newNode, newNode->left);
	Node* buffer = newNode->left;
	newNode->left = newNode->right;
	newNode->right = newNode->left->right;
	newNode->right->parent = newNode;
	newNode->right->left = newNode->right->right;
	newNode->right->left->parent = newNode->right;
	newNode->left->right = newNode->left->left;
	newNode->left->right->parent = newNode->left;
	newNode->left->left = buffer;
	newNode->left->left->parent = newNode->left;
}
void rightRotate(Tree &tree, Node* &Nodet) {
		//Node* pivot = n->left;

		//pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
		//if (n->parent != leaf) {
		//	if (n->parent->left == n)
		//		n->parent->left = pivot;
		//	else
		//		n->parent->right = pivot;
		//}

		//n->left = pivot->right;
		//if (pivot->right != leaf)
		//	pivot->right->parent = n;

		//n->parent = pivot;
		//pivot->right = n;
	if (NodeExists(Nodet->right))
	swapN(Nodet, Nodet->right);
	Node* buffer = Nodet->right;
	Nodet->right = Nodet->left;
	Nodet->left = Nodet->right->left;
	Nodet->left->parent = Nodet;
	Nodet->right->left = Nodet->right->right;
	Nodet->right->left->parent = Nodet->right;
	Nodet->right->right = buffer;
	Nodet->right->right->parent = Nodet->right;
}
Node* search(Node* node, int key) {
	if (node == leaf) return leaf;
	if (node->key == key)return node;
	return(key < node->key ? search(node->left, key) : search(node->right, key));
}
void removeN(Tree &tree, int key) {
	Node* nodeToDelete = search(tree.root, key);
	if (nodeToDelete == leaf) return;
		bool removedNodeColor = nodeToDelete->color;
		Node* child;
		if (getChildrenCount(nodeToDelete) < 2) {
			child = getChildorMock(nodeToDelete);
			transplantNode(tree, nodeToDelete, child);
		}
		else {
			Node* minNode = getmin(nodeToDelete->right);
			nodeToDelete->key = minNode->key;
			nodeToDelete->info = minNode->info;
			removedNodeColor = minNode->color;
			child = getChildorMock(minNode);
			transplantNode(tree, minNode, child);
		}
		if (removedNodeColor == 0)fixRulesAfterRemoval(tree, child);
		delete nodeToDelete;
	
}
void fixRulesAfterRemoval(Tree &tree, Node* &node) {
while(node != tree.root && node->color == 0) { 
Node* brother; 
if(node == node->parent->left) { 
	brother = node->parent->right; 
	if (brother->color == 1) {
		brother->color = 0;
		node->parent->color = 1;
		leftRotate(tree, node->parent);
		brother = node->parent->right;
	}
	if(brother->left->color == 0 && brother->right->color == 0) { 
		brother->color = 1; 
		node = node->parent; 
	} 
	else { 
		if (brother->right->color == 0) {
			brother->left->color = 0;
			brother->color = 1;
			rightRotate(tree, brother);
			brother = node->parent->right;
		}
		brother->color = node->parent->color, 
		node->parent->color = 0; 
		brother->right->color = 0; 
		leftRotate(tree, node->parent); 
		node = tree.root; 
		} 
} 
else { 
	brother = node->parent->left; 
	if (brother->color == 1) {
		brother->color = 0;
		node->parent->color = 1;
		rightRotate(tree, node->parent);
		brother = node->parent->left;
	}
	if(brother->left->color == 0 && brother->right->color == 0) { 
		rightRotate(tree, node->parent); 
		brother = node->parent->left; 
	} 
else { 
		if (brother->left->color == 0) {
			brother->right->color = 0;
			brother->color = 1;
			leftRotate(tree, brother);
			brother = node->parent->left;
		}
		brother->color = node->parent->color;
		node->parent->color = 0; 
		brother->left->color = 0; 
		rightRotate(tree, node->parent); 
		node = tree.root; 
			} 
		} 
	} 
node->color = 0; 
	}
void transplantNode(Tree &tree, Node* &toNode, Node* &fromNode) {
	if (toNode == tree.root)tree.root = fromNode;
	else if (toNode == toNode->parent->left)toNode->parent->left = fromNode;
	else toNode->parent->right = fromNode;
	fromNode->parent = toNode->parent;
	return;
}
int getChildrenCount(Node* node) {
	int count = 0;
	if (NodeExists(node->left))count += 1;
	if (NodeExists(node->right))count += 1;
	return count;
}
Node* getmin(Node* node) {
	if (node == leaf) return leaf;
	if (node->left == leaf)return node;
	return getmin(node->left);
}
Node* getmax(Node* node) {
	if (node == leaf) return leaf;
	if (node->right == leaf)return node;
	return getmax(node->right);
}
Node* getChildorMock(Node* node) {
	return NodeExists(node->left) ? node->left : node->right;
}
int kolvoNodes(Node* node,int &kolvo) {
	if (node == leaf) return kolvo;
	kolvo++;
	kolvoNodes(node->left,kolvo);
	kolvoNodes(node->right,kolvo);
}
int* keymass(Node* node,int* &mass, int &kolvo) {
	if (node == leaf)return mass;
	keymass(node->left, mass, kolvo);
	mass[kolvo] = node->info;
	kolvo--;
	keymass(node->right, mass, kolvo);
}
int searchfor(Node* node, int key, int kakoi) {
	Node* iskomoe = search(node, key);
	int kolvo = 0;
	kolvo = kolvoNodes(tree.root, kolvo);
	int* mass = new int(kolvo);
	int kol = kolvo;
	mass = keymass(node, mass, kolvo);
	int helpp;
	if (kakoi) {
		for (int i = kol; i > 0; i--) 
			if (key < mass[i]) helpp = mass[i];
			delete[] mass;
			return helpp;
		
	}
	else {
		for (int i = 0; i < kol; i++) 
			if (key >= mass[i]) helpp = mass[i];
			delete[] mass;
			return helpp;
		
	}
}
void printTree(Node* node) {
	if (node == leaf) return;
	printTree(node->left);
	std::cout << node->info << " ";
	printTree(node->right);
}
int main() {
	
	int kod,key,kolvo; 
	leaf->color = 0;
	leaf->right = nullptr;
	leaf->left = nullptr;
	leaf->parent =nullptr;
	tree.root = leaf;
	while (true) {
		std::cout << "\n\tVvedite zapros:\n\tdobavit` element(-y) -1\n\tFind element po key - 2\n\tUdalt` element po key - 3\n\tFind max element - 4\n\t Find min element - 5\n\tFind max blijh element - 6\n\tFind min blijh element - 7\n\tObhod dereva sleva na pravo - 8\n\tZakryt program - 9\n\t";
		std::cin >> kod;
		switch (kod) {
		case 1:
			std::cout << "vvedite kolvo elementov: ";
			std::cin >> kolvo;
			for (int i = 0; i < kolvo; i++) {
				std::cout << std::endl << "vvedite key i information: ";
				std::cin >> key;
				Insert(tree, key, key);
			}
			break;

		case 2:
			if (NodeExists(tree.root)) {
				std::cout << std::endl << "vvedite Key: ";
				std::cin >> key;
				std::cout << std::endl << search(tree.root, key);
			}
			else
				std::cout << std::endl << "derevo pysto yoy";
			break;
		case 3:
			if (NodeExists(tree.root)) {
				std::cout << std::endl << "vvedite Key: ";
				std::cin >> key;
				removeN(tree, key);
			}
			else
				std::cout << std::endl << "derevo pysto yoy";
			break;
		case 4:
			if (NodeExists(tree.root)) {
			std::cout << std::endl << (getmax(tree.root))->key;
			}
			else
				std::cout << std::endl << "derevo pysto yoy";
			break;
		case 5:
			if (NodeExists(tree.root)) {
			std::cout << std::endl << (getmin(tree.root))->key;
			}
			else
				std::cout << std::endl << "derevo pysto yoy";
			break;
		case 6:
			if (NodeExists(tree.root)) {
				std::cout << std::endl<<"vvedite key elementa otnosit kotorogo iskat`"; std::cin >> key;
			std::cout << std::endl << searchfor(tree.root,key,1);
			}
			else
				std::cout << std::endl << "derevo pysto yoy";
			break;
		case 7:
			if (NodeExists(tree.root)) {
				std::cout << std::endl << "vvedite key elementa otnosit kotorogo iskat`"; std::cin >> key;
			std::cout << std::endl << searchfor(tree.root, key, 0);
			}
			else
				std::cout << std::endl << "derevo pysto yoy";
			break;
		case 8:
			std::cout << "\nDerevo:\n";
			printTree(tree.root);
			break;
		case 9:
			return -105;
		}
		
	}
}