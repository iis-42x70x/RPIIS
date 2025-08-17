#include "quadtree.hpp"
#include <cmath>

// Проверка матрицы
bool isMatrixValid(const std::vector<std::vector<int>>& matrix) {
    // 1. Пустая матрица
    if (matrix.empty() || matrix[0].empty()) {
        std::cerr << "Error: Matrix is empty!\n";
        return false;
    }

    // 2. Проверка на 1x1
    if (matrix.size() == 1 && matrix[0].size() == 1) {
        std::cerr << "Error: 1x1 matrix is too small for quadtree!\n";
        return false;
    }

    // 3. Квадратная ли?
    int size = matrix.size();
    for (const auto& row : matrix) {
        if (row.size() != size) {
            std::cerr << "Error: Matrix is not square!\n";
            return false;
        }
    }

    // 4. Степень двойки?
    if ((size & (size - 1)) != 0) {
        std::cerr << "Error: Size must be a power of two (2, 4, 8, ...)!\n";
        return false;
    }

    return true;
}

// Построение дерева
QuadNode* buildTree(const std::vector<std::vector<int>>& matrix, int x, int y, int size) {
    if (!isMatrixValid(matrix)) return nullptr;

    // Проверка на однородность
    bool allSame = true;
    int firstVal = matrix[y][x];
    for (int i = y; i < y + size; ++i) {
        for (int j = x; j < x + size; ++j) {
            if (matrix[i][j] != firstVal) {
                allSame = false;
                break;
            }
        }
        if (!allSame) break;
    }

    // Создание листа
    if (allSame) {
        QuadNode* node = new QuadNode;
        node->isLeaf = true;
        node->value = firstVal;
        for (int i = 0; i < 4; ++i) node->children[i] = nullptr;
        return node;
    }

    // Рекурсивное деление
    QuadNode* node = new QuadNode;
    node->isLeaf = false;
    int half = size / 2;
    node->children[0] = buildTree(matrix, x, y, half);          // NW
    node->children[1] = buildTree(matrix, x + half, y, half);   // NE
    node->children[2] = buildTree(matrix, x, y + half, half);   // SW
    node->children[3] = buildTree(matrix, x + half, y + half, half); // SE
    return node;
}

// Восстановление матрицы
void treeToMatrix(QuadNode* root, std::vector<std::vector<int>>& matrix, int x, int y, int size) {
    if (!root) return;

    if (root->isLeaf) {
        for (int i = y; i < y + size; ++i) {
            for (int j = x; j < x + size; ++j) {
                matrix[i][j] = root->value;
            }
        }
    } else {
        int half = size / 2;
        treeToMatrix(root->children[0], matrix, x, y, half);          // NW
        treeToMatrix(root->children[1], matrix, x + half, y, half);   // NE
        treeToMatrix(root->children[2], matrix, x, y + half, half);   // SW
        treeToMatrix(root->children[3], matrix, x + half, y + half, half); // SE
    }
}

// Очистка памяти
void freeTree(QuadNode* root) {
    if (!root) return;
    if (!root->isLeaf) {
        for (int i = 0; i < 4; ++i) {
            freeTree(root->children[i]);
        }
    }
    delete root;
}