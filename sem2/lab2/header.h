#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

const int MAX_LINE_LENGTH = 200;
const int MAX_SETS = 10;

vector<string> parseElements(const string&);
string normalizeElement(const string&);
void Difference(const char*, const char*, char*);
bool isValidSet(const char*);
int readSets(const char*, char[MAX_SETS][MAX_LINE_LENGTH], int&);
void writeSets(const char*, char[MAX_SETS][MAX_LINE_LENGTH], int);
void menu(const char*);


#endif