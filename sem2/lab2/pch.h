#pragma once
#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

enum ElementType { STRING, SET, ORSET };

struct SetElement {
    ElementType type;
    string strvalue;
    vector<SetElement> vecvalue;
};

string NotSpace(string& str);
bool CheckStr(const string& str);
SetElement ParsingElements(const string& str, int& pos);
SetElement ParsingSets(const string& str, int& pos);
void Printf(const SetElement& el);
vector<vector<SetElement>> Permute(const vector<SetElement>& elems);
void GenerateCombinations(const vector<vector<SetElement>>& childOpts, vector<vector<SetElement>>& combos, vector<SetElement>& cur, int i);
void BuildCombinations(const vector<vector<SetElement>>& options, vector<vector<SetElement>>& base, vector<SetElement>& cur, int i);
bool CompareElements(const SetElement& a, const SetElement& b);
string ReadFromFile();
