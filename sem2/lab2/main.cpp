/*
 * Разработчик: Пушистова Екатерина Сергеевна
 * Дата разработки: 22.04.25
 *
 * Назначение: программа формирует множество равное
 * разности двух исходных (прочитанных из файла) множеств
 * (с учётом кратных вхождений)                            */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Set_lib/Set.hpp"


using namespace std;

int main() {
    string line1, line2;
    if (!Set::read_input("input.txt", line1, line2)) {  // Вызов статического метода
        cout << "Ошибка открытия файла" << endl;
        return 1;
    }

    vector<Element> set1, set2;
    string name1, name2;
    if (!Set::process_set_line(line1, name1, set1) ||
        !Set::process_set_line(line2, name2, set2)) {
        cout << "Некорректный формат множества или имя" << endl;
        return 1;
    }

    Set setObj1(set1), setObj2(set2);
    Set result = setObj1.difference(setObj2);

    Set::output_results(setObj1, setObj2, result, name1, name2, "S");

    return 0;
}