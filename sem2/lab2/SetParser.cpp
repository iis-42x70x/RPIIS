#include "pch.h"
#include "SetParser.h"

vector<string> string_to_vector(const string& str) {
    vector<string> result;

    if (str.empty() || str.front() != '{' || str.back() != '}') {
        cerr << "Ошибка: множество должно начинаться с '{' и заканчиваться '}'\n";
        return {};
    }

    string cleanStr = str.substr(1, str.size() - 2);
    string temp;
    int braceDepth = 0;
    int angleDepth = 0;

    for (char ch : cleanStr) {
        if (ch == ',') {
            if (braceDepth == 0 && angleDepth == 0) {
                if (temp.empty()) {
                    cerr << "Ошибка: пустой элемент между запятыми\n";
                    return {};
                }
                result.push_back(temp);
                temp.clear();
            }
            else {
                temp += ch;
            }
        }
        else {
            if (ch == '{') ++braceDepth;
            else if (ch == '}') --braceDepth;
            else if (ch == '<') ++angleDepth;
            else if (ch == '>') --angleDepth;

            if (braceDepth < 0 || angleDepth < 0) {
                cerr << "Ошибка: лишняя закрывающая скобка\n";
                return {};
            }

            temp += ch;
        }
    }

    if (braceDepth != 0 || angleDepth != 0) {
        cerr << "Ошибка: несоответствие открывающих и закрывающих скобок\n";
        return {};
    }

    if (!temp.empty())
        result.push_back(temp);

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
