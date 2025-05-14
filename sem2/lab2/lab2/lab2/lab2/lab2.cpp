#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "func.hpp"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");

    int k = 0;
    while (k <= 0) {
        wall();
        cout << "Введите количество множеств: ";
        cin >> k;
        wall();
        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); k = 0; }
        if (k <= 0) cout << "Ошибка: требуются положительное число.\n";
    }
    cin.ignore();

    vector<string> raw_inputs;

    for (int i = 0; i < k; ++i) {
        string line;
        bool ok = false;
        while (!ok) {
            cout << "Введите множество (A = {a,b,{c}}): ";
            getline(cin, line);
            wall();
            size_t eq = line.find('='), l = line.find('{'), r = line.rfind('}');
            ok = (eq != string::npos && l != string::npos && r != string::npos && r > l);
            if (!ok) cout << "Ошибка формата.\n";
        }

        string inside = line.substr(line.find('{') + 1,
            line.rfind('}') - line.find('{') - 1);
        raw_inputs.push_back(inside);
    }

    map<string, int> common = intersect_sets(raw_inputs);

    if (common.empty()) cout << "S = ∅\n";
    else {
        cout << "S = {";
        bool first = true;
        for (auto& p : common)
            for (int c = 0; c < p.second; ++c) {
                if (!first) cout << ", ";
                cout << p.first;
                first = false;
            }
        cout << "}\n";
    }
    wall();
    return 0;
}