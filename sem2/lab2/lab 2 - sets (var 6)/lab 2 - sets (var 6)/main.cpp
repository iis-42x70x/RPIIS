// main.cpp (обновленный вывод)
#include "sets.hpp"
#include <locale>
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    const string files_path = "tests/file.txt";

    try {
        vector<Set> sets = ParseFile(files_path);
        Set product = DecartProduct(sets);

        cout << "Декартово произведение (" << product.elements.size() << " элементов):\n";
        for (const auto& elem : product.elements) {
            cout << "   ";
            printElement(elem);
            cout << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}