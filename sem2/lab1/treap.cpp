include "treap.h"
#include <random>
#include <ctime>


Node::Node(int k) : key(k), priority(rand()) {}

// merge
Node* merge(Node* a, Node* b) {
    if (!a || !b) return a ? a : b;
    if (a->priority > b->priority) {
        a->r = merge(a->r, b);
        return a;
    }
    else {
        b->l = merge(a, b->l);
        return b;
    }
}

// split
void split(Node* root, int key, Node*& a, Node*& b) {
    if (!root) {
        a = b = nullptr;
        return;
    }
    if (root->key < key) {
        a = root;
        split(root->r, key, root->r, b);
    }
    else {
        b = root;
        split(root->l, key, a, root->l);
    }
}

// insert
void insert(Node*& root, int key) {
    Node* less, * greater;
    split(root, key, less, greater);
    less = merge(less, new Node(key));
    root = merge(less, greater);
}

// search
Node* search(Node* root, int key) {
    if (!root || root->key == key) return root;
    return key < root->key ? search(root->l, key) : search(root->r, key);
}

// remove
void remove(Node*& root, int key) {
    if (!root) return;
    if (root->key == key) {
        Node* temp = root;
        root = merge(root->l, root->r);
        delete temp;
    }
    else {
        remove(key < root->key ? root->l : root->r, key);
    }
}

// buildTree
void buildTree(Node*& root, vector<int>& arr) {
    for (int key : arr) insert(root, key);
}

// printTree
void printTree(Node* root, int level) {
    if (root == nullptr)
        return;

    printTree(root->r, level + 1);
    for (int i = 0; i < level; i++)
        cout << "          ";
    cout << root->key << " (" << root->priority << ")\n";
    printTree(root->l, level + 1);
}

// mergeTrees
Node* mergeTrees(Node* tree1) {
    cout << "Введите колличество элементов второго дерева:: ";
    int n;
    cin >> n;

    Node* tree2 = nullptr;
    cout << "Введите элемены второго дерева: ";
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        insert(tree2, value);
    }
    return merge(tree1, tree2);
}

// intersection
Node* intersection(Node* left, Node* right) {
    if (!left || !right) return nullptr;

    if (search(right, left->key)) {
        Node* newTree = new Node(left->key);
        newTree->priority = left->priority;
        newTree->l = intersection(left->l, right);
        newTree->r = intersection(left->r, right);
        return newTree;
    }

    Node* leftSubtree = intersection(left->l, right);
    Node* rightSubtree = intersection(left->r, right);
    return merge(leftSubtree, rightSubtree);
}

// intersectionTrees
Node* intersectionTrees(Node* tree1) {
    cout << "Введите колличество элементов второго дерева: ";
    int n;
    cin >> n;

    Node* tree2 = nullptr;
    cout << "Введите элемены второго дерева: ";
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        insert(tree2, value);
    }
    return intersection(tree1, tree2);
}

// Menu
void Menu() {
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));

    Node* root = nullptr;
    int choice, value, n;
    vector<int> values;


    do {
        cout << "\nМеню:\n";
        cout << "1. Вставка\n2. Поиск\n3. Удаление\n4. Построение дерева\n5. Объединение\n6. Пересечение\n7. Вывод дерева\n8. Выход\nВыбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите значение: ";
            cin >> value;
            insert(root, value);
            break;
        case 2:
            cout << "Введите значение для поиска: ";
            cin >> value;
            if (search(root, value))
                cout << "Найдено: " << value << "\n";
            else
                cout << "Отсутствует\n";
            break;
        case 3:
            cout << "Введите значение для удаления: ";
            cin >> value;
            remove(root, value);
            break;
        case 4:
            cout << "Количество элементов: ";
            cin >> n;
            values.resize(n);
            cout << "Введите элементы: ";
            for (int& v : values) cin >> v;
            buildTree(root, values);
            cout << "Дерево построено.\n";
            break;
        case 5:
            root = mergeTrees(root);
            cout << "Деревья объединены.\n";
            break;
        case 6:
            root = intersectionTrees(root);
            cout << "Пересечение деревьев выполнено.\n";
            break;
        case 7:
            cout << "Дерево:\n";
            printTree(root);
            break;
        case 8:
            cout << "Выход...\n";
            break;
        default:
            cout << "Неверный ввод.\n";
        }
    } while (choice != 8);
}
