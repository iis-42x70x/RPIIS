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

using namespace std;

struct Element {
    string value;
    int count;
};

bool is_correct_char(char c) { //проверяет корректность символов.
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
    (c >= '0' && c <= '9') || (c == '_');
}

bool is_correct_name(const string &s) { //посимвольно проверяет имя.
    if (s.empty()) return false;
    for (char c : s) {
        if (!is_correct_char(c)) return false;
    }
    return true;
}
//считывает по одному элементу множества.
//на вход - строка input, начало считывания - позиция pos, сохранение в element.
bool parse_element(const string &input, size_t &pos, string &element) {
    while (pos < input.size() && input[pos] == ' ') ++pos; // пропуск пробелов.

    if (input[pos] == '{') { // если элемент - множество.
        size_t start = pos++;
        int balance = 1; //учёт вложенности.
        while (pos < input.size() && balance > 0) {
            if (input[pos] == '{') ++balance;
            else if (input[pos] == '}') --balance;
            ++pos;
        }
        if (balance != 0) return false; // синтаксическая ошибка кол-ва скобок.
        element = input.substr(start, pos - start);
        return true;
    } else if (input[pos] == '<') { // элемент - ориентированное множество.
        size_t start = pos++;
        int balance = 1;
        while (pos < input.size() && balance > 0) {
            if (input[pos] == '<') ++balance;
            else if (input[pos] == '>') --balance;
            ++pos;
        }
        if (balance != 0) return false;
        element = input.substr(start, pos - start);
        return true;
    } else { // элемент - просто имя
        size_t start = pos;
        while (pos < input.size() && is_correct_char(input[pos])) ++pos; // пока имя коректно считывает.
        if (start == pos) return false;
        element = input.substr(start, pos - start);
        return true;
    }
}

//поиск элемента по значению
//на вход - вектор с информацией об элементах elements, строка, которую ищем value, индекс найденного эл index
bool find_element(vector<Element> &elements, const string &value, size_t &index) {
    for (size_t i = 0; i < elements.size(); ++i) {
        if (elements[i].value == value) {
            index = i;
            return true;
        }
    }
    return false;
}

//считывает множество целиком из строки
//на вход - строка input, позиция начала считывания pos и вектор для хранения информации о элементах elements
bool parse_set(const string &input, size_t &pos, vector<Element> &elements) {
    while (pos < input.size() && input[pos] == ' ') ++pos;
    if (input[pos] != '{') return false;
    ++pos;
    while (true) {
        while (pos < input.size() && input[pos] == ' ') ++pos;
        if (input[pos] == '}') {
            ++pos;
            return true;
        }
        string el;
        if (!parse_element(input, pos, el)) return false; // считывание одного элемента

        size_t idx; // счётчик кратности
        if (find_element(elements, el, idx)) {
            elements[idx].count++;
        } else {
            elements.push_back({el, 1});
        }

        while (pos < input.size() && input[pos] == ' ') ++pos;
        if (input[pos] == ',') {
            ++pos;
        } else if (input[pos] == '}') {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

//функция нахождения разности двух множеств
//на вход - два вектора, хранящие данные о элементах множеств считанных из файла
vector<Element> difference(const vector<Element> &a, const vector<Element> &b) {
    vector<Element> result = a;
    for (const auto &el_b : b) {
        for (auto &el_r : result) {
            if (el_r.value == el_b.value) {
                el_r.count -= el_b.count;
                break;
            }
        }
    }

    vector<Element> filtered;
    for (const auto &el : result) {
        if (el.count > 0) filtered.push_back(el);
    }
    return filtered;
}

// вывод множества
//на вход - вектор, хранящий информацию об элементах множества; константная строка, хранящая имя множества
void print_set(const vector<Element> &elements, const string name) {
    cout << name << "={";
    bool first = true;
    for (const auto &el : elements) {
        for (int i = 0; i < el.count; ++i) {
            if (!first) cout << ",";
            cout << el.value;
            first = false;
        }
    }
    cout << "}" << endl;
}

int main() {
    ifstream fin("input.txt");
    if (!fin) {
        cout << "Ошибка открытия файла" << endl;
        return 1;
    }

    string line1, line2;
    getline(fin, line1);
    getline(fin, line2);

    size_t pos1 = 0, pos2 = 0;
    string name1, name2;
    string name3 = "S";
    if (line1.find('=') != string::npos) {
        name1 = line1.substr(0, line1.find('='));
        if (!is_correct_name(name1)) {
            cout << "Некорректное имя множества" << endl;
            return 1;
        }
        pos1 = line1.find('=') + 1;
    }

    if (line2.find('=') != string::npos) {
        name2 = line2.substr(0, line2.find('='));
        if (!is_correct_name(name2)) {
            cout << "Некорректное имя множества" << endl;
            return 1;
        }
        pos2 = line2.find('=') + 1;
    }

    vector<Element> set1, set2;
    if (!parse_set(line1, pos1, set1) || !parse_set(line2, pos2, set2)) {
        cout << "Некорректный формат множества" << endl;
        return 1;
    }
    cout << "Исходные множества:\n";
    print_set(set1, name1);
    print_set(set2, name2);
    vector<Element> result = difference(set1, set2);
    cout << "Разность множеств " << name1 << " и " << name2 <<":\n";
    print_set(result, name3);

    return 0;
}