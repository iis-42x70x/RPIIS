#include <iostream>
#include <iomanip>
#include "AVL_tree.hpp"

unsigned char AVL_tree::height(node* p)
{
    return p ? p->height : 0; // Если указатель не нулевой, возвращает высоту; иначе возвращает 0
}

// Вычисляет балансировочный фактор узла
int AVL_tree::bfactor(node* p)
{
    return height(p->right) - height(p->left);
}

// Восстанавливает корректное значение поля height заданного узла 
void AVL_tree::fixheight(node* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

// Правый поворот вокруг p
AVL_tree::node* AVL_tree::rotateright(node* p)
{
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

// Левый поворот вокруг q
AVL_tree::node* AVL_tree::rotateleft(node* q)
{
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

// Балансировка узла p
AVL_tree::node* AVL_tree::balance(node* p)
{
    fixheight(p);
    if (bfactor(p) == 2)
    {
        if (bfactor(p->right) < 0)
            p->right = rotateleft(p->right);
        return rotateleft(p);
    }

    if (bfactor(p) == -2)
    {
        if (bfactor(p->left) > 0)
            p->left = rotateright(p->left);
        return rotateright(p);
    }
    return p; // Если балансировка не нужна
}

AVL_tree::node* AVL_tree::insert(node* p, int k) // Вставка ключа k в дерево с корнем p
{
    if (!p) return new node(k); // Если узел пуст, создаем новый
    else if (k < p->key)
        p->left = insert(p->left, k); // Рекурсивно вставляем в левое поддерево
    else if (k > p->key)
        p->right = insert(p->right, k); // Рекурсивно вставляем в правое поддерево

    return balance(p); // Возвращаем сбалансированный узел
}

void AVL_tree::show_pass(node* p, int indent = 0, const std::string& prefix = "", bool isRoot = true)
{
    if (p == nullptr) return;

    // Выводим текущий узел
    if (isRoot) {
        std::cout << "ROOT: " << p->key << std::endl;
    }
    else {
        std::cout << std::string(indent, ' ') << prefix << p->key << std::endl;
    }

    // Сначала правое поддерево
    show_pass(p->right, indent + 4, "R----", false);
    // Затем левое поддерево
    show_pass(p->left, indent + 4, "L----", false);
}

AVL_tree::node* AVL_tree::findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
    return p->left ? findmin(p->left) : p;
}

AVL_tree::node* AVL_tree::removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
    if (p->left == 0)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}
AVL_tree::node* AVL_tree::remove(node* p, int k) // удаление ключа k из дерева p
{
    if (!p) return 0;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else //  k == p->key 
    {
        node* q = p->left;
        node* r = p->right;
        delete p;
        if (!r) return q;
        node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

AVL_tree::node* AVL_tree::search_pass(node* p, int k)
{
    if (!p) return nullptr;

    if (p->key == k) return p;

    if (k > p->key)
        search_pass(p->right, k);
    else if (k < p->key)
        search_pass(p->left, k);
}

void AVL_tree::insert(int k)
{
    root = insert(root, k); // Вставка нового ключа
}

void AVL_tree::show()
{
    std::cout << "AVL Tree Structure:" << std::endl;
    show_pass(root); // Показать все ключи в дереве
}

void AVL_tree::remove(int k)
{
    root = remove(root, k);
}

bool AVL_tree::search(int k)
{
    if (search_pass(root, k) == nullptr)
        return 0;
    else
        return 1;
}

int AVL_tree::findPredecessor(int key) // Ближайший минимум
{
    node* current = search_pass(root, key); // Находим узел
    if (!current) return -1; // Узел не найден

    // Случай 1: Есть левое поддерево - ищем максимум в нём
    if (current->left) {
        node* temp = current->left;
        while (temp->right) {
            temp = temp->right;
        }
        return temp->key;
    }
    // Случай 2: Нет левого поддерева - ищем первого меньшего родителя
    else {
        node* predecessor = nullptr;
        node* ancestor = root;
        while (ancestor != current) {
            if (current->key > ancestor->key) {
                predecessor = ancestor;
                ancestor = ancestor->right;
            }
            else {
                ancestor = ancestor->left;
            }
        }
        return predecessor ? predecessor->key : -1; // Если нет предшественника
    }
}

int AVL_tree::findSuccessor(int key) // Ближайший максимум
{   
    node* current = search_pass(root, key); // Находим узел
    if (!current) return -1; // Узел не найден

    // Случай 1: Есть правое поддерево - ищем минимум в нём
    if (current->right) {
        node* temp = current->right;
        while (temp->left) {
            temp = temp->left;
        }
        return temp->key;
    }
    // Случай 2: Нет правого поддерева - ищем первого большего родителя
    else {
        node* successor = nullptr;
        node* ancestor = root;
        while (ancestor != current) {
            if (current->key < ancestor->key) {
                successor = ancestor;
                ancestor = ancestor->left;
            }
            else {
                ancestor = ancestor->right;
            }
        }
        return successor ? successor->key : -1; // Если нет преемника
    }
}

int AVL_tree::findAbsMax()
{
    node* p = root;

    while (p->right != nullptr)
    {
        p = p->right;
    }

    return p->key;
}

int AVL_tree::findAbsMin()
{
    node* p = root;

    while (p->left != nullptr)
    {
        p = p->left;
    }

    return p->key;
}

void AVL_tree::delete_subtree(node* p)
{
    if (p != nullptr)
    {
        delete_subtree(p->left);
        delete_subtree(p->right);
        delete p;
    }
}

void AVL_tree::delete_all()
{
    delete_subtree(root);
    root = nullptr;
}