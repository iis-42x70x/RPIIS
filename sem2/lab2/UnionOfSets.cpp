#include "UnionOfSets.h"
#include <iostream>

using namespace std;

void run_testcase(const string& path, int& num_sets, vector<vector<string>>& sets) {
    ifstream file;
    file.open(path);
    if (!file.is_open()) {
        cout << "File is not open\n";
    }
    else {
        file >> num_sets;
        file.ignore();
        sets.resize(num_sets);
        for (int i = 0; i < num_sets; ++i) {
            string line;
            getline(file, line);
            string element;
            bool inside_brackets = false;
            bool should_sort = true;
            for (char symbol : line) {
                if (symbol == '{') {
                    inside_brackets = true;
                    element += symbol;
                }
                else if (symbol == '}') {
                    inside_brackets = false;
                    element += symbol;

                    if (element.size() == 2) {
                        sets[i].push_back(element);
                    }
                    else {
                        string inner = element.substr(1, element.size() - 2);
                        vector<string> inner_elements;
                        string inner_element;
                        for (char inner_symbol : inner) {
                            if (inner_symbol == ' ') {
                                if (!inner_element.empty()) {
                                    inner_elements.push_back(inner_element);
                                    inner_element.clear();
                                }
                            }
                            else {
                                inner_element += inner_symbol;
                            }
                        }
                        if (!inner_element.empty()) {
                            inner_elements.push_back(inner_element);
                        }
                        sort(inner_elements.begin(), inner_elements.end());
                        element = "{";
                        for (const string& sorted_element : inner_elements) {
                            element += sorted_element + " ";
                        }
                        element.pop_back();
                        element += "}";

                        sets[i].push_back(element);
                    }
                    element.clear();
                }
                else if (symbol == ' ' && !inside_brackets) {
                    if (!element.empty()) {
                        sets[i].push_back(element);
                        element.clear();
                    }
                }
                else {
                    element += symbol;
                }
            }
            if (!element.empty()) {
                sets[i].push_back(element);
            }
        }
        file.close();
    }
}

vector<vector<pair<string, int>>> CountMultiplicities(const vector<vector<string>>& sets) {
    vector<vector<pair<string, int>>> counts(sets.size());

    for (int i = 0; i < sets.size(); ++i) {
        vector<string> unique_elements;
        vector<int> element_counts;

        for (const string& element : sets[i]) {
            bool found = false;

            for (int j = 0; j < unique_elements.size(); ++j) {
                if (unique_elements[j] == element) {

                    element_counts[j]++;
                    found = true;
                    break;
                }
            }

            if (!found) {
                unique_elements.push_back(element);
                element_counts.push_back(1);
            }
        }

        for (int j = 0; j < unique_elements.size(); ++j) {
            counts[i].push_back(make_pair(unique_elements[j], element_counts[j]));
        }
    }
    return counts;
}

vector<pair<string, int>> FindMaxMultiplicities(const vector<vector<pair<string, int>>>& counts) {
    vector<pair<string, int>> max_counts;
    for (const auto& set : counts) {
        for (const auto& pair : set) {
            bool found = false;
            for (auto& max_pair : max_counts) {
                if (max_pair.first == pair.first) {
                    max_pair.second = max(max_pair.second, pair.second);
                    found = true;
                    break;
                }
            }
            if (!found) {
                max_counts.push_back(pair);
            }
        }
    }

    return max_counts;
}

void OutputResult(const vector<pair<string, int>>& max_counts) {
    cout << "The union of the sets: " << endl;
    for (const auto& pair : max_counts) {
        for (int i = 0; i < pair.second; ++i) {
            cout << pair.first << " ";
        }
    }
    cout << endl;
}
