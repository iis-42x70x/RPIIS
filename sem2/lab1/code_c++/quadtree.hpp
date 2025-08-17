#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <iostream>

struct QuadNode {
    int value;
    bool isLeaf;
    QuadNode* children[4]; // NW, NE, SW, SE
};

// Проверка матрицы на валидность
bool isMatrixValid(const std::vector<std::vector<int>>& matrix);

// Построение квадродерева
QuadNode* buildTree(const std::vector<std::vector<int>>& matrix, int x, int y, int size);

// Восстановление матрицы из дерева
void treeToMatrix(QuadNode* root, std::vector<std::vector<int>>& matrix, int x, int y, int size);

// Освобождение памяти
void freeTree(QuadNode* root);

#endif