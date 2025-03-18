#include"pch.h"

#include "C:\Users\julia\source\repos\QuadTree\QuadTree\QuadTree.cpp"

// Тест для создания узла квадродерева
TEST(QuadTreeNodeTest, NodeCreation) {
    QuadTreeNode node(5, true);
    EXPECT_EQ(node.value, 5);
    EXPECT_TRUE(node.isLeaf);
}

// Тест для проверки однородности матрицы
TEST(QuadTreeTest, IsUniform) {
    int n = 2;
    int** matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
    }
    matrix[0][0] = 1;
    matrix[0][1] = 1;
    matrix[1][0] = 1;
    matrix[1][1] = 1;

    // Создаём неоднородность
    matrix[1][1] = 0;

    // Проверяем, что матрица не однородна
    EXPECT_FALSE(QuadTree::isUniform(matrix, 0, 2, 0, 2));

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}



TEST(QuadTreeTest, DeleteQuadTree) {   // проверка на то, что удаление не вызывает ошибок
    int n = 2;
    int** matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
    }
    matrix[0][0] = 1; matrix[0][1] = 1;
    matrix[1][0] = 1; matrix[1][1] = 1;

    QuadTreeNode* root = QuadTree::buildQuadTree(matrix, 0, n, 0, n, "Root", 0);
    EXPECT_NO_THROW(QuadTree::deleteQuadTree(root)); 

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

TEST(QuadTreeTest, BuildMatrix) {
    int n = 2;
    int** matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
    }
    matrix[0][0] = 1; matrix[0][1] = 1;
    matrix[1][0] = 1; matrix[1][1] = 1;

    // Построение дерева
    QuadTreeNode* root = QuadTree::buildQuadTree(matrix, 0, n, 0, n, "Root", 0);

    // Новый массив для восстановления матрицы
    int** restoredMatrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        restoredMatrix[i] = new int[n];
    }

    // Преобразование дерева в матрицу
    QuadTree::buildMatrix(root, restoredMatrix, 0, n, 0, n);

    // Проверяем, что восстановленная матрица совпадает с исходной
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            EXPECT_EQ(restoredMatrix[i][j], matrix[i][j]);
        }
    }

    // Удаляем дерево и освобождаем память
    QuadTree::deleteQuadTree(root);
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
        delete[] restoredMatrix[i];
    }
    delete[] matrix;
    delete[] restoredMatrix;
}

TEST(QuadTreeTest, BuildQuadTreeWithHeterogeneousMatrix) {
    int n = 2;
    int** matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
    }
    matrix[0][0] = 1; matrix[0][1] = 2;
    matrix[1][0] = 3; matrix[1][1] = 4;

    // Построение квадродерева
    QuadTreeNode* root = QuadTree::buildQuadTree(matrix, 0, n, 0, n, "Root", 0);

    // Проверяем свойства корня
    ASSERT_FALSE(root->isLeaf); // Корень не должен быть листом

    // Проверяем дочерние узлы (каждый должен быть листом)
    ASSERT_TRUE(root->topLeft->isLeaf);
    ASSERT_TRUE(root->topRight->isLeaf);
    ASSERT_TRUE(root->bottomLeft->isLeaf);
    ASSERT_TRUE(root->bottomRight->isLeaf);

    EXPECT_EQ(root->topLeft->value, 1); // Верхний левый квадрант - 1
    EXPECT_EQ(root->topRight->value, 2); // Верхний правый квадрант - 2
    EXPECT_EQ(root->bottomLeft->value, 3); // Нижний левый квадрант - 3
    EXPECT_EQ(root->bottomRight->value, 4); // Нижний правый квадрант - 4

    // Удаляем дерево и освобождаем память
    QuadTree::deleteQuadTree(root);
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
 
// Запуск всех тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}