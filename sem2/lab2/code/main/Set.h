#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <variant>
#include <string>
#include <unordered_set>
#include <unordered_map> 
#include <algorithm>
#include <sstream>
#include <regex>
#include <random>
#include<stack>

using namespace std;

using SetElement = std::variant<
    int,
    std::string,
    std::vector<int>,
    std::unordered_set<std::string>
>;

struct CustomSet {
    vector<SetElement> elements;

    void addElement(const SetElement& element);
    bool contains(const SetElement& element) const;
    size_t size() const;
    CustomSet difference(const CustomSet& other) const;
    static string elementToString(const SetElement& element);
    static CustomSet parseFromString(const string& str);
    string toString() const;
};

bool isValid(const string& str);

void solution(const std::string& filepath, bool isConst);
