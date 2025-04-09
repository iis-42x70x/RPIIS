#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool check(const string& input);
bool checkSet(const string& input, int& index, vector<char>& uniqueChars, vector<string>& uniqueSubsets);
bool checkTuple(const string& input, int& index, vector<char>& uniqueChars);
void parse(const string& input, vector<string>& output);
string parseElement(const string& input, int& index);
bool isElementFound(const string& elemA, const vector<string>& B);
bool isSubset(const vector<string>& A, const vector<string>& B, const string& a, const string& b);
bool isElement(const string& A, const string& B);

#endif