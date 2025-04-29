#pragma once

#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;


string trim(const string& str);
int find_next_bracker(const string& s, int i);
string corteges(string s);
string sets(string s);
multiset<string> intersection(const string& file_path);
void process();
