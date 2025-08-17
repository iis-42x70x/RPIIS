#ifndef SETS_H
#define SETS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_set>
using namespace std;

bool checkBrackets(const string& input);

vector<string> parseSet(const string& input);

string unionSets(vector<string>& set1, vector<string>& set2);

vector<string> readSets(const string& path);

void openFile(string& path);

void unionAllSets(const string& inputPath, const string& outputPath);

#endif 
