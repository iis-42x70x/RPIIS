<h1>Лабораторная работа №2</h1>

## Вариант 3
 Реализовать программу, формирующую множество равное симметрической разности произвольного количества исходных множеств (без учёта кратных вхождений элементов).

## Цели работы
1. Исследовать свойства структур данных и разработать библиотеку алгоритмов обработки структур данных.
2. Изучение и реализация алгоритма формирования множества, равного булеану произвольного исходного множества.

## Задачи работы 
1. Исследовать теоретические основы операций с множествами, включая построение булеана.  
2. Создать алгоритм генерации булеана для заданного множества.  
3. Протестировать программу на разных входных данных, чтобы убедиться в правильности её работы.  
4. Оценить результаты тестирования, сопоставив их с ожидаемыми значениями.  
5. Реализовать тесты в GoogleTest для проверки корректности всех функций программы.

## Понятия
**Множество** – это структурированный тип данных, представляющий собой набор взаимосвязанных по какому-либо признаку или группе признаков неповторяющихся объектов, которые можно рассматривать как единое целое.

**Симметрическая разность** – это набор элементов, которые принадлежат либо первому, либо второму множеству, но не их пересечению. Иными словами, симметрическая разность содержит все элементы обоих множеств, кроме общих.

 $$
A \triangle B = (A \setminus B) \cup (B \setminus A)
$$

**Пример симметрической разностью:**
```math
\begin{aligned}
A &= \{a, b, c, d\} \\
B &= \{b, c, e, f\} \\
A \triangle B &= \{a, d, e, f\}
\end{aligned}
```

## Функция для вычесления симметрической разности

```C++
void symmetricDifference(std::string* set1, int count1, std::string* set2, int count2, std::string* result, int& resultCount) {
    resultCount = 0;

    
    for (int i = 0; i < count1; ++i) {
        bool found = false;
        for (int j = 0; j < count2; ++j) {
            if (areElementsEqual(set1[i], set2[j])) {
                found = true;
                break;
            }
        }
        if (!found) {
            result[resultCount++] = set1[i];
        }
    }

   
    for (int i = 0; i < count2; ++i) {
        bool found = false;
        for (int j = 0; j < count1; ++j) {
            if (areElementsEqual(set2[i], set1[j])) {
                found = true;
                break;
            }
        }
        if (!found) {
            result[resultCount++] = set2[i];
        }
    }

    
    removeDuplicates(resultCount, result);
}
```

## Реализация тестов

``` C++
#include <gtest/gtest.h>
#include "pch.h"
#include "Header.h"
#include <fstream>
#include <cstdio>

// Тесты для removeSpaces
TEST(RemoveSpacesTest, BasicTest) {
    EXPECT_EQ(removeSpaces("a b c"), "abc");
    EXPECT_EQ(removeSpaces("  { a , b }  "), "{a,b}");
}

TEST(RemoveSpacesTest, EmptyString) {
    EXPECT_EQ(removeSpaces(""), "");
}

// Тесты для sortString
TEST(SortStringTest, SimpleSort) {
    EXPECT_EQ(sortString("cba"), "abc");
    EXPECT_EQ(sortString("dcba"), "abcd");
}

TEST(SortStringTest, AlreadySorted) {
    EXPECT_EQ(sortString("abc"), "abc");
}

// Тесты для sortNestedSet
TEST(SortNestedSetTest, NestedElements) {
    EXPECT_EQ(sortNestedSet("{b,a}"), "{a,b}");
    EXPECT_EQ(sortNestedSet("{b,{d,c},a}"), "{a,b,{c,d}}");
    EXPECT_EQ(sortNestedSet("{{d,c},b,a}"), "{a,b,{c,d}}");
}

// Тесты для areElementsEqual
TEST(AreElementsEqualTest, EqualElements) {
    EXPECT_TRUE(areElementsEqual("{a,b}", "{b,a}"));
    EXPECT_TRUE(areElementsEqual("{{c,d},a}", "{a,{d,c}}"));
    EXPECT_FALSE(areElementsEqual("{a,b}", "{a,c}"));
}

// Тесты для extractElements
TEST(ExtractElementsTest, SimpleSet) {
    std::string elements[10];
    int count = 0;
    extractElements("{a,b,c}", elements, count);

    ASSERT_EQ(count, 3);
    EXPECT_EQ(elements[0], "a");
    EXPECT_EQ(elements[1], "b");
    EXPECT_EQ(elements[2], "c");
}

TEST(ExtractElementsTest, NestedSet) {
    std::string elements[10];
    int count = 0;
    extractElements("{a,{b,c},d}", elements, count);

    ASSERT_EQ(count, 3);
    EXPECT_EQ(elements[0], "a");
    EXPECT_EQ(elements[1], "{b,c}");
    EXPECT_EQ(elements[2], "d");
}

// Тесты для removeDuplicates
TEST(RemoveDuplicatesTest, BasicTest) {
    std::string elements[] = { "a", "b", "a", "c" };
    int count = 4;

    removeDuplicates(count, elements);

    ASSERT_EQ(count, 3);
    EXPECT_EQ(elements[0], "a");
    EXPECT_EQ(elements[1], "b");
    EXPECT_EQ(elements[2], "c");
}

// Тесты для symmetricDifference
TEST(SymmetricDifferenceTest, BasicTest) {
    std::string set1[] = { "a", "b" };
    std::string set2[] = { "b", "c" };
    std::string result[10];
    int resultCount = 0;

    symmetricDifference(set1, 2, set2, 2, result, resultCount);

    ASSERT_EQ(resultCount, 2);
    EXPECT_TRUE(areElementsEqual(result[0], "a"));
    EXPECT_TRUE(areElementsEqual(result[1], "c"));
}

// Тесты для save/load
TEST(SaveLoadTest, FileOperations) {
    const char* filename = "test_temp.txt";
    std::string sets[] = { "{a,b}", "{b,c}" };
    std::string elements[] = { "a", "c" };

    // Тестирование сохранения
    save(sets, 2, elements, 2, filename);

    // Проверка содержимого файла
    std::ifstream fin(filename);
    ASSERT_TRUE(fin.is_open());

    std::string line;
    std::getline(fin, line);
    EXPECT_EQ(line, "Количество множеств: 2");

    // Тестирование загрузки
    std::string loaded_sets[10];
    std::string loaded_elements[10];
    int loaded_sets_count = 0, loaded_count = 0;

    load(loaded_sets, loaded_sets_count, loaded_elements, loaded_count, filename);

    EXPECT_EQ(loaded_sets_count, 2);
    EXPECT_EQ(loaded_count, 2);
    EXPECT_TRUE(areElementsEqual(loaded_elements[0], "a"));
    EXPECT_TRUE(areElementsEqual(loaded_elements[1], "c"));

    fin.close();
    std::remove(filename);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## Результат выполнения тестов 






## Вывод

В результате выполнения данной работы были получены следующие практические навыки: Изучение теории множеств и выполнения операций над ними; Работа header-файлами.

## Используемые источники

1) **Создание библиотеки** :(https://www.youtube.com/watch?v=pAxEfF2yVlM&t=1s)
2) **Учебное пособие "Дискретная математика", В.Е. Алексеев.** :[itmm.unn.ru](https://itmm.unn.ru/wp-content/uploads/sites/19/2020/04/DM-MM-uchebnik.pdf)
3) **GoogleTests** (https://github.com/google/googletest/blob/main/docs/primer.md)

