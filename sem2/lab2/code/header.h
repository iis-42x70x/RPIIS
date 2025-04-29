#ifndef PIOVIS_LABA2
#define PIOVIS_LABA2

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>

using namespace std;

const char skoba1 = '{';
const char skoba2 = '}';
const char skoba3 = '<';
const char skoba4 = '>';

class Union {
private:
    vector<string> test;

public:
    void shitivanie() {
        cout << "Введите размерность множества" << endl;
        int si;
        cin >> si;
        cin.ignore();
        for (int i = 0; i < si; i++) {
            string stroka;
            getline(cin, stroka);
            if (!stroka.empty()) {
                test.push_back(stroka);
            }
        }
    }

    void set_of_vector(const vector<string>& testi) {
        test = testi;
    }

    void print() const {
        for (size_t i = 0; i < test.size(); ++i) {
            cout << test[i] << ' ';
        }
    }

    vector<string>& get_vector() {
        return test;
    }

    string first_stroka_in_vector() const {
        return test[0];
    }
};

bool is_set(const string& str) {
    return str[0] == '{' && str[str.length() - 1] == '}';
}

bool is_kortezh(const string& str) {
    return str[0] == '<' && str[str.length() - 1] == '>';
}

bool compare_strings(const string& a, const string& b) {
    int i = 0, j = 0;
    while (i < a.length() && j < b.length()) {
        if (a[i] < b[j]) return true;
        if (a[i] > b[j]) return false;
        ++i;
        ++j;
    }
    return a.length() < b.length();
}

void bubble_sort(vector<string>& elements) {
    for (size_t i = 0; i < elements.size(); i++) {
        for (size_t j = 0; j < elements.size() - 1 - i; j++) {
            if (!compare_strings(elements[j], elements[j + 1])) {
                swap(elements[j], elements[j + 1]);
            }
        }
    }
}

void remove_duplicates(vector<string>& elements) {
    vector<string> unique;
    for (size_t i = 0; i < elements.size(); i++) {
        bool flag = false;
        for (size_t j = 0; j < unique.size(); j++) {
            if (elements[i] == unique[j]) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            unique.push_back(elements[i]);
        }
    }
    elements = unique;
}

vector<string> get_elements(const string& set) {
    vector<string> elements;
    string current;
    int bracket_count = 0;
    int bracket_count_treug = 0;

    for (size_t i = 1; i < set.length() - 1; i++) {
        char c = set[i];

        if (c == '{') bracket_count++;
        else if (c == '}') bracket_count--;
        else if (c == '<') bracket_count_treug++;
        else if (c == '>') bracket_count_treug--;

        current += c;

        if ((c == ',' || i == set.length() - 2) && bracket_count == 0 && bracket_count_treug == 0) {
            elements.push_back(current.substr(0, current.length() - (c == ',' ? 1 : 0)));
            current.clear();
        }
    }

    if (!current.empty()) {
        elements.push_back(current);
    }

    return elements;
}

string sort_set(string& str) {
    if (is_kortezh(str)) {
        vector<string> elements = get_elements(str);
        for (size_t i = 0; i < elements.size(); ++i) {
            if (is_set(elements[i]) || is_kortezh(elements[i])) {
                elements[i] = sort_set(elements[i]);
            }
        }
        string result = "<";
        for (size_t i = 0; i < elements.size(); i++) {
            if (i > 0) result += ",";
            result += elements[i];
        }
        result += ">";
        return result;
    }

    if (is_set(str)) {
        vector<string> elements = get_elements(str);
        for (size_t i = 0; i < elements.size(); ++i) {
            if (is_set(elements[i]) || is_kortezh(elements[i])) {
                elements[i] = sort_set(elements[i]);
            }
        }
        bubble_sort(elements);
        remove_duplicates(elements);
        string result = "{";
        for (size_t i = 0; i < elements.size(); i++) {
            if (i > 0) result += ",";
            result += elements[i];
        }
        result += "}";
        return result;
    }

    return str;
}

void checking_znaki(string& stroka) {
    while (!stroka.empty() && stroka[stroka.length() - 1] == ',') {
        stroka.pop_back();
    }
}

bool checking_pravilnost_stroki(const string& stroka) {
    stack<char> stack1;
    for (size_t i = 0; i < stroka.length(); i++) {
        char ch = stroka[i];
        if (ch == skoba1 || ch == skoba3) {
            stack1.push(ch);
        }
        else if (ch == skoba2) {
            if (stack1.empty() || stack1.top() != skoba1) return false;
            stack1.pop();
        }
        else if (ch == skoba4) {
            if (stack1.empty() || stack1.top() != skoba3) return false;
            stack1.pop();
        }
        else if (i != 0 && stack1.empty() && stroka.length() > 2) {
            return false;
        }
    }
    return stack1.empty();
}

bool check_podrad(const string& stroka) {
    for (size_t i = 0; i < stroka.length() - 1; i++) {
        if ((stroka[i] == skoba2 && (stroka[i + 1] == skoba1 || stroka[i + 1] == skoba3)) ||
            (stroka[i] == skoba4 && (stroka[i + 1] == skoba3 || stroka[i + 1] == skoba1))) {
            return false;
        }
    }
    return true;
}

void shitivanie_file(vector<Union>& us) {
    char filename[50];
    cout << "Введите название файла: ";
    cin >> filename;
    ifstream file(filename);
    if (file.is_open()) {
        string stroka;
        getline(file, stroka);
        int size_of_union = stoi(stroka);
        us.resize(size_of_union);
        for (int i = 0; i < size_of_union; i++) {
            getline(file, stroka);
            int size_of_mn = stoi(stroka);
            vector<string> legend;
            for (int j = 0; j < size_of_mn; j++) {
                string res;
                getline(file, res);
                legend.push_back(res);
            }
            us[i].set_of_vector(legend);
        }
        file.close();
    }
    else {
        cout << "Файл не открыт!!!" << endl;
    }
}

void symm_diff(const vector<string>& a, const vector<string>& b, vector<string>& result) {
    result.clear();
    for (size_t i = 0; i < a.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < b.size(); ++j) {
            if (a[i] == b[j]) {
                found = true;
                break;
            }
        }
        if (!found) result.push_back(a[i]);
    }

    for (size_t i = 0; i < b.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < a.size(); ++j) {
            if (b[i] == a[j]) {
                found = true;
                break;
            }
        }
        if (!found) result.push_back(b[i]);
    }

    remove_duplicates(result);
}

void main_symm_diff(vector<Union>& sets, vector<string>& result) {
    result = sets[0].get_vector();
    vector<string> temp;
    for (size_t i = 1; i < sets.size(); ++i) {
        symm_diff(result, sets[i].get_vector(), temp);
        result = temp;
    }
}

#endif
