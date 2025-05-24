#pragma once
#ifndef SETPARSER_H
#define SETPARSER_H

#include <string>
#include <vector>

using namespace std;

vector<string> string_to_vector(const string& str);
vector<vector<string>> parseMultipleSets(const string& filename);
vector<vector<string>> cartesianProduct(const vector<vector<string>>& sets);
void calculateCartesianProduct(const string& filename);

#endif
