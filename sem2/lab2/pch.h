#pragma once
#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
bool CheckStr(const string& str);
string NotSpace(string& str);
vector<string> Fragmentation(string& str);
void CreatePermutations(vector<string>& elements);
bool Permutation(vector<string>& elements);
