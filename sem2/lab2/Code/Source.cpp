#include "Header.h"

string removeSpaces(const string& s) {
    string result;
    for (char c : s) {
        if (!isspace(c)) result += c;
    }
    return result;
}

SetElement parseSet(istringstream& iss) {
    SetElement result;
    result.is_subset = true;

    char ch;
    while (iss >> ch) {
        if (ch == '}') break;
        else if (ch == '{') {
            result.subset.push_back(parseSet(iss));
        }
        else if (isalpha(ch)) {
            result.subset.push_back({ false, ch, {} });
        }
    }
    return result;
}

SetElement inputSet() {
    cout << "Введите множество (пример: {A,B,{C,D,{E,F},G}}): ";
    string input;
    getline(cin, input);

    istringstream iss(removeSpaces(input));
    char first;
    iss >> first;

    if (first != '{') {
        cerr << "Ошибка: должно начинаться с '{'\n";
        exit(1);
    }

    return parseSet(iss);
}

void collectElements(const SetElement& set, vector<char>& elements) {
    if (!set.is_subset) {
        elements.push_back(set.value);
        return;
    }
    for (const auto& el : set.subset) {
        collectElements(el, elements);
    }
}

int countElements(const SetElement& set) {
    if (!set.is_subset) return 1;
    int count = 0;
    for (const auto& el : set.subset) {
        count += countElements(el);
    }
    return count;
}

void generateCombinations(const vector<char>& elements, int k,
    vector<char>& current, int start,
    vector<vector<char>>& result) {
    if (current.size() == k) {
        result.push_back(current);
        return;
    }

    for (int i = start; i < elements.size(); ++i) {
        current.push_back(elements[i]);
        generateCombinations(elements, k, current, i + 1, result);
        current.pop_back();
    }
}

void printSet(const SetElement& set) {
    if (!set.is_subset) {
        cout << set.value;
        return;
    }
    cout << "{";
    for (size_t i = 0; i < set.subset.size(); ++i) {
        if (i > 0) cout << ",";
        printSet(set.subset[i]);
    }
    cout << "}";
}

int inputDimension(int max_dimension) {
    int n;
    while (true) {
        cout << "\nВведите размерность множеств (n): ";
        cin >> n;
        if (cin.fail() || n <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: введите положительное число\n";
        }
        else if (n > max_dimension) {
            cout << "Ошибка: размерность не может превышать " << max_dimension << "\n";
        }
        else {
            break;
        }
    }
    return n;
}