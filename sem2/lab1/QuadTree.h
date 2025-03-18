#ifndef QUADTREE_H
#define QUADTREE_H

#include <string> // Для работы с типом std::string

// Структура узла квадродерева
struct QuadTreeNode {
    int value;                // Значение узла (если это лист)
    bool isLeaf;              // Является ли узел листом (true - да, false - нет)
    QuadTreeNode* topLeft;    // Указатель на верхний левый дочерний узел
    QuadTreeNode* topRight;   // Указатель на верхний правый дочерний узел
    QuadTreeNode* bottomLeft; // Указатель на нижний левый дочерний узел
    QuadTreeNode* bottomRight;// Указатель на нижний правый дочерний узел

    // Конструктор класса
    QuadTreeNode(int val, bool leaf);

    // Деструктор класса
    ~QuadTreeNode();
};

// Класс для работы с квадродеревом
class QuadTree {
public:
    // Статическая функция для построения квадродерева из матрицы
    static QuadTreeNode* buildQuadTree(int** matrix, int rowStart, int rowEnd, int colStart, int colEnd, const std::string& quadrant, int level);

    // Статическая функция для заполнения матрицы на основе квадродерева
    static void buildMatrix(QuadTreeNode* root, int** matrix, int rowStart, int rowEnd, int colStart, int colEnd);

    // Статическая функция для освобождения памяти, занятой квадродеревом
    static void deleteQuadTree(QuadTreeNode* root);

    // Статическая функция для вывода структуры квадродерева
    static void printQuadTree(QuadTreeNode* root, int level = 0);

    // Приватная функция для проверки, является ли подматрица однородной
    static bool isUniform(int** matrix, int rowStart, int rowEnd, int colStart, int colEnd);
};

#endif // QUADTREE_H


