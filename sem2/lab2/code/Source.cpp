#include "Header.h"

// Проверка на сбалансированность всех типов скобок
bool IsBalanced(const string& input) {
    vector<char> stack;

    for (char c : input) {
        if (c == '{' || c == '<' || c == '(') {
            stack.push_back(c);
        }
        else if (c == '}' || c == '>' || c == ')') {
            if (stack.empty()) return false;

            char openBracket = stack.back();
            stack.pop_back();

            if ((c == '}' && openBracket != '{') ||
                (c == '>' && openBracket != '<') ||
                (c == ')' && openBracket != '(')) {
                return false;
            }
        }
    }
    return stack.empty();
}

// Проверка на допустимые символы
bool IsValidCharacter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') ||
        c == '{' || c == '}' || c == '<' || c == '>' ||
        c == '(' || c == ')' || c == ',' || c == ' ';
}

// Проверка структуры множества
bool ValidateStructure(const string& input) {
    for (char c : input) {
        if (!IsValidCharacter(c)) {
            cout << "Ошибка: обнаружен недопустимый символ \"" << c << "\"." << endl;
            return false;
        }
    }
    return IsBalanced(input);
}

// Добавление элементов множества
int Add(vector<string>& Set, const string& input_str) {
    string currentElement;
    int braceCount = 0, angleCount = 0, roundCount = 0;

    for (char s : input_str) {
        if (s == '{') braceCount++;
        if (s == '}') braceCount--;
        if (s == '<') angleCount++;
        if (s == '>') angleCount--;
        if (s == '(') roundCount++;
        if (s == ')') roundCount--;

        if (s == ',' && braceCount == 0 && angleCount == 0 && roundCount == 0) {
            if (!currentElement.empty()) {
                Set.push_back(currentElement);
                currentElement.clear();
            }
        }
        else {
            currentElement.push_back(s);
        }
    }

    if (!currentElement.empty()) {
        Set.push_back(currentElement);
    }

    return (braceCount == 0 && angleCount == 0 && roundCount == 0) ? 0 : 1;
}

// Проверка на уникальность элементов
int Check_Elements(const vector<string>& set) {
    for (size_t i = 0; i < set.size(); i++) {
        for (size_t j = i + 1; j < set.size(); j++) {
            if (set[i] == set[j]) {
                cout << "Ошибка: множество содержит повторяющийся элемент \"" << set[i] << "\"." << endl;
                return 1;
            }
        }
    }
    return 0;
}

// Печать подмножества
void PrintSubset(const vector<string>& subset) {
    cout << "{ ";
    for (size_t j = 0; j < subset.size(); j++) {
        cout << subset[j];
        if (j < subset.size() - 1) cout << ", ";
    }
    cout << " }";
}

// Генерация булеана
void Generate_Boolean(const vector<string>& set, vector<vector<string>>& boolean, vector<string>& el_of_boolean, int index) {
    boolean.push_back(el_of_boolean);
    for (size_t i = index; i < set.size(); i++) {
        el_of_boolean.push_back(set[i]);
        Generate_Boolean(set, boolean, el_of_boolean, i + 1);
        el_of_boolean.pop_back();
    }
}

// Удаление внешних фигурных или угловых скобок
void RemoveOuterBraces(string& line) {
    if ((line.front() == '{' && line.back() == '}') || (line.front() == '<' && line.back() == '>')) {
        line = line.substr(1, line.size() - 2);
    }
}
