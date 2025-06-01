#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <utility>
#include <unordered_set>

using namespace std;

struct SetCollection {
    vector<vector<string>> sets;
};

void trim(string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start != string::npos) {
        str = str.substr(start);
    }

    size_t end = str.find_last_not_of(" \t\n\r");
    if (end != string::npos) {
        str = str.substr(0, end + 1);
    }
}

bool is_balanced(const string& s) {
    int balance_curly = 0;
    int balance_angle = 0;
    for (char c : s) {
        if (c == '{') balance_curly++;
        else if (c == '}') balance_curly--;
        else if (c == '<') balance_angle++;
        else if (c == '>') balance_angle--;

        if (balance_curly < 0 || balance_angle < 0) return false;
    }
    return balance_curly == 0 && balance_angle == 0;
}

bool is_set(const string& s) {
    return (s.size() >= 2 && s.front() == '{' && s.back() == '}') ||
        (s.size() >= 2 && s.front() == '<' && s.back() == '>');
}

vector<string> parse_element(const string& element) {
    vector<string> result;
    string current;
    int curly_depth = 0;
    int angle_depth = 0;

    for (char c : element) {
        if (c == '{') curly_depth++;
        else if (c == '}') curly_depth--;
        else if (c == '<') angle_depth++;
        else if (c == '>') angle_depth--;

        if (c == ',' && curly_depth == 0 && angle_depth == 0) {
            trim(current);
            if (!current.empty()) {
                result.push_back(current);
            }
            current.clear();
        }
        else {
            current += c;
        }
    }

    trim(current);
    if (!current.empty()) {
        result.push_back(current);
    }

    return result;
}

void sort_set_elements(vector<string>& elements, bool is_ordered) {
    if (!is_ordered) {
        sort(elements.begin(), elements.end());
    }
}

vector<string> parse_set(const string& set_str) {
    vector<string> elements;
    string content;
    bool is_ordered = false;

    size_t start_brace = set_str.find('{');
    size_t start_angle = set_str.find('<');

    if (start_brace != string::npos && (start_angle == string::npos || start_brace < start_angle)) {
       
        size_t end_brace = set_str.rfind('}');
        if (end_brace != string::npos) {
            content = set_str.substr(start_brace + 1, end_brace - start_brace - 1);
        }
    }
    else if (start_angle != string::npos) {
       
        is_ordered = true;
        size_t end_angle = set_str.rfind('>');
        if (end_angle != string::npos) {
            content = set_str.substr(start_angle + 1, end_angle - start_angle - 1);
        }
    }
    else {
        return elements;
    }

    elements = parse_element(content);
    sort_set_elements(elements, is_ordered);

    return elements;
}

void parse_input(const string& line, SetCollection& collection) {
    size_t pos = 0;
    while (pos < line.size()) {
        size_t start_curly = line.find('{', pos);
        size_t start_angle = line.find('<', pos);

        size_t start;
        char open_char, close_char;

        if (start_curly != string::npos &&
            (start_angle == string::npos || start_curly < start_angle)) {
            start = start_curly;
            open_char = '{';
            close_char = '}';
        }
        else if (start_angle != string::npos) {
            start = start_angle;
            open_char = '<';
            close_char = '>';
        }
        else {
            break;
        }

        size_t end = start + 1;
        int balance = 1;
        while (end < line.size() && balance > 0) {
            if (line[end] == open_char) balance++;
            else if (line[end] == close_char) balance--;
            end++;
        }

        if (balance == 0) {
            string set_str = line.substr(start, end - start);
            collection.sets.push_back(parse_set(set_str));
            pos = end;
        }
        else {
            pos++;
        }
    }
}

string normalize_element(const string& elem) {
    if (!is_set(elem)) return elem;

    bool is_ordered = (elem.front() == '<');
    string content = elem.substr(1, elem.size() - 2);
    vector<string> nested_elements = parse_element(content);

    if (!is_ordered) {
        sort(nested_elements.begin(), nested_elements.end());
    }

    string result;
    result += is_ordered ? '<' : '{';
    for (size_t i = 0; i < nested_elements.size(); ++i) {
        if (i > 0) result += ",";
        result += normalize_element(nested_elements[i]);
    }
    result += is_ordered ? '>' : '}';

    return result;
}

bool elements_equal(const string& a, const string& b) {
    string norm_a = normalize_element(a);
    string norm_b = normalize_element(b);
    return norm_a == norm_b;
}

vector<string> symmetric_diff(const SetCollection& collection) {
    vector<pair<string, int>> elements_count;

    for (const auto& set : collection.sets) {
        for (const auto& elem : set) {
            auto it = find_if(elements_count.begin(), elements_count.end(),
                [&elem](const pair<string, int>& p) {
                    return elements_equal(p.first, elem);
                });
            if (it != elements_count.end()) it->second++;
            else elements_count.emplace_back(elem, 1);
        }
    }

    vector<string> result;
    for (const auto& p : elements_count) {
        if (p.second == 1) result.push_back(p.first);
    }

    return result;
}

void print_set(const vector<string>& elements) {
    cout << "{";
    for (size_t i = 0; i < elements.size(); i++) {
        if (i > 0) cout << ",";
        cout << elements[i];
    }
    cout << "}";
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetCollection collection;

    while (true) {
        cout << "\nМеню:\n1. Ввод множеств\n2. Просмотр\n3. Симметрическая разность\n4. Выход\nВыбор: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            cout << "Введите строку вида A = {1,2}, B = <2,{3,4}>, ...\n> ";
            string line;
            getline(cin, line);
            collection.sets.clear();
            parse_input(line, collection);
            cout << "Считано множеств: " << collection.sets.size() << endl;
            break;
        }
        case 2:
            for (size_t i = 0; i < collection.sets.size(); i++) {
                cout << "Множество " << (i + 1) << ": ";
                print_set(collection.sets[i]);
                cout << endl;
            }
            break;
        case 3:
            if (collection.sets.size() < 2) {
                cout << "Нужно минимум два множества!" << endl;
                break;
            }
            cout << "Симметрическая разность всех множеств: ";
            print_set(symmetric_diff(collection));
            cout << endl;
            break;
        case 4:
            return 0;
        default:
            cout << "Неверный выбор\n";
        }
    }
}
