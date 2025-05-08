#pragma once
#ifndef HEADER_H 
#define HEADER_H 

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


bool Parentheses(const string& input);
bool Check_symbols(char c);
bool check(const string& input);
int Add(vector<string>& Set, const string& input_str);
int Duplicate(const vector<string>& set);
void Generate_Boolean(const vector<string>& set, vector<vector<string>>& boolean, vector<string>& el_of_boolean, int index);
void RemoveOuterBraces(string& line);
void ProcessSetFromString(const string& input, vector<vector<string>>& result);

#endif
