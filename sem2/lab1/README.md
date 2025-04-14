<h1>Лабораторная работа №1</h1>
<hr></hr>

## Цели:
* Изучить основные понятия, связанные с ориентированными графами
* Научиться правильно использовать ориентриованные графы
* Уметь использовать основные алгоритмы при работе с ориентированными графами 

## Задачи:
* Выполнить свой вариант лабораторной работы 
* Перенести получившееся решение на язык программирования С++
* Реализовать все указанные в задании операции над ориентированным графом

## Вариант:
Для работы мне был выдан **28** вариант. Граф представлен в виде дерева.

## Граф:
**Графом** (англ. directed graph) G называется пара G=(V,E), где 
V — множество вершин (англ. vertices),
E⊂V×V — множество рёбер.

## Дерево: 
Дерево — одна из наиболее широко распространённых структур данных в информатике, эмулирующая древовидную структуру в виде набора связанных узлов. Является связным графом, не содержащим циклы. Большинство источников также добавляет условие на то, что рёбра графа не должны быть ориентированными. В дополнение к этим трём ограничениям, в некоторых источниках указывается, что рёбра графа не должны быть взвешенными.

<img src="imageslab1\tree.png"></img>
<h6>пример дерева.</h6>

### Дерево Хаффмана:
Алгоритм Хаффмана (англ. Huffman's algorithm) — алгоритм оптимального префиксного кодирования алфавита.


В ходе данной лабораторной работы проект имел 3 основных файла: **header.h**, **main.cpp**, **graph.cpp**.

### Cтруктура узла дерева:
``` 
struct Node
{
	char ch;
	int freq;
	Node* left, * right;
};
```

### Получение нового узла:
```
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}
```
### Структура для сравнения частоты символов:
```
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};
```
### Кодировка текста:
```
void encode(Node* root, string str, unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;

	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}
```
### Декодировка текста:
```
void decode(Node* root, int& index, string str)
{
	if (root == nullptr) {
		return;
	}

	
	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}
```
### Построение дерева Хаффмана:
```
void buildHuffmanTree(string text)
{
	
	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}

	
	priority_queue<Node*, vector<Node*>, comp> pq;

	
	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	
	while (pq.size() != 1)
	{
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();

		
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	
	Node* root = pq.top();

	
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Huffman Codes are :\n" << '\n';
	for (auto pair : huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}

	cout << "\nOriginal string was :\n" << text << '\n';

	
	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}

	cout << "\nEncoded string is :\n" << str << '\n';

	
	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
}
```
## Результаты тестов:
Тест 1:
<img src="imageslab1\1.png"></img>

Тест 2:
<img src="imageslab1\2.png"></img>

Тест 3:
<img src="imageslab1\3.png"></img>

Тест 4:
<img src="imageslab1\4.png"></img>

Тест 5:
<img src="imageslab1\5.png"></img>

<hr></hr>

## Вывод:
В результате лабораторной работы:

Ознакомился с понятием графа и всех других определений, связанных с графами.

Изучил структуру данных типа дерево.

Реализовал алгоритм кодировки текста с помощью дерева Хаффмана.

## Используемые источники:

### Свободная энциклопедия "Википедия" [Электронный ресурс]-Режим доступа
<a href="https://ru.wikipedia.org/wiki/%D0%9A%D0%BE%D0%B4_%D0%A5%D0%B0%D1%84%D1%84%D0%BC%D0%B0%D0%BD%D0%B0">* https://ru.wikipedia.org/wiki</a>

### Алгоритм сжатия Хаффмана - habr
<a href="https://habr.com/en/companies/otus/articles/497566/">* https://habr.com</a>
