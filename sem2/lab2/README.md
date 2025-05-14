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
*7. Реализовать программу, формирующую без повторений всевозможные ориентированные
множества из элементов исходного неориентированного множества, количество
элементов в сформированных множествах должно быть равно исходному натуральному n.*

## Основные понятия:
**Множество** — простейшая информационная конструкция и математическая структура, позволяющая рассматривать какие-то объекты как целое, связывая их. Объекты, связываемые некоторым множеством, называются элементами этого множества.

**Неориентированное множество** — это множество, элементы которого не обладают направлением или порядком, то есть между элементами множества не задано отношение ориентации или упорядоченности. 

**Ориентированное множество** — это множество, в котором элементы имеют заданное направление или порядок. 

## Функции и алгоритмы операций:
*В программе я реализовала следующие функции: parseSet, generatePermutations, clearInputBuffer.*
### 1. Функция parseSet 
Предназначена для разбора строки, представляющей множество, и извлечения из нее элементов. Она принимает строку в формате, начинающемся с { и заканчивающемся }, и внутри нее ищет отдельные элементы, разделенные запятыми. В процессе анализа она учитывает вложенные скобки {} и <>, чтобы не ошибочно разделить элементы внутри вложенных структур. После проверки правильности формата она удаляет внешние фигурные скобки, затем по символам проходит по содержимому, выделяя отдельные элементы, очищая их от лишних пробелов и добавляя в результирующий вектор строк. В случае неправильного формата выбрасывает исключение.

### 2. Функция generatePermutations 
Реализует рекурсивный алгоритм генерации всех перестановок заданного вектора элементов. Она принимает текущий вектор элементов, текущий уровень рекурсии (level) и ссылку на вектор для хранения всех полученных перестановок (result). На каждом шаге она меняет местами текущий элемент с каждым последующим и вызывает себя для следующего уровня. Когда уровень достигает размера исходного массива, текущая перестановка добавляется в результат. После каждого вызова происходит возврат к исходной конфигурации элементов (с помощью swap), что обеспечивает перебор всех вариантов.

### 3. Функция clearInputBuffer 
Служит для очистки входного буфера после чтения данных с помощью cin. Она сбрасывает состояние потока и игнорирует все оставшиеся символы до конца строки или до максимального размера буфера, чтобы избежать ошибок при последующих вводах. Это важно для корректной работы программы при обработке пользовательского ввода, особенно после чтения чисел или строк.

## Система Google Test:
```
TEST_F(SetOperationsTest, ParenthesesValidation) {
    EXPECT_TRUE(CheckParentheses("{}"));
    EXPECT_TRUE(CheckParentheses("{a,b}"));
    EXPECT_TRUE(CheckParentheses("<a,(b,c)>"));
    EXPECT_FALSE(CheckParentheses("{"));
    EXPECT_FALSE(CheckParentheses("}"));
    EXPECT_FALSE(CheckParentheses("{a,b))"));
    EXPECT_FALSE(CheckParentheses("{(})"));
}

TEST_F(SetOperationsTest, SymbolValidation) {
    EXPECT_TRUE(IsValidSymbol('a'));
    EXPECT_TRUE(IsValidSymbol('Z'));
    EXPECT_TRUE(IsValidSymbol('0'));
    EXPECT_TRUE(IsValidSymbol('{'));
    EXPECT_TRUE(IsValidSymbol(' '));
    EXPECT_FALSE(IsValidSymbol('!'));
    EXPECT_FALSE(IsValidSymbol('@'));
    EXPECT_FALSE(IsValidSymbol('\n'));
}

TEST_F(SetOperationsTest, InputValidation) {
    EXPECT_TRUE(ValidateInputString("{a,b}")); 
    EXPECT_TRUE(ValidateInputString("a,b"));   
    EXPECT_TRUE(ValidateInputString("<1,2,3>")); 
    EXPECT_FALSE(ValidateInputString("{a,!b}"));
    EXPECT_FALSE(ValidateInputString("{a\nb}")); 
}

TEST_F(SetOperationsTest, ElementParsing) {
    EXPECT_EQ(ParseElements(elements, "a,b"), 0);
    ASSERT_EQ(elements.size(), 2);
    EXPECT_EQ(elements[0], "a");
    EXPECT_EQ(elements[1], "b");

    elements.clear();
    EXPECT_EQ(ParseElements(elements, "<1,2>,3"), 0);
    ASSERT_EQ(elements.size(), 2);
    EXPECT_EQ(elements[0], "<1,2>");
    EXPECT_EQ(elements[1], "3");
}

TEST_F(SetOperationsTest, DuplicateDetection) {
    std::vector<std::string> unique = { "a", "b" };
    std::vector<std::string> duplicates = { "a", "a" };
    EXPECT_FALSE(HasDuplicates(unique));
    EXPECT_TRUE(HasDuplicates(duplicates));
}

TEST_F(SetOperationsTest, BraceTrimming) {
    std::string s1 = "{a}";
    std::string s2 = "<b>";
    std::string s3 = "plain";
    TrimOuterBraces(s1);
    TrimOuterBraces(s2);
    TrimOuterBraces(s3);
    EXPECT_EQ(s1, "a");
    EXPECT_EQ(s2, "b");
    EXPECT_EQ(s3, "plain");
}

TEST_F(SetOperationsTest, InputProcessing) {
    auto result = ProcessInput("{a,b}");
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "b");

    result = ProcessInput("{}");
    EXPECT_TRUE(result.empty());
}

TEST_F(SetOperationsTest, PermutationGeneration) {
    std::vector<std::string> input = { "a", "b" };
    GenerateAllPermutations(input, permutations);
    ASSERT_EQ(permutations.size(), 2);
    EXPECT_EQ(permutations[0], std::vector<std::string>({ "a", "b" }));
    EXPECT_EQ(permutations[1], std::vector<std::string>({ "b", "a" }));
}
```
![Снимок экрана 2025-05-02 202328](https://github.com/user-attachments/assets/bfcebb02-5cd4-458d-85c5-a2e2a3336323)

## Выводы:
В результате выполнения лабораторной работы были получены знания из теории множеств, создана программа, реализующая операции на множествах.
## Используемые источники:
Основные определения теории графов [https://neerc.ifmo.ru/wiki/index.php?title=%D0%9E%D1%81%D0%BD%D0%BE%D0%B2%D0%BD%D1%8B%D0%B5_%D0%BE%D0%BF%D1%80%D0%B5%D0%B4%D0%B5%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F_%D1%82%D0%B5%D0%BE%D1%80%D0%B8%D0%B8_%D0%B3%D1%80%D0%B0%D1%84%D0%BE%D0%B2]

Ориентированные и неориентированные множества [https://habr.com/ru/articles/564594/]

Множество[https://ru.wikipedia.org/wiki/%D0%9C%D0%BD%D0%BE%D0%B6%D0%B5%D1%81%D1%82%D0%B2%D0%BE_(%D1%82%D0%B8%D0%BF_%D0%B4%D0%B0%D0%BD%D0%BD%D1%8B%D1%85)]
