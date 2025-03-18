#include "QuadTree.h"
#include <iostream>
using namespace std;
// Конструктор узла
QuadTreeNode::QuadTreeNode(int val, bool leaf)
    : value(val), isLeaf(leaf), topLeft(nullptr), topRight(nullptr), bottomLeft(nullptr), bottomRight(nullptr) {
}

// Деструктор узла
QuadTreeNode::~QuadTreeNode() {
    delete topLeft;
    delete topRight;
    delete bottomLeft;
    delete bottomRight;
}

// Проверка, однородна ли подматрица
bool QuadTree::isUniform(int** matrix, int rowStart, int rowEnd, int colStart, int colEnd) {
    int value = matrix[rowStart][colStart];
    for (int i = rowStart; i < rowEnd; ++i) {
        for (int j = colStart; j < colEnd; ++j) {
            if (matrix[i][j] != value) {
                return false;
            }
        }
    }
    return true;
}

// Построение дерева
QuadTreeNode* QuadTree::buildQuadTree(int** matrix, int rowStart, int rowEnd, int colStart, int colEnd, const string& quadrant, int level) {
    for (int i = 0; i < level; ++i) cout << "  ";
   cout << "Level " << level << ", " << quadrant << ": ";

    if (isUniform(matrix, rowStart, rowEnd, colStart, colEnd)) {
       cout << "Homogeneous, value = " << matrix[rowStart][colStart] << endl;
        return new QuadTreeNode(matrix[rowStart][colStart], true);
    }

   cout << "Heterogeneous, requires division" << endl;

    int midRow = (rowStart + rowEnd) / 2;
    int midCol = (colStart + colEnd) / 2;

    QuadTreeNode* node = new QuadTreeNode(0, false);
    node->topLeft = buildQuadTree(matrix, rowStart, midRow, colStart, midCol, "Top left", level + 1);
    node->topRight = buildQuadTree(matrix, rowStart, midRow, midCol, colEnd, "Top right", level + 1);
    node->bottomLeft = buildQuadTree(matrix, midRow, rowEnd, colStart, midCol, "Bottom left", level + 1);
    node->bottomRight = buildQuadTree(matrix, midRow, rowEnd, midCol, colEnd, "Bottom right", level + 1);

    return node;
}

// Перевод дерева обратно в матрицу
void QuadTree::buildMatrix(QuadTreeNode* root, int** matrix, int rowStart, int rowEnd, int colStart, int colEnd) {
    if (root->isLeaf) {
        for (int i = rowStart; i < rowEnd; ++i) {
            for (int j = colStart; j < colEnd; ++j) {
                matrix[i][j] = root->value;
            }
        }
        return;
    }

    int midRow = (rowStart + rowEnd) / 2;
    int midCol = (colStart + colEnd) / 2;

    buildMatrix(root->topLeft, matrix, rowStart, midRow, colStart, midCol);
    buildMatrix(root->topRight, matrix, rowStart, midRow, midCol, colEnd);
    buildMatrix(root->bottomLeft, matrix, midRow, rowEnd, colStart, midCol);
    buildMatrix(root->bottomRight, matrix, midRow, rowEnd, midCol, colEnd);
}

// Удаление дерева
void QuadTree::deleteQuadTree(QuadTreeNode* root) {
    if (root == nullptr) return;
    delete root;
}

// Вывод дерева
void QuadTree::printQuadTree(QuadTreeNode* root, int level) {
    if (!root) return;

    for (int i = 0; i < level; ++i) cout << "  ";
    if (root->isLeaf) {
        cout << "Leaf: value = " << root->value << endl;
    }
    else {
       cout << "Node: division into quadrants" << endl;

        for (int i = 0; i < level + 1; ++i) cout << "  ";
        cout << "Top left:" << endl;
        printQuadTree(root->topLeft, level + 2);

        for (int i = 0; i < level + 1; ++i) cout << "  ";
        cout << "Top right:" << endl;
        printQuadTree(root->topRight, level + 2);

        for (int i = 0; i < level + 1; ++i) cout << "  ";
        cout << "Bottom left:" << endl;
        printQuadTree(root->bottomLeft, level + 2);

        for (int i = 0; i < level + 1; ++i) cout << "  ";
        cout << "Bottom right:" << endl;
        printQuadTree(root->bottomRight, level + 2);
    }
}