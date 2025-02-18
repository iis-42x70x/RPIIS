# README

## Цель

Цель данного проекта — создание и тестирование двусторонней очереди (Deque) с использованием принципов объектно-ориентированного программирования (ООП). Дек поддерживает добавление элементов с обеих сторон (в начало и в конец) и их удаление с обеих сторон, а также позволяет проверять, пуста ли она.

## Задача

Реализовать структуру данных "Двусторонняя очередь" (Deque) на основе двусвязного списка с использованием классов и методов для:
1. Добавления элементов с левой и правой стороны.
2. Удаления элементов с левой и правой стороны.
3. Проверки состояния очереди (пустая или нет).
4. Вывод строкового представления очереди.
5. Написания тестов для проверки корректности работы методов очереди.

## Список используемых понятий с указанием источников

1. **Двусвязный список (Doubly Linked List)**  
   Описание структуры: [https://en.wikipedia.org/wiki/Doubly_linked_list](https://en.wikipedia.org/wiki/Doubly_linked_list)

2. **Очередь (Queue)**  
   Объяснение структуры: [https://en.wikipedia.org/wiki/Queue](https://en.wikipedia.org/wiki/Queue)

3. **Двусторонняя очередь (Deque)**  
   Описание структуры: [https://en.wikipedia.org/wiki/Deque](https://en.wikipedia.org/wiki/Deque)

4. **Объектно-ориентированное программирование (OOP)**  
   Основы: [https://en.wikipedia.org/wiki/Object-oriented_programming](https://en.wikipedia.org/wiki/Object-oriented_programming)

5. **Тестирование с использованием unittest**  
   Документация: [https://docs.python.org/3/library/unittest.html](https://docs.python.org/3/library/unittest.html)

## Описание алгоритмов с указанием источников

1. **Алгоритм добавления элемента в начало и конец двусвязного списка (left_add, right_add)**  
   Алгоритм описан в статье: [https://www.geeksforgeeks.org/doubly-linked-list/](https://www.geeksforgeeks.org/doubly-linked-list/)

2. **Алгоритм удаления элемента из начала и конца двусвязного списка (del_left, del_right)**  
   Подробности алгоритмов удаления элементов можно найти в статье: [https://www.geeksforgeeks.org/doubly-linked-list-implementation/](https://www.geeksforgeeks.org/doubly-linked-list-implementation/)

3. **Алгоритм проверки на пустоту очереди (is_empty)**  
   Основы работы с очередями: [https://www.geeksforgeeks.org/queue-set-1-introduction-and-array-implementation/](https://www.geeksforgeeks.org/queue-set-1-introduction-and-array-implementation/)

## Результаты тестирования

### Входные данные:

1. Добавление элементов в очередь:
   - `left_add(1)`
   - `right_add(2)`
   - `left_add(3)`

2. Удаление элементов:
   - `del_left()`
   - `del_right()`

### Ожидаемые выходные данные:

1. После добавления элементов:  
   Очередь будет выглядеть как: `[3, 1, 2]`

2. После удаления с левой стороны:  
   Ожидаемый результат: Очередь: `[1, 2]`

3. После удаления с правой стороны:  
   Ожидаемый результат: Очередь: `[1]`

### Результаты тестирования:

```python
Deque is empty: False
Deque after left_add(1): [1]
Deque after right_add(2): [1, 2]
Deque after left_add(3): [3, 1, 2]
Deque after del_left: [1, 2]
Deque after del_right: [1]
```
![image](https://github.com/user-attachments/assets/6de0d11d-7822-4c26-b578-5e3d08ba6b63)



## Вывод

В ходе реализации были продемонстрированы основные операции с двусторонней очередью и их реализация с использованием принципов объектно-ориентированного программирования. Алгоритмы добавления и удаления элементов были реализованы эффективно с использованием двусвязного списка. Все тесты прошли успешно, что подтверждает правильность реализации.

