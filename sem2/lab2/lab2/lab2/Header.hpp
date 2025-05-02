#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stack>

using namespace std;

bool is_correct(string str);
vector<string> parse(string str);
set<set<string>> combinations(vector<string>& elements, int n, int start = 0, vector<string> current = {});