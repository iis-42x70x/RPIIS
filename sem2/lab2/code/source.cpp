
#include "Header.h"


void Set::reading() {
    cout << "¬ведите размерность множества" << endl;
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

void Set::set_of_vector(vector <string> tests) {
    test = tests;
}

void Set::print() {
    for (const auto& el : test) {
        cout << el << ' ';
    }
}
vector<string>& Set::get_vector() {
    return test;
}
string Set::first_str_in_vector() {
    return test[0];
}

vector <string>& Set::set_vector(vector<string> tests) {
    test = tests;
    return test;
}



bool is_set(const string& str) {
    return str[0] == bracket1 && str[str.length() - 1] == bracket2;
}
bool is_tupple(const string& str) {
    return str[0] == bracket3 && str[str.length() - 1] == bracket4;
}

bool compare_strings(const string& a, const string& b) {
    int i = 0;
    int j = 0;

    while (i < a.length() && j < b.length()) {
        if (a[i] < b[j]) return true;
        if (a[i] > b[j]) return false;
        i++; j++;
    }
    return a.length() < b.length();
}



void bubble_sort(vector<string>& elements) {
    for (size_t i = 0; i < elements.size(); i++) {
        for (size_t j = 0; j < elements.size() - 1 - i; j++) {
            if (!compare_strings(elements[j], elements[j + 1])) {
                string temp = elements[j];
                elements[j] = elements[j + 1];
                elements[j + 1] = temp;
            }
        }
    }
}

void remove_duplicates(vector<string>& elements) {
    if (elements.empty()) return;
    vector <string> unique;
    for (int i = 0; i < elements.size(); i++) {
        bool flag = false;
        for (int j = 0; j < unique.size(); j++) {
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


vector<string> get_elements(string& set) {
    vector<string> elements;
    string current;
    int bracket_count = 0;
    int bracket_count_treug = 0;

    for (int i = 1; i < set.length() - 1; i++) {
        char c = set[i];

        if (c == bracket1) {
            bracket_count++;
            current += c;
        }
        else if (c == bracket2) {
            bracket_count--;
            current += c;
            if (bracket_count == 0 && bracket_count_treug == 0) {
                elements.push_back(current);
                current.clear();
            }
        }
        else if (c == bracket3) {
            bracket_count_treug++;
            current += c;
        }
        else if (c == bracket4) {
            bracket_count_treug--;
            current += c;
            if (bracket_count == 0 && bracket_count_treug == 0) {
                elements.push_back(current);
                current.clear();
            }
        }
        else if ((c == ',' || c == ' ') && bracket_count == 0 && bracket_count_treug == 0) {
            if (!current.empty()) {
                elements.push_back(current);
                current.clear();
            }

        }
        else {
            current += c;
        }
    }

    if (!current.empty()) {
        elements.push_back(current);
    }

    return elements;
}

string sort_set(string& str) {
    if (is_tupple(str)) {
        vector<string> elements = get_elements(str);
        for (auto& element : elements) {
            if (is_set(element) || is_tupple(element)) {
                element = sort_set(element);
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
        for (auto& element : elements) {
            if (is_set(element) || is_tupple(element)) {
                element = sort_set(element);
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
void peresechenie(vector <string> res, vector<string>& result) {
    vector <string> temp;
    for (auto& el : res) {
        bool flag = false;
        for (auto& s : result) {
            if (el == s) {
                flag = true;
                break;
            }
        }
        if (flag) {
            temp.push_back(el);
        }
    }
    result.clear();
    result = temp;
}
void main_intersection(vector <Set>& test, vector<string>& result) {
    vector <string>temp;
    for (int i = 1; i < test.size(); i++) {
        peresechenie(test[i].get_vector(), result);
    }
}
void checking_symbol(string& str) {
    while (str.back() == ',' && !str.empty()) {
        str.pop_back();
    }
}

bool checking_correct_str(string str) {
    stack<char> stack1;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == bracket1) {
            stack1.push(bracket1);
        }
        else if (str[i] == bracket2) {
            if (stack1.empty()) {
                return false;
            }
            else if (stack1.top() == bracket1) {
                stack1.pop();
            }
            else return false;
        }
        else if (str[i] == bracket3) {
            stack1.push(bracket3);
        }
        else if (str[i] == bracket4) {
            if (stack1.empty()) {
                return false;
            }
            else if (stack1.top() == bracket3) {
                stack1.pop();
            }
            else return false;
        }
        else if (i != 0 && stack1.empty() && str.length() > 2) {
            return false;
        }
    }
    if (stack1.empty()) return true;
    else return false;
}

bool checking_next(string str) {
    for (int i = 0; i < str.length() - 1; i++) {
        if ((str[i] == bracket2 && (str[i + 1] == bracket1 || str[i + 1] == bracket3)) || (str[i] == bracket4 && (str[i + 1] == bracket3 || str[i + 1] == bracket1))) {
            return false;
        }
    }
    return true;
}



void reading_file(vector <Set>& intersection) {
    ifstream file;
    file.open("input.txt");
    if (file.is_open()) {
        string str;
        getline(file, str);
        int size_of_set = stoi(str);
        intersection.resize(size_of_set);
        for (int i = 0; i < size_of_set; i++) {
            string str2;
            getline(file, str2);

            vector <string> buffer;
            buffer.clear();
            int size_of_s = stoi(str2);
            for (int j = 0; j < size_of_s; j++) {
                string res;
                getline(file, res);
                buffer.push_back(res);
            }
            intersection[i].set_of_vector(buffer);

        }
        file.close();

    }
    else {
        cout << "‘айл не открыт!";
        return;
    }
}
