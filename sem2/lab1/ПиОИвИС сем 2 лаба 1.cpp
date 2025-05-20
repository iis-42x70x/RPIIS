#include "rb_tree.hpp"
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    RBTree tree;

    // Тестирование вставки
    cout << "Вставка элементов: 20, 15, 25, 10, 18, 22, 30" << endl;
    tree.insert(20);
    tree.insert(15);
    tree.insert(25);
    tree.insert(10);
    tree.insert(18);
    tree.insert(22);
    tree.insert(30);

    cout << "Inorder обход: ";
    tree.inorder();

    // Тестирование поиска
    int key = 15;
    Node* found = tree.search(key);
    if (found)
        cout << "Элемент " << key << " найден в дереве." << endl;
    else
        cout << "Элемент " << key << " не найден." << endl;

    // Тестирование поиска минимума и максимума
    Node* minNode = tree.findMin();
    Node* maxNode = tree.findMax();
    if (minNode)
        cout << "Минимальный элемент: " << minNode->data << endl;
    if (maxNode)
        cout << "Максимальный элемент: " << maxNode->data << endl;

    // Тестирование поиска ближайшего большего и меньшего
    int testVal = 18;
    Node* successor = tree.findSuccessor(testVal);
    Node* predecessor = tree.findPredecessor(testVal);
    if (successor)
        cout << "Ближайший больший для " << testVal << ": " << successor->data << endl;
    else
        cout << "Ближайший больший для " << testVal << " отсутствует." << endl;
    if (predecessor)
        cout << "Ближайший меньший для " << testVal << ": " << predecessor->data << endl;
    else
        cout << "Ближайший меньший для " << testVal << " отсутствует." << endl;

    // Тестирование удаления
    cout << "Удаление элемента 15." << endl;
    if (tree.remove(15))
        cout << "Элемент 15 успешно удалён." << endl;
    else
        cout << "Удаление элемента 15 не удалось." << endl;
    cout << "Inorder обход после удаления: ";
    tree.inorder();

    // Попытка удаления несуществующего элемента
    cout << "Попытка удаления несуществующего элемента 100." << endl;
    if (!tree.remove(100))
        cout << "Элемент 100 не найден, удаление не выполнено." << endl;

    // Очистка дерева
    //cout << "Очистка дерева." << endl;
    //tree.clear();
    //cout << "Inorder обход после очистки: ";
    //tree.inorder();

    tree.clear();
    cout << "Попытка удаления несуществующего элемента 10." << endl;
    if (!tree.remove(10))
        cout << "Элемент 10 не найден, удаление не выполнено." << endl;

    tree.insert(7);

    return 0;
}
