#include <iostream>
#include <vector>
#include "SegTree.hpp"

using namespace std;

int main() {
    setlocale (LC_ALL, "RU");
    int choice, element;
    int left, right;
    long long summa;
    bool flag = true;
    int N;
    cout << "Введите количество элементов массива\n";
    while (true) {
        cin >> N;
        if (N <= 0) cout << "Введите положительное число\n";
        else break;
    }
    vector<int> array(N);
    cout << "Введите " << N << " элементов массива\n";
    for (int i = 0; i < N; i++) {
        cin >> array[i];
    }
    SegTree tree(array);
    while (flag) {
        cout << "Введите номер операции :\n"
             <<"1 - изменить числа на отрезке массива;\n"
             <<"2 - найти сумму на отрезке;\n"
             <<"3 - вывести массив;\n"
             <<"4 - завершить программу;\n";
        cin >> choice;
        switch (choice) {
            case 1: {
                cout << "Введите границы отрезка от 0 до " << N - 1 << endl;
                while (true) {
                    cin >> left >> right;
                    if (tree.is_valid_index(left, N) && tree.is_valid_index(right, N)) break;
                    else cout << "Введите границы отрезка от 0 до " << N - 1 << endl;
                }
                cout << "Введите значение, на которое изменятся числа на отрезке\n";
                cin >> element;
                tree.update_array(left, right, element);
                array = tree.get_final_array();
                break;
            }
            case 2: {
                cout << "Введите границы отрезка от 0 до " << N - 1 << endl;
                while (true) {
                    cin >> left >> right;
                    if (tree.is_valid_index(left, N) && tree.is_valid_index(right, N)) break;
                    else cout << "Введите границы отрезка от 0 до " << N - 1 << endl;
                }
                summa = tree.get_sum(left, right);
                cout << "Сумма чисел на отрезке :\n"
                     << summa << endl;
                break;
            }
            case 3: {
                    tree.array_output(array, N);
                break;
            }
            case 4: {
                flag = false;
                break;
            }
            default: {
                cout << "Введите корректное значение (1 - 4)\n";
                break;
            }
        }
    }
    return 0;
}