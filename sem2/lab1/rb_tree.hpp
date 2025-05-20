#ifndef RB_TREE_HPP
#define RB_TREE_HPP

// Определение цвета узла
enum Color { RED, BLACK };

// Структура узла красно-чёрного дерева
struct Node {
    int data;       // Значение узла
    Color color;    // Цвет узла (RED или BLACK)
    Node* left;     // Указатель на левое поддерево
    Node* right;    // Указатель на правое поддерево
    Node* parent;   // Указатель на родительский узел

    // Конструктор узла
    Node(int data);
};

// Класс красно-чёрного дерева с операциями вставки, удаления, поиска и др.
class RBTree {
public:
    RBTree();
    ~RBTree();

    // Основные операции
    void insert(int data);
    bool remove(int data);
    Node* search(int data) const;
    Node* findMin() const;
    Node* findMax() const;
    Node* findSuccessor(int data) const;
    Node* findPredecessor(int data) const;
    void inorder() const; // Обход дерева (inorder) для демонстрации

    // Очистка дерева
    void clear();

private:
    Node* root; // Корень дерева

    // Вспомогательные функции
    void leftRotate(Node* x);
    void rightRotate(Node* x);
    void insertFixup(Node* z);
    void deleteFixup(Node* x, Node* xParent);
    Node* treeMinimum(Node* node) const;
    Node* treeMaximum(Node* node) const;
    void transplant(Node* u, Node* v);
    void inorderHelper(Node* node) const;
    void destroyTree(Node* node);
    Node* searchNode(Node* node, const int& data) const;
};

#endif // RB_TREE_HPP
