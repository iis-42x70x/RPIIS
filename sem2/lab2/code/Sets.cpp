#include "Sets.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
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

string removeSpaces(const string& input) {
    string result;
    bool keepSpace = false;

    for (char c : input) {
        if (c == ',') {
            keepSpace = true;
            result += c;
        }
        else if (isspace(c)) {
            if (keepSpace) {
                result += c;
                keepSpace = false;
            }
        }
        else {
            result += c;
            keepSpace = false;
        }
    }

    return result;
}

Set parseSet(const string& line) {
    Set newSet;
    size_t equalPos = line.find('=');

    if (equalPos != string::npos) {
        // Извлекаем имя множества
        string name = line.substr(0, equalPos);
        // Удаляем пробелы в имени
        name.erase(remove_if(name.begin(), name.end(), ::isspace), name.end());

        // Устанавливаем имя через конструктор
        newSet = Set(name, {});

        // Извлекаем содержимое множества
        string content = line.substr(equalPos + 1);
        content = removeSpaces(content);

        // Удаляем фигурные скобки
        size_t openBrace = content.find('{');
        size_t closeBrace = content.find('}');

        if (openBrace != string::npos && closeBrace != string::npos) {
            string elementsStr = content.substr(openBrace + 1, closeBrace - openBrace - 1);

            // Разделяем элементы по запятым
            stringstream ss(elementsStr);
            string element;

            while (getline(ss, element, ',')) {
                // Удаляем лишние пробелы вокруг элемента
                element.erase(0, element.find_first_not_of(" \t\n\r\f\v"));
                element.erase(element.find_last_not_of(" \t\n\r\f\v") + 1);

                if (!element.empty()) {
                    newSet.addElement(element);
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
