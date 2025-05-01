#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

string NotSpace(string& str) {
    string newstr = "";
    for (char el : str) {
        if (el != ' ') newstr += el;
    }
    return newstr;
}
bool CheckStr(const string& str) {
    if (str.empty()) {
        cout << "Ошибка: не введено ни одного элемента" << endl;
        return false;
    }
    int col1 = 0;
    int col2 = 0;
    int size = str.size();
    string s;
    for (int i = 0; i < size; i++) {
        if (str[i] == '{') {
            col1++;
            s += str[i];
        }
        else
            if (str[i] == '<') {
                col2++;
                s += str[i];
            }
            else
                if (str[i] == '}') {
                    col1--;
                    s += str[i];
                }
                else
                    if (str[i] == '>') {
                        col2--;
                        s += str[i];
                    }
        if (i > 0 && (str[i] == '{' || str[i] == '<') && (str[i - 1] != '{' && str[i - 1] != '<' && str[i - 1] != ',')) {
            cout << "Ошибка: перед '{' и '<' не может стоять ничего кроме  '{', '<' и ','\n";
            return false;
        }
        if (i < size - 2 && (str[i] == '}' || str[i] == '>') && (str[i + 1] != '}' && str[i + 1] != '>' && str[i + 1] != ',')) {
            cout << "Ошибка: после '}' и '>' не может стоять ничего кроме  '}', '>' и ','\n";
            return false;
        }
        if (i > 0 && (str[i] == '}' || str[i] == '>') && str[i - 1] == ',') {
            cout << "Ошибка: перед '}' и '>' не может стоять ','\n";
            return false;
        }
        if (i < size - 2 && (str[i] == '{' || str[i] == '<') && str[i + 1] == ',') {
            cout << "Ошибка: после '{' и '<' не может стоять ','\n";
            return false;
        }
    }
    if (col1) {
        cout << "Ошибка: количество '{' отличается от '}'\n";
        return false;
    }
    if (col2) {
        cout << "Ошибка: количество '<' отличается от '>'\n";
        return false;
    }
    for (int i = 0; i < s.size() - 1; i++) {
        if ((s[i] == '{' && s[i + 1] == '>') || (s[i] == '<' && s[i + 1] == '}')) {
            cout << "Ошибка: разные открывающие и закрывающие скобки\n";
            return false;
        }
    }
    return true;
}
SetElement ParsingElements(const string& str, int& pos) {
    if (pos < str.size() && (str[pos] == '{' || str[pos] == '<')) return ParsingSets(str, pos);
    string s;
    while (pos < str.size() && str[pos] != ',' && str[pos] != '}' && str[pos] != '>') {
        s += str[pos];
        pos++;
    }
    SetElement el;
    el.type = STRING;
    el.strvalue = s;
    return el;
}
SetElement ParsingSets(const string& str, int& pos) {
    SetElement result;
    char StartStr = str[pos];
    char EndStr;
    if (StartStr == '{') {
        EndStr = '}';
        result.type = SET;
    }
    if (StartStr == '<') {
        EndStr = '>';
        result.type = ORSET;
    }
    pos++;
    vector<SetElement> v;
    while (pos < str.size()) {
        if (str[pos] == EndStr) {
            pos++;
            break;
        }
        SetElement el = ParsingElements(str, pos);
        v.push_back(el);
        if (str[pos] == ',') pos++;
    }
    result.vecvalue = v;
    return result;
}
void Printf(const SetElement& el) {
    if (el.type == STRING) {
        cout << el.strvalue;
    }
    else {
        char StartStr = (el.type == SET ? '{' : '<');
        char EndStr = (el.type == SET ? '}' : '>');
        cout << StartStr;
        for (int i = 0; i < el.vecvalue.size(); ++i) {
            Printf(el.vecvalue[i]);
            if (i + 1 < el.vecvalue.size()) cout << ',';
        }
        cout << EndStr;
    }
}
vector<vector<SetElement>> Permute(const vector<SetElement>& elems) {
    vector<vector<SetElement>> result;
    vector<vector<SetElement>> options;
    for (const auto& e : elems) {
        if (e.type == STRING) {
            options.push_back({ e });
        }
        else if (e.type == SET) {
            auto PermuteChild = Permute(e.vecvalue);
            vector<SetElement> vec1;
            for (auto& v : PermuteChild) {
                SetElement t;
                t.type = SET;
                t.vecvalue = v;
                vec1.push_back(t);
            }
            options.push_back(vec1);
        }
        else {
            vector<vector<SetElement>> childOpts;
            for (auto& el : e.vecvalue) {
                if (el.type == SET) {
                    auto PermuteChild = Permute(el.vecvalue);
                    vector<SetElement> vec2;
                    for (auto& v : PermuteChild) {
                        SetElement t;
                        t.type = SET;
                        t.vecvalue = v;
                        vec2.push_back(t);
                    }
                    childOpts.push_back(vec2);
                }
                else {
                    childOpts.push_back({ el });
                }
            }
            vector<vector<SetElement>> combos;
            vector<SetElement> cur;
            GenerateCombinations(childOpts, combos, cur, 0);
            vector<SetElement> vec3;
            for (auto& v : combos) {
                SetElement t;
                t.type = ORSET;
                t.vecvalue = v;
                vec3.push_back(t);
            }
            options.push_back(vec3);
        }
    }
    vector<vector<SetElement>> base;
    vector<SetElement> cur;
    BuildCombinations(options, base, cur, 0);
    for (auto& line : base) {
        sort(line.begin(), line.end(), CompareElements);
        do {
            result.push_back(line);
        } while (next_permutation(line.begin(), line.end(), CompareElements));
    }
    return result;
}
void GenerateCombinations(const vector<vector<SetElement>>& childOpts, vector<vector<SetElement>>& combos, vector<SetElement>& cur, int i) {
    if (i == childOpts.size()) {
        combos.push_back(cur);
        return;
    }
    for (auto& opt : childOpts[i]) {
        cur.push_back(opt);
        GenerateCombinations(childOpts, combos, cur, i + 1);
        cur.pop_back();
    }
}
void BuildCombinations(const vector<vector<SetElement>>& options, vector<vector<SetElement>>& base, vector<SetElement>& cur, int i) {
    if (i == options.size()) {
        base.push_back(cur);
        return;
    }
    for (auto& opt : options[i]) {
        cur.push_back(opt);
        BuildCombinations(options, base, cur, i + 1);
        cur.pop_back();
    }
}
bool CompareElements(const SetElement& a, const SetElement& b) {
    if (a.type != b.type) return a.type < b.type;
    if (a.type == STRING) return a.strvalue < b.strvalue;
    return false;
}
string ReadFromFile() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        return "";
    }
    string str;
    getline(file, str);
    file.close();
    return str;
}
