#include "pch.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stack>
#include <cctype>

using namespace std;

Set::Set(const string& name, const set<string>& elements) {
    this->name = name;
    this->elements = elements;
}

string Set::getName() const {
    return name;
}

set<string> Set::getElements() const {
    return elements;
}

void Set::addElement(const string& element) {
    elements.insert(element);
}

bool Set::contains(const string& element) const {
    return elements.find(element) != elements.end();
}

size_t Set::size() const {
    return elements.size();
}

Set Set::symmetricDifference(const vector<Set>& sets) {
    if (sets.empty()) return Set("result", {});

    // Собираем все уникальные элементы
    set<string> allElements;
    for (const auto& s : sets) {
        for (const auto& elem : s.getElements()) {
            allElements.insert(elem);
        }
    }

    // Вычисляем симметрическую разность
    set<string> result;
    for (const auto& elem : allElements) {
        int count = 0;
        for (const auto& s : sets) {
            if (s.contains(elem)) {
                count++;
            }
        }
        if (count % 2 != 0) {
            result.insert(elem);
        }
    }

    return Set("SymmetricDifference", result);
}

// Улучшенная функция normalizeSpaces - сохраняет оригинальное форматирование
string normalizeSpaces(const string& input) {
    string result;
    int depth = 0;
    bool justAddedComma = false;

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];

        if (c == '<' || c == '{') {
            depth++;
            result += c;
            justAddedComma = false;
        }
        else if (c == '>' || c == '}') {
            depth--;
            result += c;
            justAddedComma = false;
        }
        else if (c == ',') {
            result += c;
            result += ' ';
            justAddedComma = true;
        }
        else if (isspace(c)) {
            // Пробелы пропускаем, если они:
            // 1. перед следующим элементом после запятой
            // 2. вне элемента, не между значимыми символами
            continue;
        }
        else {
            if (justAddedComma && !result.empty() && result.back() == ' ') {
                // уже добавили нужный пробел
            }
            result += c;
            justAddedComma = false;
        }
    }

    // Удаляем лишний пробел в конце, если есть
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

bool isValidSetFormat(const std::string& str) {
    std::stack<char> brackets;
    bool lastWasComma = false;
    bool lastWasOpening = false;
    bool expectElement = false;

    for (size_t i = 0; i < str.size(); ++i) {
        char c = str[i];

        // Обработка открывающих скобок
        if (c == '{' || c == '<') {
            brackets.push(c);
            lastWasComma = false;
            lastWasOpening = true;
        }
        // Обработка закрывающих скобок
        else if (c == '}' || c == '>') {
            if (brackets.empty()) return false;
            char open = brackets.top();
            if ((c == '}' && open != '{') || (c == '>' && open != '<')) {
                return false;
            }
            brackets.pop();

            if (lastWasComma) return false; // {a,} или <a,> — ошибка
            lastWasComma = false;
            lastWasOpening = false;
        }
        // Обработка запятых
        else if (c == ',') {
            if (lastWasComma || lastWasOpening) return false; // ,, или {, — ошибка
            lastWasComma = true;
            lastWasOpening = false;
        }
        // Символы — допустимы
        else {
            lastWasComma = false;
            lastWasOpening = false;
        }
    }

    // Проверка на незакрытые скобки
    return brackets.empty() && !lastWasComma;
}




// Улучшенная функция parseElements - сохраняет оригинальный формат
vector<string> parseElements(const string& elementsStr) {
    string normalized = normalizeSpaces(elementsStr);

    if (!isValidSetFormat(normalized)) {
        cout << "Error! Incorrect input set!" << endl;
        return {}; // пустой список
    }

    vector<string> elements;
    string current;
    int angleDepth = 0;  // Глубина вложенности по < >
    int braceDepth = 0;  // Глубина вложенности по { }

    for (size_t i = 0; i < elementsStr.size(); ++i) {
        char c = elementsStr[i];

        if (c == '<') {
            angleDepth++;
            current += c;
        }
        else if (c == '>') {
            angleDepth--;
            current += c;
        }
        else if (c == '{') {
            braceDepth++;
            current += c;
        }
        else if (c == '}') {
            braceDepth--;
            current += c;
        }
        else if (c == ',' && angleDepth == 0 && braceDepth == 0) {
            // завершение элемента вне вложенности
            size_t first = current.find_first_not_of(" \t");
            if (first != string::npos) {
                size_t last = current.find_last_not_of(" \t");
                elements.push_back(current.substr(first, last - first + 1));
            }
            current.clear();
        }
        else {
            current += c;
        }
    }

    // Добавляем последний элемент (если есть)
    if (!current.empty()) {
        size_t first = current.find_first_not_of(" \t");
        if (first != string::npos) {
            size_t last = current.find_last_not_of(" \t");
            elements.push_back(current.substr(first, last - first + 1));
        }
    }

    return elements;
}


Set parseSet(const string& line) {
    Set newSet;
    size_t equalPos = line.find('=');

    if (equalPos != string::npos) {
        // Извлекаем имя множества
        string name = line.substr(0, equalPos);
        name.erase(remove_if(name.begin(), name.end(), ::isspace), name.end());
        newSet = Set(name, {});

        // Нормализуем содержимое
        string content = normalizeSpaces(line.substr(equalPos + 1));

        size_t openBrace = content.find('{');
        size_t closeBrace = content.rfind('}'); // Используем rfind для поиска последней }

        if (openBrace != string::npos && closeBrace != string::npos) {
            string elementsStr = content.substr(openBrace + 1, closeBrace - openBrace - 1);
            vector<string> elements = parseElements(elementsStr);

            for (string& elem : elements) {
                // Дополнительная нормализация
                elem = normalizeSpaces(elem);
                size_t first = elem.find_first_not_of(" \t");
                if (first != string::npos) {
                    size_t last = elem.find_last_not_of(" \t");
                    elem = elem.substr(first, last - first + 1);
                    newSet.addElement(elem);
                }
            }
        }
    }

    return newSet;
}

vector<Set> readSetsFromFile(const string& filename) {
    vector<Set> sets;
    ifstream file(filename);

    if (!file.is_open()) {
        return sets;
    }

    string line;
    while (getline(file, line)) {
        // Удаляем пробелы в начале и конце строки
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);

        if (!line.empty()) {
            Set newSet = parseSet(line);
            if (!newSet.getName().empty()) {
                sets.push_back(newSet);
            }
        }
    }

    file.close();
    return sets;
}
