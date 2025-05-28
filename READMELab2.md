# Лабораторная работа 2

## Цели:
*1. Разработать библиотеку содержащую функции, выполняющие действия, указанные в
индивидуальном задании, на любом императивнойм языке
программирования (Pascal, C\C++, Java, C#, Python и др.)*

*2. Разработать тестовую программу, которая демонстрирует
работоспособность реализованной библиотеки работы со структурой
данных.*

*3. По результатам выполнения задания составить отчет.*

## Вариант: 
*9. Реализовать программу, определяющую является ли одно, либо оба из двух исходных множеств подмножеством другого.*

## Основные понятия:
**Множество**-простейшая информационная конструкция и математическая структура,позволяющая рассматривать какие-то объекты как целое, связывая их. Объекты, связываемые некоторым множеством, называются элементами этого множества. Если объект связан
некоторым множеством, то говорят, что существует вхождение объекта в это множество, а объект принадлежит этому множеству. Допускается неограниченное количество вхождений одного объекта в какое-либо множество. Допускаются множества, каждое из которых имеет
только одно вхождение какого-либо единственного элемента этого множества, а также допускается множество, не имеющее вхождений, – пустое множество.

**Подмножеством** данного множества называется множество, все элементы которого принадлежат данному множеству. Подмножеством множества { Δ ; О ; # } является, например, { Δ ; О }, или { О ; # }, или { Δ ; # }. Выборками называются подмножества какого-либо множества.
## Примеры работы функции с множиствами:

![Снимок экрана 2025-05-28 232448](https://github.com/user-attachments/assets/ff754fa5-b4f2-40df-98f9-0bd56ac83870)
![Снимок экрана 2025-05-28 231554](https://github.com/user-attachments/assets/52093801-905b-43a6-a75c-4b6d68ba72a4)
![image](https://github.com/user-attachments/assets/def96ece-a8d5-4739-a63a-385dafd856f3)


## Функции и алгоритмы операций:
*В программе я реализовала следующие функции: parseSet, checkSubsets.*

### 1. Функция по чтению из файла

Основная цель функции **parseSet** - разбор строки, содержащей описание множества, и извлечения его компонентов.

Функция **parseSet** предназначена для разбор строки, содержащей описание множества, и извлечения его компонентов. Она выполняет несколько важных задач:

Определяет имя множества – если строка начинается с <имя>=, она извлекает название множества.
Определяет тип множества – ориентированное (<...>) или неориентированное ({...}).
Извлекает элементы множества – разделяет их по запятой и сохраняет в структуре SetData.

Процесс работы:
Проверяет, содержит ли строка имя множества.
Определяет тип множества по соответствующему регулярному выражению.
Разбирает строку с элементами множества и сохраняет их в векторе elements.
В результате **parseSet** возвращает структуру SetData, которая содержит имя, тип и элементы множества. Это упрощает дальнейшую обработку данных и проверку подмножеств.

### 2. Функция проверки подмножеств
Функция **checkSubsets** играет ключевую роль в анализе отношений между двумя множествами. Давай разберем её работу более подробно:

1. Преобразование множеств
Каждое множество передается в функцию как объект SetData, содержащий вектор элементов. Чтобы сравнивать множества удобно, элементы преобразуются в set<string>:
```
cpp
set<string> s1(set1.elements.begin(), set1.elements.end());
set<string> s2(set2.elements.begin(), set2.elements.end());
Контейнер set автоматически удаляет дубликаты и упорядочивает элементы, что делает проверку подмножеств более простой.
```
2. Проверка отношений
Функция выполняет три основные проверки:

Совпадают ли множества
Если оба множества содержат одинаковые элементы, они считаются идентичными.

Первое множество содержится во втором
Используется алгоритм includes(), который проверяет, содержатся ли все элементы s1 внутри s2. Если да – первое множество является подмножеством второго.

Второе множество содержится в первом
Аналогично, если s2 полностью содержится в s1, значит второе множество является подмножеством первого.

Множества не связаны.
Если ни одно из множеств не включает другое, они считаются разными и не связанными.

## Система Google Test:

Первые два теста проверяют работу функции **parseSet**, сравнивая ожидаемый результат и результат работы функций
```
TEST(RunTestcaseTest, SubsetPermutation) {
    int num_sets = 0;
    vector<vector<string>> sets;
    run_testcase("permutation.txt", num_sets, sets);
    vector<vector<string>> expected_sets = { {"{a b}", "{a b}"}, {"{a b}"} };
    ASSERT_EQ(num_sets, expected_sets.size());

    for (int i = 0; i < num_sets; ++i) {
        ASSERT_EQ(sets[i], expected_sets[i]);
    }
}

TEST(RunTestcaseTest, FileNotFoundTest) {
    int num_sets = 0;
    vector<vector<string>> sets;
    run_testcase("non_existent_file.txt", num_sets, sets);
    ASSERT_EQ(num_sets, 0);
    ASSERT_TRUE(sets.empty());
}
```

Следующие два теста проверяют работу функции **checkSubsets**:

```
TEST(CountMultiplicitiesTest, SingleSetTest) {
    vector<vector<string>> sets = { {"aa", "b", "b", "{}"} };
    vector<vector<pair<string, int>>> expected_counts = { {{"aa", 1}, {"b", 2}, {"{}", 1}} };
    ASSERT_EQ(CountMultiplicities(sets), expected_counts);
}

TEST(CountMultiplicitiesTest, MultipleSetsTest) {
    vector<vector<string>> sets = { {"a", "b", "b", "c"}, {"x", "y", "z", "x", "y"} };
    vector<vector<pair<string, int>>> expected_counts = { {{"a", 1}, {"b", 2}, {"c", 1}}, {{"x", 2}, {"y", 2}, {"z", 1}} };
    ASSERT_EQ(CountMultiplicities(sets), expected_counts);
}
```



 **Проверка работы с подмножествами**
 ```
TEST_F(SetOperationsTest, CheckSubsetsValidation) {
    SetData set1 = { "A", false, {"1", "2", "3"} };
    SetData set2 = { "B", false, {"1", "2", "3", "4"} };

    testing::internal::CaptureStdout();
    checkSubsets(set1, set2);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("A является подмножеством B") != std::string::npos);

    SetData set3 = { "C", false, {"5", "6", "7"} };
    testing::internal::CaptureStdout();
    checkSubsets(set1, set3);
    output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Множества не пересекаются") != std::string::npos);
}
```
**Проверка идентичности множеств**
```
TEST_F(SetOperationsTest, IdenticalSetsValidation) {
    SetData set1 = { "X", false, {"1", "2", "3"} };
    SetData set2 = { "Y", false, {"1", "2", "3"} };

    testing::internal::CaptureStdout();
    checkSubsets(set1, set2);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Множества идентичны") != std::string::npos);
}
```
**Проверка обработки некорректного ввода**
```
TEST_F(SetOperationsTest, InvalidSetFormat) {
    testing::internal::CaptureStderr();
    SetData set = parseSet("Некорректный ввод");
    std::string errorOutput = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(errorOutput.find("Ошибка: Некорректный формат множества") != std::string::npos);
}
```
**Проверка работы с пустыми множествами**
```
TEST_F(SetOperationsTest, EmptySetValidation) {
    SetData emptySet1 = parseSet("A={}");
    EXPECT_EQ(emptySet1.name, "A");
    EXPECT_TRUE(emptySet1.elements.empty());

    SetData emptySet2 = parseSet("B=<>");
    EXPECT_EQ(emptySet2.name, "B");
    EXPECT_TRUE(emptySet2.elements.empty());
}
```
**Проверка работы с подмножеством из одного элемента**
```
TEST_F(SetOperationsTest, CheckSubsetWithSingleElement) {
    SetData set1 = { "A", false, {"42"} };
    SetData set2 = { "B", false, {"42", "99"} };

    testing::internal::CaptureStdout();
    checkSubsets(set1, set2);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("A является подмножеством B") != std::string::npos);
}
```

![image](https://github.com/user-attachments/assets/dd48414b-b64f-4a38-b959-a8228c0990e4)




## Выводы:
В результате выполнения лабораторной работы были получены знания из теории множеств, создана программа, реализующая операции на множествах, подключена система Google Test для проверки работы программы.

## Используемые источники:
Подмножества множеств[https://www.yaklass.ru/p/algebra/11-klass/nachalnye-svedeniia-kombinatoriki-9340/razmeshcheniia-razmeshcheniia-s-povtoreniiami-9499/re-8f87406b-e6bb-428d-9076-041df9a6b885]

Тесты [[(https://ru.wikipedia.org/wiki/Очередь_с_приоритетом_(программирование))](https://vitalissius.github.io/GoogleTest+VisualStudio/)]
