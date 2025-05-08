
#include "Header.h"

bool Parentheses(const string& input) {
    vector<char> stack;
    for (char c : input) {
        if (c == '{' || c == '<' || c == '(') stack.push_back(c);
        else if (c == '}' || c == '>' || c == ')') {
            if (stack.empty()) return false;
            char openBracket = stack.back();
            stack.pop_back();
            if ((c == '}' && openBracket != '{') ||
                (c == '>' && openBracket != '<') ||
                (c == ')' && openBracket != '(')) return false;
        }
    }
    return stack.empty();
}

bool Check_symbols(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || c == '{' || c == '}' ||
        c == '<' || c == '>' || c == '(' || c == ')' ||
        c == ',' || c == ' ';
}

bool check(const string& input) {
    for (char c : input) {
        if (!Check_symbols(c)) {
            cerr << "Error: invalid character \"" << c << "\"" << endl;
            return false;
        }
    }
    return Parentheses(input);
}

int Add(vector<string>& Set, const string& input_str) {
    string currentElement;
    int braceCount = 0, angleCount = 0, roundCount = 0;

    for (char s : input_str) {
        if (s == '{') braceCount++;
        else if (s == '}') braceCount--;
        else if (s == '<') angleCount++;
        else if (s == '>') angleCount--;
        else if (s == '(') roundCount++;
        else if (s == ')') roundCount--;

        if (s == ',' && braceCount == 0 && angleCount == 0 && roundCount == 0) {
            if (!currentElement.empty()) {
                Set.push_back(currentElement);
                currentElement.clear();
            }
        }
        else {
            currentElement.push_back(s);
        }
    }

    if (!currentElement.empty()) Set.push_back(currentElement);
    return (braceCount == 0 && angleCount == 0 && roundCount == 0) ? 0 : 1;
}

int Duplicate(const vector<string>& set) {
    for (size_t i = 0; i < set.size(); i++) {
        for (size_t j = i + 1; j < set.size(); j++) {
            if (set[i] == set[j]) {
                cerr << "Error: duplicate element \"" << set[i] << "\"" << endl;
                return 1;
            }
        }
    }
    return 0;
}



void Generate_Boolean(const vector<string>& set, vector<vector<string>>& boolean,
    vector<string>& el_of_boolean, int index) {
    boolean.push_back(el_of_boolean);
    for (size_t i = index; i < set.size(); i++) {
        el_of_boolean.push_back(set[i]);
        Generate_Boolean(set, boolean, el_of_boolean, i + 1);
        el_of_boolean.pop_back();
    }
}

void RemoveOuterBraces(string& line) {
    if ((line.front() == '{' && line.back() == '}') ||
        (line.front() == '<' && line.back() == '>')) {
        line = line.substr(1, line.size() - 2);
    }
}

void ProcessSetFromString(const string& input, vector<vector<string>>& result) {
    string noSpaces;
    for (char c : input) if (c != ' ') noSpaces += c;

    size_t equalPos = noSpaces.find('=');
    string line = (equalPos != string::npos) ? noSpaces.substr(equalPos + 1) : noSpaces;

    if (!check(line)) {
        cerr << "Structure error: " << line << endl;
        return;
    }

    RemoveOuterBraces(line);
    vector<string> set;
    vector<string> el_of_boolean;

    if (Add(set, line) || Duplicate(set)) return;
    Generate_Boolean(set, result, el_of_boolean, 0);
}
