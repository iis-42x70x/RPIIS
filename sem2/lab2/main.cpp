#include "pch.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector <element> sets;

    cout << "Читаем множества из файла..." << endl;
    ifstream input("data.txt");

    if (!input.is_open()) {
        cout << "Не удалось открыть файл!" << endl;
        return -1;
    }

    string line;
    element temp;
    for (int i = 1; getline(input, line); i++) {
        cout << i << "-е множество: " << line << endl;
        if (!StringCheck(line)) {
            cout << "Некорректный ввод множества " << i << endl;
            return -1;
        }
        StringToElement(temp, line, 0, (int)line.size() - 1);
        if (!SetUniqueCheck(temp)) {
            cout << "Обнаружена неуникальность во множестве " << i << endl;
            return -1;
       }
        sets.push_back(temp);
        temp.setik.clear();
    }

    input.close();
    
    if (sets.size() == 0) {
        cout << "Множества не прочитаны" << endl;
        return -1;
    }

    temp = sets[0];
    for (int i = 1; i < sets.size(); i++) temp = intersection(temp, sets[i]);
    cout << "Пересечение введённых множеств: ";
    ElementCout(temp);
    return 0;
}
