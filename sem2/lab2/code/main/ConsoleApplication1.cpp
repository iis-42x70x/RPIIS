#include <iostream>
#include"Set.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    int choise;
    bool isTrue = true;

    do {
        cout << "Выберите опцию:";
        cout << "\n\n\t1. Решить задание, используя заготовленные множества;";
        cout << "\n\t2. Решить задание, используя собственные множества;";
        cout << "\n\t3. Выход;";
        cout << "\n\n\tВаш выбор: ";
        cin >> choise;

        switch (choise) {
        case 1: {
            system("cls");
            solution("C:\\Users\\555\\Desktop\\учёба\\ПиОИвИС\\2 семестр\\ConsoleApplication1\\input_const.txt", true);
        } break;
        case 2: {
            system("cls");
            solution("C:\\Users\\555\\Desktop\\учёба\\ПиОИвИС\\2 семестр\\ConsoleApplication1\\input_user.txt", false);
        } break;
        case 3: {
            system("cls");
            cout << "Вы вышли из программы!\n";
            isTrue = false;
        } break;
        default: {
            system("cls");
            cout << "Вы ввели неверное число! Попробуйте ещё раз!\n\n";
        } break;
        }
    } while (isTrue != false);
}