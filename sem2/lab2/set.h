#pragma once

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <Windows.h>

using namespace std;



multiset<string> intersection(const string& file_path);
string trim(const string& str);
string sets(string s);
string corteges(string s);