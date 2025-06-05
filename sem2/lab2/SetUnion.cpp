#include "SetUnion.hpp"
#include <fstream>
#include <sstream>
#include <stack>

using namespace std;

// ========== ВАЛИДАЦИЯ ==========

bool SetUnion::is_valid_name(const string& name) const {
    if (name.empty()) return false;
    if (!isalpha(name[0]) && name[0] != '_') return false;

    return all_of(name.begin(), name.end(), [](char c) {
        return isalnum(c) || c == '_';
    });
}

bool SetUnion::is_valid_tuple(const string& tuple) const {
    if (tuple.size() < 3 || tuple.front() != '<' || tuple.back() != '>') {
        return false;
    }

    string content = tuple.substr(1, tuple.size() - 2);
    size_t pos = 0;
    int element_count = 0;

    while (pos < content.size()) {
        string element = parse_element(content, pos);
        if (element.empty()) break;

        if (!is_valid_element(element)) return false;
        element_count++;

        if (pos < content.size() && content[pos] == ',') pos++;
    }

    return element_count >= 1;
}

bool SetUnion::is_valid_element(const string& element) const {
    if (element.empty()) return false;

    // Числа (только цифры)
    if (all_of(element.begin(), element.end(), ::isdigit)) {
        return true;
    }

    // Кортежи
    if (element.front() == '<' && element.back() == '>') {
        return is_valid_tuple(element);
    }

    // Вложенные множества
    if (element.front() == '{' && element.back() == '}') {
        if (element == "{}") return true;

        try {
            string fake_name = "temp=" + element;
            parse_set(fake_name); // Рекурсивная проверка
            return true;
        } catch (...) {
            return false;
        }
    }

    // Имена переменных
    return is_valid_name(element);
}

// ========== ПАРСИНГ ==========

string SetUnion::parse_element(const string& str, size_t& pos) const {
    while (pos < str.size() && isspace(str[pos])) pos++;
    if (pos >= str.size()) return "";

    size_t start = pos;
    char first_char = str[pos];

    if (first_char == '{' || first_char == '<') {
        char closing_char = (first_char == '{') ? '}' : '>';
        int balance = 1;
        pos++;

        while (pos < str.size() && balance > 0) {
            if (str[pos] == first_char) balance++;
            else if (str[pos] == closing_char) balance--;
            pos++;
        }

        if (balance != 0) {
            throw runtime_error("Unbalanced brackets");
        }
    } else {
        while (pos < str.size() && str[pos] != ',' &&
               str[pos] != '{' && str[pos] != '<') {
            pos++;
        }
    }

    string element = str.substr(start, pos - start);
    while (pos < str.size() && isspace(str[pos])) pos++;

    return element;
}

set<string> SetUnion::parse_set(const string& str) const {
    set<string> result;
    size_t eq_pos = str.find('=');
    if (eq_pos == string::npos || str.size() < eq_pos + 2) {
        throw runtime_error("Invalid set format: missing '='");
    }

    string content = str.substr(eq_pos + 1);
    content.erase(remove_if(content.begin(), content.end(), ::isspace), content.end());

    if (content.empty() || content.front() != '{' || content.back() != '}') {
        throw runtime_error("Set must be enclosed in curly braces");
    }

    if (content == "{}") return result;

    string inner = content.substr(1, content.size() - 2);
    size_t pos = 0;

    while (pos < inner.size()) {
        string element = parse_element(inner, pos);
        if (!element.empty()) {
            if (!is_valid_element(element)) {
                throw runtime_error("Invalid element: " + element);
            }
            result.insert(element);
        }
        if (pos < inner.size() && inner[pos] == ',') pos++;
    }

    return result;
}

// ========== ОСНОВНЫЕ МЕТОДЫ ==========

void SetUnion::performUnion(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    string line;
    while (getline(file, line)) {
        line.erase(remove_if(line.
        begin(), line.end(), ::isspace), line.end());
        if (line.empty()) continue;

        try {
            sets.push_back(parse_set(line));
        } catch (const exception& e) {
            throw runtime_error("Error parsing line: " + line + " - " + e.what());
        }
    }

    compute_union();
}

void SetUnion::compute_union() {
    union_set.clear(); // Очищаем перед вычислением

    for (const auto& s : sets) {
        // Добавляем элементы как строки (сохраняя вложенные структуры)
        for (const auto& elem : s) {
            if (!elem.empty()) {
                union_set.insert(elem);
            }
        }
    }
}

set<string> SetUnion::getUnionResult() const {
    return union_set;
}