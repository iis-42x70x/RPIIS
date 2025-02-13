#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Node//класс для хранения символов и указателей на другие узлы
{
public:
	vector<Node*> front_ptrs = { nullptr };// вектор указателей на дочерние узлы
	Node* back_ptr;//указатель на родительский узел
	char c;//символ в узле
	int num = 0;
	bool is_root = false;//является узел ли корнем
	bool terminal = false;

	Node();
	Node(char c);
	Node(Node* p);
};