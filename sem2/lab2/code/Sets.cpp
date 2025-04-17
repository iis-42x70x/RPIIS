//
// pch.cpp
//

#include "pch.h"
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
        name.erase(remove_if(name.begin(), name.end(), ::isspace), name.end());
        newSet = Set(name, {});

        // Извлекаем содержимое множества
        string content = line.substr(equalPos + 1);
        content = removeSpaces(content);

        size_t openBrace = content.find('{');
        size_t closeBrace = content.find('}');

        if (openBrace != string::npos && closeBrace != string::npos) {
            string elementsStr = content.substr(openBrace + 1, closeBrace - openBrace - 1);

            vector<string> elements;
            bool inTuple = false;
            int tupleDepth = 0;  // Для отслеживания вложенности кортежей
            string currentElement;

            for (char c : elementsStr) {
                if (c == '<') {
                    inTuple = true;
                    tupleDepth++;
                    currentElement += c;
                }
                else if (c == '>') {
                    tupleDepth--;
                    currentElement += c;
                    if (tupleDepth == 0) {
                        inTuple = false;
                        elements.push_back(currentElement);
                        currentElement.clear();
                    }
                }
                else if (c == ',' && !inTuple) {
                    if (!currentElement.empty()) {
                        elements.push_back(currentElement);
                        currentElement.clear();
                    }
                }
                else {
                    currentElement += c;
                }
            }

            // Добавляем последний элемент, если он есть
            if (!currentElement.empty()) {
                elements.push_back(currentElement);
            }

            // Очищаем пробелы в начале и конце каждого элемента
            for (const auto& element : elements) {
                string trimmed = element;
                trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r\f\v"));
                trimmed.erase(trimmed.find_last_not_of(" \t\n\r\f\v") + 1);

                if (!trimmed.empty()) {
                    newSet.addElement(trimmed);
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
