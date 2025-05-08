#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Set.hpp"

using namespace std;

Set::Set(const vector<Element> &elements) : elements(elements) {}

const vector<Element>& Set::get_elements() const {
    return elements;
}

bool Set::is_correct_char(char c) { //проверяет корректность символов.
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9') || (c == '_');
}

bool Set::is_correct_name(const string &s) { //посимвольно проверяет имя.
    if (s.empty()) return false;
    for (char c : s) {
        if (!is_correct_char(c)) return false;
    }
    return true;
}

//функция открытия файла и прочтения из него двух строк
//на вход - название файла; первая, вторая строки для хранения
bool Set::read_input(const string &filename, string &line1, string &line2) {
    ifstream fin(filename);
    if (!fin) return false;
    getline(fin, line1);
    getline(fin, line2);
    return true;
}

//считывает по одному элементу множества.
//на вход - строка input, начало считывания - позиция pos, сохранение в element.
bool Set::parse_element(const string &input, size_t &pos, string &element) {
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
bool Set::find_element(vector<Element> &elements_param, const string &value, size_t &index) {
    for (size_t i = 0; i < elements_param.size(); ++i) {
        if (elements_param[i].value == value) {
            index = i;
            return true;
        }
    }
    return false;
}

//считывает множество целиком из строки
//на вход - строка input, позиция начала считывания pos и вектор для хранения информации о элементах elements
bool Set::parse_set(const string &input, size_t &pos, vector<Element> &elements_param) {
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
        if (find_element(elements_param, el, idx)) {
            elements_param[idx].count++;
        } else {
            elements_param.push_back({el, 1});
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

// обёрточная функция разбора строки множества
//на вход - строка; имя множества; вектор, для хранения информации об элементах множества
bool Set::process_set_line(const string &line, string &name, vector<Element> &set) {
    size_t pos = 0;
    if (line.find('=') == string::npos) return false;
    name = line.substr(0, line.find('='));
    Set set_instance;
    if (!set_instance.is_correct_name(name)) return false;
    pos = line.find('=') + 1;
    return set_instance.parse_set(line, pos, set);
}

//функция нахождения разности двух множеств
//на вход - два вектора, хранящие данные о элементах множеств считанных из файла
Set Set::difference(const Set& other) const {
    vector<Element> result = elements;
    for (const auto &el_b : other.elements) {
        for (auto &el_r : result) {
            if (el_r.value == el_b.value) {
                el_r.count -= el_b.count;
                break;
            }
        }
    }

    vector<Element> filtered;
    for (const auto &el : result) {
        if (el.count > 0)
            filtered.push_back(el);
    }

    return Set(filtered);
}
// вывод множесва
// на вход - вектор, хранящий информацию об элементах множества; константная строка, хранящая имя множества
void Set::print_set(const vector<Element> &elements_param, const string &name) {
    cout << name << "={";
    bool first = true;
    for (const auto &el : elements_param) {
        for (int i = 0; i < el.count; ++i) {
            if (!first) cout << ",";
            cout << el.value;
            first = false;
        }
    }
    cout << "}" << endl;
}

// вывод результатов
//на вход - векторы, хранящий информацию об элементах множества; константные строки, хранящие имена множеств
void Set::output_results(const Set &set1, const Set &set2, const Set &result,
                         const string &name1, const string &name2, const string &result_name) {
    cout << "Исходные множества:\n";
    Set do_smth;
    do_smth.print_set(set1.get_elements(), name1);
    do_smth.print_set(set2.get_elements(), name2);
    cout << "Разность множеств " << name1 << " и " << name2 << ":\n";
    do_smth.print_set(result.get_elements(), result_name);
}
