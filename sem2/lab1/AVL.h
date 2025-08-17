#pragma once
template<typename keyType, typename dataType>
class AVL
{
public:
	AVL();
	~AVL();
	int getSize() const;
	void insert(keyType key, dataType data);
	dataType getDataAt(keyType key) const;
	void deleteAt(keyType key);
	void printPreOrder() const;
	void printPostOrder() const;
	void printInOrder() const;
	keyType getMax() const;
	keyType getMin() const;
	keyType getNearestMax(keyType key) const;
	keyType getNearestMin(keyType key) const;
	void clear();
private:
	template<typename keyType, typename dataType>
	class Node {
	public:
		Node* pLeft;
		Node* pRight;
		keyType key;
		dataType data;

		Node(keyType key = keyType(), dataType data = dataType(), Node* pLeft = nullptr, Node* pRight = nullptr) {
			this->key = key;
			this->data = data;
			this->pLeft = pLeft;
			this->pRight = pRight;
		}
	};
	int size;
	Node<keyType, dataType>* root;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Node<keyType, dataType>* balance(Node<keyType, dataType>* node);
	Node<keyType, dataType>* rotateLeft(Node<keyType, dataType>* node);
	Node<keyType, dataType>* rotateRight(Node<keyType, dataType>* node);
	int height(Node<keyType, dataType>* node);
	int getBalanceFactor(Node<keyType, dataType>* node);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void printPreOrderRecursive(Node<keyType, dataType>* currentNode) const;
	void printPostOrderRecursive(Node<keyType, dataType>* currentNode) const;
	void printInOrderRecursive(Node<keyType, dataType>* currentNode) const;
	void clearRecursive(Node<keyType, dataType>*& currentNode);
};
#include "AVL.cpp"