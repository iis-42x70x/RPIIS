#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

vector<string> stringToVectorOfSetElements(const string& str);
void permute(vector<string>& setElements, int l, int r, vector<vector<string>>& result);
vector<vector<string>> generatePermutations(const vector<string>& setElements);
void findAllCombinations(const string& filename);