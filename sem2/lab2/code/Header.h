#ifndef UNION
#define UNION
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <fstream>
#include <algorithm>
using namespace std;

class Union
{
private:
	vector<string> set;

	bool Checking_Set(string& set);
	bool Breckets_Check(string& str);
	string removeSpaces(string& str);
	void removeDuplicates(vector<string>& set);
	bool ValidElement(string& elem);
	vector<string> parseSet(string str);
	string sortSetString(string str);
	void normalizeSet();
public:
	vector<string> getSet();
	vector<string> setSet(vector<string>& new_set);
	vector<string> setsUnion(vector<string>& result);
	bool Correct_Set(string str);
	void add(string& str);
};

void printUnion(vector<string> result);
void read_file(vector<Union>& sets);
#endif