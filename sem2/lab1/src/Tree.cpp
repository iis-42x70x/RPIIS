#include "../libs/Tree.h"
#include <iostream>

using namespace std;

Node::~Node (){
	delete tl;
	delete bl;
	delete br;
	delete tr;
	
}


Node::Node (int val, bool stat){
	value = val;
	IsLeaf = stat;
	tl = NULL;
	bl = NULL;
	br = NULL;
	tr = NULL;
}

 bool Tree::IsSame (int** matrix, int startx, int endx, int starty, int endy){
	int value = matrix[startx][starty];
	for(int i = startx; i<endx; i++){
		for(int j = starty; j<endy; j++){
			if(matrix[i][j]!=value){
				return false;
			}
		}
	}
	return true;
}
 Node* Tree::buildTree (int** matrix, int startx, int endx, int starty, int endy, const string name, int depth){
	//for(int i = 0; i<depth; i++)
		//cout << " ";
	
	//cout << "depth: " << depth << " " << name;
	if(IsSame(matrix, startx, endx, starty, endy)){
		//cout << "Same, val = " << matrix[startx][starty] << "\n";
		return new Node(matrix[startx][starty], true);
	}

	//cout << "not same, devides\n"; 
	
	int midx = (startx + endx)/2;
	int midy = (starty + endy)/2;

	Node* node = new Node(0, false);
	node->tl = buildTree(matrix, startx, midx, starty, midy, "tl: ", depth+1);
	node->bl = buildTree(matrix, midx, endx, starty, midy, "bl: ", depth+1);
	node->br = buildTree(matrix, midx, endx, midy, endy, "br: ", depth+1);
	node->tr = buildTree(matrix, startx, midx, midy, endy, "tr: ", depth+1);
	return node;	
}

 void Tree::buildMatrix (Node* root, int** matrix, int startx, int endx, int starty, int endy){
	if(root->IsLeaf){
		for(int i = startx; i<endx; i++){
			for(int j = starty; j<endy; j++){
				matrix[i][j] = root->value;
			}
		}
		return;
	}
	 
	int midx = (startx+endx)/2;
	int midy = (starty+endy)/2;

	buildMatrix(root->tl, matrix, startx, midx, starty, midy);
	buildMatrix(root->bl, matrix, midx, endx, starty, midy);
	buildMatrix(root->br, matrix, midx, endx, midy, endy);
	buildMatrix(root->tr, matrix, startx, midx, midy, endy);
}

 void Tree::deleteTree (Node* root){
	if(root == nullptr) return;
	delete root;
}

 void Tree::printTree (Node* root, int depth){
	if(!root) return;

	for(int i = 0; i < depth; i++)
		cout << " ";
	if(root->IsLeaf){
		cout << "leaf: value - " << root->value << endl;
	}else{
		cout << "node devided\n";

		for(int i = 0; i<depth+1; i++) 
			cout << " ";
		cout << "1: \n";
		printTree(root->tl, depth+2);

		for(int i = 0; i<depth+1; i++) 
			cout << " ";
		cout << "2: \n";
		printTree(root->bl, depth+2);

		for(int i = 0; i<depth+1; i++) 
			cout << " ";
		cout << "3: \n";
		printTree(root->br, depth+2);

		for(int i = 0; i<depth+1; i++) 
			cout << " ";
		cout << "4: \n";
		printTree(root->tr, depth+2);
	}
}

