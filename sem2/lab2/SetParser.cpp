#include "pch.h"

vector<string> string_to_vector_OfSetElements(const string& str) {
    vector<string> setElements;
    string temp;
    int braceLevel = 0;
    int angleLevel = 0;

    if (str == "{}")  return setElements;

    if (str.empty()  str.front() != '{'   str.back() != '}') {
        cerr << "Error: Wrong input \n";
        return {};
    }

    string cleanStr = str.substr(1, str.length() - 2);

    for (size_t i = 0; i < cleanStr.length(); ++i) {
        char ch = cleanStr[i];

        if (ch == '{') {
            braceLevel++;
            temp += ch;
        }
        else if (ch == '}') {
            braceLevel--;
            if (braceLevel < 0) {
                cerr << "Error: Unmatched closing curly brace\n";
                return {};
            }
            temp += ch;
        }
        else if (ch == '<') {
            angleLevel++;
            temp += ch;
        }
        else if (ch == '>') {
            angleLevel--;
            if (angleLevel < 0) {
                cerr << "Error: Unmatched closing angle bracket\n";
                return {};
            }
            temp += ch;
        }
        else if (ch == ',' && braceLevel == 0 && angleLevel == 0) {
            if (!temp.empty()) {
                setElements.push_back(temp);
                temp.clear();
            }
            else {
                cerr << "Error: Invalid comma placement\n";
                return {};
            }
        }
        else {
            temp += ch;
        }
    }

    if (braceLevel != 0 || angleLevel != 0) {
        cerr << "Error: Unmatched braces or angle brackets\n";
        return {};
    }

    if (!temp.empty()) {
        setElements.push_back(temp);
    }

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

vector<vector<string>> generateUniquePermutations(const vector<string>& setElements) {
    vector<vector<string>> allPerms;
    vector<string> temp = setElements;
    permute(temp, 0, temp.size() - 1, allPerms);

    set<vector<string>> uniqueSets;
    for (auto& p : allPerms) {
        uniqueSets.insert(p);
    }

    return vector<vector<string>>(uniqueSets.begin(), uniqueSets.end());
}

void findAllCombinations(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open input file!\n";
        return;
    }

    string line;
    getline(file, line);
    file.close();

    vector<string> elements = string_to_vector_OfSetElements(line);
    if (elements.empty()) {
        cerr << "Error: Failed to parse elements from input.\n";
        return;
    }

    vector<vector<string>> uniquePermutations = generateUniquePermutations(elements);

    ofstream outputFile("output.txt");
    if (!outputFile) {
        cerr << "Error: Unable to create output file\n";
        return;
    }

    for (const auto& permutation : uniquePermutations) {
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