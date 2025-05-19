#pragma once
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
struct Set {
	//////////////////-=-METHODS-=-//////////////////
	Set(string);
	vector<pair<int, char>> SetDifference(int);
	void PrintSet(int);
	void PrintDifference();
	//////////////////-=-VARIABLES-=-///////////////////
	vector<vector<pair<int, char>>> SETS;
	vector<pair<int, char>> result;
};
