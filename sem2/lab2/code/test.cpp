#include "Sets.hpp"
#include <fstream>

// Тест 1: Создание пустого множества
TEST(SetTest, EmptySet) {
    Set s("empty", {});
    EXPECT_TRUE(s.getElements().empty());
    EXPECT_EQ(s.size(), 0);
}

// Тест 2: Добавление элементов
TEST(SetTest, AddElements) {
    Set s("test", {});
    s.addElement("a");
    s.addElement("b");
    EXPECT_EQ(s.size(), 2);
    EXPECT_TRUE(s.contains("a"));
    EXPECT_TRUE(s.contains("b"));
}

// Тест 3: Проверка contains()
TEST(SetTest, ContainsCheck) {
    Set s("test", { "a", "b", "c" });
    EXPECT_TRUE(s.contains("a"));
    EXPECT_FALSE(s.contains("d"));
}

// Тест 4: Симметрическая разность пустых множеств
TEST(SetTest, SymDiffEmptySets) {
    vector<Set> sets;
    Set result = Set::symmetricDifference(sets);
    EXPECT_TRUE(result.getElements().empty());
}

// Тест 5: Симметрическая разность одного множества
TEST(SetTest, SymDiffSingleSet) {
    vector<Set> sets = { Set("A", {"a", "b"}) };
    Set result = Set::symmetricDifference(sets);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(result.contains("a"));
    EXPECT_TRUE(result.contains("b"));
}

// Тест 6: Симметрическая разность двух непересекающихся множеств
TEST(SetTest, SymDiffDisjointSets) {
    vector<Set> sets = { Set("A", {"a", "b"}), Set("B", {"c", "d"}) };
    Set result = Set::symmetricDifference(sets);
    EXPECT_EQ(result.size(), 4);
}

// Тест 7: Симметрическая разность двух пересекающихся множеств
TEST(SetTest, SymDiffOverlappingSets) {
    vector<Set> sets = { Set("A", {"a", "b"}), Set("B", {"b", "c"}) };
    Set result = Set::symmetricDifference(sets);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(result.contains("a"));
    EXPECT_TRUE(result.contains("c"));
}

// Тест 8: Симметрическая разность трёх множеств
TEST(SetTest, SymDiffThreeSets) {
    vector<Set> sets = { Set("A", {"a", "b"}), Set("B", {"b", "c"}), Set("C", {"c", "d"}) };
    Set result = Set::symmetricDifference(sets);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(result.contains("a"));
    EXPECT_TRUE(result.contains("d"));
}

// Тест 9: Парсинг множества из строки
TEST(SetTest, ParseSetFromString) {
    string line = "A = {a, b, c}";
    Set s = parseSet(line);
    EXPECT_EQ(s.getName(), "A");
    EXPECT_EQ(s.size(), 3);
}

// Тест 10: Парсинг множества с пробелами
TEST(SetTest, ParseSetWithSpaces) {
    string line = "B  =  {  x ,  y  , z }";
    Set s = parseSet(line);
    EXPECT_EQ(s.getName(), "B");
    EXPECT_EQ(s.size(), 3);
}

// Тест 11: Удаление пробелов
TEST(SetTest, RemoveSpaces) {
    string input = "   a  ,         b      ,              c    ";
    string result = removeSpaces(input);
    EXPECT_EQ(result, "a, b, c");
}

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

// Тест 13: Обработка пустого файла
TEST(SetTest, ReadEmptyFile) {
    ofstream tmp("empty.txt");
    tmp.close();

    vector<Set> sets = readSetsFromFile("empty.txt");
    EXPECT_TRUE(sets.empty());
    remove("empty.txt");
}

// Тест 14: Обработка несуществующего файла
TEST(SetTest, ReadNonexistentFile) {
    vector<Set> sets = readSetsFromFile("nonexistent.txt");
    EXPECT_TRUE(sets.empty());
}

// Тест 15: Множество с повторяющимися элементами
TEST(SetTest, SetWithDuplicates) {
    Set s("test", { "a", "a", "b" });
    EXPECT_EQ(s.size(), 2); // Дубликаты должны быть удалены
}

// Тест 16: Симметрическая разность с пустым множеством
TEST(SetTest, SymDiffWithEmptySet) {
    vector<Set> sets = { Set("A", {"a", "b"}), Set("empty", {}) };
    Set result = Set::symmetricDifference(sets);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(result.contains("a"));
    EXPECT_TRUE(result.contains("b"));
}

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

