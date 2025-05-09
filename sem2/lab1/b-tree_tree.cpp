#include "library.h"
#include <iostream>

using namespace std;

//Функция для рекурсивного обхода узлов B-дерева и сбора информации о каждом узле для последующей печати.
void PrettyPrint::visit(BTreeNode const* node, unsigned level, unsigned child_index)
{
	//Проверяем, есть ли информация о текущем уровне дерева в векторе levels. Если нет, то уровень увеличивается до уровня level + 1.
	if (level >= levels.size())
		levels.resize(level + 1);

	//Создаем новаую структуру NodeInfo для текущего узла. Позиция текста устанавливается в 0. 
	// Если уровень не пустой, то позиция текста выставляется после последнего узла уровня с учетом разделителей (пустых пространств) между узлами. 
	// Если текущий узел является самым левым дочерним узлом, добавляется дополнительное пустое пространство.
	LevelInfo& level_info = levels[level];
	NodeInfo info;

	info.text_pos = 0;
	if (!level_info.empty())  // один пробел между узлами, один дополнительный пробел, если самый левый дочерний элемент
		info.text_pos = level_info.back().text_end + (child_index == 0 ? 2 : 1);

	info.text = node_text(node->keys, unsigned(node->n));

	//Проверка, является ли текущий узел листовым. Если да, то text_end устанавливается как позиция текста плюс длина текста узла.
	if (node->leaf)
	{
		info.text_end = info.text_pos + unsigned(info.text.length());
	}
	else // Иначе рекурсивно вызывается visit() для всех его детей. При этом уровень увеличивается на 1, а индекс дочернего узла обновляется.
		 //После завершения обхода всех детей text_end устанавливается как text_end последнего узла уровня выше.
	{
		for (unsigned i = 0, e = unsigned(node->n); i <= e; ++i)  // на один указатель больше, чем ключей
			visit(node->C[i], level + 1, i);

		info.text_end = levels[level + 1].back().text_end;
	}

	levels[level].push_back(info);
}

//Функция для представления ключей узла в виде строки
string PrettyPrint::node_text(int const keys[], unsigned key_count)
{
	ostringstream os;//Создаем объект os, который используется для формирования строки
	string sep = ""; //Устанавливаем начальное значение разделителя sep как пустая строка

	//Проходим по всем ключам
	os << "[";
	for (unsigned i = 0; i < key_count; ++i) {
		os << sep << keys[i];
		sep = " ";
	}
	os << "]";

	return os.str();
}

//Просто выводит пробелы для выравнивания уровней
void print_blanks(unsigned n)
{
	while (n--)
		std::cout << ' ';
}

//Функция для завершения обхода дерева и печати собранной информации об узлах
void PrettyPrint::after_traversal()
{
	//обход уровней дерева
	for (size_t l = 0, level_count = levels.size(); ; )
	{
		auto const& level = levels[l];
		unsigned prev_end = 0;

		for (auto const& node : level)
		{
			unsigned total = node.text_end - node.text_pos;
			unsigned slack = total - unsigned(node.text.length());
			unsigned blanks_before = node.text_pos - prev_end;

			print_blanks(blanks_before + slack / 2);
			cout << node.text;

			if (&node == &level.back())
				break;

			print_blanks(slack - slack / 2);

			prev_end += blanks_before + total;
		}

		if (++l == level_count)
			break;

		cout << "\n\n";
	}

	cout << "\n";
}

BTreeNode::BTreeNode(int t1, bool leaf1)
{
	// Копируем заданную минимальную степень (параметр дерева) и свойство листа
	t = t1;
	leaf = leaf1;

	// Выделяем память для максимального количества возможных ключей и дочерние указатели (размер находим по формуле)
	keys = new int[2 * t - 1];
	C = new BTreeNode * [2 * t];

	// Инициализируем количество ключей как 0
	n = 0;
}

// Вспомогательная функция, которая возвращает индекс первого ключа, который больше или равно k
int BTreeNode::findKey(int k)
{
	int idx = 0;
	while (idx < n && keys[idx] < k)
		++idx;
	return idx;
}

// Функция для удаления ключа k из поддерева, корнем которого является этот узел
void BTreeNode::delete_key(int k)
{
	int idx = findKey(k);

	// Ключ, который нужно удалить, присутствует в этом узле
	if (idx < n && keys[idx] == k)
	{

		// Если узел является листовым узлом - вызывается метод RemoveFromLeaf. В противном случае вызывается функция RemoveFromNonLeaf
		if (leaf)
			delete_from_leaf(idx);
		else
			delete_from_nonleaf(idx);
	}
	else
	{

		// Если этот узел является листовым узлом, то ключ отсутствует в дереве
		if (leaf)
		{
			cout << "The key " << k << " is does not exist in the tree\n";
			return;
		}

		// Ключ, который нужно удалить, есть в поддереве, корнем которого является этот узел
        // Флаг указывает, присутствует ли ключ в корневом поддереве с последним дочерним элементом этого узла
		bool flag = ((idx == n) ? true : false);

		// Если дочерний элемент, в котором должен существовать ключ, имеет менее t ключей, мы заполняем этот дочерний элемент
		if (C[idx]->n < t)
			fill(idx);

		// Если последний дочерний элемент был объединен, он должен быть объединен с предыдущим дочерний элемент, и поэтому мы рекурсивно обращаемся к (idx-1)-му дочернему элементу. 
		// В противном случае мы возвращаемся (idx)-й дочерний элемент, у которого теперь есть не менее t ключей
		if (flag && idx > n)
			C[idx - 1]->delete_key(k);
		else
			C[idx]->delete_key(k);
	}
	return;
}

// Функция для удаления idx-го ключа из этого узла, который является листом
void BTreeNode::delete_from_leaf(int idx)
{

	// Перемещаем все ключи после idx-й позиции на одну позицию назад
	for (int i = idx + 1; i < n; ++i)
		keys[i - 1] = keys[i];

	// Уменьшаем количество ключей
	n--;

	return;
}

// Функция для удаления idx-го ключа из этого узла, который не является листом
void BTreeNode::delete_from_nonleaf(int idx)
{

	int k = keys[idx];

	// Если дочерний элемент, предшествующий k (C[idx]), имеет как минимум t ключей, находим предшественника 'pred' k в поддереве с корнем в C[idx].
	//  Заменяем k на пред. Рекурсивно удаляем пред. в C[idx]
	if (C[idx]->n >= t)
	{
		int pred = getPred(idx);
		keys[idx] = pred;
		C[idx]->delete_key(pred);
	}

	// Если дочерний C[idx] имеет меньше t ключей, проверяем C[idx+1].
    // Если C[idx+1] имеет по крайней мере t ключей, находим преемника 'succ' k в поддереве с корнем в C[idx+1]
    // Заменяем k на succ. Рекурсивно удаляем succ в C[idx+1]
	else if (C[idx + 1]->n >= t)
	{
		int succ = getSucc(idx);
		keys[idx] = succ;
		C[idx + 1]->delete_key(succ);
	}

	// Если оба C[idx] и C[idx+1] имеют меньше t ключей, объединяем k и все C[idx+1] в C[idx]
    // Теперь C[idx] содержит 2t-1 ключей. Освобождаем C[idx+1] и рекурсивно удаляем k из C[idx]
	else
	{
		merge(idx);
		C[idx]->delete_key(k);
	}
	return;
}

// Функция для получения предшественника ключей[idx]
int BTreeNode::getPred(int idx)
{
	// Продолжаем двигаться к самому правому узлу, пока не достигнем листа
	BTreeNode* cur = C[idx];
	while (!cur->leaf)
		cur = cur->C[cur->n];

	// Возвращаем последний ключ листа
	return cur->keys[cur->n - 1];
}

int BTreeNode::getSucc(int idx)
{

	// Продолжаем перемещать самый левый узел, начиная с C[idx+1], пока не достигнем листа
	BTreeNode* cur = C[idx + 1];
	while (!cur->leaf)
		cur = cur->C[0];

	// Возвращаем первый ключ листа
	return cur->keys[0];
}

// Функция для заполнения дочернего элемента C[idx], имеющего менее t-1 ключей
void BTreeNode::fill(int idx)
{

	// Если предыдущий дочерний элемент (C[idx-1]) имеет более t-1 ключей, заимствуем ключ от этого дочернего элемента
	if (idx != 0 && C[idx - 1]->n >= t)
		borrowFromPrev(idx);

	// Если следующий дочерний элемент (C[idx+1]) имеет более t-1 ключей, заимствуем ключ от этого дочернего элемента
	else if (idx != n && C[idx + 1]->n >= t)
		borrowFromNext(idx);

	// Объединяем C[idx] с его братом
    // Если C[idx] — последний дочерний элемент, объединяем его с предыдущим братом, иначе объединяем его со следующим братом
	else
	{
		if (idx != n)
			merge(idx);
		else
			merge(idx - 1);
	}
	return;
}

// Функция для заимствования ключа из C[idx-1] и вставки его в C[idx]
void BTreeNode::borrowFromPrev(int idx)
{

	BTreeNode* child = C[idx];
	BTreeNode* sibling = C[idx - 1];

	// Последний ключ из C[idx-1] доходит до родителя и ключа[idx-1]
    // из родителя вставляется как первый ключ в C[idx

	// Перемещаем все ключи в C[idx] на шаг вперед
	for (int i = child->n - 1; i >= 0; --i)
		child->keys[i + 1] = child->keys[i];

	// Если C[idx] не является листом, переместим все его дочерние указатели на шаг вперед
	if (!child->leaf)
	{
		for (int i = child->n; i >= 0; --i)
			child->C[i + 1] = child->C[i];
	}

	// Установка первого ключа дочернего элемента, равного key[idx-1] из текущего узла
	child->keys[0] = keys[idx - 1];

	// Перемещение последнего дочернего элемента родственного брата в качестве первого дочернего элемента C[idx]
	if (!child->leaf)
		child->C[0] = sibling->C[sibling->n];

	// Перемещаем ключ от родственного к родительскому. Это уменьшает количество ключей в родственном элементе
	keys[idx - 1] = sibling->keys[sibling->n - 1];

	child->n += 1;
	sibling->n -= 1;

	return;
}

// Функция для заимствования ключа из C[idx+1] и размещения это в C[idx]
void BTreeNode::borrowFromNext(int idx)
{

	BTreeNode* child = C[idx];
	BTreeNode* sibling = C[idx + 1];

	//keys[idx] вставляется последним ключом в C[idx]
	child->keys[(child->n)] = keys[idx];

	// Первый дочерний элемент одного из братьев вставляется как последний дочерний элемент в C[idx]
	if (!(child->leaf))
		child->C[(child->n) + 1] = sibling->C[0];

	//Первый ключ из одного уровня вставляется вkeys[idx]
	keys[idx] = sibling->keys[0];

	// Перемещаем все ключи в родителе на шаг назад
	for (int i = 1; i < sibling->n; ++i)
		sibling->keys[i - 1] = sibling->keys[i];

	// Перемещаем дочерние указатели на шаг назад
	if (!sibling->leaf)
	{
		for (int i = 1; i <= sibling->n; ++i)
			sibling->C[i - 1] = sibling->C[i];
	}

	// Увеличение и уменьшение количества ключей C[idx] и C[idx+1] соответственно
	child->n += 1;
	sibling->n -= 1;

	return;
}

// Функция для объединения C[idx] с C[idx+1] 
void BTreeNode::merge(int idx)
{
	BTreeNode* child = C[idx];
	BTreeNode* sibling = C[idx + 1];

	// Извлекаем ключ из текущего узла и вставляем его в (t-1)-й позиция C[idx]
	child->keys[t - 1] = keys[idx];

	// Копируем ключи из C[idx+1] в C[idx] в конце
	for (int i = 0; i < sibling->n; ++i)
		child->keys[i + t] = sibling->keys[i];

	// Копируем дочерние указатели из C[idx+1] в C[idx]
	if (!child->leaf)
	{
		for (int i = 0; i <= sibling->n; ++i)
			child->C[i + t] = sibling->C[i];
	}

	// Перемещаем все ключи после idx в текущем узле на шаг раньше 
	for (int i = idx + 1; i < n; ++i)
		keys[i - 1] = keys[i];

	// Перемещение дочерних указателей после (idx+1) в текущем узле шаг раньше
	for (int i = idx + 2; i <= n; ++i)
		C[i - 1] = C[i];

	// Обновление количества ключей дочернего и текущего узла
	child->n += sibling->n + 1;
	n--;

	// Освобождаем память, занятую братом
	delete(sibling);
	return;
}

// Деструктор
BTreeNode::~BTreeNode() 
{
	delete[] keys;
	delete[] C;
}

// Основная функция, которая вставляет новый ключ в это B-дерево
void BTree::insert_key(int k)
{
	// Если дерево пусто
	if (root == NULL)
	{
		// Выделяем память для root
		root = new BTreeNode(t, true);
		root->keys[0] = k; // Вставляем ключ
		root->n = 1; // Обновляем количество ключей в корне
	}
	else // Если дерево не пусто
	{
		// Если корень заполнен, дерево растет в высоту
		if (root->n == 2 * t - 1)
		{
			// Выделяем память для нового корня
			BTreeNode* s = new BTreeNode(t, false);

			// Делаем старый корень дочерним по отношению к новому корню
			s->C[0] = root;

			// Разделяем старый корень и перемещаем 1 ключ в новый корень
			s->splitChild(0, root);

			// У нового корня теперь двое потомков. 
			int i = 0;
			if (s->keys[0] < k)
				i++;
			s->C[i]->insertNonFull(k);

			// ПЕреопределяем корень
			root = s;
		}
		else // Если корень не заполнен, вызываем метод InsertNonFull для корня
			root->insertNonFull(k);
	}
}

// Вспомогательная функция для вставки нового ключа в этот узел
// Предполагается, что узел не должен быть заполнен, когда эта функция вызывается
void BTreeNode::insertNonFull(int k)
{
	// Инициализируем индекс как индекс самого правого элемента
	int i = n - 1;

	// Если это листовой узел
	if (leaf == true)
	{
		// Следующий цикл делает две вещи
        // а) Находит место вставки нового ключа
        // б) Перемещает все старшие ключи на одно место вперед
		while (i >= 0 && keys[i] > k)
		{
			keys[i + 1] = keys[i];
			i--;
		}

		// Вставляем новый ключ в найденное место
		keys[i + 1] = k;
		n = n + 1;
	}
	else // Если этот узел не листовой
	{
		// Находим дочерний элемент, у которого будет новый ключ
		while (i >= 0 && keys[i] > k)
			i--;

		// Проверяем, заполнен ли найденный дочерний элемент
		if (C[i + 1]->n == 2 * t - 1)
		{
			// Если дочерний элемент заполнен, то разделяем его
			splitChild(i + 1, C[i + 1]);

			// После разделения средний ключ C[i] поднимается вверх и C[i] разделяется на две части. 
			if (keys[i + 1] < k)
				i++;
		}
		C[i + 1]->insertNonFull(k);
	}
}

// Вспомогательная функция для разделения дочернего элемента y этого узла
void BTreeNode::splitChild(int i, BTreeNode* y)
{
	// Создаем новый узел, который будет хранить (t-1) ключи из y
	BTreeNode* z = new BTreeNode(y->t, y->leaf);
	z->n = t - 1;

	// Копируем последние (t-1) ключи от y до z
	for (int j = 0; j < t - 1; j++)
		z->keys[j] = y->keys[j + t];

	// Копируем t последних дочерних элементов y в z
	if (y->leaf == false)
	{
		for (int j = 0; j < t; j++)
			z->C[j] = y->C[j + t];
	}

	// Уменьшаем количество ключей в y
	y->n = t - 1;

	// Поскольку у этого узла будет новый дочерний элемент, создаем пространство нового дочернего элемента
	for (int j = n; j >= i + 1; j--)
		C[j + 1] = C[j];

	// Связываем нового дочернего узла с этим узлом
	C[i + 1] = z;

	// Ключ y переместится в этот узел. Найти местоположение новый ключ и переместим все старшие ключи на один вперед
	for (int j = n - 1; j >= i; j--)
		keys[j + 1] = keys[j];

	// Копируем средний ключ y в этот узел
	keys[i] = y->keys[t - 1];

	// Увеличиваем количество ключей в этом узле
	n = n + 1;
}

// Функция для поиска ключа k в поддереве, корнем которого является этот узел
BTreeNode* BTreeNode::search_key(int k)
{
	// Находим первый ключ, больший или равный k
	int i = 0;
	while (i < n && k > keys[i])
		i++;

	// Если найденный ключ равен k, возвращаем этот узел
	if (keys[i] == k)
		return this;

	// Если ключ здесь не найден и это листовой узел
	if (leaf == true)
		return NULL;

	// Переход к соответствующему дочернему элементу
	return C[i]->search_key(k);
}

//Щсновная функция удаления ключа в дереве
void BTree::delete_key(int k)
{
	if (!root)
	{
		cout << "The tree is empty\n";
		return;
	}

	// Вызов функции удаления для корня
	root->delete_key(k);

	// Если корень имеет 0 ключей, делаем его первый дочерний узел новым корнем
    // если у него есть дочерний элемент, в противном случае устанавливаем root как NULL
	if (root->n == 0)
	{
		BTreeNode* tmp = root;
		if (root->leaf)
			root = NULL;
		else
			root = root->C[0];

		// Освобождаем старый корень
		delete tmp;
	}
	return;
}

//Деструктор
BTree:: ~BTree() 
{
	if (root != nullptr)
	{
		delete root;
		root = nullptr;
	}
}

