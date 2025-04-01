#pragma once
#ifndef HEADER_H 
#define HEADER_H 
  
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
 
// Декларации функций
bool IsBalanced(const string& input);
bool IsValidCharacter(char c);
bool ValidateStructure(const string& input);
int Add(vector<string>& Set, const string& input_str);
int Check_Elements(const vector<string>& set);
void PrintSubset(const vector<string>& subset);
void Generate_Boolean(const vector<string>& set, vector<vector<string>>& boolean, vector<string>& el_of_boolean, int index);
void RemoveOuterBraces(string& line);

#endif
