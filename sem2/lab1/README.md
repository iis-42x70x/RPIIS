# Лабораторная работа №1
## Цели:
* Изучить основные понятия, связанные с двунаправленными списками;
* Научиться правильно использовать двунаправленные списки;
* Уметь использовать основные алгоритмы при работе с двунаправленными списками.

## Задачи:
* Выполнить свой вариант лабораторной работы;
* Перенести получившееся решение на язык программирования С++;
* Реализовать все указанные в задании операции над двунаправленным списком.

## Задание
Вариант №24. Двунаправленный список. Вставка элемент в список. Удаление элемента из списка. Сортировка списка. Поиск элемента в списке. Объединение двух списков. Пересечение двух списков.

## Основные понятия
* **Список** – это структура данных, которая представляет собой упорядоченную последовательность элементов.
* **Связный список** – элементы хранят ссылки друг на друга.
* **Двусвязный список** – каждый элемент содержит ссылки на предыдущий и следующий элементы.
* **Узел** (Node) – элемент списка, содержащий данные и ссылки на другие узлы.
* **Голова** (head) – первый узел в списке.
* **Хвост** (last) – последний узел в списке.

## Алгоритм: 

### Класс List
```c++
class List{
public:
    class Node{
    public:
        int data;
        Node *next = nullptr;
        Node *prev = nullptr;
    };
    Node *head = nullptr;
    Node *last = nullptr;
// functions
// ...
}
```
* Класс состоит из структуры узла Node, хранящую значение типа int и указатели на следующий и предыдущий элементы и указателей на голову и конец списка.
* Также в классе описаны методы проверки на пустоту списка, добавления, удаления, вывода, сортировки и поиска элементов списка.
* Реализованы также методы нахождения пересечения и объединения двух списков.


### Добавление элемента в начало или конец списка: 
```c++
class List{
// ------------------------------------
    void pushFront(int new_value)
    {
        Node *new_node = new Node;
        new_node->data = new_value;

        if(isEmpty()){
            head = new_node;
            last = new_node;
            return;
        }
        
        head->next = new_node;
        new_node->prev = head;
        head = new_node;
    }

    void pushLast(int new_value)
    {
        Node *new_node = new Node;
        new_node->data = new_value;

        if(isEmpty()){
            head = new_node;
            last = new_node;
            return;
        }

        last->prev = new_node;
        new_node->next = last;
        last = new_node;
    }
// ------------------------------------
}
```
* Если элемент должен быть добавлен в начало, используется *pushHead*.
* Если в конец — *pushLast*.


### Удаление элемента
```c++
class List{
// ------------------------------------
    void popFront()
    {
        Node *temp = head;
        head = head->prev;
        if(head)
            head->next = nullptr;
        else {
            last->next = nullptr;
            last = nullptr;
        }
        delete temp;
    }

    void popLast()
    {
        Node *temp = last;
        last = last->next;
        if(last)
            last->prev = nullptr;
        else {
            head->prev = nullptr;
            head = nullptr;
        }
        delete temp;
    }  
// ------------------------------------
}
```
* Если список состоит из одного узла, очищает оба указателя head и last.
* Если узел — голова списка, обновляет head и корректирует указатель на предыдущий узел.
* Если узел — хвост списка, обновляет last и корректирует указатель на следующий узел.
* В остальных случаях удаляет узел, корректируя связи между соседними узлами.
* Освобождает память под удалённый узел.


###  Поиск элемента
```c++
class List{
// ------------------------------------
    bool find(int value)
    {
        Node *curr = head;
        while(curr){
            if(curr->data != value)
                curr = curr->prev;
            else
                return true;
        }
        return false;
    }
// ------------------------------------
}
```
* Создает указатель *curr* на *head* и пока он не будет указывать на пустое значение движется в сторону *last* проверяя каждый элемент.
* При нахождении эл-та равного по значению искомому возвращает *true*.
* Если *curr* дойдет до *last*, то функция вернет *false*.


### Объединение двух списков.
```c++
class List{
// ------------------------------------
    void unification(List &first, List &second)
    {
        deleteAll();
        first.sort();
        second.sort();
        Node *curr_first = first.head;
        Node *curr_second = second.head;

        while (curr_first && curr_second) {
            if (curr_first->data < curr_second->data) {
                pushLast(curr_first->data);
                curr_first = curr_first->prev;
            } else if (curr_first->data > curr_second->data) {
                pushLast(curr_second->data);
                curr_second = curr_second->prev;
            } else {
                pushLast(curr_first->data);
                curr_first = curr_first->prev;
                curr_second = curr_second->prev;
            }
        }

        while (curr_first) {
            pushLast(curr_first->data);
            curr_first = curr_first->prev;
        }

        while (curr_second) {
            pushLast(curr_second->data);
            curr_second = curr_second->prev;
        }
    }
// ------------------------------------
}
```
* Очищает список, куда будет записываться объединение.
* Сортирует оба объединяемых списка.
* Одновременно идет по элементам от меньшего к большему в обоих списках, если эл-ты равны, то в объединение записывается это значение, если какой-то из эл-ов окажется меньше, то он записывается с объединение и указатель списка, в котором был такой эл-нт сдвигается дальше.
* Т.к. один из списков может закончится раньше до два цикла *while* доведут указатель до конца в любом из случаев и запишут оставшиеся эл-ты.

### Сортировка
```c++
class List{
// ------------------------------------
    void sort() 
    {    
        Node *curr;
        Node *sorted = last;
        bool swapped = true;
        while(swapped){
            swapped = false;
            curr = head;
            while(curr != sorted){
                if(curr->data > curr->prev->data){
                    std::swap(curr->data, curr->prev->data);
                    swapped = true;
                }
                curr = curr->prev;
            }
            sorted = sorted->next;
        }
    }
// ------------------------------------
}
```
* Оптимизированная сортировка пузырьком (сортировка остановится, если список уже отсортирован).
## Тесты:
* Добавление элементов
  
![Push front/back](img\push_front_back.png)

* Удаление элементов
  
![Delete front/back](img\delete_front_back.png)

* Сортировка
  
![Sort](img\sort.png)

* Поиск
  
![Find](img\find.png)

* Объединение
  
![Unification](img\unification.png)

* Пересечение
  
![Intersection](img\intersection.png)

  ## Вывод

В ходе выполнения лабораторной работы был создан класс для работы с двунаправленными списками. В нем я реализовал основные операции над двунарпавленными списками: вставка элемента в список, удаление элемента из списка, сортировка списка, поиск элемента в списке, объединение двух списков, пересечение двух списков.

## Источники

[Youtube](https://www.youtube.com/watch?v=lQ-lPjbb9Ew)

[Prog.cpp](https://prog-cpp.ru/data-dls/)

[BestProg](https://www.bestprog.net/ru/2022/02/16/c-linear-doubly-linked-bidirectional-list-general-concepts-ru/)

