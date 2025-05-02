#pragma once

#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stack>
#include <fstream>

using namespace std;

bool is_correct(string str);
vector<string> parse(string str);
set<set<string>> combinations(vector<string>& elements, int n, int start = 0, vector<string> current = {});
int numOfSets(set<set<string>> comb);
bool contains(vector<string>& elements, string el);
string ReadFile(char* filename);