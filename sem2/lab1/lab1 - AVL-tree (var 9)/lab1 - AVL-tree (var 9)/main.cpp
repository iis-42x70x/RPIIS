#include <iostream>
#include <locale>

#include "AVL_tree.hpp"
using namespace std;
//AVL-дерево. Вставка. Удаление. Поиск. Поиск минимума, максимума,
//ближайшего большего и ближайшего меньшего.

int main()
{
    setlocale(LC_ALL, "RU");

    AVL_tree tree;
    int choice;

    while (true)
    {
        system("cls");

        std::cout << "Выберите операцию: " << endl
            << "1. Создать AVL-дерево/Добавить n элементов в дерево." << endl // готово
            << "2. Вывести элементы." << endl // готово
            << "3. Найти элемент." << endl // готово
            << "4. Удалить элемент." << endl // готово
            << "5. Вывести минимум, максимум, ближайший минимум и ближайший максимум." << endl
            << "6. Очистить дерево." << endl
            << "7. Вставить элемент." << endl // готово
            << "8. Завершить программу." << endl // готово
            << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            int n, buf;
            std::cout << "Введите кол-во элементов для дерева:\n";
            std::cin >> n;
            std::cout << "Введите " << n << " элементов дерева:\n";

            for (int i = 0; i < n; i++)
            {
                cin >> buf;
                tree.insert(buf);
            }
            system("pause");
            break;
        }
        case 2:
        {
            system("cls");

            tree.show();

            system("pause");
            break;
        }
        case 3: 
        {
            system("cls");
            int buf;

            std::cout << "Введите элемент, который хотите найти:";
            std::cin >> buf;

            buf = tree.search(buf);

            if (buf == 0)
                std::cout << "Такого элемента нет." << endl;
            else if (buf == 1)
                std::cout << "Элемент найден." << endl;

            system("pause");
            break;
        }
        case 4:
        {
            system("cls");
            int buf;

            std::cout << "Введите ключ, который хотите удалить: ";
            std::cin >> buf;
            tree.remove(buf);

            system("pause");
            break;
        }
        case 5:
        {
            system("cls");
            int buf;

            std::cout << "Введите ключ, относительно которого хотите вести поиск: ";
            cin >> buf;

            std::cout << "Абсолютный минимум: " << tree.findAbsMin() << endl;
            std::cout << "Абсолютный максимум: " << tree.findAbsMax() << endl;
            std::cout << "Ближайший минимум: " << tree.findPredecessor(buf) << endl;
            std::cout << "Ближайший максимум: " << tree.findSuccessor(buf) << endl;

            system("pause");
            break;
        }
        case 6:
        {
            system("cls");

            tree.delete_all();

            system("pause");
            break;
        }
        case 7:
        {
            system("cls");

            int buf;

            std::cout << "Введите ключ, который хотите добавить: ";
            std::cin >> buf;
            tree.insert(buf);

            system("pause");
            break;
        }
        case 8:
        {
            system("cls");
            return 0;
        }
        default:
            break;
        }
    }

    return 0;
}