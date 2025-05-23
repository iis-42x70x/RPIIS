# Лабораторная работа №2

# Цель
* Изучить основы теории множеств и операций над ними
* Разроботать программу выполняюую задание
* Разработать тесты, проверяющие корректное выполнение программы

# Постановка задачи (Вариант 6)
Реализовать программу, формирующую множество равное декартовому произведению произвольного количества исходных множеств.

# Список используемых понятий
**Множество** – простейшая информационная конструкция и математическая структура, позволяющая рассматривать какие-то объекты как целое, связывая их.

**Элементы множества** – объекты, связываемые некоторым множеством.

**Неориентированное множество** – это множество элементов, где порядок следования данных элементов не имеет значения.
Например, неориентированное множество, имеющее малое количество вхождений, может быть представлено в тексте в следующем виде:

`S = {a, b, a, a, c}.`

Элементы a, b и c принадлежат множеству с именем S, причём множество S имеет три вхождения элемента *a* и по одному вхождению элементов *b* и *c*

# Описание программы и алгоритмов
Проект состоит из 4 файлов: `LAB_2_2_2.cpp`, `SetParser.cpp`, `pch.h`, `SetParser.h`, `test.cpp`. Файл `LAB_2_2_2.cpp` содержит функцию main, в которой реализована логика обработки аргументов командной строки, запроса имени входного файла, вызов основной функции обработки множества. Файл `SetParser.h` - заголовочный файл, включающий в себя объявления функций, подключение библиотек. Основные функции описаны в `SetParser.cpp` (функции для разбора входной строки с множеством, генерации уникальных перестановок элементов, а также для чтения входных данных и записи результата в файл). Также есть файл  `test.cpp` с тестами для проверки работоспособности программы с помощью GoogleTest. В файле `pch.h` объявоены библиотеки, использующиеся в программе.
# LAB_2_2_2.cpp
```
#include <gtest/gtest.h>
#include "SetParser.h"

TEST(ParseTest, BasicParsing) {
    auto result = string_to_vector("{a,b,c}");
    EXPECT_EQ(result, (std::vector<std::string>{"a", "b", "c"}));
}

TEST(CartesianProductTest, TwoSets) {
    std::vector<std::vector<std::string>> sets = {
        {"1", "2"},
        {"x", "y"}
    };
    auto result = cartesianProduct(sets);
    EXPECT_EQ(result.size(), 4);
    EXPECT_TRUE(std::find(result.begin(), result.end(), std::vector<std::string>{"1", "x"}) != result.end());
    EXPECT_TRUE(std::find(result.begin(), result.end(), std::vector<std::string>{"2", "y"}) != result.end());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```
# SetParser.cpp
```
#include "pch.h"
#include "SetParser.h"

vector<string> string_to_vector(const string& str) {
    vector<string> result;
    string temp;
    if (str.empty() || str.front() != '{' || str.back() != '}') return result;
    string cleanStr = str.substr(1, str.size() - 2);

    for (char ch : cleanStr) {
        if (ch == ',') {
            if (!temp.empty()) {
                result.push_back(temp);
                temp.clear();
            }
            else
                continue;
                 
        }
        else temp += ch;
    }
    if (!temp.empty()) result.push_back(temp);
    return result;
}

vector<vector<string>> parseMultipleSets(const string& filename) {
    ifstream file(filename);
    vector<vector<string>> sets;
    string line;
    while (getline(file, line)) {
        vector<string> parsedSet = string_to_vector(line);
        if (!parsedSet.empty()) sets.push_back(parsedSet);
    }
    return sets;
}

vector<vector<string>> cartesianProduct(const vector<vector<string>>& sets) {
    vector<vector<string>> result = { {} };

    for (const auto& set : sets) {
        vector<vector<string>> temp;
        for (const auto& prefix : result) {
            for (const auto& elem : set) {
                auto newTuple = prefix;
                newTuple.push_back(elem);
                temp.push_back(newTuple);
            }
        }
        result = move(temp);
    }

    return result;
}

void calculateCartesianProduct(const string& filename) {
    vector<vector<string>> sets = parseMultipleSets(filename);
    if (sets.empty()) {
        cerr << "Error: No sets parsed.\n";
        return;
    }

    vector<vector<string>> product = cartesianProduct(sets);
    ofstream output("output.txt");

    for (const auto& tuple : product) {
        output << "< ";
        cout << "< ";
        for (size_t i = 0; i < tuple.size(); ++i) {
            output << tuple[i];
            cout << tuple[i];
            if (i < tuple.size() - 1) {
                output << ", ";
                cout << ", ";
            }
        }
        output << " >\n";
        cout << " >\n";
    }
}
```
# SetParser.h
```
#pragma once
#ifndef SETPARSER_H
#define SETPARSER_H

#include <string>
#include <vector>

using namespace std;

vector<string> string_to_vector(const string& str);
vector<vector<string>> parseMultipleSets(const string& filename);
vector<vector<string>> cartesianProduct(const vector<vector<string>>& sets);
void calculateCartesianProduct(const string& filename);

#endif
```
# pch.h
```
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

```
# test.cpp
```
#include <gtest/gtest.h>
#include "SetParser.h"



TEST(ParseTest, SimpleSet) 
{
    auto result = string_to_vector("{a,b,c}");
    EXPECT_EQ(result, (std::vector<std::string>{"a", "b", "c"}));
}

TEST(ParseTest, EmptySet) 
{
    auto result = string_to_vector("{}");
    EXPECT_TRUE(result.empty());
}

TEST(ParseTest, SetWithWhitespace) // Лишние пробелы
{
    auto result = string_to_vector("{ a , b , c }");
    
    EXPECT_EQ(result, (std::vector<std::string>{" a ", " b ", " c "}));
}

TEST(ParseTest, NoBraces) // Нет фигурных скобок
{
    auto result = string_to_vector("a,b,c");
    EXPECT_TRUE(result.empty()); 
}

TEST(ParseTest, MalformedInput_UnclosedBrace) // нет закрытия
{ 
    auto result = string_to_vector("{a,b,c");
    EXPECT_TRUE(result.empty());
}

TEST(ParseTest, SingleElementSet) // словл
{
    auto result = string_to_vector("{solo}");
    EXPECT_EQ(result, (std::vector<std::string>{"solo"}));
}

TEST(CartesianTest, TwoSets) {
    std::vector<std::vector<std::string>> sets = {
        {"1", "2"},
        {"a", "b"}
    };
    auto result = cartesianProduct(sets);
    EXPECT_EQ(result.size(), 4);
    EXPECT_TRUE(std::find(result.begin(), result.end(), std::vector<std::string>{"1", "a"}) != result.end());
    EXPECT_TRUE(std::find(result.begin(), result.end(), std::vector<std::string>{"2", "b"}) != result.end());
}

TEST(CartesianTest, ThreeSetsWithSingleElement) {
    std::vector<std::vector<std::string>> sets = {
        {"x"},
        {"y"},
        {"z"}
    };
    auto result = cartesianProduct(sets);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], (std::vector<std::string>{"x", "y", "z"}));
}

TEST(CartesianTest, OneEmptySet) {
    std::vector<std::vector<std::string>> sets = {
        {"1", "2"},
        {},
        {"a", "b"}
    };
    auto result = cartesianProduct(sets);
    EXPECT_TRUE(result.empty());
}

TEST(CartesianTest, AllEmptySets) {
    std::vector<std::vector<std::string>> sets = {
        {},
        {},
        {}
    };
    auto result = cartesianProduct(sets);
    EXPECT_TRUE(result.empty());
}

TEST(CartesianTest, LargeSetCombination) {
    std::vector<std::vector<std::string>> sets = {
        {"a", "b", "c", "d", "e"},
        {"1", "2", "3"},
        {"x", "y"}
    };
    auto result = cartesianProduct(sets);
    EXPECT_EQ(result.size(), 5 * 3 * 2);
}

TEST(CartesianTest, SingleSet) {
    std::vector<std::vector<std::string>> sets = {
        {"a", "b", "c"}
    };
    auto result = cartesianProduct(sets);
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0].size(), 1);
}

TEST(CartesianTest, NoSets) {
    std::vector<std::vector<std::string>> sets = {};
    auto result = cartesianProduct(sets);
    EXPECT_EQ(result.size(), 1); 
    EXPECT_TRUE(result[0].empty());
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
