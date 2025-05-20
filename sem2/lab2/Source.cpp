#include "Header.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <unordered_map>

using namespace std;

vector<string> split_elements(const string& str) {
    vector<string> elements;
    string current;
    bool in_angle = false;

    for (char c : str) {
        if (c == '<') {
            in_angle = true;
            current += c;
        }
        else if (c == '>') {
            in_angle = false;
            current += c;
            elements.push_back(current);
            current.clear();
        }
        else if (in_angle) {
            current += c;
        }
        else if (c == ',') {
            if (!current.empty()) {
                elements.push_back(current);
                current.clear();
            }
        }
        else if (c != ' ') {
            current += c;
        }
    }

    if (!current.empty()) {
        elements.push_back(current);
    }

    return elements;
}

void process_line(const string& line, vector<string>& result) {
    stack<vector<string>> nested_sets;
    nested_sets.push({});
    bool has_nested_sets = false;
    bool in_angle = false;
    string angle_content;

    size_t pos = 0;
    while (pos < line.length()) {
        if (line[pos] == '{') {
            if (nested_sets.size() > 1) has_nested_sets = true;
            nested_sets.push({});
            pos++;
        }
        else if (line[pos] == '}') {
            if (nested_sets.size() <= 1) {
                cerr << "Error: Unbalanced braces" << endl;
                return;
            }

            vector<string> current_set = nested_sets.top();
            nested_sets.pop();

            if (has_nested_sets || current_set.size() > 1) {
                sort(current_set.begin(), current_set.end());
                string formatted_set = "{";
                for (size_t i = 0; i < current_set.size(); ++i) {
                    if (i > 0) formatted_set += " ";
                    formatted_set += current_set[i];
                }
                formatted_set += "}";
                nested_sets.top().push_back(formatted_set);
            }
            else {
                for (const auto& element : current_set) {
                    nested_sets.top().push_back(element);
                }
            }
            pos++;
        }
        else if (line[pos] == '<') {
            in_angle = true;
            angle_content = "<";
            pos++;
        }
        else if (line[pos] == '>' && in_angle) {
            in_angle = false;
            angle_content += ">";
            nested_sets.top().push_back(angle_content);
            angle_content.clear();
            pos++;
        }
        else if (in_angle) {
            angle_content += line[pos];
            pos++;
        }
        else if (line[pos] == ',') {
            pos++;
        }
        else {
            size_t end_pos = line.find_first_of("{},<>", pos);
            if (end_pos == string::npos) end_pos = line.length();

            string element = line.substr(pos, end_pos - pos);
            auto elements = split_elements(element);
            for (const auto& e : elements) {
                if (!e.empty()) {
                    nested_sets.top().push_back(e);
                }
            }

            pos = end_pos;
        }
    }

    if (nested_sets.size() != 1) {
        cerr << "Error: Unbalanced braces in final check" << endl;
        return;
    }

    result = nested_sets.top();
}

void open_and_sets(const string& path, vector<vector<string>>& sets) {
    ifstream file(path);
    if (!file) {
        cerr << "File is not open\n";
        return;
    }

    sets.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty() || line.size() < 2) continue;

        if (line.front() == '{' && line.back() == '}') {
            line = line.substr(1, line.size() - 2);
        }

        vector<string> current_set;
        process_line(line, current_set);
        if (!current_set.empty()) {
            sets.push_back(current_set);
        }
    }
    file.close();
}

vector<vector<pair<string, int>>> set_element_count(const vector<vector<string>>& sets) {
    vector<vector<pair<string, int>>> counts(sets.size());

    for (size_t i = 0; i < sets.size(); ++i) {
        unordered_map<string, int> element_count_map;

        for (const string& element : sets[i]) {
            element_count_map[element]++;
        }

        for (const auto& pair : element_count_map) {
            counts[i].emplace_back(pair.first, pair.second);
        }
    }
    return counts;
}

vector<pair<string, int>> final_set_count(const vector<vector<pair<string, int>>>& counts) {
    unordered_map<string, int> max_counts_map;

    for (const auto& set : counts) {
        for (const auto& pair : set) {
            auto it = max_counts_map.find(pair.first);
            if (it == max_counts_map.end() || pair.second > it->second) {
                max_counts_map[pair.first] = pair.second;
            }
        }
    }

    vector<pair<string, int>> max_counts(max_counts_map.begin(), max_counts_map.end());
    sort(max_counts.begin(), max_counts.end());
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