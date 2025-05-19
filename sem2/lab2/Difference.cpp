#include "Difference.h"
#include <iostream>
Set::Set(string file) {
    int multiplicity;
    char element;
    vector<pair<int, char>> temp;
    ifstream fin(file);
    string line;
    while (getline(fin, line)) {
        istringstream iss(line); // ������� ��������� ����� �� ������� ������
        temp.clear();


        while (iss >> multiplicity >> element) {
            temp.push_back(make_pair(multiplicity, element));
        }
        SETS.push_back(temp);
    }
    fin.close();
}
vector<pair<int, char>> Set::SetDifference(int polarity) {
    int uno;
    int dos;
    if (polarity == 1) {
        uno = 0;
        dos = 1;
    }
    else {
        uno = 1;
        dos = 0;
    }
    switch (polarity) {
    default: {
        cout << "There is no such option." << '\n';
        return result;
        break;
    }
    case 1:
    case 2: {
        for (int i = 0; i < SETS[uno].size(); i++) {

            for (int j = 0; j < SETS[dos].size(); j++) {

                if (SETS[uno][i].second == SETS[dos][j].second) {

                    if (SETS[uno][i].first > SETS[dos][j].first) {

                        result.push_back(make_pair(SETS[uno][i].first - SETS[dos][j].first, SETS[uno][i].second));
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    if (j == SETS[dos].size() - 1 && SETS[uno][i].second != SETS[dos][j].second) {
                        result.push_back(make_pair(SETS[uno][i].first, SETS[uno][i].second));
                    }
                }
            }
        }
        return result;
    }
    }
}
void Set::PrintSet(int ordinalNumber) {
    switch (ordinalNumber) {
    default: {
        cout << "Set with ordinal number you've entered doesnt exist!" << '\n';
        exit(0);
        break;
    }
    case 1:
    case 2: {

        for (int i = 0; i < SETS[ordinalNumber - 1].size(); i++) {
            cout << SETS[ordinalNumber - 1][i].first << SETS[ordinalNumber - 1][i].second << " ";
        }
        cout << "\n\n";
    }
    }
}
void Set::PrintDifference() {
    for (int i = 0; i < result.size(); i++) {
        cout << result[i].first << result[i].second << " ";
    }
    result.clear();
    cout << "\n\n";
}