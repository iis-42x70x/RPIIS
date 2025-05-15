#include "quadtree.hpp"
#include <iostream>
#include <string>

// Функция для печати матрицы
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) std::cout << val << " ";
        std::cout << "\n";
    }
}

// Рекурсивная визуализация дерева с направлениями
void printTree(QuadNode* node, const std::string& direction = "Root", const std::string& prefix = "", bool isLast = true) {
    if (!node) return;

    // Вывод текущего узла с направлением
    std::cout << prefix;
    std::cout << (isLast ? "└── " : "├── ");
    std::cout << "[" << direction << "] ";

    if (node->isLeaf) {
        std::cout << "Value: " << node->value << " (все " << node->value << ")\n";
    } else {
        std::cout << "Node (разделён на 4)\n";
    }

    // Рекурсивный вывод детей с направлениями
    std::string newPrefix = prefix + (isLast ? "    " : "│   ");
    printTree(node->children[0], "NW", newPrefix, false);  // Северо-запад
    printTree(node->children[1], "NE", newPrefix, false);  // Северо-восток
    printTree(node->children[2], "SW", newPrefix, false);  // Юго-запад
    printTree(node->children[3], "SE", newPrefix, true);   // Юго-восток
}

int main() {
    // Пример матрицы 8x8
    std::vector<std::vector<int>> matrix = {
        {8,8,8,8},
        {8,8,0,0},
        {1,1,2,2},
        {1,1,2,2}
    };

    // Проверка на валидность
    if (!isMatrixValid(matrix)) {
        std::cerr << "Матрица не подходит для квадродерева!\n";
        return 1;
    }

    // Построение дерева
    QuadNode* root = buildTree(matrix, 0, 0, matrix.size());

    // Вывод матрицы и дерева
    std::cout << "Исходная матрица 8x8:\n";
    printMatrix(matrix);

    std::cout << "\nСтруктура квадродерева:\n";
    printTree(root);

    // Очистка памяти
    freeTree(root);
    return 0;
}