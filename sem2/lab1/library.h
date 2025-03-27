#include <sstream>
#include <queue>
#include <iostream>

#ifndef LIBRARY_H
#define LIBRARY_H

using namespace std;

// класс узла В-дерева
class BTreeNode
{
	int* keys; // Массив ключей
	int t;	 // параметр дерева (от него зависит кол-во ключей в узле и кол-во потомков узла)
	BTreeNode** C; // Массив указателей на детей
	int n;	 // Текущее количество ключей
	bool leaf; // Истина, когда узел является листовым

public:

	BTreeNode(int _t, bool _leaf); // Констурктор

	// Функция для поиска ключа в поддереве, корнем которого является этот узел.
	BTreeNode* search_key(int k); // возвращает NULL, если k отсутствует.

	// Вспомогательна функция, которая возвращает индекс первого ключа, который больше или равно k
	int findKey(int k);

	// Вспомогательная функция для вставки нового ключа в поддерево с корнем
	// этот узел. Предполагается, что узел должен быть неполным, когда это функция вызывается
	void insertNonFull(int k);

	// Вспомогательная функция для разделения ребенка y этого узла.
	//  Ребенок должен быть заполненным, когда эта функция вызывается
	void splitChild(int i, BTreeNode* y);

	// Функция для удаления ключа k в поддереве с корнем этот узел.
	void delete_key(int k);

	// Вспомогательная функция для удаления ключа, стоящего на idx-й позиции узла, который является листом
	void delete_from_leaf(int idx);

	// Вспомогательная функция для удаления ключа, стоящего на idx-й позиции узла, который не является листом
	void delete_from_nonleaf(int idx);

	// Функция для получения предшественника ключа, где ключ стоит на idx-й позиции узла
	int getPred(int idx);

	// Функция для получения преемника ключа, где ключ стоит на idx-й позиции узла
	int getSucc(int idx);

	// Функция для заполнения дочернего узла, стоящего на idx-ой позиции в массиве C[], если у этого дочернего элемента меньше t-1 ключей
	void fill(int idx);

	// Функция для заимствования ключа из C[idx-1]-го узла и размещения это в C[idx]-м узле
	void borrowFromPrev(int idx);

	// Функция для заимствования ключа из C[idx+1]-го узла и размещения его в C[idx]-м узле
	void borrowFromNext(int idx);

	// Функция слияния idx-го дочернего узла с (idx+1)-м дочерним элементом узла узел
	void merge(int idx);

        // Деструктор
        ~BTreeNode();

	friend class BTree;
	friend class PrettyPrint;
};

class BTree
{
	BTreeNode* root; // Указатель на корень
	int t; // параметр дерева
public:

	// Конструктор (инициализирует дерево как пустое)
	BTree(int _t)
	{
		root = NULL;
		t = _t;
	}

	//Главная функция для поиска ключа в этом дереве
	BTreeNode* search_key(int k)
	{
		return (root == NULL) ? NULL : root->search_key(k);
	}

	// Основная функция вставки нового ключа в B-дерево
	void insert_key(int k);

	// Основная функция удаления ключа в B-дереве
	void delete_key(int k);

        // Деструктор
        ~BTree();

	friend class PrettyPrint;
};

//Создаем класс, который поможет нам красивенько вывести дерево :)
class PrettyPrint
{
	//Создаем внутреннюю структуру, используемую для хранения информации о каждом узле в дереве
	struct NodeInfo
	{
		string text; //текстовое представление ключей узла
		unsigned text_pos, text_end;
	};

	typedef vector<NodeInfo> LevelInfo;

	vector<LevelInfo> levels;

	//Функция для представления ключей узла в виде строки.
	string node_text(int const keys[], unsigned key_count);

	void before_traversal()
	{
		levels.resize(0);
		levels.reserve(10);
	}

	//Функция для рекурсивного обхода узлов B-дерева и сбора информации о каждом узле для последующей печати.
	void visit(BTreeNode const* node, unsigned level = 0, unsigned child_index = 0);

	//Функция для завершения обхода дерева и печати собранной информации об узлах
	void after_traversal();

public:

	//сама печать
	void print(BTree const& tree)
	{
		before_traversal();
		visit(tree.root);
		after_traversal();
	}
};

#endif