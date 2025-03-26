#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool check(string input);

bool checkSet(string input, int& index);

bool checkTuple(string input, int& index);

void createFile(string filename);

string returnset(string input, int& pointer);

string returntuple(string input, int& pointer);

void parse(string input, vector<string>& output);

bool isunderset();

bool iselement();