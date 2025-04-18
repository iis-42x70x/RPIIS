#include <iostream>
#include <string>
#include "../libs/Tree.h"

using namespace std;

bool ispowertwo(int n){
	return (n>0)&&((n&(n-1))==0);
}

void printMatrix(int** matrix, int n){
	for(int i = 0; i<n;i++){
		for(int j = 0; j<n; j++){
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int main(){
	int n;
	cout << "Введите размер матрицы nxn: ";
	cin >> n;
	if(!ispowertwo(n)){
		while(!ispowertwo(n)){
			cout << "Введите размер матрицы nxn: ";
			cin >> n;
		}
	}

	int **matrix = new int* [n];
	for(int i = 0; i<n;i++)
		matrix[i]=new int[n];
	
	
	cout << "Введите элементы матрицы: \n";
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			cin >> matrix[i][j];
		}
	}
	cout << endl;
	Node* root = Tree::buildTree(matrix, 0, n, 0, n, "Node: ", 1);

	Tree::printTree(root, n);

	int **newmatrix = new int* [n];
	for(int i = 0; i<n;i++)
		newmatrix[i]=new int[n];

	Tree::buildMatrix(root, newmatrix, 0, n, 0, n);

	cout << "New matrix: "<< root->IsLeaf << "\n";

	printMatrix(newmatrix, n);

	for(int i = 0; i<n; i++){
		delete [] matrix[i];
		delete [] newmatrix[i];
	}

	delete [] newmatrix;
	delete [] matrix;

	Tree::deleteTree(root);

	return 0;
}
