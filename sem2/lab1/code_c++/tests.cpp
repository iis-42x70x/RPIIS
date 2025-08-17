#include "quadtree.hpp"
#include <iostream>

void runTest(const std::vector<std::vector<int>>& matrix, const std::string& testName) {
    std::cout << "\n=== " << testName << " ===\n";
    QuadNode* root = buildTree(matrix, 0, 0, matrix.size());
    if (!root) {
        std::cout << "Тест провален (ожидаемо для некорректных данных).\n";
        return;
    }

    std::vector<std::vector<int>> restoredMatrix(matrix.size(), std::vector<int>(matrix.size(), 0));
    treeToMatrix(root, restoredMatrix, 0, 0, matrix.size());

    std::cout << "Исходная матрица:\n";
    for (const auto& row : matrix) {
        for (int val : row) std::cout << val << " ";
        std::cout << "\n";
    }
    std::cout << "Восстановленная матрица:\n";
    for (const auto& row : restoredMatrix) {
        for (int val : row) std::cout << val << " ";
        std::cout << "\n";
    }

    freeTree(root);
}

int main() {
    // Корректные тесты
    runTest({ {1, 1}, {1, 1} }, "Корректная матрица 2x2");
    runTest({ {1,1,0,0}, {1,1,0,0}, {0,0,1,1}, {0,0,1,1} }, "Корректная матрица 4x4");

    // Некорректные тесты
    runTest({ {1} }, "Матрица 1x1");
    runTest({ {1,2}, {3} }, "Неквадратная матрица 2x1");
    runTest({ {1,2,3}, {4,5,6}, {7,8,9} }, "Матрица 3x3");
    runTest({}, "Пустая матрица");

    return 0;
}