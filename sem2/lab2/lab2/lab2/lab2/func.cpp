#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "func.hpp"

using namespace std;

void wall() {
    cout << "--------------------------------------------------------------------------------------------------------------\n";
}

string trim(const string& s) {
    size_t f = s.find_first_not_of(" \t");
    if (f == string::npos) return "";
    size_t l = s.find_last_not_of(" \t");
    return s.substr(f, l - f + 1);
}

vector<string> split_elements(const string& src) {
    vector<string> el;
    string buf;
    int depth_brace = 0, depth_angle = 0;

    for (char ch : src) {
        if (ch == '{') ++depth_brace;
        if (ch == '}') --depth_brace;
        if (ch == '<') ++depth_angle;
        if (ch == '>') --depth_angle;

        if (ch == ',' && depth_brace == 0 && depth_angle == 0) {
            if (!buf.empty()) { el.push_back(trim(buf)); buf.clear(); }
        }
        else buf += ch;
    }
    if (!buf.empty()) el.push_back(trim(buf));
    return el;
}

string normalize_element(const string& s) {
    string t = trim(s);
    if (t.size() >= 2 && t.front() == '{' && t.back() == '}') {
        string inner = t.substr(1, t.size() - 2);
        vector<string> items = split_elements(inner);
        for (string& x : items) x = trim(x);
        sort(items.begin(), items.end());
        string res = "{";
        for (size_t i = 0; i < items.size(); ++i) {
            if (i > 0) res += ",";
            res += items[i];
        }
        res += "}";
        return res;
    }
    return t;
}


void collect_elements(const string& src, map<string, int>& out) {
    string norm = normalize_element(src);
    if (!norm.empty()) ++out[norm];
}

map<string, int> intersect_sets(const vector<string>& inputs) {
    map<string, int> common;

    for (size_t i = 0; i < inputs.size(); ++i) {
        map<string, int> current;
        vector<string> top = split_elements(inputs[i]);
        for (const string& el : top)
            collect_elements(el, current);

        if (i == 0)
            common = current;
        else {
            map<string, int> tmp;
            for (auto& p : common) {
                if (current.count(p.first))
                    tmp[p.first] = min(p.second, current[p.first]);
            }
            common.swap(tmp);
        }
    }
    return common;
}