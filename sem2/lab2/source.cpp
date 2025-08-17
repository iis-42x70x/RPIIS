#include "header.h"
vector<string> stringToVectorOfSetElements(const string& str) {
	vector<string> setElements;
	string temp;
	bool inBrackets = false;

	string cleanStr = str;
	if (!str.empty() && str.front() == '{' && str.back() == '}') {
		cleanStr = str.substr(1, str.length() - 2);
	}
	for (char ch : cleanStr) {
		if (ch == '{' ) {
			inBrackets = true;
			temp += ch;
		}
		else if (ch == '}') {
			inBrackets = false;
			temp += ch;
			setElements.push_back(temp);
			temp.clear();
		}
		else if (ch == ',' && !inBrackets) {
			if (!temp.empty()) {
				setElements.push_back(temp);
				temp.clear();
			}
		}
		else if (/*inBrackets || */ch != ' ') {
			temp += ch;
		}
	}

	if (!temp.empty()) setElements.push_back(temp);
	return setElements;
}

void permute(vector<string>& setElements, int l, int r, vector<vector<string>>& result) {
	if (l == r) {
		result.push_back(setElements);
		return;
	}
	for (int i = l; i <= r; ++i) {
		swap(setElements[l], setElements[i]);
		permute(setElements, l + 1, r, result);
		swap(setElements[l], setElements[i]);
	}
}

vector<vector<string>> generatePermutations(const vector<string>& setElements) {
	vector<vector<string>> result;
	vector<string> temp = setElements;
	permute(temp, 0, temp.size() - 1, result);
	return result;
}

void findAllCombinations(const string& filename) {
	ifstream file(filename);
	if (!file) {
		cerr << "Error: Unable to create output file!\n";
		return;
	}
	string line;
	getline(file, line);
	file.close();

	vector<vector<string>> permutations = generatePermutations(stringToVectorOfSetElements(line));

	ofstream outputFile("output.txt");
	if (!outputFile) {
		cerr << "Error: Unable to create output file\n";
		return;
	}
	for (const auto& permutation : permutations) {
		cout << "{ ";
		outputFile << "{ ";
		for (size_t i = 0; i < permutation.size(); ++i) {
			cout << permutation[i];
			outputFile << permutation[i];
			if (i < permutation.size() - 1) {
				cout << ", ";
				outputFile << ", ";
			}
		}
		cout << " }\n";
		outputFile << " }\n";
	}
	outputFile.close();
}