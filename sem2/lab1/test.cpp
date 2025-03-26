#include "pch.h"
#include "jungtable.h"
#include "gtest/gtest.h"

// Тест на добавление элементов
TEST(jungtableTest, PushTest) {
    jungtable table;

    EXPECT_EQ(table.push(5), 0);  // Успешное добавление 5
    EXPECT_EQ(table.push(3), 0);  // Добавление 3
    EXPECT_EQ(table.push(7), 0);  // Добавление 7
    EXPECT_EQ(table.push(5), 404); // Повторное добавление 5 должно вернуть 404
}

// Тест на удаление
TEST(jungtableTest, DeleteTest) {
    jungtable table;
    table.push(10);
    table.push(5);
    table.push(15);
    table.push(7);
    table.push(3);

    EXPECT_EQ(table.del(1, 1), 404); // Неверный индекс
    EXPECT_EQ(table.del(1, 2), 404);
    EXPECT_EQ(table.del(2, 1), 404);
    EXPECT_EQ(table.del(2, 2), 0);
    std::vector<std::vector<int>> expected = { { 3, 15 }, { 5 }, { 10 } };
    EXPECT_EQ(table.body, expected);
    EXPECT_EQ(table.del(3, 1), 0); // Удаление первого элемента 
    expected = { { 5, 15 }, { 10 } };
    EXPECT_EQ(table.body, expected);
}

// Тест на сортировку элементов
TEST(jungtableTest, OrderTest) {
    jungtable table;
    table.push(10);
    table.push(5);
    table.push(15);
    table.push(7);
    table.push(3);

    std::vector<std::vector<int>> expected = { { 3, 7 }, { 5, 15 }, { 10 } };
    EXPECT_EQ(table.body, expected);
}

// Проверка пустой таблицы
TEST(jungtableTest, EmptyTest) {
    jungtable table;
    EXPECT_TRUE(table.body.empty());  // Должно быть пусто в начале
}

// Тест на вывод (проверяет, что программа не падает)
TEST(jungtableTest, PrintTest) {
    jungtable table;
    table.push(8);
    table.push(2);
    table.print();
}

// Запуск всех тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
