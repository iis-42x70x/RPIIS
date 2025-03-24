#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void displaySets(vector<string> sets);
void readFile(vector<string>& sets, ifstream& inputFile);
vector<string> extractAndSortElements(const string& setString);
void differenceSets(vector<string>& sets, string& initialResult);
