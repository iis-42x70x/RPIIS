/*Декартово дерево.Вставка.Поиск.Удаление.Построение дерева из
массива значений. Объединение двух деревьев.Пересечение двух
деревьев.*/
#include "Header.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    Node* root = NULL;
    int choice, value;

    while (true) {
        printMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            // Создание нового дерева
            root = NULL;
            cout << "Введите количество элементов: ";
            int n;
            cin >> n;
            cout << "Введите элементы:" << endl;
            for (int i = 0; i < n; ++i) {
                cin >> value;
                root = insert(root, value);
            }
            break;
        }
        case 2: {
            // Вставка элемента
            cout << "Введите элемент для вставки: ";
            cin >> value;
            root = insert(root, value);
            break;
        }
        case 3: {
            // Удаление элемента
            cout << "Введите элемент для удаления: ";
            cin >> value;
            root = remove(root, value);
            break;
        }
        case 4: {
            // Поиск элемента
            cout << "Введите элемент для поиска: ";
            cin >> value;
            if (search(root, value)) {
                cout << "Элемент найден.\n";
            }
            else {
                cout << "Элемент не найден.\n";
            }
            break;
        }
        case 5: {
            // Объединение двух деревьев
            cout << "Создайте второе дерево:\n";
            Node* root2 = NULL;
            cout << "Введите количество элементов: ";
            int n;
            cin >> n;
            cout << "Введите элементы:" << endl;
            for (int i = 0; i < n; ++i) {
                cin >> value;
                root2 = insert(root2, value);
            }
            root = unionTreaps(root, root2);
            cout << "Деревья объединены.\n";
            break;
        }
        case 6: {
            // Пересечение двух деревьев
            cout << "Создайте второе дерево:\n";
            Node* root2 = NULL;
            cout << "Введите количество элементов: ";
            int n;
            cin >> n;
            cout << "Введите элементы:" << endl;
            for (int i = 0; i < n; ++i) {
                cin >> value;
                root2 = insert(root2, value);
            }
            Node* intersection = intersectionTreaps(root, root2);
            cout << "Результат пересечения:\n";
            inorder(intersection);
            root = intersection;
            break;
        }
        case 7: {
            // Вывод дерева
            cout << "Дерево:\n";
            inorder(root);
            break;
        }
        case 8: {
            // Выход
            return 0;
        }
        default: {
            cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
        }
    }

    return 0;
}