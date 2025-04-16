#include<iostream>
#include<vector>
using namespace std;
struct Treenode {
    int data;
    vector <Treenode*> children;
};
Treenode* GetNewRoot() {
    int data;
    cout << "Введите числовое значение корня дерева\n";
    cin >> data;
    Treenode* newnode = new Treenode;
    newnode->data = data;
    return newnode;
}
void addChild(Treenode*& parent, int n) {
    if (!parent) {
        cout << "Ошибка: Дерево не создано. Создайте корень сначала.\n";
        return;
    }
    int o; int depth;
    cout << "Введите уровень (1 это корень)" << endl;
    cin >> depth;
    Treenode* g = parent;
    if (depth == 1) {
        if (parent->children.size() < n) {
            int value;
            cout << "Введите значение нового узла: ";
            cin >> value;
            Treenode* newNode = new Treenode{ value, {} };
            parent->children.push_back(newNode);
            cout << "Узел добавлен к корню\n";
        }
        else {
            cout << "Ошибка: Достигнута максимальная арность (" << n << ") у корня.\n";
        }
        return;
    }
    for (int i = 0; i < depth - 1; i++) {
        if (g->children.empty()) {
            cout << "Ошибка: У этого узла нет потомков.\n";
            return;
        }
        cout << "Доступные узлы: ";
        for (int j = 0; j < g->children.size(); j++) {
            cout << j + 1 << ": " << g->children[j]->data << " ";
        }
        cout << "Введите номер узла " << endl;
        cin >> o;
        if (o < 1 || o > g->children.size()) {
            cout << "Ошибка: Неверный номер узла\n";
            return;
        }
        g = g->children[o - 1];
    }
    cout << "Дети текущего узла: ";
    for (int j = 0; j < g->children.size(); j++) {
        cout << g->children[j]->data;
    }
    int value;
    cout << "Введите значение " << endl;
    cin >> value;
    if (g->children.size() < n) {
        Treenode* k = new Treenode;
        k->data = value;
        g->children.push_back(k);
        cout << "Узел добавлен\n";
        return;
    }
    else {
        cout << "Ошибка: Достигнута максимальная арность (" << n << ").\n";
    }
}
void deleteNode(Treenode* parent, Treenode* nodeToDelete) {
    if (!parent || !nodeToDelete)
        return;
    for (int i = 0; i < parent->children.size(); i++) {
        if (parent->children[i] == nodeToDelete) {
            for (int j = i; j < parent->children.size() - 1; j++) {
                parent->children[j] = parent->children[j + 1];
            }
            parent->children.resize(parent->children.size() - 1);
            break;
        }
    }
    while (!nodeToDelete->children.empty()) {
        deleteNode(nodeToDelete, nodeToDelete->children.back());
    }
    delete nodeToDelete;
}
void findtodelete(Treenode* parent) {
    if (!parent) {
        cout << "Ошибка: Дерево пустое\n";
        return;
    }
    int o; int depth;
    cout << "Введите уровень дерева" << endl;
    cin >> depth;
    Treenode* g = parent;
    for (int i = 0; i < depth; i++) {

        for (int j = 0; j < g->children.size(); j++) {
            cout << j + 1 << ":" << g->children[j]->data << " ";
        }
        cout << "Выберите номер узла " << endl;

        cin >> o;
        if (o < 1 || o > g->children.size()) {
            cout << "Ошибка: Неверный номер узла\n";
            return;
        }
        parent = g;
        g = g->children[o - 1];

        deleteNode(parent, g);
    }
}
void printTree(Treenode* root, int depth = 0) {
    if (root == nullptr)
        return;

    for (int i = 0; i < depth; i++)
        cout << "  ";
    cout << "|--" << root->data << endl;
    for (Treenode* child : root->children)
        printTree(child, depth + 1);
}
void deleteTree(Treenode*& parent)
{
    for (Treenode* child : parent->children)
    {
        deleteNode(parent, child);
    }
    delete parent;
    parent = NULL;


}
void choice(int n) {
    cout << "Арность дерева " << n << endl;
    cout << "Создать дерево: 1\n";
    cout << "Добавить узел: 2\n";
    cout << "Удалить узел: 3\n";
    cout << "Вывод дерева на экран: 4\n";
    cout << "Удалить дерево: 5\n";
    cout << "Выход: 6\n";

}
void menu() {
    cout << "Введите арность дерева \n";
    int n;
    cin >> n;
    Treenode* root = NULL;
    int kod;

    while (true)
    {
        choice(n);
        cin >> kod;
        switch (kod) {
        case 1:
            root = GetNewRoot();
            break;
        case 2:
            addChild(root, n);
            break;
        case 3:
            findtodelete(root);
            break;
        case 4:
            cout << "       Tree        \n";
            printTree(root, 0);
            break;
        case 5:
            deleteTree(root);
            break;
        case 6:
            cout << "выход";
            return;
        }
    }
}
