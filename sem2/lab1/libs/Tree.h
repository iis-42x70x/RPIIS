#ifndef TREE_H
#define TREE_H
#include <string>

using namespace std;

struct Node{
	int value;
	bool IsLeaf;
	Node* tl;
	Node* bl;
	Node* br;
	Node* tr;
	Node(int val, bool stat);
	~Node();
};

class Tree{
public:
	static bool IsSame(int** matrix, int startx, int endx, int starty, int endy);

	static Node* buildTree(int** matrix, int startx, int endx, int starty, int endy, const string name, int depth);
	
	static void buildMatrix(Node* root, int** matrix, int startx, int endx, int starty, int endy);

	static void deleteTree(Node* root);

	static void printTree(Node* root, int depth);
};
#endif
