#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
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
    stack<char> brackets;
    for (char c : s) {
        switch (c) {
        case '{': case '<': case '(':
            brackets.push(c);
            break;
        case '}':
            if (brackets.empty() || brackets.top() != '{') return false;
            brackets.pop();
            break;
        case '>':
            if (brackets.empty() || brackets.top() != '<') return false;
            brackets.pop();
            break;
        case ')':
            if (brackets.empty() || brackets.top() != '(') return false;
            brackets.pop();
            break;
        }
    }
    return brackets.empty();
}


bool is_set(const string& s) {
    if (s.size() < 2) return false;
    return (s.front() == '{' && s.back() == '}') ||
        (s.front() == '<' && s.back() == '>') ||
        (s.front() == '(' && s.back() == ')');
}


vector<string> parse_element(const string& element) {
    vector<string> result;
    string current;
    stack<char> brackets;

    for (char c : element) {
        switch (c) {
        case '{': case '<': case '(':
            brackets.push(c);
            current += c;
            break;
        case '}': case '>': case ')':
            if (!brackets.empty()) brackets.pop();
            current += c;
            break;
        case ',':
            if (brackets.empty()) {
                trim(current);
                if (!current.empty()) {
                    result.push_back(current);
                }
                current.clear();
            }
            else {
                current += c;
            }
            break;
        default:
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
    if (set_str.empty() || !is_set(set_str)) return {};

    char open_char = set_str[0];
    char close_char;
    bool is_ordered = false;

    switch (open_char) {
    case '{': close_char = '}'; break;
    case '<': close_char = '>'; is_ordered = true; break;
    case '(': close_char = ')'; break;
    default: return {};
    }

    string content = set_str.substr(1, set_str.size() - 2);
    vector<string> elements = parse_element(content);
    sort_set_elements(elements, is_ordered);

    return elements;
}

// Проверка корректности ввода
bool validate_set_input(const string& line) {
    if (!is_balanced(line)) {
        return false;
    }


    bool in_set = false;
    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];

        if (c == '{' || c == '<' || c == '(') {
            in_set = true;
        }
        else if (c == '}' || c == '>' || c == ')') {
            in_set = false;
        }
        else if (c == ',') {
           
            if (i == 0 || i == line.size() - 1 ||
                line[i + 1] == '}' || line[i + 1] == '>' || line[i + 1] == ')') {
                return false;
            }
    
            if (i > 0 && line[i - 1] == ',') {
                return false;
            }
        }
    }

    return true;
}

void parse_input(const string& line, SetCollection& collection) {
    size_t pos = 0;
    while (pos < line.size()) {
        size_t start = line.find_first_of("{<(", pos);
        if (start == string::npos) break;

        char open_char = line[start];
        char close_char;
        switch (open_char) {
        case '{': close_char = '}'; break;
        case '<': close_char = '>'; break;
        case '(': close_char = ')'; break;
        default: pos++; continue;
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
            vector<string> set = parse_set(set_str);
            if (!set.empty()) {
                collection.sets.push_back(set);
            }
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
    vector<string> nested = parse_element(content);

    if (!is_ordered) {
        sort(nested.begin(), nested.end());
    }

    string result;
    result += elem.front();
    for (size_t i = 0; i < nested.size(); ++i) {
        if (i > 0) result += ",";
        result += normalize_element(nested[i]);
    }
    result += elem.back();

    return result;
}


bool elements_equal(const string& a, const string& b) {
    return normalize_element(a) == normalize_element(b);
}


vector<string> symmetric_diff(const SetCollection& collection) {
    vector<pair<string, int>> elements;

    for (const auto& set : collection.sets) {
        for (const auto& elem : set) {
            bool found = false;
            for (auto& p : elements) {
                if (elements_equal(p.first, elem)) {
                    p.second++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                elements.emplace_back(elem, 1);
            }
        }
    }

    vector<string> result;
    for (const auto& p : elements) {
        if (p.second == 1) {
            result.push_back(p.first);
        }
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

            if (!validate_set_input(line)) {
                cout << "Ошибка: некорректный ввод множеств!" << endl;
                break;
            }

            parse_input(line, collection);
            cout << "Считано множеств: " << collection.sets.size() << endl;
            break;
        }
        case 2:
            if (collection.sets.empty()) {
                cout << "Нет множеств для просмотра!" << endl;
                break;
            }
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
            cout << "Симметрическая разность: ";
            print_set(symmetric_diff(collection));
            cout << endl;
            break;
        case 4:
            return 0;
        default:
            cout << "Неверный выбор!" << endl;
        }
    }
}
