#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

string NotSpace(const char* input) {
    string newstr;
    while (*input) {
        if (*input != ' ') newstr += *input;
        input++;
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

void PrintSetElement(const SetElement& el) {
    if (el.type == STRING) {
        cout << el.strvalue;
    }
    else if (el.type == SET) {
        cout << "<";
        for (size_t i = 0; i < el.vecvalue.size(); ++i) {
            PrintSetElement(el.vecvalue[i]);
            if (i + 1 != el.vecvalue.size()) cout << ",";
        }
        cout << ">";
    }
}


void PrintSet(const vector<SetElement>& set) {
    cout << "{";
    for (size_t i = 0; i < set.size(); ++i) {
        PrintSetElement(set[i]);
        if (i + 1 != set.size()) cout << ",";
    }
    cout << "}" << endl;
}


void GenerateCombinations(const vector<SetElement>& elems, int n, int start,
    vector<SetElement>& current, vector<vector<SetElement>>& result) {
    if (current.size() == n) {
        result.push_back(current);
        return;
    }
    for (int i = start; i < elems.size(); ++i) {
        current.push_back(elems[i]);
        GenerateCombinations(elems, n, i + 1, current, result);
        current.pop_back();
    }
}


vector<SetElement> ParseCustomFormat(const string& input) {
    vector<SetElement> result;
    int i = 0;
    if (input[i] != '{') return result;
    ++i;

    while (i < input.size()) {
        if (input[i] == '<') {
            ++i;
            vector<SetElement> nested;
            string temp;
            while (i < input.size() && input[i] != '>') {
                if (input[i] == ',') {
                    if (!temp.empty()) {
                        SetElement el;
                        el.type = STRING;
                        el.strvalue = temp;
                        nested.push_back(el);
                        temp.clear();
                    }
                }
                else {
                    temp += input[i];
                }
                ++i;
            }
            if (!temp.empty()) {
                SetElement el;
                el.type = STRING;
                el.strvalue = temp;
                nested.push_back(el);
            }
            SetElement setEl;
            setEl.type = SET;
            setEl.vecvalue = nested;
            result.push_back(setEl);
            ++i; 
        }
        else if (input[i] == ',') {
            ++i;
        }
        else if (input[i] == '}') {
            break;
        }
        else {
            string temp;
            while (i < input.size() && input[i] != ',' && input[i] != '}') {
                temp += input[i++];
            }
            if (!temp.empty()) {
                SetElement el;
                el.type = STRING;
                el.strvalue = temp;
                result.push_back(el);
            }
        }
    }

    return result;
}

vector<SetElement> ReadFromFile() {
    char buffer[1024];
    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "Ошибка открытия файла\n";
        return vector<SetElement>();
    }

    file.getline(buffer, sizeof(buffer));
    file.close();

    string cleaned = NotSpace(buffer);

    if (!CheckStr(cleaned)) {
        return vector<SetElement>();
    }
    return ParseCustomFormat(cleaned);
}