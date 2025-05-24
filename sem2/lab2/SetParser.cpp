#include "pch.h"
#include "SetParser.h"

vector<string> string_to_vector(const string& str) {
    vector<string> result;
    string temp;
    if (str.empty() || str.front() != '{' || str.back() != '}') return result;
    string cleanStr = str.substr(1, str.size() - 2);

    for (char ch : cleanStr) {
        if (ch == ',') {
            if (!temp.empty()) {
                result.push_back(temp);
                temp.clear();
            }
            else
                continue;
                 
        }
        else temp += ch;
    }
    if (!temp.empty()) result.push_back(temp);
    return result;
}

vector<vector<string>> parseMultipleSets(const string& filename) {
    ifstream file(filename);
    vector<vector<string>> sets;
    string line;
    while (getline(file, line)) {
        vector<string> parsedSet = string_to_vector(line);
        if (!parsedSet.empty()) sets.push_back(parsedSet);
    }
    return sets;
}

vector<vector<string>> cartesianProduct(const vector<vector<string>>& sets) {
    vector<vector<string>> result = { {} };

    for (const auto& set : sets) {
        vector<vector<string>> temp;
        for (const auto& prefix : result) {
            for (const auto& elem : set) {
                auto newTuple = prefix;
                newTuple.push_back(elem);
                temp.push_back(newTuple);
            }
        }
        result = move(temp);
    }

    return result;
}

void calculateCartesianProduct(const string& filename) {
    vector<vector<string>> sets = parseMultipleSets(filename);
    if (sets.empty()) {
        cerr << "Error: No sets parsed.\n";
        return;
    }

    vector<vector<string>> product = cartesianProduct(sets);
    ofstream output("output.txt");

    for (const auto& tuple : product) {
        output << "< ";
        cout << "< ";
        for (size_t i = 0; i < tuple.size(); ++i) {
            output << tuple[i];
            cout << tuple[i];
            if (i < tuple.size() - 1) {
                output << ", ";
                cout << ", ";
            }
        }
        output << " >\n";
        cout << " >\n";
    }
}
