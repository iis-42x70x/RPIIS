#include <iostream>
#include <vector>
#include "header.h"

using namespace std;

int main() {
    vector<Union> testi;
    int n;
    cout << "Введите 1, если хотите считать множества из файла\n";
    cout << "Введите 2, если хотите ввести множества вручную\n";
    cin >> n;

    switch (n) {
    case 1: {
        shitivanie_file(testi);
        break;
    }
    case 2: {
        cout << "Введите количество множеств: ";
        int size1;
        cin >> size1;
        cin.ignore();
        testi.resize(size1);
        for (int i = 0; i < size1; ++i) {
            cout << "Заполните множество " << i + 1 << ":\n";
            testi[i].shitivanie();
        }
        break;
    }
    default:
        cout << "Неверный ввод, завершение программы.\n";
        return 1;
    }

    for (size_t i = 0; i < testi.size(); ++i) {
        bool flag = true;
        vector<string>& current = testi[i].get_vector();
        for (size_t j = 0; j < current.size(); ++j) {
            checking_znaki(current[j]);
            if (!checking_pravilnost_stroki(current[j]) || !check_podrad(current[j])) {
                flag = false;
                break;
            }
        }
        if (!flag) {
            cout << "\nЭлемент множества " << i + 1 << " заполнен некорректно! Программа завершается!\n";
            return 1;
        }
    }

    cout << "\nОтсортированные множества:\n";
    for (size_t i = 0; i < testi.size(); ++i) {
        testi[i].print();
        cout << endl;
    }

    vector<string> result;
    main_symm_diff(testi, result);

    cout << "\nСимметрическая разность множеств:\n";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << ' ';
    }

    return 0;
}
