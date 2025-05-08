#define _CRT_SECURE_NO_WARNINGS
#include "header.h"         // добавить сортировку

vector<string> parseElements(const string& element) {       // делит строку на элементы вектора через ,
    vector<string> elements;
    if (element.empty() || element.size() < 2) return elements;

    int depth = 0, start = 1;

    for (int i = 1; i < element.size() - 1; i++) {
        char c = element[i];
        if (c == '{' || c == '<') depth++;
        else if (c == '}' || c == '>') depth--;

        if (depth == 0 && c == ',') {
            string elem = element.substr(start, i - start);
            elem.erase(0, elem.find_first_not_of(" \t"));
            elem.erase(elem.find_last_not_of(" \t") + 1);
            if (!elem.empty()) 
                elements.push_back(elem);
            start = i + 1;
        }
    }

    string lastElem = element.substr(start, element.size() - 1 - start);
    lastElem.erase(0, lastElem.find_first_not_of(" \t"));
    lastElem.erase(lastElem.find_last_not_of(" \t") + 1);
    if (!lastElem.empty()) 
        elements.push_back(lastElem);

    return elements;
}

string normalizeElement(const string& elem) {       // приводит строку в приличный вид
    if (elem.empty()) return "";

    if (elem.front() == '<' && elem.back() == '>') {
        vector<string> inner = parseElements(elem);
        for (auto& it : inner) {
            it = normalizeElement(it);
        }

        string res = "<";
        for (int i = 0; i < inner.size(); ++i) {
            if (i > 0) res += ",";
            res += inner[i];
        }
        res += ">";
        return res;
    }
    else if (elem.front() == '{' && elem.back() == '}') {
        vector<string> inner = parseElements(elem);
        vector<string> normalized; 

        for (auto& it : inner)
            normalized.push_back(normalizeElement(it));

        sort(normalized.begin(), normalized.end(), [](const string& a, const string& b) {
            char first_a = a.front();
            char first_b = b.front();

            if (first_a == first_b) return a < b;
            if (first_a == '{') return false;
            if (first_b == '{') return true;
            if (first_a == '<') return false;
            if (first_b == '<') return true;
            return a < b; 
        });

        if (normalized.size() == 1) {
            return normalized[0];
        }

        string result = "{";
        for (int i = 0; i < normalized.size(); i++) {
            if (i > 0) result += ",";
            result += normalized[i];
        }
        result += "}";
        return result;
    }
    else {
        string simple = elem;
        simple.erase(remove_if(simple.begin(), simple.end(), ::isspace), simple.end());
        return simple;
    }
}

void Difference(const char* set1, const char* set2, char* res) {
    string s1(set1), s2(set2);

    auto elems1 = parseElements(s1);
    auto elems2 = parseElements(s2);

    vector<string> norm1, norm2;
    for (const auto& el : elems1) 
        norm1.push_back(normalizeElement(el));
    for (const auto& el : elems2) 
        norm2.push_back(normalizeElement(el));
    
    vector<string> diff;
    for(int i = 0; i < norm1.size(); i++) {
        bool wasFound = false;
        for (int j = 0; j < norm2.size(); j++) 
            if(norm1[i] == norm2[j]) {
                wasFound = true;
                norm2[j] = "_";
                break;
            }
        if(!wasFound)
            diff.push_back(norm1[i]);
    }
    
    string temp = "{";
    for (int i = 0; i < diff.size(); ++i) {
        if (i > 0) temp += ",";
        temp += diff[i];
    }
    temp += "}";
    normalizeElement(temp);
    strcpy(res, temp.c_str());
}

bool isValidSet(const char* line) {
    int braces = 0, arrows = 0;
    bool prev_comma = false;
    for (; *line; line++) { 
        if (*line == ',') {
            if (prev_comma) return false;
            prev_comma = true;
        }
        else if (!isspace(*line)) { 
            prev_comma = false;
        }
        switch (*line) {
        case '{': braces++; break;
        case '}': braces--; break;
        case '<': arrows++; break;
        case '>': arrows--; break;
        }
        if (braces < 0 || arrows < 0) return false;
    }
    return braces == 0 && arrows == 0;
}

int readSets(const char* filename, char sets[MAX_SETS][MAX_LINE_LENGTH], int& setCount) {
    ifstream file(filename);
    if (!file) {
        cout <<"Файл не найден\n" << filename << endl;
        return -1;
    }

    setCount = 0;
    char line[MAX_LINE_LENGTH];
    while (file.getline(line, MAX_LINE_LENGTH)) {
        if (setCount >= MAX_SETS) {
            cout << "Слишком большое кол-во мн-в\n\n";
            return -1;
        }
        if (isValidSet(line)) {
            strcpy(sets[setCount], line);
            setCount++;
        }
        else {
            cout << "Что-то явно не так\n\n";
            return -1;
        }
    }
    return 0;
}

void writeSets(const char* filename, char sets[MAX_SETS][MAX_LINE_LENGTH], int setCount) {
    ofstream file(filename);
    if (!file) {
        return;
    }
    for (int i = 0; i < setCount; ++i)
        file << sets[i] << endl;
}

void menu(const char* filename) {
    char sets[MAX_SETS][MAX_LINE_LENGTH];
    int setCount = 0;
    if (readSets(filename, sets, setCount) != 0) return;

    while (true) {
        cout << "\nМеню:\n"
                "1.Просмотр\n"
                "2.Добавить\n"
                "3.Разность\n"
                "0.Выход\n"
                "Введите число: ";
        int whatToDo; cin >> whatToDo; cin.ignore();

        if (whatToDo == 1) {
            for (int i = 0; i < setCount; i++) {
                string normalized = normalizeElement(sets[i]);
                cout << i + 1 << ". " << normalized << endl;
            }
        }
        else if (whatToDo == 2) {
            char newSet[MAX_LINE_LENGTH];
            cout << "Введите мн-во: ";
            cin.getline(newSet, MAX_LINE_LENGTH);
            if (isValidSet(newSet)) {
                strcpy(sets[setCount], newSet);
                setCount++;
                writeSets(filename, sets, setCount);
                cout << "Добавлено!\n" << endl;
            }
            else {
                cout << "Некорректный ввод\n" << endl;
            }
        }
        else if (whatToDo == 3) {
            int a, b;
            cout << "Введите номера множеств: ";    cin >> a >> b;  cin.ignore();
            if (a < 1 || a > setCount || b < 1 || b > setCount) {
                cout << "Нет таких\n" << endl;
                continue;
            }

            char res[MAX_LINE_LENGTH];
            Difference(sets[a - 1], sets[b - 1], res);
            string normRes = normalizeElement(res);
            cout << "Разность: " << normRes << endl;
        }
        else if (whatToDo == 0) {
            break;
        }
    }
}