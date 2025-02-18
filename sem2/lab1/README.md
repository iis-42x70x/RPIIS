# <p align="center">Лабораторная работа №1</p>
Вариант 27. Однонаправленный список. Вставка элемента в список. Удаление
элемента из списка. Сортировка списка. Поиск элемента в списке.
## <p align="center">Цели лабораторной работы:</p>
1. Разработать библиотеку для работы с однонаправленным списком на выбранном императивном языке программирования (например, C++, Java, Python).
2. Создать тестовую программу для демонстрации функциональности разработанной библиотеки.
3. Разработать систему тестов для проверки работоспособности и корректности библиотеки, учитывая требования полноты, адекватности и непротиворечивости.
4. Обеспечить обработку некорректных данных, предусмотрев корректное завершение программы при возникновении ошибок.
5. Составить отчет по выполнению лабораторной работы.
## <p align="center">Задачи лабораторной работы:</p>
1. Изучить спецификацию задачи по работе с однонаправленным списком.
2. Выбрать язык программирования для реализации библиотеки (например, C++, Java, Python) в соответствии с индивидуальным заданием.
3. Разработать и реализовать библиотеку для работы с односвязным списком, включая операции описанные в индивидуальном задании.
4. Написать тестовую программу, которая демонстрирует работоспособность библиотеки.
5. Разработать систему тестов, включающую тест-кейсы для проверки различных аспектов работы библиотеки, включая корректность, производительность и обработку ошибок.
6. Провести тестирование разработанной библиотеки, убедившись в ее правильной работе на различных входных данных.
7. Составить подробный отчет, включая описание решения задачи, архитектуры библиотеки, результаты тестирования и выводы.
## <p align="center">Список используемых понятий:</p>
1. `Библиотека программного обеспечения (Библиотека кода):` в программировании библиотека представляет собой совокупность программного кода, предназначенного для решения определенных задач. Этот код может содержать функции, классы, процедуры или другие компоненты, которые разработчики могут повторно использовать в своих программных проектах. Библиотеки упрощают разработку, так как они предоставляют готовые решения для типовых задач.
2. `Библиотека gtest/gtest.h:` библиотека для модульного тестирования на языке С++.
3. `Библиотека type_traits:` библиотека для работы с шаблонами и типами на С++.
4. `Библиотека stdexcept` в C++ предоставляет классы исключений, которые могут быть брошены во время выполнения программы для сигнализации об ошибках.
5. `Однонаправленный список:` базовая структура данных, представляющая собой соединённые узлы с однотипными данными. Каждый узел состоит из элемента и ссылки на следующий элемент.
## <p align="center">Описание используемых алгоритмов:</p>
### <p align="center">Реализация однонаправленного списка</p>
1. **Класс List:** необходим для работы с однонаправленным списком. Содержит методы добавления элемента, удаления элемента, сортировки, поиска, пересечения и объединения списков, а также дургие вспомогательные и/или внутренние функции. Класс является шаблоным, что позволяет создавать список любого типа (int, float, str и др.).
```cpp
template<typename T>
class List{
public:
	List();
	List(const List<T>& other);
	~List();

	void Add(T data, int position = 0);
	void Del(int position = 0);
	void Sort();
	int Search(T data);
	List<T> operator+(List list);
	List<T> operator^(List list);

	void View();
	int GetSize();

	T &operator[](const int index);
	List<T> &operator=(const List &other);

private:
	class Node{
	public:
		Node *next;
		T data;
	
		Node(T data, Node *next = NULL);
	};

	Node *head;
	int size;

public:
	Node *GetHead();
};
```
### <p align="center">Реализация узла односвязного списка</p>
2. **Kласс Node:** ключевая структура на которой работает `класс List`. Имеет два поля: ячейку с информацией и ячейку с ссылкой на следущий элемент.
```cpp
class Node{
public:
	Node *next;
	T data;

	Node(T data, Node *next = NULL);
};
```
### <p align="center">Реализация метода Add</p>
3. **Метод Add:** добавляет новый узел в указанную позицию (или по дефолту в начало списка).
```cpp
template<typename T>
void List<T>::Add(T data, int position){

	if (position > size || position < 0)
		throw invalid_argument("Incorrect index");
	

	if (position == 0){
		head = new Node(data, this->head);

	} else{
		Node *current = this->head;

		for (int i{1}; i < position; i++){
			current = current->next;
		}

		current->next = new Node(data, current->next);
	}
	

	size++;
}
```
### <p align="center">Реализация метода Del</p>
4. **Метод Del:** удаляет указанный элемент (или по дефолту самый первый элемент списка).
```cpp
template<typename T>
void List<T>::Del(int position){

	if (position >= size || position < 0)
		throw invalid_argument("Incorrect index");


	if (position == 0){

		if (size == 1){
			delete head;
		} else {
			Node *temp = head;
			head = head->next;
			delete temp;
		}

	} else{
		Node *current = head;

		for (int i{1}; i < position; i++){
			current = current->next;
		}

		Node *temp = current->next;
		current->next = temp->next;
		delete temp;

	}
	size--;
}
```
### <p align="center">Реализация метода Sort</p>
5. **Метод Sort:** сортирует элементы от меньшего к большему. Используется сортировка пузырьком.
```cpp
template<typename T>
void List<T>::Sort(){
	Node *current;
	Node *next_node;

	for (int i{0}; i < size - 1; i++){
		current = head;
		next_node = head->next;
		for (int j{0}; j < size - 1 - i; j++){
			if (current->data > next_node->data){
				T temp = current->data;
				current->data = next_node->data;
				next_node->data = temp;
			}
			current = current->next;
			next_node = next_node->next;
		}
	}
}
```
### <p align="center">Реализация метода Search</p>
6. **Метод Search:** ищет элемент по значению. Возвращает индекс первого подходящего элемента, а в случае когда такого элемета нет возвращает -1.
```cpp
template<typename T>
int List<T>::Search(T data){
	Node *current = head;
	int index = 0;

	while (current != NULL){
		if constexpr (is_floating_point_v<T>){
			if (current->data - data < 0.000001 && current->data - data > -0.000001)
				return index;
		}else if (current->data == data){
			return index;
		}
		
		current = current->next;
		index++;
	}
	return -1;
}
```
### <p align="center">Реализация метода поиска по индексу</p>
7. **Оператор [ ]:** ищет элемент по индексу. Возвращает значение элемента.
```cpp
template<typename T>
T &List<T>::operator[](const int index){
	if (index >= size || index < 0)
		throw invalid_argument("Incorrect index");

	Node *current = this->head;
	for (int i{0}; i < index; i++){
		current = current->next;
	}
	return current->data;
}
```
### <p align="center">Реализация метода объединения</p>
8. **Оператор +:** объединяет два списка.
```cpp
template<typename T>
List<T> List<T>::operator+(List list){

	Sort();
	list.Sort();

	List<T> result;
	Node *current_1 = head;
	Node *current_2 = list.head;


	while (current_1 != NULL && current_2 != NULL){
		if (current_1->data < current_2->data){
			result.Add(current_1->data);
			current_1 = current_1->next;

		} else if (current_1->data > current_2->data){
			result.Add(current_2->data);
			current_2 = current_2->next;

		} else {
			int count_1{1}, count_2{1};

			if constexpr (is_floating_point_v<T>){
				while(current_1->next != NULL && abs(current_1->data - current_1->next->data) < 0.000001){
					count_1++;
					current_1 = current_1->next;
				}
	
				while(current_2->next != NULL && abs(current_2->data - current_2->next->data) < 0.000001){
					count_2++;
					current_2 = current_2->next;
				}

			} else {
				while(current_1->next != NULL && current_1->data == current_1->next->data){
					count_1++;
					current_1 = current_1->next;
				}
	
				while(current_2->next != NULL && current_2->data == current_2->next->data){
					count_2++;
					current_2 = current_2->next;
				}
			}

			for (int i{0}; i < max(count_1, count_2); i++)
				result.Add(current_1->data);

			current_1 = current_1->next;
			current_2 = current_2->next;
		}
	}

	while (current_1 != NULL) {
		result.Add(current_1->data);
		current_1 = current_1->next;
	}

	while (current_2 != NULL) {
		result.Add(current_2->data);
		current_2 = current_2->next;
	}
	

	return result;
}
```
### <p align="center">Реализация метода пересечения</p>
9. **Оператор ^:** возвращает пересечение двух списков.
```cpp
template<typename T>
List<T> List<T>::operator^(List list){

	this->Sort();
	list.Sort();

	List<T> result;
	Node *current_1 = this->GetHead();
	Node *current_2 = list.GetHead();


	while (current_1 != NULL && current_2 != NULL){
		if (current_1->data < current_2->data){
			current_1 = current_1->next;

		} else if (current_1->data > current_2->data){
			current_2 = current_2->next;

		} else {
			int count_1{1}, count_2{1};

			if constexpr (is_floating_point_v<T>){
				while(current_1->next != NULL && (current_1->data - current_1->next->data < 0.000001) && (current_1->data - current_1->next->data > -0.000001)){
					count_1++;
					current_1 = current_1->next;
				}
	
				while(current_2->next != NULL && (current_2->data - current_2->next->data < 0.000001) && (current_2->data - current_2->next->data > -0.000001)){
					count_2++;
					current_2 = current_2->next;
				}

			} else {
				while(current_1->next != NULL && current_1->data == current_1->next->data){
					count_1++;
					current_1 = current_1->next;
				}
	
				while(current_2->next != NULL && current_2->data == current_2->next->data){
					count_2++;
					current_2 = current_2->next;
				}
			}

			for (int i{0}; i < min(count_1, count_2); i++)
				result.Add(current_1->data);

			current_1 = current_1->next;
			current_2 = current_2->next;
		}
	}

	return result;
}
```
### <p align="center">Дополнительные методы</p>
10. **Коструктор копирования List:** необходим при копировании списка.
11. **Метод View:** выводит весь список.
12. **Оператор =:** необходим при присваивании одного класса другим.
13. **Метод GetSize:** возвращает `size` класса List.
14. **Метод GetHead:** возвращает `head` класса List.
## <p align="center">Результаты тестирования:</p>
Тестирование проводилось с помощью `gtest.h`. Результат выполнения:
![Снимок экрана 2025-02-18 154038](https://github.com/user-attachments/assets/477a84c1-a0fe-4af7-8c16-e71ab20a5405)
![Снимок экрана 2025-02-18 154052](https://github.com/user-attachments/assets/0ce2607a-0579-4849-9400-a3b0265f0cc0)
![Снимок экрана 2025-02-18 154100](https://github.com/user-attachments/assets/40933d89-83a4-4e82-bf9e-bad566114b52)
## <p align="center">Вывод</p>
В ходе выполнения работы познакомился созданием библиотек в С++, познакомился с концепцией реализация в .срр файлах, декларация $-$ в .hpp (узнал о файле .inl), познакомился с классами в С++, познакомился с Google C++ Testing Framework, познакомился с шаблонами, познакомился с исключениями, реализоавал библиотеку для работы c однонаправленным списком,а также создал систему тестов,которая проверяет корректность созданной библиотеки, собрал проект с помощью cmake.
## <p align="center">Используемые источники и материалы:</p>
- https://stackoverflow.com/questions/1208028/significance-of-a-inl-file-in-c (.inl)
- https://www.cyberforum.ru/cpp-beginners/thread2600085.html (про .inl, .h и .cpp)
- https://www.youtube.com/watch?v=SajrPhE6FoQ (реализация однонаправленного списка от SimleCode)
- https://habr.com/ru/articles/667880/ (googletest)
- http://google.github.io/googletest/ (googletest)
- https://habr.com/ru/articles/155467/ (cmake)
- https://chat.deepseek.com (помощь в освоении материала)
