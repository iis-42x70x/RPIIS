#include "Lab2_set_2.0_tests.h"
#include <algorithm>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

SetOperations::Element::Element()
    : type(ElementType::NUMBER), number(0), letter('\0'), count(1) {}

bool SetOperations::Element::operator<(const Element& other) const {
    if (type != other.type) return type < other.type;
    if (type == ElementType::NUMBER) return number < other.number;
    if (type == ElementType::LETTER || type == ElementType::MULTIPLE_LETTER) {
        if (letter != other.letter) return letter < other.letter;
        return count < other.count;
    }
    return subset < other.subset;
}

bool SetOperations::Element::operator==(const Element& other) const {
    if (type != other.type) return false;
    if (type == ElementType::NUMBER) return number == other.number;
    if (type == ElementType::LETTER || type == ElementType::MULTIPLE_LETTER) {
        return letter == other.letter && count == other.count;
    }
    return subset == other.subset;
}

vector<vector<SetOperations::Element>> SetOperations::readSetsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error";
    }
    vector<vector<SetOperations::Element>> sets;
    string line;

    while (getline(file, line)) {
        size_t pos = 0;
        sets.push_back(parseSet(line, pos));
    }

    return sets;
}

void SetOperations::writeIntersectionToFile(const vector<Element>& intersection, const string& filename) {
    ofstream file(filename);
    file << "{";

    bool first = true;
    for (const auto& elem : intersection) {
        if (!first) file << ", ";
        first = false;

        switch (elem.type) {
        case ElementType::NUMBER:
            file << elem.number;
            break;
        case ElementType::LETTER:
            file << elem.letter;
            break;
        case ElementType::MULTIPLE_LETTER:
            file << elem.letter << elem.count;
            break;
        case ElementType::SUBSET:
            file << "{";
            for (size_t i = 0; i < elem.subset.size(); ++i) {
                if (i > 0) file << ", ";
                if (elem.subset[i].type == ElementType::NUMBER) {
                    file << elem.subset[i].number;
                }
                else {
                    file << elem.subset[i].letter;
                }
            }
            file << "}";
            break;
        case ElementType::TUPLE:
            file << "<";
            for (size_t i = 0; i < elem.subset.size(); ++i) {
                if (i > 0) file << ", ";
                if (elem.subset[i].type == ElementType::NUMBER) {
                    file << elem.subset[i].number;
                }
                else {
                    file << elem.subset[i].letter;
                }
            }
            file << ">";
            break;
        }
    }

    file << "}";
}

vector<SetOperations::Element> SetOperations::findIntersection(const vector<vector<Element>>& sets) {
    if (sets.empty()) return {};

    set<Element> result(sets[0].begin(), sets[0].end());

    for (size_t i = 1; i < sets.size(); ++i) {
        set<Element> currentSet(sets[i].begin(), sets[i].end());
        set<Element> temp;

        set_intersection(
            result.begin(), result.end(),
            currentSet.begin(), currentSet.end(),
            inserter(temp, temp.begin())
        );

        result = move(temp);
        if (result.empty()) break;
    }

    return vector<Element>(result.begin(), result.end());
}

vector<SetOperations::Element> SetOperations::parseSet(const string& str, size_t& pos) {
    vector<Element> elements;
    skipWhitespace(str, pos);

    if (pos >= str.size() || str[pos] != '{') {
        throw runtime_error("Invalid set format - missing '{'");
    }
    pos++;

    while (pos < str.size() && str[pos] != '}') {
        skipWhitespace(str, pos);
        if (str[pos] == '}') break;

        elements.push_back(parseElement(str, pos));

        skipWhitespace(str, pos);
        if (pos < str.size() && str[pos] == ',') {
            pos++;
        }
    }

    if (pos >= str.size() || str[pos] != '}') {
        throw runtime_error("Invalid set format - missing '}'");
    }
    pos++;

    return elements;
}

SetOperations::Element SetOperations::parseElement(const string& str, size_t& pos) {
    skipWhitespace(str, pos);
    Element elem;

    if (pos >= str.size()) {
        throw runtime_error("Unexpected end of input");
    }

    if (str[pos] == '{') {
        elem.type = ElementType::SUBSET;
        elem.subset = parseSet(str, pos);
    }
    else if (str[pos] == '<') {
        elem.type = ElementType::TUPLE;
        elem.subset = parseTuple(str, pos);
    }
    else if (isNumber(str[pos])) {
        elem.type = ElementType::NUMBER;
        int num = 0;
        while (pos < str.size() && isNumber(str[pos])) {
            num = num * 10 + (str[pos] - '0');
            pos++;
        }
        elem.number = num;

        // Проверка на букву после числа (4d)
        if (pos < str.size() && isLetter(str[pos])) {
            elem.type = ElementType::MULTIPLE_LETTER;
            elem.letter = str[pos];
            elem.count = num;
            pos++;
        }
    }
    else if (isLetter(str[pos])) {
        elem.type = ElementType::LETTER;
        elem.letter = str[pos];
        pos++;

        // Проверка на числа после буквы (S14)
        if (pos < str.size() && isNumber(str[pos])) {
            elem.type = ElementType::MULTIPLE_LETTER;
            int count = 0;
            while (pos < str.size() && isNumber(str[pos])) {
                count = count * 10 + (str[pos] - '0');
                pos++;
            }
            elem.count = count;
        }
    }
    else {
        throw runtime_error("Unexpected character in set");
    }

    return elem;
}

vector<SetOperations::Element> SetOperations::parseTuple(const string& str, size_t& pos) {
    vector<Element> elements;
    skipWhitespace(str, pos);

    if (pos >= str.size() || str[pos] != '<') {
        throw runtime_error("Invalid tuple format - missing '<'");
    }
    pos++;

    while (pos < str.size() && str[pos] != '>') {
        skipWhitespace(str, pos);
        if (str[pos] == '>') break;

        elements.push_back(parseElement(str, pos));

        skipWhitespace(str, pos);
        if (pos < str.size() && str[pos] == ',') {
            pos++;
        }
    }

    if (pos >= str.size() || str[pos] != '>') {
        throw runtime_error("Invalid tuple format - missing '>'");
    }
    pos++;

    return elements;
}

bool SetOperations::isNumber(char c) {
    return c >= '0' && c <= '9';
}

bool SetOperations::isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void SetOperations::skipWhitespace(const string& str, size_t& pos) {
    while (pos < str.size() && isspace(str[pos])) {
        pos++;
    }
}