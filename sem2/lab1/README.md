# Лабоаторная работа 1
## Цели: 
*Исследовать свойства структур данных и разработать
библиотеку алгоритмов обработки структур данных*

## Задачи:
*1. Разработать библиотеку для работы со структурой данных, указанной в
индивидуальном задании, на любом императивнойм языке
программирования (Pascal, C\C++, Java, C#, Python и др.)*

*2. Разработать тестовую программу, которая демонстрирует
работоспособность реализованной библиотеки работы со структурой
данных.*

*3. По результатам выполнения задания составить отчет.*

## Вариант: 
*Вариант 5. Дерево отрезков. Поиск количества вхождений какого-то числа на отрезке массива. Изменение всех чисел на отрезке массива на какое-то значение.*

## Основные понятия:
**Дерево отрезков** - структура данных, позволяющая выполнять многие операции с отрезками массива за O(logN).
![lab1.1](https://github.com/iis-42x70x/RPIIS/blob/sem2/lab1/пересеч.png)


**Методы используемые в структуре данных:**
* Метод `build`: Построение дерева из исходного массива.
* Метод `push_lazy`: Ленивая обработка отложенных обновлений для узлов дерева.
* Метод `update_range`: Обновление значения в указанном отрезке массива, используя ленивую обработку.
* Метод `query_count`: Возвращение количества вхождений числа в указанном диапазоне.
* Метод `update`: Обновление значения в указанном диапазоне на новое значение val.
* Метод `count`: Этот метод возвращает количество числа в диапазоне.
* Метод `get_arr`: Возвращение оригинального массива.

## Алгоритмы операций:
Метод `build`: реализована проверка на нахождение в листовом узле, а также разделение отрезка на левую (left, mid) и правую (mid + 1, right) части. 
```
void SegmentTree::build(int node, int left, int right) {
    if (left == right) {
        tree[node].count[arr[left]] = 1;
    }
    else {
        int mid = (left + right) / 2;
        build(2 * node, left, mid);
        build(2 * node + 1, mid + 1, right);

        tree[node].count = tree[2 * node].count;
        for (const auto& pair : tree[2 * node + 1].count) {
            tree[node].count[pair.first] += pair.second;
        }
    }
}
```
Метод `push_lazy`: Проверка текущего узла на отложенное обновление, передача этого обновления потомкам узла и обновление текущего узла на число. 
```
void SegmentTree::push_lazy(int node, int left, int right) {
    if (tree[node].has_lazy) {
        int lazy_val = tree[node].lazy;

        if (left != right) {
            tree[2 * node].lazy = lazy_val;
            tree[2 * node].has_lazy = true;
            tree[2 * node + 1].lazy = lazy_val;
            tree[2 * node + 1].has_lazy = true;
        }

        tree[node].count.clear();
        tree[node].count[lazy_val] = right - left + 1;
        tree[node].has_lazy = false;
    }
}
```
Метод `update_range`: реализована обработка отложенного обновления. 
```
void SegmentTree::update_range(int node, int left, int right, int l, int r, int val) {
    push_lazy(node, left, right);

    if (right < l || left > r) {
        return;
    }

    if (l <= left && right <= r) {
        tree[node].lazy = val;
        tree[node].has_lazy = true;
        push_lazy(node, left, right);
        return;
    }

    int mid = (left + right) / 2;
    update_range(2 * node, left, mid, l, r, val);
    update_range(2 * node + 1, mid + 1, right, l, r, val);

    tree[node].count.clear();
    for (const auto& pair : tree[2 * node].count) {
        tree[node].count[pair.first] += pair.second;
    }
    for (const auto& pair : tree[2 * node + 1].count) {
        tree[node].count[pair.first] += pair.second;
    }
}
```
Метод `query_count`: этот метод выполняет запрос для подсчёта количества вхождений числа на указанном отрезке. 
```
int SegmentTree::query_count(int node, int left, int right, int l, int r, int target) {
    push_lazy(node, left, right);

    if (right < l || left > r) {
        return 0;
    }

    if (l <= left && right <= r) {
        auto it = tree[node].count.find(target);
        return it != tree[node].count.end() ? it->second : 0;
    }

    int mid = (left + right) / 2;
    return query_count(2 * node, left, mid, l, r, target) +
        query_count(2 * node + 1, mid + 1, right, l, r, target);
}
```
Метод `update`: 
```
void SegmentTree::update(int l, int r, int val) {
    if (l < 0 || r >= size || l > r) {
        return;
    }
    update_range(1, 0, size - 1, l, r, val);

    for (int i = l; i <= r; ++i) {
        arr[i] = val;
    }
}
```
Метод `count`: 
```
int SegmentTree::count(int l, int r, int target) {
    if (l < 0 || r >= size || l > r) {
        return 0;
    }
    return query_count(1, 0, size - 1, l, r, target);
}
```

## Тестовая программа:

Данная программа проверяет работу функций, созданной библиотеки.
```
#include <iostream>
#include <vector>
#include <limits>
#include "SegmentTree.h"
using namespace std;

void print_array(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int get_positive_integer(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка при вводе." << endl;
        }
        else if (value <= 0) {
            cout << "Введите положительное целое число." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int get_integer(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка при вводе." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

void get_array_elements(vector<int>& arr, int n) {
    for (int i = 0; i < n; ++i) {
        while (true) {
            cout << "Элемент[" << i << "]: ";
            if (cin >> arr[i]) {
                break;
            }
            else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка при вводе." << endl;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n = get_positive_integer("Введите количество элементов в массиве: ");

    vector<int> arr(n);
    cout << "Введите элементы массива:\n";
    get_array_elements(arr, n);

    SegmentTree st(arr);

    int choice;
    do {
        cout << "\nВыберете операцию:\n";
        cout << "1. Поиск количества вхождений какого-то числа на отрезке массива.\n";
        cout << "2. Изменение всех чисел на отрезке массива на какое-то значение.\n";
        cout << "3. Вывод массива.\n";
        cout << "4. Выход\n";

        choice = get_integer("Введите число: ");

        switch (choice) {
        case 1: {
            int left = get_integer("Введите левую границу: ");
            int right = get_integer("Введите правую границу: ");
            int value = get_integer("Введите значение числа: ");

            if (left < 0 || right >= n || left > right) {
                cout << "Неверный отрезок." << endl;
                break;
            }

            int count = st.count(left, right, value);
            cout << "Количество вхождений числа " << value << " на отрезке [" << left << ", " << right << "]: "
                << count << endl;
            break;
        }
        case 2: {
            int left = get_integer("Введите левую границу: ");
            int right = get_integer("Введите правую границу: ");
            int newValue = get_integer("Введите новое значение: ");

            if (left < 0 || right >= n || left > right) {
                cout << "Неверный отрезок." << endl;
                break;
            }

            st.update(left, right, newValue);
            cout << "Массив изменён." << endl;
            break;
        }
        case 3:
            cout << "Массив: ";
            print_array(st.get_arr());
            break;
        case 4:
            cout << "Выход." << endl;
            break;
        default:
            cout << "Выберете число от 1 до 4. " << endl;
        }
    } while (choice != 4);

    return 0;
}
```

## Файл SegmentTree.h:
```
#pragma once
#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H

#include <vector>
#include <unordered_map>
using namespace std;

class SegmentTree {
private:
    struct Node {
        unordered_map<int, int> count; 
        int lazy = 0;                       
        bool has_lazy = false;               
    };

    vector<Node> tree;
    vector<int> arr;
    int size;

    void build(int node, int left, int right);
    void push_lazy(int node, int left, int right);
    void update_range(int node, int left, int right, int l, int r, int val);
    int query_count(int node, int left, int right, int l, int r, int target);

public:
    SegmentTree(const vector<int>& input);
    void update(int l, int r, int val);
    int count(int l, int r, int target);
    vector<int> get_arr();
};
#endif 
```
## Выводы:
в ходе лабораторной работы освоили навыки работы со структурами и классами языка программирования C++. Разработали библиотеку для поиска количества вхождений какого-то числа на отрезке массива и изменения всех чисел на отрезке массива на какое-то значение, исоользуя дерево отрезков.

## Используемые источники:
1. https://habr.com/en/articles/808511/
2. https://brestprog.by/topics/segmenttree/
3. https://www.youtube.com/watch?v=LEkEPE_BKQY
4. http://e-maxx.ru/algo/segment_tree
