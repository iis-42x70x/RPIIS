#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool Permutation(vector<string>&);
void CreatePermutations(vector<string>&);
vector<string> Fragmentation(string&);
bool CheckStr(const string&);
string NotSpace(string&);
int main() {
    setlocale(LC_ALL, "RU");
    string str;
    cout << "Введите неориентированноt множество: ";
    getline(cin, str);
    str = NotSpace(str);
    if (!CheckStr(str)) {
        return 0;
    }
    cout << "\nВсе возможные ориентированные множества:\n";
    vector<string> a = Fragmentation(str);
    CreatePermutations(a);
    return 0;
}
bool Permutation(vector<string>& elements) {
    int n = elements.size();
    int i = n - 2;
    while (i >= 0 && elements[i] >= elements[i + 1]) {
        i--;
    }
    if (i < 0) {
        return false;
    }
    int j = n - 1;
    while (elements[j] <= elements[i]) {
        j--;
    }
    swap(elements[i], elements[j]);
    reverse(elements.begin() + i + 1, elements.end());
    return true;
}
void CreatePermutations(vector<string>& elements) {
    sort(elements.begin(), elements.end());
    int count = 1;
    do {
        cout << count++ << ": <";
        for (size_t i = 0; i < elements.size(); ++i) {
            cout << elements[i];
            if (i != elements.size() - 1) cout << ", ";
        }
        cout << ">" << endl;
    } while (Permutation(elements));
}
vector<string> Fragmentation(string& str) {
    if (str.front() == '{' && str.back() == '}') {
        str = str.substr(1, str.size() - 2);
    }
    vector<string> el;
    int col = 0;
    string s;
    for (char c : str) {
        if (c == '{' || c == '<') col++;
        if (c == '}' || c == '>') col--;
        if (c == ',' && col == 0) {
            if (!s.empty()) {
                el.push_back(s);
                s.clear();
            }
        }
        else {
            s += c;
        }
    }
    if (!s.empty()) {
        el.push_back(s);
    }
    return el;
}
string NotSpace(string& str) {
    string newstr = "";
    for (char el : str) {
        if (el != ' ') {
            newstr += el;
        }
    }
    return newstr;
}
bool CheckStr(const string& str) {
    if (str.empty()) {
        cout << "Ошибка: не введено ни одного элемента" << endl;
        return false;
    }
    int col1 = 0;
    int col2 = 0;
    int size = str.size();
    for (int i = 0; i < size; i++) {
        if (str[i] == '{') col1++;
        if (str[i] == '<') col2++;
        if (str[i] == '}') col1--;
        if (str[i] == '>') col2--;
        if (i > 0 && (str[i] == '{' || str[i] == '<') && (str[i - 1] != '{' && str[i - 1] != '<' && str[i - 1] != ',')) {
            cout << "Ошибка: перед '{' и '<' не может стоять ничего кроме  '{', '<' и ','\n";
            return false;
        }
        if (i < size - 2 && (str[i] == '}' || str[i] == '>') && (str[i + 1] != '}' && str[i + 1] != '>' && str[i + 1] != ',')) {
            cout << "Ошибка: после '}' и '>' не может стоять ничего кроме  '}', '>' и ','\n";
            return false;
        }
    }
    if (col1) {
        cout << "Ошибка: количество '{' отличается от '}'\n" << endl;
        return false;
    }
    if (col2) {
        cout << "Ошибка: количество '<' отличается от '>'\n" << endl;
        return false;
    }
    return true;
}
