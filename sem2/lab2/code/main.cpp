// tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Header.h"

using namespace std;


int main() {
    vector<Set> new_test;
    int number_of_choice;
    cout << "Введите 1, если хотите считать множества из файла" << endl;
    cout << "Введите 2, если хотите ввести множеств в ручную" << endl;
    cin >> number_of_choice;
    switch (number_of_choice) {
    case 1: {
        reading_file(new_test);

    }break;
    case 2: {
        cout << "Введите количество множеств: " << endl;
        int size1;
        cin >> size1;
        cin.ignore();
        new_test.resize(size1);
        for (int i = 0; i < size1; i++) {
            cout << "Заполните множество " << i + 1 << ":" << endl;
            new_test[i].reading();
        }


    }break;
    default: {
        cout << "вы ввели неправильный номер операции, программа завершена";
    }break;

    }


    for (int i = 0; i < new_test.size(); i++) {
        auto& vec = new_test[i].get_vector();
        for (auto& el : vec) {
            /* el.erase(remove(el.begin(), el.end(), ' '), el.end());*/
            string result = sort_set(el);
            el = result;
        }
    }

    for (int i = 0; i < new_test.size(); i++) {
        bool flag = true;
        for (auto& el : new_test[i].get_vector()) {
            checking_symbol(el);
            if (!checking_correct_str(el) || !checking_next(el)) {
                flag = false;
                break;
            }
        }
        if (!flag) {
            cout << endl << "Элемент множества " << ' ' << i + 1 << ' ' << "заполнен не корректно! Пргорамма завершается!" << endl;
            return 0;
        }
    }
    cout << endl << "Отсортированные множества:" << endl;
    for (int i = 0; i < new_test.size(); i++) {
        new_test[i].print();
        cout << endl;
    }
    vector <string> result = new_test[0].get_vector();
    cout << "Пересечение множеств:" << endl;
    main_intersection(new_test, result);
    for (auto& els : result) {
        cout << els << ' ' << ' ';
    }
    return 0;
}
