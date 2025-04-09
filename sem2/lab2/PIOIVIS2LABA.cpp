#include "header.h"



int main() {
    setlocale(LC_ALL, "Russian");
    string filename = "input.txt";

    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка! Не могу открыть файл: " << filename << endl;
        cerr << "Убедитесь, что файл существует и находится в той же папке, что и программа." << endl;
        return 1;
    }

    string set1, set2;
    getline(file, set1);
    getline(file, set2);
    file.close();

    cout << "Прочитано из файла:\nSet1: " << set1 << "\nSet2: " << set2 << endl;

    if (!check(set1) || !check(set2)) {
        cout << "Ошибка в формате множеств!\n";
        return 1;
    }

    vector<string> elements1, elements2;
    parse(set1, elements1);
    parse(set2, elements2);

    cout << "\nРезультаты:\n";
    cout << "1. Является ли первое множество подмножеством второго: "
        << isSubset(elements1, elements2, set1, set2) << endl;
    cout << "2. Является ли второе множество подмножеством первого: "
        << isSubset(elements2, elements1, set1, set2) << endl;
    cout << "3. Является ли первое множество элементом второго: "
        << isElement(set1, set2) << endl;
    cout << "4. Является ли второе множество элементом первого: "
        << isElement(set2, set1) << endl;

    return 0;
}
