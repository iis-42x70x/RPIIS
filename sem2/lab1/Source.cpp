#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Header.h"
using namespace std;

// Структура узла декартова дерева
struct Node {
    int key;
    int priority;
    Node* left;
    Node* right;

    Node(int k) : key(k), priority(rand()), left(NULL), right(NULL) {}
}; 

Node* insert(Node* root, int key) {
    if (!root) {
        return new Node(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
        if (root->left->priority > root->priority) {
            Node* temp = root;
            root = root->left;
            temp->left = root->right;
            root->right = temp;
        }
    }
    else {
        root->right = insert(root->right, key);
        if (root->right->priority > root->priority) {
            Node* temp = root;
            root = root->right;
            temp->right = root->left;
            root->left = temp;
        }
    }

    return root;
}

// Функция для разделения декартова дерева на два поддерева
void split(Node* root, int key, Node*& left, Node*& right) {
    if (!root) {
        left = right = NULL;
    }
    else if (root->key <= key) {
        split(root->right, key, root->right, right);
        left = root;
    }
    else {
        split(root->left, key, left, root->left);
        right = root;
    }
}

// Функция для слияния двух декартовых деревьев
Node* merge(Node* left, Node* right) {
    if (!left || !right) {
        return left ? left : right;
    }

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        return right;
    }
}

// Функция для удаления узла из декартова дерева
Node* remove(Node* root, int key) {
    if (!root) {
        return NULL;
    }

    if (key < root->key) {
        root->left = remove(root->left, key);
    }
    else if (key > root->key) {
        root->right = remove(root->right, key);
    }
    else {
        Node* temp = root;
        root = merge(root->left, root->right);
        delete temp;
    }

    return root;
}

// Функция для поиска узла по ключу
bool search(Node* root, int key) {
    if (!root) {
        return false;
    }

    if (key < root->key) {
        return search(root->left, key);
    }
    else if (key > root->key) {
        return search(root->right, key);
    }
    else {
        return true;
    }
}

// Функция для обхода дерева и сбора всех ключей
void collectKeys(Node* root, vector<int>& keys) {
    if (root) {
        collectKeys(root->left, keys);
        keys.push_back(root->key);
        collectKeys(root->right, keys);
    }
}

// Функция для объединения двух деревьев
Node* unionTreaps(Node* treap1, Node* treap2) {
    vector<int> keys;
    collectKeys(treap2, keys);

    Node* result = treap1;
    for (int key : keys) {
        if (!search(result, key)) {
            result = insert(result, key);
        }
    }

    return result;
}

// Функция для пересечения двух деревьев
Node* intersectionTreaps(Node* treap1, Node* treap2) {
    vector<int> keys;
    collectKeys(treap1, keys);

    Node* result = NULL;
    for (int key : keys) {
        if (search(treap2, key)) {
            result = insert(result, key);
        }
    }

    return result;
}

// Функция для вывода дерева
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << "Key: " << root->key << " Priority: " << root->priority << endl;
        inorder(root->right);
    }
}

// Функция для вывода меню
void printMenu() {
    cout << "\nМеню:\n"
        << "1. Создать новое дерево\n" << "2. Вставить элемент\n" << "3. Удалить элемент\n"
        << "4. Поиск элемента\n" << "5. Объединение двух деревьев\n" << "6. Пересечение двух деревьев\n"
        << "7. Вывести дерево\n" << "8. Выйти\n" << "Выберите опцию: ";
}