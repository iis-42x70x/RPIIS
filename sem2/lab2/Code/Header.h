#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct SetElement {
    bool is_subset;
    char value;
    vector<SetElement> subset;
};

string removeSpaces(const string& s);
SetElement parseSet(istringstream& iss);
SetElement inputSet();
void collectElements(const SetElement& set, vector<char>& elements);
int countElements(const SetElement& set);
void generateCombinations(const vector<char>& elements, int k,
    vector<char>& current, int start,
    vector<vector<char>>& result);
void printSet(const SetElement& set);
int inputDimension(int max_dimension);