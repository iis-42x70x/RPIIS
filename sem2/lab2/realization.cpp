#include <C:\Users\omen\source\repos\RPIIS_2LAB_BOOLEAN\RPIIS_2LAB_BOOLEAN\Header.h>


using namespace std;

Boolean::Boolean(string sourceSet)
{
	source = sourceSet;
	boolean = findBoolean();
}

void Boolean::print()
{
	cout << source << endl;
	cout << boolean << endl;
}


vector<string> Boolean::separate() {
	vector<string> sepElements;
	string processed = source;

	processed.erase(remove(processed.begin(), processed.end(), ' '), processed.end());

	if (!processed.empty()) {
		processed.erase(0, 1);
		if (!processed.empty()) {
			processed.erase(processed.length() - 1, 1);
		}
	}

	int size = processed.length();
	int level = 1;
	string in;

	for (int i = 0; i < size; i++) {
		if (processed[i] == '{' || processed[i] == '<') {
			level++;
		}
		else if (processed[i] == '}' || processed[i] == '>') {
			level--;
		}

		if (level == 1 && processed[i] != ',') {
			in += processed[i];
		}
		else if (processed[i] == ',' && level == 1) {
			if (!in.empty()) {
				sepElements.push_back(in);
				in.clear();
			}
		}
		else if (level != 1) {
			in += processed[i];
		}
	}

	if (!in.empty()) {
		sepElements.push_back(in);
	}

	return sepElements;
}

string Boolean::findBoolean() {
	vector<string> sep = separate();
	vector<vector<string>> subsets = { {} };

	for (string elem : sep) {
		int size = subsets.size();
		for (int i = 0; i < size; i++) {
			vector<string> newSubset = subsets[i];
			newSubset.push_back(elem);
			subsets.push_back(newSubset);
		}
	}

	string result = "{";
	for (size_t i = 0; i < subsets.size(); i++) {
		result += "{";
		if (!subsets[i].empty()) {
			for (int j = 0; j < subsets[i].size(); j++) {
				result += subsets[i][j];
				if (j != subsets[i].size() - 1) {
					result += ", ";
				}
			}
		}
		result += "}";
		if (i != subsets.size() - 1) {
			result += ", ";
		}
	}
	result += "}";
	return result;
}

string readfromfile()
{

	ifstream inputFile("input.txt");
		string line;
		if (!inputFile.is_open())
		{
			return "{a}";
		}

		getline(inputFile, line);
		inputFile.close();
		return line;
}


