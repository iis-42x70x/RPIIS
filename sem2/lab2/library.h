#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <stack>

using namespace std;

string readSets(const char* filename);
int checkString(string sets);
vector<string> parseString(int num, string str);
vector<string> addSets(string str);
string sortSet(string& elem);
vector<string> cross(vector<string> set1, vector<string> set2);

#endif
