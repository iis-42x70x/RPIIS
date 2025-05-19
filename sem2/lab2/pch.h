#pragma once
#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

enum ElementType { STRING, SET};

struct SetElement {
    ElementType type;
    string strvalue;
    vector<SetElement> vecvalue;
};

string NotSpace(const char* input);
bool CheckStr(const string& str);
void PrintSetElement(const SetElement& el);
void PrintSet(const vector<SetElement>& set);
void GenerateCombinations(const vector<SetElement>& elems, int n, int start, vector<SetElement>& current, vector<vector<SetElement>>& result);
vector<SetElement> ParseCustomFormat(const string& input);
vector<SetElement> ReadFromFile();