# Лабораторная работа №1
## Цели:
* Изучить основные понятия, связанные с двунаправленными списками
* Научиться правильно использовать двунаправленные списки
* Уметь использовать основные алгоритмы при работе с двунаправленными списками

## Задачи:
* Выполнить свой вариант лабораторной работы 
* Перенести получившееся решение на язык программирования С++
* Реализовать все указанные в задании операции над двунаправленным списком

## Задание
Вариант №24. Двунаправленный список. Вставка элемент в список. Удаление элемента из списка. Сортировка списка. Поиск элемента в списке. Объединение двух списков. Пересечение двух списков.

## Основные понятия
* **Список** – это структура данных, которая представляет собой упорядоченную последовательность элементов
* **Связный список** (Linked List) – элементы хранят ссылки друг на друга
* **Двусвязный список** – каждый элемент содержит ссылки на предыдущий и следующий элементы
* **Узел** (Node) – элемент списка, содержащий данные и ссылки на другие узлы
* **Голова** (Head) – первый узел в списке
* **Хвост** (Tail) – последний узел в списке

## Алгоритм: 

### Добавление элемента в начало(конец) или на определенную позицию: 
```c++
void push_head(Node*& head, Node*& tail, int value) {
	Node* newnode = new Node(value);
	if (!head) {
		head = tail = newnode;
	}
	else {
		newnode->next = head;
		head->prev = newnode;
		head = newnode;
	}
}

void push_tail(Node*& head, Node*& tail, int value) {
	Node* newnode = new Node(value);
	if (!tail) {
		head = tail = newnode;
	}
	else {
		newnode->prev = tail;
		tail->next = newnode;
		tail = newnode;
	}
}

void push(Node*& head, Node*& tail, int value, int element) {
	Node* newnode = new Node(value);
	Node* temp = head;
	int num = 0;
	if (element == 1) {
		push_head(head, tail, value);
		return;
	}
	while (temp) {
		++num;
		if (num == element) {
			newnode->prev = temp->prev;
			temp->prev->next = newnode;
			temp->prev = newnode;
			newnode->next = temp;
			return;
		}
		temp = temp->next;
	}
}
```
* Если элемент должен быть добавлен в начало, используется *push_head*.
* Если в конец — используется *push_tail*.
* Если в указанную позицию (по индексу), вставляется элемент между соседними узлами.

### Удаление элемента
```c++
void deleteNode(Node*& head, Node*& tail, Node* node) {
	if (!node) {
		cout << "Данного элемента не существует в списке." << endl;
		return;
	}
	if (head == tail) {
		head = tail = nullptr;
	}
	else if (node == head) {
		head = head->next;
		head->prev = nullptr;
	}
	else if (node == tail) {
		tail = tail->prev;
		tail->next = nullptr;
	}
	else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	delete node;
}
```
* Если узел пустой, выводит сообщение об ошибке.
* Если список состоит из одного узла, очищает оба указателя head и tail.
* Если узел — голова списка, обновляет head и корректирует указатель на предыдущий узел.
* Если узел — хвост списка, обновляет tail и корректирует указатель на следующий узел.
* В остальных случаях удаляет узел, корректируя связи между соседними узлами.
* Освобождает память под удалённый узел.


###  Поиск элемента по номеру. Поиск номера элемента
```c++
Node* Find(Node*& head, Node*& tail, int element) {
	Node* temp = head;
	int num = 0;
	while (temp) {
		++num;
		if (num == element) {
			return temp;
		}
		temp = temp->next;
	}
	return nullptr;
}

int Find_num(Node*& head, Node*& tail, int value) {
	Node* temp = head;
	int num = 0;
	while (temp) {
		++num;
		if (temp->info == value) {
			return num;
		}
		temp = temp->next;
	}
	return 0;
}
```
Find:

Ищет узел по индексу (позиции) в списке.
Перебирает элементы, пока не достигнет указанной позиции (element), и возвращает узел на этой позиции.
Если позиция не найдена, возвращает nullptr.

Find_num:

Ищет элемент по значению (value).
Перебирает список и возвращает номер (позицию) узла с данным значением.
Если элемент не найден, возвращает ничего (по умолчанию 0, если не обработано иначе).

### Объединение двух списков.
```c++
void unification(Node*& unihead, Node*& unitail, Node*& head1, Node*& tail1, Node*& head2, Node*& tail2) {
	if (!head1 && !head2) {
		unihead = unitail = nullptr;
		return;
	}
	if (!head1) {
		unihead = head2;
		unitail = tail2;
		return;
	}
	if (!head2) {
		unihead = head1;
		unitail = tail1;
		return;
	}
	Node* temp1 = head1;
	unihead = new Node(temp1->info);
	unitail = unihead;
	temp1 = temp1->next;
	while (temp1) {
		push_tail(unihead, unitail, temp1->info);
		temp1 = temp1->next;
	}

	Node* temp2 = head2;
	while (temp2) {
		push_tail(unihead, unitail, temp2->info);
		temp2 = temp2->next;
	}
}
```
* Если оба списка пусты, результат пуст.
* Если один список пуст, копирует второй список в результат.
* Если оба списка не пусты, добавляет все элементы первого списка в новый список, а затем все элементы второго списка.
### Пересечение двух списков.
```c++
bool exist_in(Node* head, int value) {
	Node* temp = head;
	while (temp) {
		if (temp->info == value) {
			return true;
		}
		temp = temp->next;
	}
	return false;
}

void intersection(Node*& interhead, Node*& intertail, Node*& head1, Node*& tail1, Node*& head2, Node*& tail2) {
	Node* temp = head2;
	while (temp) {
		if (exist_in(head1, temp->info)) {
			push_tail(interhead, intertail, temp->info);
		}
		temp = temp->next;
	}
}
```
Перебирает все элементы второго списка (head2).
Для каждого элемента проверяет, существует ли он в первом списке (head1) с помощью функции exist_in.
Если элемент найден в обоих списках, добавляет его в новый список пересечений (interhead и intertail).
Результат — новый список, содержащий только общие элементы из обоих списков.
### Сортировка
```c++
void Sort(Node*& head, Node*& tail) {
	if (!head || !head->next) {
		return;
	}
	bool swap = true;
	while (swap) {
		Node* temp = head;
		swap = false;
		while (temp && temp->next) {
			if (temp->info > temp->next->info) {
				int t = temp->info;
				temp->info = temp->next->info;
				temp->next->info = t;
				swap = true;
			}
			temp = temp->next;
		}
	}
}
```
Проверяет, пуст ли список или содержит только один элемент. Если да — завершает выполнение. Далее применяется сортировка пузырьком
## Тесты:
* Тест 1
![]()

* Тест 2
  ![]()

* Тест 3
  ![]()
  ![]()

* Тест 4
  ![]()

* Тест 5
  ![]()

  ## Вывод

В ходе выполнения лабораторной работы была разработана библиотека по работе двунаправленными списками. В ней я реализовал основные операции над двунарпавленными списками: вставка элемента в список, удаление
элемента из списка, сортировка списка, поиск элемента в списке, объединение двух списков, пересечение двух списков.

## Источники

[Youtube](https://www.youtube.com/watch?v=lQ-lPjbb9Ew)

[Prog.cpp](https://prog-cpp.ru/data-dls/)

[BestProg](https://www.bestprog.net/ru/2022/02/16/c-linear-doubly-linked-bidirectional-list-general-concepts-ru/)


