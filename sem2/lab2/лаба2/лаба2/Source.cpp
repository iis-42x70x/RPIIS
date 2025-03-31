#include "Header.h"
using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

void open_and_sets(const string& path, vector<vector<string>>& sets) {
    ifstream file(path);
    if (!file) {
        cerr << "File is not open\n";
        return;
    }

    sets.clear();
    string line;
    while (getline(file, line)) {
        if (line.size() < 2) continue;
        line = line.substr(1, line.size() - 2);
        replace(line.begin(), line.end(), ',', ' '); 

        istringstream ss(line);
        string element;
        stack<vector<string>> nested_sets;
        nested_sets.push({});
        bool inside_angle = false;
        string current_angle;

        while (ss >> element) {
            int open_braces = count(element.begin(), element.end(), '{');
            int close_braces = count(element.begin(), element.end(), '}');
            int open_angle = count(element.begin(), element.end(), '<');
            int close_angle = count(element.begin(), element.end(), '>');

            if (open_angle > 0) {
                inside_angle = true;
                current_angle.clear();
                element = element.substr(open_angle - 1);
            }

            if (inside_angle) {
                if (!current_angle.empty()) current_angle += " ";
                current_angle += element;

                if (close_angle > 0) {
                    inside_angle = false;
                    nested_sets.top().push_back(current_angle);
                }
                continue;
            }

            if (open_braces > 0) {
                for (int i = 0; i < open_braces; ++i) {
                    nested_sets.push({});
                }
                element = element.substr(open_braces);
            }

            if (close_braces > 0) {
                element = element.substr(0, element.size() - close_braces);
                nested_sets.top().push_back(element);

                for (int i = 0; i < close_braces; ++i) {
                    vector<string> completed_set = nested_sets.top();
                    nested_sets.pop();
                    sort(completed_set.begin(), completed_set.end());

                    string formatted_set = "{";
                    for (size_t j = 0; j < completed_set.size(); ++j) {
                        if (j > 0) formatted_set += " ";
                        formatted_set += completed_set[j];
                    }
                    formatted_set += "}";

                    nested_sets.top().push_back(formatted_set);
                }
                continue;
            }

            nested_sets.top().push_back(element);
        }

        if (!nested_sets.empty()) {
            sets.push_back(nested_sets.top());
        }
    }
    file.close();
}







vector<vector<pair<string, int>>> set_element_count(const vector<vector<string>>& sets) {
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


vector<pair<string, int>> final_set_count(const vector<vector<pair<string, int>>>& counts) {
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

void output(const vector<pair<string, int>>& max_counts) {
    cout << "The union of the sets: " << endl;
    for (const auto& pair : max_counts) {
        for (int i = 0; i < pair.second; ++i) {
            cout << pair.first << " ";
        }
    }
    cout << endl;
}
