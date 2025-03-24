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
*21.Система непересекающихся множеств. Создание множества.
Объединение двух множеств. Определение множества, которому
принадлежит указанный элемент.*

## Основные понятия:
Непересекающиеся множества — это множества, пересечение которых является пустым множеством.
![lab1.1](https://github.com/iis-42x70x/RPIIS/blob/sem2/lab1/пересеч.png)

Объединение множеств — множество, содержащее в себе все элементы исходных множеств.
![lab1.2](https://github.com/iis-42x70x/RPIIS/blob/%D0%91%D0%B5%D0%BB%D0%BA%D0%BE%D0%B2%D1%81%D0%BA%D0%B0%D1%8F_%D0%9C/sem2/lab1/%D0%A1%D0%BD%D0%B8%D0%BC%D0%BE%D0%BA%20%D1%8D%D0%BA%D1%80%D0%B0%D0%BD%D0%B0%202025-03-20%20075605.)
## Описание алгоритмов:
Для работы со множествами я использую стандартный шаблон std:: vector.Вектор хранит элементы заданного типа в линейном расположении и обеспечивает быстрый случайный доступ к любому элементу. Для создания множества пользователю необходимо ввести его мощность и значение каждого элемента.В моей программе эта операция реализована следующим образом:
```
bool getInput(int& value) {
    string input;
    while (true) {
        getline(cin, input); 

       
        stringstream ss(input);
        if (ss >> value && ss.eof()) {
            return true; 
        }
        else {
            cout << "Ошибка: введите число." << endl;
        }
    }
}
```
где getInput(int& value) -функция проверки на нечисловой ввод;
```
void insert(int element) {
    if (!contains(element)) {
        elements.push_back(element);
    }
}
```
гле insert(int element) -функция добавления элемента во множество. В основной программе пользователь вводит мощность множества, а затем значение каждого элемента, которое с помощью цикла for добавляется во множество
```
cout << "Введите мощность множества 1: ";
getInput(set1_n); 
cout << "Введите элементы множества 1: ";
for (int i = 0; i < set1_n; ++i) {
    cout << "Элемент " << (i + 1) << ": ";
    getInput(element); // Используем функцию для получения элемента
    set1.insert(element); // Вставляем элемент в множество
}
```
Затем выполняется функция проверки на пересекаемость двух введенных множеств. Если множества пересекаются, программа заканчивает работу:
```
bool intersects(const Set& other) const {
    for (const auto& elem : elements) {
        if (other.contains(elem)) {
            return true; 
        }
    }
    return false; // не пересекаются
}
```
*Объединение множеств*
Функция unite добавляет во множество объединения все элементы первого множества, а затем добавляет элементы второго.
```
Set unite(const Set& other) const {
 
    Set result;
    for (const auto& elem : elements) {
        result.insert(elem);
    }
    for (const auto& elem : other.elements) {
        result.insert(elem); 
    }
```
*Поиск элеметва во множествах*
```
bool contains(int element) const {
    return std::find(elements.begin(), elements.end(), element) != elements.end();
}
```
## Файл Header.h:
```
#ifndef SET_H
#define SET_H

#include <iostream>
#include <vector>
#include <algorithm>

class Set {
public:
    std::vector<int> elements;

    // Добавление элемента
    void insert(int element);

    // Отображение элементов
    void display() const;

    // Наличие элемента
    bool contains(int element) const;

    // Объединение двух множеств
    Set unite(const Set& other) const;

    // Пересечение
    bool intersects(const Set& other) const;
};

#endif // SET_H
```
## Тестовая программа:
```
#include "Header.h"
#include <iostream>
#include <limits>
#include <string>
#include <sstream> 
using namespace std;


bool getInput(int& value) {
    string input;
    while (true) {
        getline(cin, input); 

       
        stringstream ss(input);
        if (ss >> value && ss.eof()) {
            return true; 
        }
        else {
            cout << "Ошибка: введите число." << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    Set set1, set2;

    int set1_n, set2_n, element, input;

    cout << "Введите мощность множества 1: ";
    getInput(set1_n); 

    cout << "Введите мощность множества 2: ";
    getInput(set2_n); 

    cout << "Введите элементы множества 1: ";
    for (int i = 0; i < set1_n; ++i) {
        cout << "Элемент " << (i + 1) << ": ";
        getInput(element); // Используем функцию для получения элемента
        set1.insert(element); // Вставляем элемент в множество
    }

    cout << "Введите элементы множества 2: ";
    for (int i = 0; i < set2_n; ++i) {
        cout << "Элемент " << (i + 1) << ": ";
        getInput(element); // Используем функцию для получения элемента
        set2.insert(element); // Вставляем элемент в множество
    }

    if (set1.intersects(set2)) {
        std::cout << "Множества пересекаются. Программа завершает работу." << std::endl;
        return 0;
    }

    int choice;
    do {
        cout << "\nВыберите действие:\n";
        cout << "1 - Объединение множеств\n";
        cout << "2 - Поиск элемента\n";
        cout << "3 - Выход\n";
        cout << "Ваш выбор: ";
        getInput(choice); 

        switch (choice) {
        case 1: {
            // Объединение 
            Set unionSet = set1.unite(set2);
            std::cout << "Объединение множеств: ";
            unionSet.display();
            break;
        }
        case 2: {
            // Поиск элемента
            std::cout << "Введите элемент для поиска: ";
            getInput(input); // Используем функцию для получения элемента

            if (set1.contains(input)) {
                std::cout << "Элемент " << input << " найден в первом множестве." << std::endl;
            }
            else if (set2.contains(input)) {
                std::cout << "Элемент " << input << " найден во втором множестве." << std::endl;
            }
            else {
                std::cout << "Элемент " << input << " не найден." << std::endl;
            }
            break;
        }
        case 3:
            std::cout << "Выход из программы." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова." << std::endl;
            break;
        }
    } while (choice != 3);

    return 0;
}
```
## Вывод: 
в ходе лабораторной работы освоили навыки работы со структурами и классами языка программирования C++. Разработали библиотеку для создания множеств с помощью std::vector, проверки их пересекаемости, объединения и поиска множества с заданным элементов, а также тестовую программу для проверки работы библиотеки.
## Источники:
https://metanit.com/cpp/tutorial/7.4.php

https://education.yandex.ru/handbook/cpp/article/classes

https://codelessons.dev/ru/vektory-v-c-dlya-nachinayushhix/

https://codelessons.dev/ru/vector-insert-in-cplusplus/
