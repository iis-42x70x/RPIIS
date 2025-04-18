# Лабораторная работа №1
## Цели:
* Изучить основные понятия, связанные с квадродеревьями;
* Уметь создавать квадродеревья.
* научиться создавать тесты для программы.

## Задачи:
* Выполнить свой вариант лабораторной работы;
* Перенести получившееся решение на язык программирования С++;
* Реализовать все указанные в задании функции для кыадродерева.

## Задание
Вариант №15: Квадродерево. Перевод матрицы в дерево. Перевод дерева в матрицу.

## Основные понятия
* **дерево** - структура данных, пожрожаюцщя древовидной структуре в виде набора связанных узлов.
* **квадродерево** – дерево, в котором у каждого внутреннего узла ровно 4 потомка.
* **узел** (Node) – элемент квадродерева, содержащий данные и ссылки на другие узлы.
* **корень** (root) – первый узел в квадродереве.
* **листья** (leafs) – последний узел в списке.

## Алгоритм: 

### Структура Node
```c++
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
```
Класс состоит из структуры узла Node, хранящую значение типа int и указатели на детей этого узла.
Также в классе описаны консьруктор и деструктор структуры.

### Структура Node
```c++
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
```
### конструктор Node
```c++
Node::Node (int val, bool stat){
	value = val;
	IsLeaf = stat;
	tl = NULL;
	bl = NULL;
	br = NULL;
	tr = NULL;
}
```
Инициализирует все переменные в структуре.

### деструктор Node
```c++
Node::~Node (){
	delete tl;
	delete bl;
	delete br;
	delete tr;
}
```
Освобождает место.

### Класс Tree
``` c++
class Tree{
public:
	static bool IsSame(int** matrix, int startx, int endx, int starty, int endy);

	static Node* buildTree(int** matrix, int startx, int endx, int starty, int endy, const string name, int depth);
	
	static void buildMatrix(Node* root, int** matrix, int startx, int endx, int starty, int endy);

	static void deleteTree(Node* root);

	static void printTree(Node* root, int depth);
};
```
класс ответственен за создание дерева из матрицы, воссоздание матрицы из дерева, вывод дерева, проверку матрицы на одинаковые элементы.

### создание дерева из матрицы: 
```c++
 Node* Tree::buildTree (int** matrix, int startx, int endx, int starty, int endy, const string name, int depth){
	if(IsSame(matrix, startx, endx, starty, endy)){
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
```
этот метод принимает матрицу, делит её на 4 части до тех пор, пока все элементы не будут равны друг другу.

### проверка на схожие элементы в матрице: 
```c++
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
```
этот метод возвращает true, если все элементы одинаковые, false - если иное

### проверка на схожие элементы в матрице: 
```c++
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
```

## Тесты:
### Создание дерева
  
![Push front/back](https://github.com/iis-42x70x/RPIIS/blob/Рассохов_Е/sem2/lab1/img/buildtree.png)

### Удаление дерева
  
![Delete front/back](https://github.com/iis-42x70x/RPIIS/blob/Рассохов_Е/sem2/lab1/img/deletetree.png)

### одинаковые элементы
  
![Sort](https://github.com/iis-42x70x/RPIIS/blob/Рассохов_Е/sem2/lab1/img/equals.png)

### Поиск
  
![Find](https://github.com/iis-42x70x/RPIIS/blob/Рассохов_Е/sem2/lab1/img/matrix.png)

### Создание узла
  
![Unification](https://github.com/iis-42x70x/RPIIS/blob/Рассохов_Е/sem2/lab1/img/node.png)

## Вывод

В ходе выполнения лабораторной работы был создан класс для работы с квадродеревьями. В нем я реализовал основные методы для работы с квадродеревьями: создание узла, удаление дерева, создание дерева из матрицы, воссоздание дерева из матрицы.

## Источники

[WikiPedia]([https://www.youtube.com/watch?v=lQ-lPjbb9Ew](https://ru.wikipedia.org/wiki/Дерево_(структура_данных))](https://ru.wikipedia.org/wiki/Дерево_квадрантов))

[habr]([https://prog-cpp.ru/data-dls/](https://habr.com/ru/articles/473066/))

[GeeksForGeeks]([https://www.bestprog.net/ru/2022/02/16/c-linear-doubly-linked-bidirectional-list-general-concepts-ru/](https://www.geeksforgeeks.org/quad-tree/?ysclid=m8f2ntg2l5180079933))

