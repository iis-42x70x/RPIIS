#include <iostream>
#include "pch.h"

using namespace std;

int main()
{
    int t, k;
    
    setlocale(LC_ALL, "Russian");

    Set set1;
    Set set2;

    do {
        cout << "Выберете вариант действия:" << endl;
        cout << "1. Создание множества" << endl;
        cout << "2. Добавление элемента во множество " << endl;
        cout << "3. Удаление элемента из множества" << endl;
        cout << "4. Поиск элемента во множестве" << endl;
        cout << "5. Объединение" << endl;
        cout << "6. Пересечение" << endl;
        cout << "7. Выход" << endl;
        t = set1.inputInteger();

        switch (t)
        {
        case 1:
            do {
                cout << "Создание множество А(1) или В(2): " << endl;
                cin >> k;
                switch (k) {
                case 1:
                    set1.create();
                    break;
                case 2:
                    set2.create();
                    break;
                default:
                    cout << "Неверный выбор" << endl;
                    break;
                }
                break;
            } while (k == 1 || k == 2);
            break;
        case 2:
            do {
                cout << "Добавление элемента во множество А(1) или В(2): " << endl;
                cin >> k;
                switch (k) {
                case 1:
                    set1.add();
                    break;
                case 2:
                    set2.add();
                    break;
                default:
                    cout << "Неверный выбор" << endl;
                    break;
                }
                break;
            } while (k == 1 || k == 2);
            break;
        case 3:
            do {
                cout << "Удалить множество А(1) или В(2): " << endl;
                cin >> k;
                switch (k) {
                case 1:
                    set1.remove();
                    break;
                case 2:
                    set2.remove();
                    break;
                default:
                    cout << "Неверный выбор" << endl;
                    break;
                }
                break;
            } while (k == 1 || k == 2);
            break;
        case 4:
            do {
                cout << "Поиск элемента во множество А(1) или В(2): " << endl;
                cin >> k;
                switch (k) {
                case 1:
                    set1.search();
                    break;
                case 2:
                    set2.search();
                    break;
                default:
                    cout << "Неверный выбор" << endl;
                    break;
                }
                break;
            } while (k == 1 || k == 2);
            break;
            break;
        case 5:
            set1.unionWith(set2);
            break;
        case 6:
            set1.intersectWith(set2);
            break;
        case 7:
            cout << "До свидания!" << endl;
            break;
        default:
            cout << "Неверный выбор" << endl;
            break;
        }
    } while (t != 7);

}
