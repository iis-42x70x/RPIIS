#pragma once

#include <variant>
#include <vector>
#include <string>
#include <memory>
#include <set>
#include <fstream>
#include <sstream>
#include <stack>
#include <iostream>


using namespace std;

// Предварительное объявление для рекурсивных структур
struct Set;
struct Tuple;

// Элемент множества может быть: числом, строкой, множеством или кортежем
using SetElement = std::variant<
    int,
    string,
    shared_ptr<Set>,
    shared_ptr<Tuple>
>;

// Кортеж (упорядоченные элементы)
struct Tuple {
    std::vector<SetElement> elements;
};

// Множество
struct Set {
    std::set<SetElement> elements;  // Хранит элементы
};

void printElement(const SetElement& elem);
void validateInput(const std::string& str);
void generateProduct(const vector<Set>& sets, int index, Tuple current, Set& result);

Set DecartProduct(const vector<Set>& sets);
Set parseSet(const string& str);

vector<Set> ParseFile(const string& path);

string readFile(const string& path);

pair<string, string> parseNextToken(const string& str);

SetElement parseElement(const string& token);

Tuple parseTuple(const string& str);