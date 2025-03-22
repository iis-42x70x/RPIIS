#include <iostream>
#include <fstream>
#include <vector>
#include "set_operations.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");

    string filename = "input.txt";
    ifstream inputFile(filename);
    vector<vector<string>> sets;

    // Проверяем, существует ли файл и не пуст ли он
    if (!inputFile || inputFile.peek() == EOF) {
        createAndFillFile(filename);
        inputFile.open(filename); // Открываем файл заново после создания
    }

    // Читаем множества из файла
    string line;
    while (getline(inputFile, line)) {
        if ((line.front() == '{' && line.back() == '}') || (line.front() == '<' && line.back() == '>')) {
            vector<string> elements;
            processSet(line, elements);
            sets.push_back(elements); // Добавляем множество в список
        }
        else {
            cout << "Ошибка: Некорректный формат множества: " << line << endl;
            return 1;
        }
    }
    inputFile.close();

    // Вычисляем пересечение множеств
    vector<string> result = intersection(sets);

    cout << "Пересечение множеств: {";
    bool first = true;
    for (const auto& el : result) {
        if (!first) cout << ", ";
        cout << el;
        first = false;
    }
    cout << "}" << endl;

    return 0;
}
