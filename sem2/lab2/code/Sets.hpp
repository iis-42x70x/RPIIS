#pragma once

#include "gtest/gtest.h"
#include <vector>
#include <set>
#include <string>
using namespace std;

class Set {
private:
    string name;
    set<string> elements;

public:
    // Конструкторы
    Set() = default;
    Set(const string& name, const set<string>& elements);

    // Методы доступа
    string getName() const;
    set<string> getElements() const;

    // Методы для работы с множеством
    void addElement(const string& element);
    bool contains(const string& element) const;
    size_t size() const;

    // Операции с множествами
    static Set symmetricDifference(const vector<Set>& sets);
};

// Вспомогательные функции
vector<Set> readSetsFromFile(const string& filename);
Set parseSet(const string& line);
string removeSpaces(const string& input);
