#pragma once
class AVL_tree
{
private:
    // Структура для представления узлов дерева 
    struct node
    {
        int key; // Ключ/данные
        unsigned char height; // Высота
        node* left; // Указатели на левый и правый узел соответственно
        node* right;

        node(int k) : key(k), left(nullptr), right(nullptr), height(1) {} // Конструктор узла (ноды)
    };

    node* root = nullptr;

    unsigned char height(node* p);

    int bfactor(node* p);

    void fixheight(node* p);

    node* rotateright(node* p);

    node* rotateleft(node* q);

    node* balance(node* p);

    node* insert(node* p, int k);

    void show_pass(node* p, int indent, const std::string& prefix, bool isRoot);

    node* findmin(node* p);

    node* removemin(node* p);

    node* remove(node* p, int k);

    node* search_pass(node* p, int k);

    void delete_subtree(node* p);
public:
    
    void insert(int k);

    void show();

    void remove(int k);

    bool search(int k);

    int findPredecessor(int key);

    int findSuccessor(int key);

    int findAbsMax();

    int findAbsMin();

    void delete_all();
};