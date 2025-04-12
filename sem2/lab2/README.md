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
  
```С++
// Тест 1: Создание пустого множества
TEST(SetTest, EmptySet) {
    Set s("empty", {});
    EXPECT_TRUE(s.getElements().empty());
    EXPECT_EQ(s.size(), 0);
}
```

* Тест 2
  
```С++
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
  
```С++
// Тест 3: Проверка contains()
TEST(SetTest, ContainsCheck) {
    Set s("test", { "a", "b", "c" });
    EXPECT_TRUE(s.contains("a"));
    EXPECT_FALSE(s.contains("d"));
}
```

* Тест 4
  
```С++
// Тест 4: Симметрическая разность пустых множеств
TEST(SetTest, SymDiffEmptySets) {
    vector<Set> sets;
    Set result = Set::symmetricDifference(sets);
    EXPECT_TRUE(result.getElements().empty());
}
```

* Тест 5
  
```С++
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
  
```С++
// Тест 6: Симметрическая разность двух непересекающихся множеств
TEST(SetTest, SymDiffDisjointSets) {
    vector<Set> sets = { Set("A", {"a", "b"}), Set("B", {"c", "d"}) };
    Set result = Set::symmetricDifference(sets);
    EXPECT_EQ(result.size(), 4);
}
```

* Тест 7
  
```С++
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
  
```С++
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
  
```С++
// Тест 9: Парсинг множества из строки
TEST(SetTest, ParseSetFromString) {
    string line = "A = {a, b, c}";
    Set s = parseSet(line);
    EXPECT_EQ(s.getName(), "A");
    EXPECT_EQ(s.size(), 3);
}
```

* Тест 10
  
```С++
// Тест 10: Парсинг множества с пробелами
TEST(SetTest, ParseSetWithSpaces) {
    string line = "B  =  {  x ,  y  , z }";
    Set s = parseSet(line);
    EXPECT_EQ(s.getName(), "B");
    EXPECT_EQ(s.size(), 3);
}
```

* Тест 11
  
```С++
// Тест 11: Удаление пробелов
TEST(SetTest, RemoveSpaces) {
    string input = "   a  ,         b      ,              c    ";
    string result = removeSpaces(input);
    EXPECT_EQ(result, "a, b, c");
}
```

* Тест 12
  
```С++
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
  
```С++
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
  
```С++
// Тест 14: Обработка несуществующего файла
TEST(SetTest, ReadNonexistentFile) {
    vector<Set> sets = readSetsFromFile("nonexistent.txt");
    EXPECT_TRUE(sets.empty());
}
```

* Тест 15
  
```С++
// Тест 15: Множество с повторяющимися элементами
TEST(SetTest, SetWithDuplicates) {
    Set s("test", { "a", "a", "b" });
    EXPECT_EQ(s.size(), 2); // Дубликаты должны быть удалены
}
```

* Тест 16
  
```С++
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
  
```С++
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

## Результат работы тестов: 

<img src="https://github.com/iis-42x70x/RPIIS/tree/Говор_Г/sem2/lab2/img/2.png">

## Вывод:
* Мной была разработана библиотека по работе со множествами В ней я реализовал операцию симметрической разноти между несколькими множиствами.

## Материалы и источники:

* [YouTube](https://www.youtube.com/watch?v=WXXetwePSRk) - подробное объяснение принципа работы с B-деревьями от Volodya Mozhenkov с помощью видиоматериалы
* [Викиконспекты](https://neerc.ifmo.ru/wiki/index.php?title=B-дерево) - особенности реализации B-деревьев на C++
* [Draw.io](draw.io) - платформа для составление схем, блок-схем
