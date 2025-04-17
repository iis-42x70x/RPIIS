#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;

class Boolean
{
public:

	Boolean(string sourceSet);

	void print();

private:

	string source, boolean;

	vector<string> separate();

	string findBoolean();
};

string readfromfile();