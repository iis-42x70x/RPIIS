#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 

using namespace std;

void viewSets(vector<string> sets);
void readFile(vector<string>& sets, ifstream& inputFile);
string normalizeSet(const string& setStr);
vector<string> splitElements(const string& setStr);
void differenceSets(vector<string>& sets, string& initialResult);