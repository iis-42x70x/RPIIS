#include "QuadTree.h"
#include <iostream>

using namespace std;

// Функция для проверки, является ли число степенью двойки
bool isPowerOfTwo(int n) {
    return (n > 0) && ((n & (n - 1)) == 0); //Битовая операция
}

void printMatrix(int** matrix, int n) {   //функция для дальнейшего вывода матрицы
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
  
    int n;
    cout << "Enter the size of matrix (n x n): ";
    cin >> n;

    // Проверка, является ли размер матрицы степенью двойки
    if (!isPowerOfTwo(n)) {
        cout << "Error: the size of the matrix must be a power of two!" << endl;
        return 1; // Завершение программы с кодом ошибки
    }

    int** matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
    }

    cout << "Enter the elements of matrix " << n << " x " << n << " in the line:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << "\nBuilding QuadTree..." << endl;
    QuadTreeNode* root = QuadTree::buildQuadTree(matrix, 0, n, 0, n, "Node: ", 0);

    // Перевод дерева обратно в матрицу
    int** rebuiltMatrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        rebuiltMatrix[i] = new int[n];
    }

    QuadTree::buildMatrix(root, rebuiltMatrix, 0, n, 0, n);

    // Выводим полученную матрицу
    cout << "\nThe reconstructed matrix from QuadTree:" << endl;
    printMatrix(rebuiltMatrix, n);

    // Освобождение памяти
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
        delete[] rebuiltMatrix[i];
    }
    delete[] matrix;
    delete[] rebuiltMatrix;

    QuadTree::deleteQuadTree(root);

    return 0;
}