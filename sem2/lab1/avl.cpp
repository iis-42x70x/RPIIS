#include "AVL.h"
#include <algorithm>
template<typename keyType, typename dataType>
AVL<keyType, dataType>::AVL() {
	size = 0;
	root = nullptr;
}


template<typename keyType, typename dataType>
int AVL<keyType, dataType>::getSize() const { return size; }

template<typename keyType, typename dataType>
AVL<keyType, dataType>::~AVL() { clear(); }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename keyType, typename dataType>
int AVL<keyType, dataType>::height(Node<keyType, dataType>* node) {
	return node ? max(height(node->pLeft), height(node->pRight)) + 1 : 0;
}

template<typename keyType, typename dataType>
int AVL<keyType, dataType>::getBalanceFactor(Node<keyType, dataType>* node) {
	return node ? height(node->pLeft) - height(node->pRight) : 0;
}

template<typename keyType, typename dataType>
typename AVL<keyType, dataType>::Node<keyType, dataType>* AVL<keyType, dataType>::rotateLeft(Node<keyType, dataType>* node) {
	Node<keyType, dataType>* rightNode = node->pRight;
	node->pRight = rightNode->pLeft;
	rightNode->pLeft = node;
	return rightNode;
}

template<typename keyType, typename dataType>
typename AVL<keyType, dataType>::Node<keyType, dataType>* AVL<keyType, dataType>::rotateRight(Node<keyType, dataType>* node) {
	Node<keyType, dataType>* leftNode = node->pLeft;
	node->pLeft = leftNode->pRight;
	leftNode->pRight = node;
	return leftNode;
}

template<typename keyType, typename dataType>
typename AVL<keyType, dataType>::Node<keyType, dataType>* AVL<keyType, dataType>::balance(Node<keyType, dataType>* node) {
	int balanceFactor = getBalanceFactor(node);

	if (balanceFactor > 1) {
		if (getBalanceFactor(node->pLeft) < 0) {
			node->pLeft = rotateLeft(node->pLeft);
		}
		return rotateRight(node);
	}

	if (balanceFactor < -1) {
		if (getBalanceFactor(node->pRight) > 0) {
			node->pRight = rotateRight(node->pRight);
		}
		return rotateLeft(node);
	}

	return node;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template<typename keyType, typename dataType>
void AVL<keyType, dataType>::insert(keyType key, dataType data) {
	if (size == 0) {
		root = new Node<keyType, dataType>(key, data);
		size++;
		return;
	}
	Node<keyType, dataType>* current = root;
	while (current != nullptr) {
		if (key < current->key) {
			if (current->pLeft == nullptr) {
				current->pLeft = new Node<keyType, dataType>(key, data);
				size++;
				break;
			}
			current = current->pLeft;
		}
		else if (key > current->key) {
			if (current->pRight == nullptr) {
				current->pRight = new Node<keyType, dataType>(key, data);
				size++;
				break;
			}
			current = current->pRight;
		}
		else {
			cout << "Key " << key << " already exists in the tree." << endl;
			return;
		}
	}
	root = balance(root);
}

template<typename keyType, typename dataType>
dataType AVL<keyType, dataType>::getDataAt(keyType key) const {
	const Node<keyType, dataType>* current = root;

	while (current != nullptr) {
		if (current->key == key) { return current->data; }
		current = (key > current->key) ? current->pRight : current->pLeft;
	}
	cout << "Key " << key << " wasn't found in the tree." << endl;
	return dataType{};
}

template<typename keyType, typename dataType>
void AVL<keyType, dataType>::deleteAt(keyType key) {
	Node<keyType, dataType>* current = root;
	Node<keyType, dataType>* preCurrent = nullptr;
	bool isCurrentLeft = false;

	while (current != nullptr && current->key != key) {
		preCurrent = current;
		if (current->key > key) {
			current = current->pLeft;
			isCurrentLeft = true;
		}
		else {
			current = current->pRight;
			isCurrentLeft = false;
		}
	}

	if (current == nullptr) {
		cout << "Key " << key << " wasn't found in the tree." << endl;
		return;
	}

	if (current->pLeft != nullptr && current->pRight != nullptr) {
		Node<keyType, dataType>* replace = current->pLeft;
		Node<keyType, dataType>* preReplace = current;

		while (replace->pRight != nullptr) {
			preReplace = replace;
			replace = replace->pRight;
		}

		if (preReplace != current) {
			preReplace->pRight = replace->pLeft;
			replace->pLeft = current->pLeft;
		}
		replace->pRight = current->pRight;

		if (preCurrent == nullptr) { root = replace; }
		else if (isCurrentLeft) { preCurrent->pLeft = replace; }
		else { preCurrent->pRight = replace; }
	}
	else {
		Node<keyType, dataType>* child = (current->pLeft != nullptr) ? current->pLeft : current->pRight;
		if (preCurrent == nullptr) { root = child; }
		else if (isCurrentLeft) { preCurrent->pLeft = child; }
		else { preCurrent->pRight = child; }
	}
	delete current;
	size--;
	root = balance(root);
}

template<typename keyType, typename dataType>
void AVL<keyType, dataType>::printPreOrder() const {
	if (root == nullptr) {
		cout << "AVL is empty" << endl;
		return;
	}
	cout << "Key: " << root->key << " Data: " << root->data << endl;
	printPreOrderRecursive(root->pLeft);
	printPreOrderRecursive(root->pRight);
}

template<typename keyType, typename dataType>
void AVL<keyType, dataType>::printPreOrderRecursive(Node<keyType, dataType>* currentNode) const {
	if (currentNode == nullptr) return;
	cout << "Key: " << currentNode->key << " Data: " << currentNode->data << endl;
	printPreOrderRecursive(currentNode->pLeft);
	printPreOrderRecursive(currentNode->pRight);
}

template<typename keyType, typename dataType>
void AVL<keyType, dataType>::printPostOrder() const {
	if (root == nullptr) {
		cout << "AVL is empty" << endl;
		return;
	}
	printPostOrderRecursive(root);
}

template<typename keyType, typename dataType>
void AVL<keyType, dataType>::printPostOrderRecursive(Node<keyType, dataType>* currentNode) const {
	if (currentNode == nullptr) return;
	printPostOrderRecursive(currentNode->pLeft);
	printPostOrderRecursive(currentNode->pRight);
	cout << "Key: " << currentNode->key << " Data: " << currentNode->data << endl;
}

template<typename keyType, typename dataType>
void AVL<keyType, dataType>::printInOrder() const {
	if (root == nullptr) {
		cout << "AVL is empty" << endl;
		return;
	}
	printInOrderRecursive(root);
}

template<typename keyType, typename dataType>
void AVL<keyType, dataType>::printInOrderRecursive(Node<keyType, dataType>* currentNode) const {
	if (currentNode == nullptr) return;
	printInOrderRecursive(currentNode->pLeft);
	cout << "Key: " << currentNode->key << " Data: " << currentNode->data << endl;
	printInOrderRecursive(currentNode->pRight);
}

template<typename keyType, typename dataType>
void AVL<keyType, dataType>::clear() {
	clearRecursive(root);
	root = nullptr;
	size = 0;
}

template<typename keyType, typename dataType>
void AVL<keyType, dataType>::clearRecursive(Node<keyType, dataType>*& currentNode) {
	if (currentNode == nullptr) { return; }
	clearRecursive(currentNode->pLeft);
	clearRecursive(currentNode->pRight);
	delete currentNode;
	currentNode = nullptr;
}

template<typename keyType, typename dataType>
keyType AVL<keyType, dataType>::getMax() const {
	if (size == 0) {
		cout << "Tree is empty!" << endl;
		return keyType{};
	}
	Node<keyType, dataType>* current = root;
	while (current->pRight != nullptr) { current = current->pRight; }
	return current->key;
}

template<typename keyType, typename dataType>
keyType AVL<keyType, dataType>::getMin() const {
	if (size == 0) {
		cout << "Tree is empty!" << endl;
		return keyType{};
	}
	Node<keyType, dataType>* current = root;
	while (current->pLeft != nullptr) { current = current->pLeft; }
	return current->key;
}

template<typename keyType, typename dataType>
keyType AVL<keyType, dataType>::getNearestMax(keyType key) const {
	if (size == 0) {
		cout << "Tree is empty!" << endl;
		return keyType{};
	}
	Node<keyType, dataType>* current = root;
	keyType nearestMax = keyType{};
	bool isFound = false;

	while (current != nullptr) {
		if (key < current->key) {
			nearestMax = current->key;
			isFound = true;
			current = current->pLeft;
		}
		else { current = current->pRight; }
	}
	if (!isFound) {
		cout << "No greater key found for " << key << endl;
		return keyType{};
	}

	return nearestMax;
}

template<typename keyType, typename dataType>
keyType AVL<keyType, dataType>::getNearestMin(keyType key) const {
	if (size == 0) {
		cout << "Tree is empty!" << endl;
		return keyType{};
	}
	Node<keyType, dataType>* current = root;
	keyType nearestMin = keyType{};
	bool isFound = false;

	while (current != nullptr) {
		if (current->key < key) {
			nearestMin = current->key;
			isFound = true;
			current = current->pRight;
		}
		else { current = current->pLeft; }
	}
	if (!isFound) {
		cout << "No smaller key found for " << key << endl;
		return keyType{};
	}

	return nearestMin;
}