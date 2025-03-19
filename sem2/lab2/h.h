#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>
#include <sstream>
#include <iostream>
#include <stack>

struct SubSet {
	std::vector<std::string> all_elements;
	bool notempty = 0;
};

struct Set {
	std::string name;
	std::vector<SubSet> all_subsets;
};

bool bracketsBalance(const std::string& line);
void processSubsets(const std::string& line, size_t& i, Set& SET);
std::vector<Set>read(const std::string& filename);

Set intersectionCalc(Set temp_result, Set set1, Set set2);
std::vector<std::string> intersection(const std::string& filename);