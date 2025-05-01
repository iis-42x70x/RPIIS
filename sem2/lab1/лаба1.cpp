#include "Header.h"
#include <limits> 

int main() {
    setlocale(LC_ALL, "RU");
    SinglyLinkedList list1;
    int choice, value;

    do {
        cout << "1. Добавить элемент\n";
        cout << "2. Просмотреть список\n";
        cout << "3. Удалить элемент\n";
        cout << "4. Сортировать список\n";
        cout << "5. Поиск элемента\n";
        cout << "6. Объединить с другим списком\n";
        cout << "7. Пересечение двух списков\n";
        cout << "8. Выход\n";
        cout << "Выберите действие: ";

        while (!(cin >> choice)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Ошибка: пожалуйста, введите ЧИСЛО!\nВыберите действие: ";
        }

        switch (choice) {
        case 1:
            cout << "Введите значение элемента: ";
            while (!(cin >> value)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка: введите ЧИСЛО!\nВведите значение элемента: ";
            }
            list1.insert(value);
            break;

        case 2:
            list1.display();
            break;

        case 3:
            cout << "Введите значение элемента для удаления: ";
            while (!(cin >> value)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка: введите ЧИСЛО!\nВведите значение элемента для удаления: ";
            }
            list1.remove(value);
            break;

        case 4:
            list1.sort();
            cout << "Список отсортирован.\n";
            break;

        case 5:
            cout << "Введите значение для поиска: ";
            while (!(cin >> value)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка: введите ЧИСЛО!\nВведите значение для поиска: ";
            }
            if (list1.search(value)) {
                cout << "Элемент найден.\n";
            }
            else {
                cout << "Элемент отсутствует в списке.\n";
            }
            break;

        case 6: {
            SinglyLinkedList list2;
            int n;
            cout << "Введите количество элементов второго списка: ";
            while (!(cin >> n) || n <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка: введите положительное ЧИСЛО!\nВведите количество элементов второго списка: ";
            }
            for (int i = 0; i < n; ++i) {
                cout << "Введите элемент " << (i + 1) << ": ";
                while (!(cin >> value)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Ошибка: введите ЧИСЛО!\nВведите элемент " << (i + 1) << ": ";
                }
                list2.insert(value);
            }
            list1.merge(list2);
            cout << "Списки объединены.\n";
            break;
        }

        case 7: {
            SinglyLinkedList list2;
            int n;
            cout << "Введите количество элементов второго списка: ";
            while (!(cin >> n) || n <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка: введите положительное ЧИСЛО!\nВведите количество элементов второго списка: ";
            }
            for (int i = 0; i < n; ++i) {
                cout << "Введите элемент " << (i + 1) << ": ";
                while (!(cin >> value)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Ошибка: введите ЧИСЛО!\nВведите элемент " << (i + 1) << ": ";
                }
                list2.insert(value);
            }
            SinglyLinkedList intersectionList = list1.intersect(list2);
            cout << "Пересечение списков:\n";
            intersectionList.display();
            break;
        }

        case 8:
            cout << "Выход из программы.\n";
            break;

        default:
            cout << "Неверный ввод. Попробуйте снова.\n";
            break;
        }
    } while (choice != 8);

    return 0;
}
