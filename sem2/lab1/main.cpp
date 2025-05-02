#include "..\RBtree\Header.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");
    RBTree tree;
    int choice, value, k;

    while (true) {
        std::cout << "\nВыберите операцию:\n"
                  << "1. Создать узел\n"
                  << "2. Просмотреть дерево\n"
                  << "3. Удалить узел\n"
                  << "4. Найти минимальное значение\n"
                  << "5. Найти максимальное значение\n"
                  << "6. Найти ближайший меньший элемент\n"
                  << "7. Найти ближайший больший элемент\n"
                  << "0. Выход\n"
                  << "Ваш выбор: ";

        while (!(std::cin >> choice)) {
            std::cout << "Это не число. Попробуйте снова: ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }

        switch (choice) {
            case 1:
                std::cout << "Введите значение для добавления: ";
                while (!(std::cin >> value)) {
                    std::cout << "Это не число. Попробуйте снова: ";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
                tree.RB_INSERT(value);
                break;
            case 2:
                std::cout << "Выберете способ (1 или 2) для показа дерева:\n";
                while (!(std::cin >> k)) {
                    std::cout << "Это не число. Попробуйте снова: ";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
                while (k != 1 && k != 2) {
                    std::cout << "Некорректный выбор. Попробуйте снова:\n";
                    while (!(std::cin >> k)) {
                        std::cout << "Это не число. Попробуйте снова: ";
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                    }
                }
                if (k == 1) {
                    tree.printTree(tree.getRoot());
                }
                else {
                    tree.print_2(tree.getRoot(), "", true);
                }
                break;
            case 3:
                std::cout << "Введите значение для удаления: ";
                while (!(std::cin >> value)) {
                    std::cout << "Это не число. Попробуйте снова: ";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
                tree.RB_DELETE(value);
                break;
            case 4: {
                node* min = tree.minimum(tree.getRoot());
                if (min) std::cout << "Минимальный элемент: " << min->data << std::endl;
                break;
            }
            case 5: {
                node* max = tree.maximum(tree.getRoot());
                if (max) std::cout << "Максимальный элемент: " << max->data << std::endl;
                break;
            }
            case 6: {
                std::cout << "Введите значение: ";
                while (!(std::cin >> value)) {
                    std::cout << "Это не число. Попробуйте снова: ";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
                node* found = tree.search(value);
                if (!found) {
                    std::cout << "Узел не найден\n";
                    break;
                }
                node* least = tree.most_left(found);
                if (least) std::cout << "Ближайший меньший элемент: " << least->data << std::endl;
                else std::cout << "Ближайшего меньшего элемента не существует. Данный элемент - наименьший.\n";
                break;
            }
            case 7: {
                std::cout << "Введите значение: ";
                while (!(std::cin >> value)) {
                    std::cout << "Это не число. Попробуйте снова: ";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
                node* found = tree.search(value);
                if (!found) {
                    std::cout << "Узел не найден\n";
                    break;
                }
                node* most = tree.most_right(found);
                if (most) std::cout << "Ближайший больший элемент: " << most->data << std::endl;
                else std::cout << "Ближайшего большего элемента не существует. Данный элемент - наибольший.\n";
                break;
            }
            case 8:
                tree.test_f();
                break;
            case 0:
                return 0;
            default:
                std::cout << "Некорректный выбор\n";
        }
    }
}
