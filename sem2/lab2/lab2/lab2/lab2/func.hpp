#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

void wall();
string trim(const string& s);
vector<string> split_elements(const string& src);
string normalize_element(const string& s);
void collect_elements(const string& src, map<string, int>& out);
map<string, int> intersect_sets(const vector<string>& inputs);