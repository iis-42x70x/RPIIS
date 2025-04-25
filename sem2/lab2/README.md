# Лабораторная работа №2

# :dart: Цель
* Изучить основы теории множеств и операций над ними
* Разроботать программу выполняюую задание
* Разработать тесты, проверяющие корректное выполнение программы

# :pushpin: Постановка задачи (Вариант 8)
Реализовать программу, формирующую без повторений всевозможные неориентированные множества из элементов исходного неориентированного множества,
количество элементов в сформированных множествах должно быть равно исходному натуральному n.

# :book: Список используемых понятий
**Множество** – простейшая информационная конструкция и математическая структура, позволяющая рассматривать какие-то объекты как целое, связывая их.

**Элементы множества** – объекты, связываемые некоторым множеством.

**Неориентированное множество** – это множество элементов, где порядок следования данных элементов не имеет значения.
Например, неориентированное множество, имеющее малое количество вхождений, может быть представлено в тексте в следующем виде:

`S = {a, b, a, a, c}.`

Элементы a, b и c принадлежат множеству с именем S, причём множество S имеет три вхождения элемента *a* и по одному вхождению элементов *b* и *c*

# :mag: Описание программы и алгоритмов
Проект состоит из 4 файлов: `main.cpp`, `source.cpp`(SetParser.cpp), `header.h`(SetParser.h), `test.cpp`. Файл `main.cpp` содержит функцию main, в которой реализована логика обработки аргументов командной строки, запроса имени входного файла, вызов основной функции обработки множества. Файл `header.h` - заголовочный файл, включающий в себя объявления функций, подключение библиотек. Основные функции описаны в `source.cpp` (функции для разбора входной строки с множеством, генерации уникальных перестановок элементов, а также для чтения входных данных и записи результата в файл). Также есть файл  `test.cpp` с тестами для проверки работоспособности программы с помощью GoogleTest.
# main.cpp
```
#include "pch.h"
#include <locale>
int main(int argc, char* argv[]) {
    string filename;
    if (argc > 1) filename = argv[1];
    else {
        while (true) {
            if (filename.empty()) {
                cout << "Enter file name: ";
                cin >> filename;
            }
            ifstream file(filename);
            if (file) {
                file.close();
                break;
            }
            cerr << "Error: we can't open this file. Try again\n";
            filename.clear();
        }
    }
    findAllCombinations(filename);
    cout << "You can see results in output.txt" << endl;
    return 0;
}
```
# SetParser.cpp
```
#include "pch.h"

vector<string> string_to_vector_OfSetElements(const string& str) {
    vector<string> setElements;
    string temp;
    int braceLevel = 0;
    int angleLevel = 0;

    if (str == "{}")  return setElements;

    if (str.empty()  str.front() != '{'   str.back() != '}') {
        cerr << "Error: Wrong input \n";
        return {};
    }

    string cleanStr = str.substr(1, str.length() - 2);

    for (size_t i = 0; i < cleanStr.length(); ++i) {
        char ch = cleanStr[i];

        if (ch == '{') {
            braceLevel++;
            temp += ch;
        }
        else if (ch == '}') {
            braceLevel--;
            if (braceLevel < 0) {
                cerr << "Error: Unmatched closing curly brace\n";
                return {};
            }
            temp += ch;
        }
        else if (ch == '<') {
            angleLevel++;
            temp += ch;
        }
        else if (ch == '>') {
            angleLevel--;
            if (angleLevel < 0) {
                cerr << "Error: Unmatched closing angle bracket\n";
                return {};
            }
            temp += ch;
        }
        else if (ch == ',' && braceLevel == 0 && angleLevel == 0) {
            if (!temp.empty()) {
                setElements.push_back(temp);
                temp.clear();
            }
            else {
                cerr << "Error: Invalid comma placement\n";
                return {};
            }
        }
        else {
            temp += ch;
        }
    }

    if (braceLevel != 0 || angleLevel != 0) {
        cerr << "Error: Unmatched braces or angle brackets\n";
        return {};
    }

    if (!temp.empty()) {
        setElements.push_back(temp);
    }

    return setElements;
}

void permute(vector<string>& setElements, int l, int r, vector<vector<string>>& result) {
    if (l == r) {
        result.push_back(setElements);
        return;
    }
    for (int i = l; i <= r; ++i) {
        swap(setElements[l], setElements[i]);
        permute(setElements, l + 1, r, result);
        swap(setElements[l], setElements[i]);
    }
}

vector<vector<string>> generateUniquePermutations(const vector<string>& setElements) {
    vector<vector<string>> allPerms;
    vector<string> temp = setElements;
    permute(temp, 0, temp.size() - 1, allPerms);

    set<vector<string>> uniqueSets;
    for (auto& p : allPerms) {
        uniqueSets.insert(p);
    }

    return vector<vector<string>>(uniqueSets.begin(), uniqueSets.end());
}

void findAllCombinations(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open input file!\n";
        return;
    }

    string line;
    getline(file, line);
    file.close();

    vector<string> elements = string_to_vector_OfSetElements(line);
    if (elements.empty()) {
        cerr << "Error: Failed to parse elements from input.\n";
        return;
    }

    vector<vector<string>> uniquePermutations = generateUniquePermutations(elements);

    ofstream outputFile("output.txt");
    if (!outputFile) {
        cerr << "Error: Unable to create output file\n";
        return;
    }

    for (const auto& permutation : uniquePermutations) {
        cout << "{ ";
        outputFile << "{ ";
        for (size_t i = 0; i < permutation.size(); ++i) {
            cout << permutation[i];
            outputFile << permutation[i];
            if (i < permutation.size() - 1) {
                cout << ", ";
                outputFile << ", ";
            }
        }
        cout << " }\n";
        outputFile << " }\n";
    }

    outputFile.close();
}
```
# SetParser.h
```
#pragma once
#ifndef SETPARSER_H
#define SETPARSER_H
#include <string>
#include <vector>

#include <set>


using namespace std;

vector<string> string_to_vector_OfSetElements(const string& str);
void permute(vector<string>& setElements, int l, int r, vector<vector<string>>& result);
vector<vector<string>> generateUniquePermutations(const vector<string>& setElements);
void findAllCombinations(const string& filename);
#endif
```
# pch.h
```
#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <set>
#include <algorithm>
```
# pch.cpp
```
//
// pch.cpp
//

#include "pch.h"
```
# test.cpp
```
#include "pch.h"
#include <gtest/gtest.h>
#include "SetParser.h"

TEST(TestCaseName, TestName) {//Это шаблонный тест, проверяет, что 1==1 и true это действительно true
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(string_to_vector_OfSetElementsTest, BasicCases) {//Проверяет корректное разибение множества в виде строки
//удаляет внешние фигурные скобки и разделяет строку по запятым, если они не находятся внутри вложенных скобок (< >, { }).
    EXPECT_EQ(string_to_vector_OfSetElements("{a,b,c}"), (std::vector<std::string>{"a", "b", "c"}));
    EXPECT_EQ(string_to_vector_OfSetElements("{1,2,3}"), (std::vector<std::string>{"1", "2", "3"}));
    EXPECT_EQ(string_to_vector_OfSetElements("{<x,y>,z}"), (std::vector<std::string>{"<x,y>", "z"}));
    EXPECT_EQ(string_to_vector_OfSetElements("{a,b,c}"), (std::vector<std::string>{"a", "b", "c"}));
}

TEST(string_to_vector_OfSetElementsTest, EmptySet) {//Проверяем обработку пустого множества
    std::vector<std::string> expected = {};
    EXPECT_EQ(string_to_vector_OfSetElements("{}"), expected);
}

TEST(string_to_vector_OfSetElementsTest, EmptyElements) {//Проверка строки с запятыми, но без элементов
  
    std::vector<std::string> expected = {};
    EXPECT_EQ(string_to_vector_OfSetElements("{,,}"), expected);
}

TEST(string_to_vector_OfSetElementsTest, InvalidInput) {//Проверка строки без закрывающей скобки,выводится ошибка и возвращается пустой вектор
   
    std::vector<std::string> expected = {};
    EXPECT_EQ(string_to_vector_OfSetElements("{a, b, c"), expected);
}

TEST(generateUniquePermutationsTest, BasicCases) {//Проверка генерации всех перестановок множества, permute генерирует их, set удаляет дубликаты
    std::vector<std::string> set1 = { "a", "b", "c" };
    auto permutations1 = generateUniquePermutations(set1);
    EXPECT_EQ(permutations1.size(), 6); // 3! = 6

    std::vector<std::string> set2 = { "1", "2" };
    auto permutations2 = generateUniquePermutations(set2);
    EXPECT_EQ(permutations2.size(), 2); // 2! = 2
    EXPECT_TRUE(std::find(permutations2.begin(), permutations2.end(), std::vector<std::string>{"1", "2"}) != permutations2.end());
    EXPECT_TRUE(std::find(permutations2.begin(), permutations2.end(), std::vector<std::string>{"2", "1"}) != permutations2.end());
}
```

# :point_right: Выводы
В результате данной лабораторной работы была реализована программа, формирующая без повторений всевозможные неориентированные множества из элементов 
исходного неориентированного множества, количество элементов в сформированных множествах которого должно быть равно исходному натуральному n, а также был 
реализован алгоритм формирования неповторяющихся перестановок исходного множества.Вся логика программы направлена на корректную обработку ввода, включая вложенные множества и кортежи, проверку синтаксической корректности, а также генерацию всех возможных уникальных комбинаций элементов.

# :computer: Список использованных источников
1.  Множества \[Электронный ресурс\]. – Режим доступа: [ЛР2/Множества](https://drive.google.com/drive/folders/1SLcF9njDTaNUacXMA9Nrqm7FUS7MnNsI).
2. Седжвик Р. Алгоритмы на C++. – М.: ДМК Пресс, 2011.
3. Страуструп Б. Язык программирования C++. – М.: БХВ-Петербург, 2015.
4. Верещагин Н., Шень А. Начала теории множеств. – М.: МЦНМО, 2012.
