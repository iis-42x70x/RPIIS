include <iostream>
#include <vector>
#include <string>

using namespace std;

enum ElementType { STRING, SET, ORSET };

struct SetElement {
    ElementType type;
    string strValue;
    vector<SetElement> setValue;
};

bool SpaceCheck(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r';
}

bool DigitCheck(char ch) {
    return (ch >= '0' && ch <= '9');
}

bool LetterCheck(const char& c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool EqualSets(const vector<SetElement>& setA, const vector<SetElement>& setB);
bool EqualOrsets(const vector<SetElement>& setA, const vector<SetElement>& setB);

bool operator==(const SetElement& a, const SetElement& b) {
    if (a.type != b.type) return false;
    if (a.type == STRING) return a.strValue == b.strValue;
    if (a.type == SET) return EqualSets(a.setValue, b.setValue);
    if (a.type == ORSET) return EqualOrsets(a.setValue, b.setValue);
    return false;
}

bool Contains(const vector<SetElement>& elems, const SetElement& elem) {
    for (const auto& el : elems) if (el == elem) return true;
    return false;
}

bool EqualSets(const vector<SetElement>& setA, const vector<SetElement>& setB) {
    if (setA.size() != setB.size()) return false;

    vector<bool> used(setB.size(), false);
    for (const auto& elA : setA) {
        bool found = false;
        for (int i = 0; i < setB.size(); i++) {
            if (!used[i] && (elA.type == setB[i].type)) {
                if ((elA.type == STRING && elA.strValue == setB[i].strValue) ||
                    (elA.type == SET && EqualSets(elA.setValue, setB[i].setValue)) ||
                    (elA.type == ORSET && EqualOrsets(elA.setValue, setB[i].setValue))) {
                    used[i] = true;
                    found = true;
                    break;
                }
            }
        }
        if (!found) return false;
    }

    return true;
}

bool EqualOrsets(const vector<SetElement>& setA, const vector<SetElement>& setB) {
    if (setA.size() != setB.size()) return false;
    for (int i = 0; i < setA.size(); i++) {
        if (!(setA[i] == setB[i])) return false;
    }

    return true;
}

SetElement ParsingSet(const string& s, int& pos);

SetElement ParsingElement(const string& str, int& pos) {
    while (pos < (int)str.size() && SpaceCheck(str[pos])) pos++;
    if (pos < str.size() && (str[pos] == '{' || str[pos] == '<')) return ParsingSet(str, pos);

    string token;
    while (pos < (int)str.size() && str[pos] != ',' && str[pos] != '}' && str[pos] != '>' && !SpaceCheck(str[pos])) {
        if ((str[pos] == '{' || str[pos] == '<') && !token.empty()) {
            cout << "Некорректный ввод!";
            exit(1);
        }
        token.push_back(str[pos]);
        pos++;
    }

    SetElement element;
    for (char ch : token) {
        if (!DigitCheck(ch) && !LetterCheck(ch) && ch != '_') {
            cout << "Некорректный ввод!";
            exit(1);
        }
    }
    element.type = STRING;
    element.strValue = token;

    return element;
}

SetElement ParsingSet(const string& str, int& pos) {
    SetElement result;
    char openChar = str[pos];
    char closeChar;

    if (openChar == '{') {
        closeChar = '}';
        result.type = SET;
    }
    else if (openChar == '<') {
        closeChar = '>';
        result.type = ORSET;
    }
    else {
        cout << "Некорректный ввод!";
        exit(1);
    }
    pos++;

    vector<SetElement> vec;
    while (pos < (int)str.size()) {
        while (pos < (int)str.size() && SpaceCheck(str[pos])) pos++;
        if (pos < (int)str.size() && str[pos] == closeChar) {
            pos++;
            break;
        }
        SetElement el = ParsingElement(str, pos);
        vec.push_back(el);
        while (pos < (int)str.size() && SpaceCheck(str[pos])) pos++;
        if (pos < (int)str.size() && str[pos] == ',') pos++;
    }
    result.setValue = vec;

    return result;
}

vector<SetElement> SymmetricDifferenceSet(const vector<SetElement>& setA, const vector<SetElement>& setB) {
    vector<SetElement> result;
    for (const auto& el : setA) {
        if (!Contains(setB, el)) result.push_back(el);
    }
    for (const auto& el : setB) {
        if (!Contains(setA, el)) result.push_back(el);
    }

    return result;
}

vector<SetElement> SymmetricDifferenceOrset(const vector<SetElement>& setA, const vector<SetElement>& setB) {
    vector<SetElement> result;
    int n = (setA.size() < setB.size() ? setA.size() : setB.size());
    for (int i = 0; i < n; i++) {
        if (!(setA[i] == setB[i])) {
            result.push_back(setA[i]);
            result.push_back(setB[i]);
        }
    }
    if (setA.size() > n) {
        for (int i = n; i < setA.size(); i++) result.push_back(setA[i]);
    }
    if (setB.size() > n) {
        for (int i = n; i < setB.size(); i++) {
            result.push_back(setB[i]);
        }
    }

    return result;
}

void printElement(const SetElement& el) {
    if (el.type == STRING) cout << el.strValue;
    else if (el.type == SET) {
        cout << "{";
        for (int i = 0; i < el.setValue.size(); i++) {
            printElement(el.setValue[i]);
            if (i < el.setValue.size() - 1) cout << ", ";
        } cout << "}";
    }
    else if (el.type == ORSET) {
        cout << "<";
        for (int i = 0; i < el.setValue.size(); i++) {
            printElement(el.setValue[i]);
            if (i < el.setValue.size() - 1) cout << ", ";
        } cout << ">";
    }
}

int main() {
    setlocale(LC_ALL, "RU");

    int n;
    cout << "Введите количество множеств: ";
    cin >> n;
    cin.ignore();

    if (n <= 0) {
        cout << "Количество множеств должно быть положительным" << endl;
        return 0;
    }

    vector<SetElement> Sets;
    for (int i = 0; i < n; i++) {
        cout << "Введите " << i + 1 << "-е множество (в формате {...} или <...>): ";
        string str;
        getline(cin, str);

        if (str.empty() || (str[0] != '{' && str[0] != '<')) {
            cout << "Некорректный ввод!";
            return 1;
        }
        if ((str[0] == '{' && str[str.size() - 1] != '}') ||
            (str[0] == '<' && str[str.size() - 1] != '>')) {
            cout << "Некорректный ввод!";
            return 1;
        }
        int bracket = 0;
        for (int j = 0; j < str.size(); j++) {
            if (j + 1 < str.size() && ((str[j] == '{' && str[j + 1] == ',') || (str[j] == '<' && str[j + 1] == ',') ||
                (str[j] == ',' && (str[j + 1] == '}' || str[j + 1] == '>')) || (str[j] == ',' && str[j + 1] == ',') ||
                (str[j] == '}' && str[j + 1] == '{') || (str[j] == '>' && str[j + 1] == '<'))) {
                cout << "Некорректный ввод!";
                return 1;
            }
            if (str[j] == '{' || str[j] == '<') bracket++;
            if (str[j] == '}' || str[j] == '>') bracket--;
        }
        if (bracket != 0) {
            cout << "Некорректный ввод!";
            return 1;
        }

        int pos = 0;
        SetElement curSet = ParsingSet(str, pos);
        while (pos < str.size() && SpaceCheck(str[pos])) pos++;
        if (pos != str.size()) {
            cout << "Некорректный ввод!";
            return 1;
        }
        Sets.push_back(curSet);
    }

    for (int i = 0; i < n; i++) {
        cout << i + 1 << "-е множество = "; printElement(Sets[i]); cout << endl;
    }

    if (Sets.empty() || (Sets[0].type != SET && Sets[0].type != ORSET)) {
        cout << "Некорректный ввод!" << endl;
        return 1;
    }

    for (int i = 1; i < Sets.size(); i++) {
        if (Sets[i].type != Sets[0].type) {
            cout << "Некорректный ввод! Все множества должны быть либо ориентированными, либо неориентированными." << endl;
            return 1;
        }
    }

    vector<SetElement> result = Sets[0].setValue;
    for (int i = 1; i < n; i++) {
        if (Sets[0].type == ORSET) result = SymmetricDifferenceOrset(result, Sets[i].setValue);
        else result = SymmetricDifferenceSet(result, Sets[i].setValue);
    }

    cout << "Симметрическая разность = ";
    if (Sets[0].type == ORSET) cout << "<";
    else cout << "{";
    if (result.empty()) cout << "пустое множество";
    else {
        for (int i = 0; i < result.size(); i++) {
            printElement(result[i]);
            if (i < result.size() - 1) cout << ", ";
        }
    }
    if (Sets[0].type == ORSET) cout << ">";
    else cout << "}";

    return 0;
}
