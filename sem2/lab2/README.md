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

# test.cpp
```
#include "pch.h"
#include <gtest/gtest.h>
#include "SetParser.h"

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(string_to_vector_OfSetElementsTest, BasicCases) {
    EXPECT_EQ(string_to_vector_OfSetElements("{a,b,c}"), (std::vector<std::string>{"a", "b", "c"}));
    EXPECT_EQ(string_to_vector_OfSetElements("{1,2,3}"), (std::vector<std::string>{"1", "2", "3"}));
    EXPECT_EQ(string_to_vector_OfSetElements("{<x,y>,z}"), (std::vector<std::string>{"<x,y>", "z"}));
    EXPECT_EQ(string_to_vector_OfSetElements("{a,b,c}"), (std::vector<std::string>{"a", "b", "c"}));
}

TEST(string_to_vector_OfSetElementsTest, EmptySet) {
    std::vector<std::string> expected = {};
    EXPECT_EQ(string_to_vector_OfSetElements("{}"), expected);
}

TEST(string_to_vector_OfSetElementsTest, EmptyElements) {
  
    std::vector<std::string> expected = {};
    EXPECT_EQ(string_to_vector_OfSetElements("{,,}"), expected);
}

TEST(string_to_vector_OfSetElementsTest, InvalidInput) {
   
    std::vector<std::string> expected = {};
    EXPECT_EQ(string_to_vector_OfSetElements("{a, b, c"), expected);
}

TEST(generateUniquePermutationsTest, BasicCases) {
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
