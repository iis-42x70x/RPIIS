#include "rb_tree.hpp"
#include <iostream>

// Конструктор узла
Node::Node(int data)
    : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}

// Конструктор дерева
RBTree::RBTree() : root(nullptr) {}

// Деструктор дерева – освобождает память
RBTree::~RBTree() {
    destroyTree(root);
}

// Рекурсивное удаление узлов
void RBTree::destroyTree(Node* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Рекурсивный inorder обход
void RBTree::inorderHelper(Node* node) const {
    if (node) {
        inorderHelper(node->left);
        std::cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
        inorderHelper(node->right);
    }
}

// Публичная функция inorder обхода
void RBTree::inorder() const {
    inorderHelper(root);
    std::cout << std::endl;
}

// Левый поворот вокруг узла x
void RBTree::leftRotate(Node* x) {
    Node* y = x->right;
    if (!y) return;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Правый поворот вокруг узла x
void RBTree::rightRotate(Node* x) {
    Node* y = x->left;
    if (!y) return;
    x->left = y->right;
    if (y->right)
        y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

// Вставка нового узла в дерево
void RBTree::insert(int data) {
    Node* z = new Node(data);
    Node* y = nullptr;
    Node* x = root;
    while (x) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (!y)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    z->color = RED;
    insertFixup(z);
}

// Балансировка дерева после вставки
void RBTree::insertFixup(Node* z) {
    while (z != root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        }
        else {
            Node* y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

// Рекурсивный поиск узла с заданным значением
Node* RBTree::searchNode(Node* node, const int& data) const {
    if (node == nullptr || data == node->data)
        return node;
    if (data < node->data)
        return searchNode(node->left, data);
    else
        return searchNode(node->right, data);
}

// Публичный поиск
Node* RBTree::search(int data) const {
    return searchNode(root, data);
}

// Нахождение узла с минимальным значением (начиная с node)
Node* RBTree::treeMinimum(Node* node) const {
    if (!node) return nullptr;
    while (node->left)
        node = node->left;
    return node;
}

// Публичная функция поиска минимума
Node* RBTree::findMin() const {
    return treeMinimum(root);
}

// Нахождение узла с максимальным значением (начиная с node)
Node* RBTree::treeMaximum(Node* node) const {
    if (!node) return nullptr;
    while (node->right)
        node = node->right;
    return node;
}

// Публичная функция поиска максимума
Node* RBTree::findMax() const {
    return treeMaximum(root);
}

// Поиск ближайшего большего (successor) узла для заданного значения
Node* RBTree::findSuccessor(int data) const {
    Node* x = search(data);
    if (!x) return nullptr;
    if (x->right)
        return treeMinimum(x->right);
    Node* y = x->parent;
    while (y && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

// Поиск ближайшего меньшего (predecessor) узла для заданного значения
Node* RBTree::findPredecessor(int data) const {
    Node* x = search(data);
    if (!x) return nullptr;
    if (x->left)
        return treeMaximum(x->left);
    Node* y = x->parent;
    while (y && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

// Замена поддерева: замещает u узлом v
void RBTree::transplant(Node* u, Node* v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v)
        v->parent = u->parent;
}

// Удаление узла из дерева. Возвращает true, если узел найден и удалён.
bool RBTree::remove(int data) {
    Node* z = search(data);
    if (z == nullptr)
        return false; // Узел не найден
    Node* y = z;
    Node* x = nullptr;
    Color yOriginalColor = y->color;
    if (z->left == nullptr) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == nullptr) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = treeMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x) x->parent = y;
        }
        else {
            transplant(y, y->right);
            y->right = z->right;
            if (y->right)
                y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        if (y->left)
            y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (yOriginalColor == BLACK)
        deleteFixup(x, (x ? x->parent : nullptr));
    return true;
}

// Балансировка дерева после удаления узла
// Если x == nullptr, его родитель передается отдельно (xParent)
void RBTree::deleteFixup(Node* x, Node* xParent) {
    while ((x != root) && ((x == nullptr) || (x->color == BLACK))) {
        if (x == (xParent ? xParent->left : nullptr)) {
            Node* w = xParent->right;
            if (w && w->color == RED) {
                w->color = BLACK;
                xParent->color = RED;
                leftRotate(xParent);
                w = xParent->right;
            }
            if ((w == nullptr) ||
                ((w->left == nullptr || w->left->color == BLACK) &&
                    (w->right == nullptr || w->right->color == BLACK))) {
                if (w) w->color = RED;
                x = xParent;
                xParent = xParent->parent;
            }
            else {
                if (w->right == nullptr || w->right->color == BLACK) {
                    if (w->left)
                        w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(xParent);
                    w = xParent->right;
                }
                if (w) w->color = xParent->color;
                xParent->color = BLACK;
                if (w && w->right)
                    w->right->color = BLACK;
                leftRotate(xParent);
                x = root;
            }
        }
        else { // Симметричный случай для правой части
            Node* w = xParent->left;
            if (w && w->color == RED) {
                w->color = BLACK;
                xParent->color = RED;
                rightRotate(xParent);
                w = xParent->left;
            }
            if ((w == nullptr) ||
                ((w->left == nullptr || w->left->color == BLACK) &&
                    (w->right == nullptr || w->right->color == BLACK))) {
                if (w) w->color = RED;
                x = xParent;
                xParent = xParent->parent;
            }
            else {
                if (w->left == nullptr || w->left->color == BLACK) {
                    if (w->right)
                        w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(xParent);
                    w = xParent->left;
                }
                if (w) w->color = xParent->color;
                xParent->color = BLACK;
                if (w && w->left)
                    w->left->color = BLACK;
                rightRotate(xParent);
                x = root;
            }
        }
    }
    if (x)
        x->color = BLACK;
}

// Очистка дерева (удаление всех узлов)
void RBTree::clear() {
    destroyTree(root);
    root = nullptr;
}
