#include "header.h"


vector<string> parseElements(const string& element) {
    vector<string> elements;
    if (element.empty() || element.size() < 2) return elements;

    int depth = 0;
    size_t start = 1;

    for (size_t i = 1; i < element.size() - 1; ++i) {
        char c = element[i];
        if (c == '{' || c == '<') depth++;
        else if (c == '}' || c == '>') depth--;

        if (depth == 0 && c == ',') {
            string elem = element.substr(start, i - start);
            elem.erase(0, elem.find_first_not_of(" \t"));
            elem.erase(elem.find_last_not_of(" \t") + 1);
            if (!elem.empty()) elements.push_back(elem);
            start = i + 1;
        }
    }

    string lastElem = element.substr(start, element.size() - 1 - start);
    lastElem.erase(0, lastElem.find_first_not_of(" \t"));
    lastElem.erase(lastElem.find_last_not_of(" \t") + 1);
    if (!lastElem.empty()) elements.push_back(lastElem);

    return elements;
}

string normalizeElement(const string& elem) {
    if (elem.empty()) return "";

    if (elem.front() == '<' && elem.back() == '>') {
        vector<string> inner = parseElements(elem);
        for (auto& e : inner) {
            e = normalizeElement(e);
        }

        string res = "<";
        for (size_t i = 0; i < inner.size(); ++i) {
            if (i > 0) res += ",";
            res += inner[i];
        }
        res += ">";
        return res;
    }
    else if (elem.front() == '{' && elem.back() == '}') {
        vector<string> inner = parseElements(elem);
        vector<string> normalized;

        for (auto& e : inner) {
            string norm = normalizeElement(e);


            bool is_duplicate = false;
            for (const string& item : normalized) {
                if (item == norm) {
                    is_duplicate = true;
                    break;
                }
            }

            if (!is_duplicate) {
                normalized.push_back(norm);
            }
        }

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
        for (size_t i = 0; i < normalized.size(); ++i) {
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

void symmetricDifference(const char* set1, const char* set2, char* result) {
    string s1(set1), s2(set2);

    auto elems1 = parseElements(s1);
    auto elems2 = parseElements(s2);

    vector<string> normalized1, normalized2;
    for (const auto& elem : elems1) {
        normalized1.push_back(normalizeElement(elem));
    }
    for (const auto& elem : elems2) {
        normalized2.push_back(normalizeElement(elem));
    }

    vector<string> diff;

    for (const auto& elem1 : normalized1) {
        bool found = false;
        for (const auto& elem2 : normalized2) {
            if (elem1 == elem2) {
                found = true;
                break;
            }
        }
        if (!found) {
            diff.push_back(elem1);
        }
    }
    for (const auto& elem2 : normalized2) {
        bool found = false;
        for (const auto& elem1 : normalized1) {
            if (elem2 == elem1) {
                found = true;
                break;
            }
        }
        if (!found) {
            diff.push_back(elem2);
        }
    }

    string res = "{";
    for (size_t i = 0; i < diff.size(); ++i) {
        if (i > 0) res += ",";
        res += diff[i];
    }
    res += "}";
    strcpy(result, res.c_str());
}

bool isValidSet(const char* line) {
    int braces = 0, angles = 0;
    bool prev_comma = false;
    for (; *line; ++line) {
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
            case '<': angles++; break;
            case '>': angles--; break;
        }
        if (braces < 0 || angles < 0) return false;
    }
    return braces == 0 && angles == 0;
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
            cout << "Слишком большое количество множеств\n" << endl;
            return -1;
        }
        if (isValidSet(line)) {
            strcpy(sets[setCount], line);
            setCount++;
        }
        else {
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
        cout << "\nМеню:\n1.Просмотр\n2.Добавить\n3.Сохранить\n4.Пересечение\n5.Выход\nВыбор: ";
        int choice; cin >> choice; cin.ignore();

        if (choice == 1) {
            for (int i = 0; i < setCount; ++i) {
                string normalized = normalizeElement(sets[i]);
                cout << "Множество " << i + 1 << ": " << normalized << endl;
            }
        }
        else if (choice == 2) {
            char newSet[MAX_LINE_LENGTH];
            cout << "Введите мн-во: ";
            cin.getline(newSet, MAX_LINE_LENGTH);
            if (isValidSet(newSet)) {
                strcpy(sets[setCount], newSet);
                setCount++;
                cout << "Добавлено!\n" << endl;
            }
            else {
                cout << "Некорректный ввод\n" << endl;
            }


        }
        else if (choice == 3) {
            writeSets(filename, sets, setCount);
            cout << "Cохранено -_-\n" << endl;
        }
        else if (choice == 4) {
            if (setCount < 2) {
                cout << "Для выполнения операции необходим минимум 2 множества!" << endl;
                continue;
            }
            int a, b;
            cout << "Введите номера множеств: "; cin >> a >> b; cin.ignore();
            if (a < 1 || a > setCount || b < 1 || b > setCount) {
                cout << "Некоректные номера!" << endl;
                continue;
            }
            if (a == b) {
                cout << "Пустое множество" << endl;
                continue;
            }
            char res[MAX_LINE_LENGTH];
            symmetricDifference(sets[a - 1], sets[b - 1], res);
            string normalizedRes = normalizeElement(res);
            cout << "Результат: " << normalizedRes << endl;
        }
        else if (choice == 5) {
            break;
        }
    }
}