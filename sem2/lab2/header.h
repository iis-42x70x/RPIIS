#ifndef SETSOPERATIONS_H
#define SETSOPERATIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;


void displaySets(vector<string> sets);
void readFile(vector<string>& sets, ifstream& inputFile);
vector<string> extractElements(const string& setString);
void unionSets(vector<string>& sets, string& initialResult);

#endif
