#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void open_and_sets(const string& path, vector<vector<string>>& sets);
vector<vector<pair<string, int>>> set_element_count(const vector<vector<string>>& sets);
vector<pair<string, int>> final_set_count(const vector<vector<pair<string, int>>>& counts);
void output(const vector<pair<string, int>>& max_counts);