#include "pch.h"
#include "C:\Users\boyarskiu\source\repos\Красно-черное дерево\Красно-черное дерево\КЧД.cpp"

TEST(Testinsert, TestInsert) {
	leaf->color = 0;
	leaf->right = leaf;
	leaf->left = leaf;
	leaf->parent =leaf;
	tree.root = leaf;
    for (int i = 1; i <= 10; i++) 
		Insert(tree, i, i);
	int kolvo = 0;
	kolvoNodes(tree.root, kolvo);
	int* mass = new int[kolvo];
	/*int kol = 9;*/
	keymass(tree.root, mass, kolvo);
	int* massETAL = new int[10];
	for (int i = 10; i >= 1; i--)
		massETAL[10-i] = i;
	massETAL[1] = 8;
	massETAL[2] = 9;
	for (int i = 0; i < 10; i++) {
		EXPECT_EQ(massETAL[i], mass[i]);
		EXPECT_TRUE(true);
	}
	delete[] mass;
	delete[] massETAL;
}
TEST(Testinsert, testSearch) {
	//leaf->color = 0;
	//leaf->right = leaf;
	//leaf->left = leaf;
	//leaf->parent = leaf;
	//tree.root = leaf;
	//for (int i = 1; i <= 10; i++)
	//	Insert(tree, i, i);
	int key;
	std::cout << "Ojhidaemoe znachenie elementa ot 1 do 10: ";
	std::cin >> key;
	EXPECT_EQ(key,(search(tree.root,key))->key);
	EXPECT_TRUE(true);
}
TEST(Testinsert, testmaxMin) {
	EXPECT_EQ(10, (getmax(tree.root))->key);
	EXPECT_TRUE(true);
	EXPECT_EQ(1, (getmin(tree.root))->key);
	EXPECT_TRUE(true);
}
TEST(Testudalenie, testudal) {
	int key=4;
	std::cout << std::endl << "Key ojidaemo udalaemogo: 4 ";
	removeN(tree, key);
	int kolvo = 0;
	kolvoNodes(tree.root, kolvo);
	int* mass = new int[kolvo];
	keymass(tree.root, mass, kolvo);
	for (int i = 0; i < 9; i++) {
		EXPECT_NE(key, mass[i]);
		EXPECT_TRUE(true);
	}
	delete[] mass;
}
TEST(Testudalenie, testbalance) {
	int* massETAL = new int[9];
	for (int i = 9; i>=4; i--) {
			massETAL[9-i] = i+1;
	}
	massETAL[1] = 10;
	massETAL[0] = 9;
	for (int i = 3; i >0; i--) {
		massETAL[9 - i] = i;
	}
	int kolvo = 0;
	kolvoNodes(tree.root, kolvo);
	int* mass = new int[kolvo];
	keymass(tree.root, mass, kolvo);
	for (int i = 0; i < 9; i++) {
		EXPECT_EQ(massETAL[i], mass[i]);
		EXPECT_TRUE(true);
	}
	delete[] mass;
	delete[] massETAL;
}
TEST(Testzadanie, testmaxMin) {
	Insert(tree, 4, 4);
	int key;
	std::cout <<'\n'<< "vvedite znachenie ot 1 do 10 otnosit kotorogo ojidaetsa poisk: ";
	std::cin >> key;
	EXPECT_EQ(key+1, searchfor(tree.root,key,1));
	EXPECT_TRUE(true);
	EXPECT_EQ(key-1, searchfor(tree.root, key, 0));
	EXPECT_TRUE(true);
}