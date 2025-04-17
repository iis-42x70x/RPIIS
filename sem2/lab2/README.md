<h1>Лабараторная работа #2</h1>

## Цели работы:

* Изучить базовые понятия теории множеств
* Научиться реализовывать основные алгоритмы при работе со множествами

## Задачи:

* Разработать библиотеку для работы со множествами на любом императивном языке программирования
* Разработать тесты, которые демонстрирует работоспособность реализованной библиотеки

## Вариант:

3. Реализовать программу, формирующую множество равное симметрической разности произвольного количества исходных множеств (без учёта кратных вхождений элементов).

## Понятия:

<h4>Множество – простейшая информационная конструкция и математическая структура,позволяющая рассматривать какие-то объекты как целое, связывая их.</h4>
<h4>Элементы множества – объекты, связываемые некоторым множеством.</h4>
<h4>Множества бывают:</h4>

* Ориентированными (важен порядок элементов во множестве)
* Неориентированными (порядок элементов во множестве не важен)

<h4>Множество может быть задано с помощью:</h4>

* Механизма
* Процедуры
   * Разрешающая процедура - процедура, которая даёт ответ для любого объекта: является он или нет элементом некоторого множества
   * Порождающей процедура - процелура, которая позволяет получить любой новый элемент некоторого множества, отличный от известных или выданных ранее элементов этого множества.

<h4>Определение симметрической разности (для обычных множеств)</h4>

Симметрической разностью множеств $A$ и $B$ называется множество $S$, содержащее элементы, которые принадлежат ровно одному из исходных множеств:

$$
A \triangle B = (A \setminus B) \cup (B \setminus A)
$$

**Пример:**
```math
\begin{aligned}
A &= \{a, b, c, d\} \\
B &= \{b, c, e, f\} \\
A \triangle B &= \{a, d, e, f\}
\end{aligned}
```

## Структура программы:

<p align="center">
   <img alt="Структура" src="https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab2/img/1.png">
</p>

### Прилагаемые файлы:
* [test.cpp](https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab2/code/test.cpp) - тесты
* [Sets.cpp](https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab2/code/Sets.cpp) - реализация методов
* [Sets.hpp](https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab2/code/Sets.hpp) - header-файл

## Тесты:
* Тест 1
  
```cpp
// Тест 1: Создание пустого множества
TEST(SetTest, EmptySet) {
    Set s("empty", {});
    EXPECT_TRUE(s.getElements().empty());
    EXPECT_EQ(s.size(), 0);
}
```

* Тест 2
  
```cpp
// Тест 2: Добавление элементов
TEST(SetTest, AddElements) {
    Set s("test", {});
    s.addElement("a");
    s.addElement("b");
    EXPECT_EQ(s.size(), 2);
    EXPECT_TRUE(s.contains("a"));
    EXPECT_TRUE(s.contains("b"));
}
```

* Тест 3
  
```cpp
// Тест 3: Проверка contains()
TEST(SetTest, ContainsCheck) {
    Set s("test", { "a", "b", "c" });
    EXPECT_TRUE(s.contains("a"));
    EXPECT_FALSE(s.contains("d"));
}
```

* Тест 4
  
```cpp
// Тест 4: Симметрическая разность пустых множеств
TEST(SetTest, SymDiffEmptySets) {
    vector<Set> sets;
    Set result = Set::symmetricDifference(sets);
    EXPECT_TRUE(result.getElements().empty());
}
```

* Тест 5
  
```cpp
// Тест 5: Симметрическая разность одного множества
TEST(SetTest, SymDiffSingleSet) {
    vector<Set> sets = { Set("A", {"a", "b"}) };
    Set result = Set::symmetricDifference(sets);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(result.contains("a"));
    EXPECT_TRUE(result.contains("b"));
}
```

* Тест 6
  
```cpp
// Тест 6: Симметрическая разность двух непересекающихся множеств
TEST(SetTest, SymDiffDisjointSets) {
    vector<Set> sets = { Set("A", {"a", "b"}), Set("B", {"c", "d"}) };
    Set result = Set::symmetricDifference(sets);
    EXPECT_EQ(result.size(), 4);
}
```

* Тест 7
  
```cpp
// Тест 7: Симметрическая разность двух пересекающихся множеств
TEST(SetTest, SymDiffOverlappingSets) {
    vector<Set> sets = { Set("A", {"a", "b"}), Set("B", {"b", "c"}) };
    Set result = Set::symmetricDifference(sets);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(result.contains("a"));
    EXPECT_TRUE(result.contains("c"));
}
```

* Тест 8
  
```cpp
// Тест 8: Симметрическая разность трёх множеств
TEST(SetTest, SymDiffThreeSets) {
    vector<Set> sets = { Set("A", {"a", "b"}), Set("B", {"b", "c"}), Set("C", {"c", "d"}) };
    Set result = Set::symmetricDifference(sets);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(result.contains("a"));
    EXPECT_TRUE(result.contains("d"));
}
```

* Тест 9
  
```cpp
// Тест 9: Парсинг множества из строки
TEST(SetTest, ParseSetFromString) {
    string line = "A = {a, b, c}";
    Set s = parseSet(line);
    EXPECT_EQ(s.getName(), "A");
    EXPECT_EQ(s.size(), 3);
}
```

* Тест 10
  
```cpp
// Тест 10: Парсинг множества с пробелами
TEST(SetTest, ParseSetWithSpaces) {
    string line = "B  =  {  x ,  y  , z }";
    Set s = parseSet(line);
    EXPECT_EQ(s.getName(), "B");
    EXPECT_EQ(s.size(), 3);
}
```

* Тест 11
  
```cpp
// Тест 11: Удаление пробелов
TEST(SetTest, RemoveSpaces) {
    string input = "   a  ,         b      ,              c    ";
    string result = removeSpaces(input);
    EXPECT_EQ(result, "a, b, c");
}
```

* Тест 12
  
```cpp
// Тест 12: Чтение множеств из файла
TEST(SetTest, ReadSetsFromFile) {
    // Создаём временный файл для теста
    ofstream tmp("test_sets.txt");
    tmp << "A = {a, b}\nB = {b, c}\n";
    tmp.close();

    vector<Set> sets = readSetsFromFile("test_sets.txt");
    EXPECT_EQ(sets.size(), 2);
    remove("test_sets.txt");
}
```

* Тест 13
  
```cpp
// Тест 13: Обработка пустого файла
TEST(SetTest, ReadEmptyFile) {
    ofstream tmp("empty.txt");
    tmp.close();

    vector<Set> sets = readSetsFromFile("empty.txt");
    EXPECT_TRUE(sets.empty());
    remove("empty.txt");
}
```

* Тест 14
  
```cpp
// Тест 14: Обработка несуществующего файла
TEST(SetTest, ReadNonexistentFile) {
    vector<Set> sets = readSetsFromFile("nonexistent.txt");
    EXPECT_TRUE(sets.empty());
}
```

* Тест 15
  
```cpp
// Тест 15: Множество с повторяющимися элементами
TEST(SetTest, SetWithDuplicates) {
    Set s("test", { "a", "a", "b" });
    EXPECT_EQ(s.size(), 2); // Дубликаты должны быть удалены
}
```

* Тест 16
  
```cpp
// Тест 16: Симметрическая разность с пустым множеством
TEST(SetTest, SymDiffWithEmptySet) {
    vector<Set> sets = { Set("A", {"a", "b"}), Set("empty", {}) };
    Set result = Set::symmetricDifference(sets);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(result.contains("a"));
    EXPECT_TRUE(result.contains("b"));
}
```

* Тест 17
  
```cpp
// Тест 17: Комбинированный тест симметрической разности из файла для 2 множеств
TEST(SetTest, CombinedReadSetsFromFile) {
    // Создаём временный файл для теста
    ofstream tmp("test_sets.txt");
    tmp << "A_551 = {       a, b     }\nB_xs1 = {                b,  c, voidaaaaa   }\n";
    tmp.close();
    vector<Set> sets = readSetsFromFile("test_sets.txt");
    Set result = Set::symmetricDifference(sets);
    EXPECT_EQ(sets.size(), 2);
    EXPECT_TRUE(result.contains("a"));
    EXPECT_TRUE(result.contains("c"));
    EXPECT_TRUE(result.contains("voidaaaaa"));
    EXPECT_FALSE(result.contains("b"));
    remove("test_sets.txt");
}
```

* Тест 18
  
```cpp
// Тест 18: Комбинированный тест симметрической разности из файла для 2 множеств с кортежём
TEST(SetTest, CombinedReadSetsFromFile2) {
    // Создаём временный файл для теста
    ofstream tmp("test_sets.txt");
    tmp << "A_551 =  {     a      ,B,<c,<b,d   >            >}\nB= {a,B}";
    tmp.close();
    vector<Set> sets = readSetsFromFile("test_sets.txt");
    Set result = Set::symmetricDifference(sets);
    EXPECT_EQ(sets.size(), 2);
    EXPECT_TRUE(result.contains("<c,<b,d>>"));
    remove("test_sets.txt");
}
```

* Тест 19

```cpp
TEST(SetTest, ThreeSetsWithTuples) {
    ofstream tmp("test_sets.txt");
    tmp << "A = {a, b, <x, y>}\nB = {a, <x, y>, <z, w>}\nC = {b, <z, w>}";
    tmp.close();

    vector<Set> sets = readSetsFromFile("test_sets.txt");
    Set result = Set::symmetricDifference(sets);

    EXPECT_EQ(sets.size(), 3);
    EXPECT_EQ(result.size(), 0);  // Ожидается пустое множество
    remove("test_sets.txt");
}
```

* Тест 20

```cpp
TEST(SetTest, ThreeSetsWithTuplesResult) {
    ofstream tmp("test_sets.txt");
    tmp << "A = {a, b, <x, y>, <z,           w>}\nB = {a,    <x   , y>, <z, w>}\nC =            {  b   , <    z, w>}";
    tmp.close();

    vector<Set> sets = readSetsFromFile("test_sets.txt");
    Set result = Set::symmetricDifference(sets);

    EXPECT_TRUE(result.contains("<z, w>"));
    remove("test_sets.txt");
}
```

## Результат работы тестов: 

<img alt="result" src="https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab2/img/2.png">

## Вывод:
Мной была разработана библиотека по работе со множествами В ней я реализовал операцию симметрической разноти между несколькими множиствами.

## Материалы и источники:

* [itmm.unn.ru](https://itmm.unn.ru/wp-content/uploads/sites/19/2020/04/DM-MM-uchebnik.pdf) - учебное пособие "Дискретная математика", В.Е. Алексеев.
* [Draw.io](draw.io) - платформа для составление схем, блок-схем
