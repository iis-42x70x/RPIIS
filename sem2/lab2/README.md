# 📚Лабораторная работа №2. Множества
## ❓Цель работы
- Научиться работать с множествами.
- Научиться разрабатывать алгоритм выполнения операции объединения произвольного количества амножеств с учетом кратности вхождиения элементов.
## 💭Задачи
- Разработать алгоритм одной из операций над множествами.
- Разработать систему тестов, которые продемонстрировали бы работоспособность реализованного алгоритма.
## #️⃣Вариант
Мой вариант – вариант 10 [методички](https://drive.google.com/drive/folders/1_xy849HXgTDetxSMlFd0KikTBo8-xalN). Нужно реализовать алгоритм вычисления декртова произведения N множеств.
## 📋Список используемых при решении задачи понятий
- Множество – одно из ключевых понятий математики, представляющее собой набор, совокупность объектов любой природы.
- Элементы множества – объекты, составляющие множество.
- Объект принадлежит множеству тогда и только тогда, когда он является его элементом.
- Говорят, что если объект принадлежит множеству, то существует вхождение этого элемента в множество. Допускается неограниченное количество вхождений
одного объекта в какое-либо множество.
- Множеством с кратными вхождениями элементов называют множество _S_ тогда и только тогда, когда существует _x_ такой, что истинно _S|x|_ > 1.

## 🌚Реализация
Создадим два файла, один для декларации и второй для реализации.
Создадим необходимый заголовчный файл:
```C++
#ifndef SETSOPERATIONS_H
#define SETSOPERATIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;


void displaySets(vector<string> sets);
void readFile(vector<string>& sets, ifstream& inputFile);
vector<string> extractElements(const string& setString);
void unionSets(vector<string>& sets, string& initialResult);

#endif
```
Для начала нужно организовать чтение из файла. Делать это будем построчно с закидыванием каждой строки(множества) в созданный вектор
```C++
#include "SetOperations.h"

void displaySets(vector<string> sets) {
    if (sets.empty()) {
        cout << "Нет загруженных множеств" << endl;
        return;
    }
    
    for (size_t i = 0; i < sets.size(); i++) {
        cout << "Множество " << i + 1 << " :" << endl;
        cout << "{" << sets[i] << "}" << endl;
    }
    cout << "Всего множеств: " << sets.size() << endl;
    cout << "----------------------" << endl;
}

void readFile(vector<string>& sets, ifstream& inputFile) {
    if (!inputFile.is_open()) {
        return;
    }
    
    string line;
    while (getline(inputFile, line)) {
        if (!line.empty()) {
            sets.push_back(line);
        }
    }
    inputFile.close();
}
```
Теперь создадим функцию, чтобы найти все самостоятельные элементы в множестве. Чтобы программа различала и подмножества, и кортежи, добавим соответствующие счетчики и необходимую логику реализации
```C++
vector<string> extractElements(const string& setString) {
    vector<string> elements;
    string currentElement;
    int braceDepth = 0;
    int angleDepth = 0; 

    for (char c : setString) {
        if (c == '{' || c == '<') {
            if (c == '{') braceDepth++;
            if (c == '<') angleDepth++;
            currentElement += c;
        }
        else if (c == '}' || c == '>') {
            if (c == '}') braceDepth--;
            if (c == '>') angleDepth--;
            currentElement += c;
            if (braceDepth < 0 || angleDepth < 0) {
                cerr << "Ошибка: неверная вложенность скобок" << endl;
                return elements;
            }
        }
        else if (c == ' ' && braceDepth == 0 && angleDepth == 0) {
            if (!currentElement.empty()) {
                elements.push_back(currentElement);
                currentElement.clear();
            }
        }
        else {
            currentElement += c;
        }
    }
    if (!currentElement.empty()) {
        elements.push_back(currentElement);
    }
    return elements;
}

```
Ну и наконец, функцию с самим объединением множеств
```C++
void unionSets(vector<string>& sets, string& initialResult) {
    if (sets.empty()) {
        cout << "Нет множеств для объединения" << endl;
        initialResult = "{}";
        return;
    }

    map<string, int> elementMultiplicity;

    for (const string& set : sets) {
        vector<string> elements = extractElements(set);
        map<string, int> currentSetMultiplicity;
        for (const string& element : elements) {
            currentSetMultiplicity[element]++;
        }
        
        for (const auto& pair : currentSetMultiplicity) {
            if (elementMultiplicity[pair.first] < pair.second) {
                elementMultiplicity[pair.first] = pair.second;
            }
        }
    }

    string finalResult;
    bool firstElement = true;
    
    for (const auto& pair : elementMultiplicity) {
        string element = pair.first;
        int count = pair.second;
        
        for (int i = 0; i < count; i++) {
            if (!firstElement) {
                finalResult += " ";
            }
            finalResult += element;
            firstElement = false;
        }
    }

    cout << "Результат объединения (" << sets.size() << " множеств):" << endl;
    cout << "{" << finalResult << "}" << endl;
    initialResult = "{" + finalResult + "}";
}

```
Часть программы, с которой пользователь будет работать через консоль
```C++
void showMenu() {
    cout << "\n=== Меню работы с множествами ===\n";
    cout << "1. Загрузить множества из файла\n";
    cout << "2. Показать загруженные множества\n";
    cout << "3. Выполнить объединение множеств\n";
    cout << "4. Очистить текущие множества\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}

int main() {
    vector<string> sets;
    string result;
    int choice;

    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                ifstream inputFile("/Users/matvejnevodnicenko/projects/C/C++/HashTable/HashTable/sets.txt");
                if (inputFile.is_open()) {
                    sets.clear();
                    readFile(sets, inputFile);
                    if (sets.empty()) {
                        cout << "Файл sets.txt пуст или содержит только пустые строки\n";
                    } else {
                        cout << "Загружено " << sets.size() << " множеств из файла sets.txt\n";
                    }
                } else {
                    cout << "Не удалось открыть файл sets.txt\n";
                }
                break;
            }
            case 2: {
                if (sets.empty()) {
                    cout << "Сначала загрузите множества из файла (пункт 1)\n";
                } else {
                    displaySets(sets);
                }
                break;
            }
            case 3: {
                if (sets.empty()) {
                    cout << "Сначала загрузите множества из файла (пункт 1)\n";
                } else {
                    unionSets(sets, result);
                }
                break;
            }
            case 4: {
                if (sets.empty()) {
                    cout << "Нет загруженных множеств для очистки\n";
                } else {
                    sets.clear();
                    result.clear();
                    cout << "Все множества очищены\n";
                }
                break;
            }
            case 0: {
                cout << "Программа завершена\n";
                break;
            }
            default: {
                cout << "Неверный выбор. Попробуйте снова\n";
                break;
            }
        }
    } while (choice != 0);

    return 0;
}

```
#Пример работы
Данные в текстовом файле:
```txt
A B C
<C>
<C>
B {C,D}
```
Вывод программы:
```txt
{<C> A B C {C,D}}
```
Еще один пример. Данные в текстовом файле:
```txt
A B B B C
<C> B A A
<C,D>
B {C,D}

```
Вывод программы:
```txt
{<C,D> <C> A A B B B C {C,D}}
```
Все тесты были успешно пройдены:

<img src="https://github.com/iis-42x70x/RPIIS/blob/Неводниченко_М/sem2/lab2/screens/IMAGE%202025-04-09%2019%3A31%3A13.jpg" alt="альтернативный текст" width ="650" height = "500" >
## Вывод
В ходе данной лабораторной работы я:
- Научился работать с множествами
- Разобрался в работе гугл тестов
