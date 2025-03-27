#include <gtest/gtest.h>
#include "B-Tree.h"
 

// Тестирование функции поиска в B-дереве
TEST(BTreeTest, SearchTest) {
    BTree tree(3); 

    tree.insert_key(1);
    tree.insert_key(3);

    ASSERT_TRUE(tree.search_key(7) == nullptr); // Ожидаем, что элемент 7 НЕ найден
    tree.insert_key(7);
    ASSERT_TRUE(tree.search_key(7) != nullptr); // Ожидаем, что элемент 7 найден
    tree.insert_key(10);

    tree.insert_key(11);
  
    ASSERT_TRUE(tree.search_key(7) != nullptr); // Ожидаем, что элемент 11 найден
    ASSERT_TRUE(tree.search_key(2) == nullptr); // Ожидаем, что элемент 2 не найден
}

// Тестирование функции вставки в B-дерево
TEST(BTreeTest, InsertTest) {
    BTree tree(3); 

    tree.insert_key(1);
    tree.insert_key(3);
    tree.insert_key(7);
    tree.insert_key(10);

    // Проверяем, что элементы действительно вставлены
    ASSERT_TRUE(tree.search_key(1) != nullptr);
    ASSERT_TRUE(tree.search_key(3) != nullptr);
    ASSERT_TRUE(tree.search_key(7) != nullptr);
    ASSERT_TRUE(tree.search_key(10) != nullptr);
}

// Тестирование функции удаления из B-дерева
TEST(BTreeTest, RemoveTest) {
    BTree tree(3); 

    tree.insert_key(1);
    tree.insert_key(3);
    tree.insert_key(7);
    tree.insert_key(10);

    //Проверяем, есть ли элемент 3 в дереве
    ASSERT_TRUE(tree.search_key(3) != nullptr);
    // Удаляем элемент из дерева
    tree.delete_key(3);
    // Проверяем, что элемент действительно удален
    ASSERT_TRUE(tree.search_key(3) == nullptr);
}

// Запуск всех тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}