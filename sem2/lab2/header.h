#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

const int MAX_LINE_LENGTH = 1024;
const int MAX_SETS = 10;

vector<string> get_elements(const string&);
string standard_view(const string&);
void symmetricDifference(const char*, const char*, char*);
bool isValidSet(const char*);
int readSets(const char*, char[MAX_SETS][MAX_LINE_LENGTH], int&);
void writeSets(const char*, char[MAX_SETS][MAX_LINE_LENGTH], int);
void menu(const char*);


#endif