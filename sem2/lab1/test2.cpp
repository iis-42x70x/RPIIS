#include <gtest/gtest.h>
#include "B-Tree.h"
 

// Тестирование функции поиска в B-дереве
TEST(BTreeTest, SearchTest) {
    BTree tree(4);

    tree.insert_key(4);
    tree.insert_key(8);

    ASSERT_TRUE(tree.search_key(7) == nullptr); // Ожидаем, что элемент 7 НЕ найден
    tree.insert_key(7);
    ASSERT_TRUE(tree.search_key(7) != nullptr); // Ожидаем, что элемент 7 найден

    tree.insert_key(10);
    tree.insert_key(15);
    tree.insert_key(22);
    tree.insert_key(18);

    ASSERT_TRUE(tree.search_key(15) != nullptr); // Ожидаем, что элемент 15 найден
    ASSERT_TRUE(tree.search_key(20) == nullptr); // Ожидаем, что элемент 20 не найден
    ASSERT_TRUE(tree.search_key(4) != nullptr); // Ожидаем, что элемент 15 найден
    ASSERT_TRUE(tree.search_key(30) == nullptr); // Ожидаем, что элемент 20 не найден
}

// Тестирование функции вставки в B-дерево
TEST(BTreeTest, InsertTest) {
    BTree tree(4);

    tree.insert_key(1);
    tree.insert_key(4);
    tree.insert_key(7);
    tree.insert_key(10);
    tree.insert_key(15);
    tree.insert_key(22);
    tree.insert_key(18);
    tree.insert_key(16);
    tree.insert_key(2);
    tree.insert_key(38);

    // Проверяем, что элементы действительно вставлены
    ASSERT_TRUE(tree.search_key(1) != nullptr);
    ASSERT_TRUE(tree.search_key(4) != nullptr);
    ASSERT_TRUE(tree.search_key(10) != nullptr);
    ASSERT_TRUE(tree.search_key(15) != nullptr);
    ASSERT_TRUE(tree.search_key(22) != nullptr);
    ASSERT_TRUE(tree.search_key(18) != nullptr);
    ASSERT_TRUE(tree.search_key(16) != nullptr);
    ASSERT_TRUE(tree.search_key(2) != nullptr);
    ASSERT_TRUE(tree.search_key(38) != nullptr);
}

// Тестирование функции удаления из B-дерева
TEST(BTreeTest, RemoveTest) {
    BTree tree(4);

    tree.insert_key(1);
    tree.insert_key(4);
    tree.insert_key(7);
    tree.insert_key(10);
    tree.insert_key(15);
    tree.insert_key(22);
    tree.insert_key(18);
    tree.insert_key(25);
    tree.insert_key(30);
    tree.insert_key(8);

    //Проверяем, есть ли элемент 15 в дереве
    ASSERT_TRUE(tree.search_key(15) != nullptr);
    // Удаляем элемент из дерева
    tree.delete_key(15);
    // Проверяем, что элемент действительно удален
    ASSERT_TRUE(tree.search_key(15) == nullptr);

    //Проверяем, есть ли элемент 18 в дереве
    ASSERT_TRUE(tree.search_key(18) != nullptr);
    // Удаляем элемент из дерева
    tree.delete_key(18);
    // Проверяем, что элемент действительно удален
    ASSERT_TRUE(tree.search_key(18) == nullptr);
}

// Запуск всех тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}