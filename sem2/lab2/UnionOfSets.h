#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void run_testcase(const string& path, int& num_sets, vector<vector<string>>& sets);
vector<vector<pair<string, int>>> CountMultiplicities(const vector<vector<string>>& sets);
vector<pair<string, int>> FindMaxMultiplicities(const vector<vector<pair<string, int>>>& counts);
void OutputResult(const vector<pair<string, int>>& max_counts);
