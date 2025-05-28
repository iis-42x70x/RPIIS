#include "Set.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int equal_str(const string& a, const string& b, int ap, int bp);

bool file_read(vector<string>& s1, vector<string>& s2) {
    s1.clear();
    s2.clear();

    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла!" << endl;
        return false;
    }

    int count = 0;
    string temp;

    while (getline(file, temp)) {
        int f1 = 0, f2 = 0;
        vector<string> s;

        string currentString;

        for (size_t i = 0; i < temp.size(); i++) {
            char ch = temp[i];
            char c = (i + 1 < temp.size()) ? temp[i + 1] : '\0';

            if (ch == ' ') continue;
            if (ch == '{') {
                f1++;
                if (c == ',' || c == '>') return false;
            }
            if (f1 == 0) continue;
            if ((ch >= 'a' && ch <= 'z') && (c >= 'a' && c <= 'z')) return false;
            if (ch == ',' && c == ',') return false;
            if (ch != '{' && ch != '}' && ch != '<' && ch != '>' && ch != ',' && !(ch >= 'a' && ch <= 'z')) return false;
            if (ch == '}') {
                f1--;
                if ((c >= 'a' && c <= 'z') || c == '<' || c == '{') return false;
            }
            if (ch == '<') {
                f2++;
                if (c == ',' || c == '}') return false;
            }
            if (ch == '>') {
                f2--;
                if ((c >= 'a' && c <= 'z') || c == '<' || c == '{') return false;
            }
            if (ch == ',' && (c == '}' || c == '>')) return false;
            if (f2 < 0) return false;
            if (f1 == 0) break;

            if ((f1 >= 2 || f2 >= 1) && ch != ',') {
                currentString += ch;
            } else if ((f1 == 1 && ch == '}') || (f2 == 0 && ch == '>')) {
                currentString += ch;
                s.push_back(currentString);
                currentString.clear();
            } else if (ch != ',' && !(ch == '{' && f1 == 1)) {
                currentString += ch;
                if (c == ',' || (c == '}' && f1 == 1)) {
                    s.push_back(currentString);
                    currentString.clear();
                }
            }
        }

        if (f1 != 0 || f2 != 0) return false;

        if (count == 0) {
            s1 = s;
        } else {
            s2 = s;
        }

        count++;
    }
    file.close();
    return true;
}

int eq_set(const string& a, const string& b, int ap, int bp) {

    vector<int> p;
    int b1 = 0, a1 = 0, a2 = 0;

    for (int i = bp; i < b.size() && b[i] != '\0'; i++) {
        if (b[i] == '{') {
            if (p.size() <= b1) p.push_back(i);
            else p[b1] = i;
            b1++;
        }
    }
    for (int i = ap; i < a.size() && a[i] != '\0'; i++) {
        if (a[i] == '{') a1++;
    }

    if (a1 != b1) return -1;

    int i;
    for (i = ap; i < a.size() && a[i] != '}'; i++) {
        if (a[i] == '{') {
            if (a2 >= p.size()) return -1;
            int level = eq_set(a, b, i + 1, p[a2] + 1);
            if (level == -1) return -1;
            a2++;
            i = level;
        }
        else if (a[i] == '<') {
            bool flag = false;
            int b2 = 0;
            for (int j = bp; j < b.size() && b2 >= 0; j++) {
                if (b[j] == '{') b2++;
                if (b[j] == '}') b2--;
                if (b[j] == '<' && b2 == 0) {
                    int result = equal_str(a, b, i + 1, j + 1);
                    if (result != -1) {
                        flag = true;
                        break;
                    }
                }
            }
            if (!flag) return -1;
        }
        else if(a[i] >= 'a' && a[i] <= 'z'){
            int b2 = 0;
            bool flag = false;
            for (int j = bp; j < b.size() && b2 >= 0; j++) {
                if (b[j] == '{') b2++;
                if (b[j] == '}') b2--;
                if (a[i] == b[j] && b2 == 0) {
                    flag = true;
                    break;
                }
            }
            if (!flag) return -1;
        }
    }

    if (i >= a.size() || a[i] != '}') return -1;

    return i;
}

int equal_str(const string& a, const string& b, int ap, int bp) {

    if (a.size() != b.size()) return -1;
    if (a[ap] != '{' && a[ap] != '<' && a == b) return ap + 1;

    int i;
    for (i = 0; ap+i < a.size() && a[ap+i] != '\0' && a[ap+i] != '>'; i++) {
        if (a[ap+i] == '{' && b[bp+i] == '{') {
            int result = eq_set(a, b, ap+i + 1, bp+i + 1);
            if (result == -1) return -1;
            i = result-ap;
        }
        else if (a[ap+i] == '<' && b[bp+i] == '<') {
            int result = equal_str(a, b, ap+i + 1, bp+i + 1);
            if (result == -1) return -1;
            i = result-ap;
        }
        else if (a[ap+i] != b[bp+i]) return -1;
    }

    if (i < a.size() && a[ap+i] == '>') return ap+i + 2;

    return ap+i;
}

void difference(vector<string>& s1, vector<string>& s2){
    vector <string> dif;
    bool exist=false;
    for (const auto& str1 : s1){
        bool flag=true;
        for (const auto& strd : dif){
            if (equal_str(str1,strd,0,0)!=-1){
                flag=false;
                break;
            }
        }
        if(flag){
            bool d=false;
            for (const auto& str2 : s2){
                if (equal_str(str1, str2,0,0)!=-1){
                    d=true;
                    break;
                }
            }
            if(!d){
                dif.push_back(str1);
                exist=true;
            }
        }
    }
    if (exist){
        cout << "Разность: { ";
        for (const auto& d : dif){
            cout << d << ", ";
        }
        cout << "}\n";
    }else{
        cout << "Разность-пустое множество.\n";
    }
}
