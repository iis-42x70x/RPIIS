#include <iostream>
#include <string>
#include "queue.h"

using namespace std;

int main() {
    setlocale(0, "");
    Element* pervyi = nullptr;
    Element* posled = nullptr;

    int choice;
    string element;

    while (true) {
        cout << "Меню:" << endl;
        cout << "1) Добавить элемент" << endl;
        cout << "2) Посмотреть очередь" << endl;
        cout << "3) Взять элемент" << endl;
        cout << "4) Очистка очереди" << endl;
        cout << "5) Закрыть программу" << endl;
        cout << "Выберите пункт меню: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Введите элемент для добавления (0 для возврата в меню): ";
            cin.ignore();
            getline(cin, element);
            while (element != "0") {
                dobavqueue(pervyi, posled, element);
                cout << "Введите следующий элемент (0 для возврата в меню): ";
                getline(cin, element);
            }
        }
        else if (choice == 2) {
            viewqueue(pervyi);
        }
        else if (choice == 3) {
            if (!isEmpty(pervyi)) {
                string value = vziatqueue(pervyi, posled);
                if (value != "") {
                    cout << "Взятый элемент: " << value << endl;
                }
            }
            else {
                cout << "Очередь пуста." << endl;
            }
        }
        else if (choice == 4) {
            clearqueue(pervyi, posled);
        }
        else if (choice == 5) {
            cout << "Программа закрыта." << endl;
            return 0;
        }
        else {
            cout << "Некорректный выбор. Пожалуйста, выберите существующий пункт меню." << endl;
        }
    }

    return 0;
}
