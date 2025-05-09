// tests.cpp
#include "pch.h"
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>

// Тесты для корректного добавления элементов в таблицу Юнга
TEST(YoungTableauTest, AddElement)
{
    YoungTableau yt;
    yt.initialize(3);
    yt.add(1, 9);
    yt.add(1, 4);
    yt.add(1, 3);

    std::vector<std::vector<int>> expected = { {3, 4, 9}, {}, {} };
    EXPECT_EQ(yt.getTable(), expected);
}



TEST(YoungTableauTest, AddElementToMultipleRows)
{
    YoungTableau yt;
    yt.initialize(3);
    yt.add(1, 5);
    yt.add(1, 2);
    yt.add(1, 1);
    yt.add(2, 9);
    yt.add(2, 4);
    yt.add(3, 3);

    std::vector<std::vector<int>> expected = { {1, 2, 5}, {3, 4}, {9} };
    EXPECT_EQ(yt.getTable(), expected);
}

// Тест на корректное удаление элементов


//Teст на удаление еще одного элемента из 2 строки, когда имеется 3 строки
TEST(YoungTableauTest1, RemoveOMElement)
{
    YoungTableau yt;
    yt.initialize(3);
    yt.add(1, 1);
    yt.add(1, 4);
    yt.add(1, 5);
    yt.add(2, 2);
    yt.add(3, 3);

    yt.remove(2, 1);
    std::vector<std::vector<int>> expected = { {1, 4, 5}, {3}, {} };
    EXPECT_EQ(yt.getTable(), expected);
}

TEST(YoungTableauTest, CheckNewMethod)
{
    YoungTableau yt;
    yt.initialize({ {3, 2, 1}, {5, 4}, {9} });

    std::vector<std::vector<int>> expected = {
        {1, 2, 3},
        {4, 5},
        {9}
    };

    EXPECT_EQ(yt.getTable(), expected);
}

TEST(YoungTableauTest, InitializeFullTable1) {
    YoungTableau yt;
    yt.initialize({ {12, 7, 5}, {2, 1}, {8, 3} });

    std::vector<std::vector<int>> expected = {
        {1, 2, 12},
        {3, 7},
        {5, 8}
    };

    EXPECT_EQ(yt.getTable(), expected);
}

TEST(YoungTableauTest, DuplicateCheck) {
    YoungTableau yt;

    // Тест без дубликатов
    yt.initialize({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });
    EXPECT_FALSE(yt.hasDuplicates());

    // Тест с дубликатом в одной строке
    yt.initialize({ {1, 2, 2}, {4, 5, 6}, {7, 8, 9} });
    EXPECT_TRUE(yt.hasDuplicates());

    // Тест с дубликатом в одном столбце
    yt.initialize({ {1, 2, 3}, {4, 2, 6}, {7, 8, 9} });
    EXPECT_TRUE(yt.hasDuplicates());

    // Тест с дубликатом в разных строках, но не в одном столбце
    yt.initialize({ {1, 2, 3}, {4, 5, 6}, {7, 8, 2} });
    EXPECT_TRUE(yt.hasDuplicates());
}

TEST(YoungTableauTest, EmptyTable)
{
    YoungTableau yt;
    EXPECT_TRUE(yt.getTable().empty());
}

// Тест на корректный вывод в файл
TEST(YoungTableauTest, PrintToFile)
{
    YoungTableau yt;
    yt.initialize(2);
    yt.add(1, 10);
    yt.add(1, 5);
    yt.add(2, 2);
    yt.printToFile("test_output.txt");

    std::ifstream file("test_output.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    std::string expected = "Таблица Юнга:\n5 10 \n2 \n";
    EXPECT_EQ(content, expected);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
