# Лабораторная рабоат №2

## Цель:
Изучить основы работы с множествами и основы теории множеств.

## Задача: 
**Реализовать программу, формирующую множество равное булеану исходного множества**

**Изучить основы теории множеств**

## Основные понятия
1. Булеан - это множество неориентированного множества A, которое является множеством всех подмножеств множества А
2. Множество - одно из ключевых понятий математики, представляющее собой набор, совокупность каких-либо (вообще говоря любых) объектов — элементов этого множества
3. Элемент множества - Объекты, из которых состоит множество, называют элементами множества или точками множества.

## Описание алгоритма
В ходе выполнения поставленной задачи был использован итеративный алгоритм создания булеана для исходного множества


Для начала алгоритм разбивает исходное множество на элементы

``` C++

vector<string> Boolean::separate() {
	vector<string> sepElements;
	string processed = source;

	processed.erase(remove(processed.begin(), processed.end(), ' '), processed.end());

	if (!processed.empty()) {
		processed.erase(0, 1);
		if (!processed.empty()) {
			processed.erase(processed.length() - 1, 1);
		}
	}

	int size = processed.length();
	int level = 1;
	string in;

	for (int i = 0; i < size; i++) {
		if (processed[i] == '{' || processed[i] == '<') {
			level++;
		}
		else if (processed[i] == '}' || processed[i] == '>') {
			level--;
		}

		if (level == 1 && processed[i] != ',') {
			in += processed[i];
		}
		else if (processed[i] == ',' && level == 1) {
			if (!in.empty()) {
				sepElements.push_back(in);
				in.clear();
			}
		}
		else if (level != 1) {
			in += processed[i];
		}
	}

	if (!in.empty()) {
		sepElements.push_back(in);
	}

	return sepElements;
}
```

В результирующее множество при записи некоторого элемента, также добавляются предыдущие элементы результирующего множества в обьединении с текущим элементом
выводим результирующее множество

```c++
string Boolean::findBoolean() {
	vector<string> sep = separate();
	vector<vector<string>> subsets = { {} };

	for (string elem : sep) {
		int size = subsets.size();
		for (int i = 0; i < size; i++) {
			vector<string> newSubset = subsets[i];
			newSubset.push_back(elem);
			subsets.push_back(newSubset);
		}
	}

	string result = "{";
	for (size_t i = 0; i < subsets.size(); i++) {
		result += "{";
		if (!subsets[i].empty()) {
			for (int j = 0; j < subsets[i].size(); j++) {
				result += subsets[i][j];
				if (j != subsets[i].size() - 1) {
					result += ", ";
				}
			}
		}
		result += "}";
		if (i != subsets.size() - 1) {
			result += ", ";
		}
	}
	result += "}";
	return result;
}
```

## Вывод

Полученная программа успешно создаёт и выводит в консоль булеан 😃
