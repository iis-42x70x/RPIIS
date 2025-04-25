#pragma once
#ifndef SETPARSER_H
#define SETPARSER_H
#include <string>
#include <vector>

#include <set>


using namespace std;

vector<string> string_to_vector_OfSetElements(const string& str);
void permute(vector<string>& setElements, int l, int r, vector<vector<string>>& result);
vector<vector<string>> generateUniquePermutations(const vector<string>& setElements);
void findAllCombinations(const string& filename);
#endif