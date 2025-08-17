#include <iostream>
// #include <googletest/googlemock/include/gmock/gmock.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../libs/Tree.h"

using namespace std;

TEST(QuadTree, IsEquals){
	int n = 2;
	int **matrix = new int*[n];
	for(int i = 0; i<n; i++){
		matrix[i] = new int[n];
		for(int j = 0; j<n; j++){
			matrix[i][j] = 1;
		}
	}

	ASSERT_TRUE(Tree::IsSame(matrix, 0, n, 0, n));

	for(int i = 0; i<n; i++)
		delete [] matrix[i];
	delete [] matrix;
};

TEST(QuadTree, CreateNode){
	Node node(5, true);
	EXPECT_EQ(node.value, 5);
	EXPECT_TRUE(node.IsLeaf);
}

TEST(QuadTree, BuildTree){
	int n = 2;
	int **matrix = new int*[n];
	for(int i = 0; i<n; i++){
		matrix[i] = new int[n];
	}

	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[1][0] = 1;
	matrix[1][1] = 1;

	Node* root = Tree::buildTree(matrix, 0, n, 0, n, "Root: ", 1);

	EXPECT_FALSE(root->IsLeaf);

	EXPECT_EQ(root->tl->value, 1);
	EXPECT_EQ(root->tr->value, 0);
	EXPECT_EQ(root->br->value, 1);
	EXPECT_EQ(root->bl->value, 1);

	for(int i = 0; i<n; i++)
		delete [] matrix[i];
	delete [] matrix;

	Tree::deleteTree(root);
};


TEST(QuadTree, deleteTree){
	int n = 2;
	int **matrix = new int*[n];
	for(int i = 0; i<n; i++){
		matrix[i] = new int[n];
	}

	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[1][0] = 1;
	matrix[1][1] = 1;

	Node* root = Tree::buildTree(matrix, 0, n, 0, n, "Root: ", 1);

	for(int i = 0; i<n; i++)
		delete [] matrix[i];
	delete [] matrix;

	EXPECT_NO_THROW(Tree::deleteTree(root));
};



TEST(QuadTree, buildMatrix){
	int n = 2;
	int **matrix = new int*[n];
	for(int i = 0; i<n; i++){
		matrix[i] = new int[n];
	}

	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[1][0] = 1;
	matrix[1][1] = 1;

	Node* root = Tree::buildTree(matrix, 0, n, 0, n, "Root: ", 1);

	int **newmatrix = new int*[n];
	for(int i = 0; i<n; i++){
		newmatrix[i] = new int[n];
	}
	
	Tree::buildMatrix(root, newmatrix, 0, n, 0, n);
	
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			EXPECT_EQ(matrix[i][j], newmatrix[i][j]);
		}
	}

	for(int i = 0; i<n; i++){
		delete [] matrix[i];
		delete [] newmatrix[i];
	}
	delete [] newmatrix;
	delete [] matrix;

	Tree::deleteTree(root);
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
   	return RUN_ALL_TESTS();
}
