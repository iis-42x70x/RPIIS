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
    int balance = 0;
    for (char c : s) {
        if (c == '{' || c == '(') balance++;
        else if (c == '}' || c == ')') balance--;
        if (balance < 0) return false;
    }
    return balance == 0;
}


vector<string> parse_element(const string& element) {
    vector<string> result;
    string current;
    int depth = 0;

    for (char c : element) {
        if (c == '{' || c == '(') {
            depth++;
            current += c;
        }
        else if (c == '}' || c == ')') {
            depth--;
            current += c;
        }
        else if (c == ',' && depth == 0) {
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


vector<string> parse_set(const string& set_str) {
    vector<string> elements;
    string content;

   
    size_t start_brace = set_str.find('{');
    size_t end_brace = set_str.rfind('}');

    if (start_brace != string::npos && end_brace != string::npos) {
        content = set_str.substr(start_brace + 1, end_brace - start_brace - 1);
    }
    else {
        return elements;
    }

   
    elements = parse_element(content);

    return elements;
}

void parse_input(const string& line, SetCollection& collection) {
    size_t start = 0;
    while ((start = line.find('{', start)) != string::npos) {
        
        size_t end = start + 1;
        int balance = 1;
        while (end < line.size() && balance > 0) {
            if (line[end] == '{') balance++;
            else if (line[end] == '}') balance--;
            end++;
        }

        if (balance == 0) {
            string set_str = line.substr(start, end - start);
            collection.sets.push_back(parse_set(set_str));
            start = end;
        }
        else {
            break; 
        }
    }
}


bool elements_equal(const string& a, const string& b) {
    
    return a == b;
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
            cout << "Введите строку вида A = {1,2}, B = {2,{3,4}}, ...\n> ";
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