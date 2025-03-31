#include <iostream>
#include "Header.h"

using namespace std;

int main() {
    int var;
    cout << "Choose a file:\n1. set1.txt\n2. set2.txt\n3. set3.txt\n";
    cin >> var;
    string path;
    switch (var) {
    case 1:
        path = "set1.txt";
        break;
    case 2:
        path = "set2.txt";
        break;
    case 3:
        path = "set3.txt";
        break;
    default:
        cout << "Invalid varoice!\n";
        return 1;
    }

    vector<vector<string>> sets;

    open_and_sets(path, sets);

    vector<vector<pair<string, int>>> sets_counts = set_element_count(sets);
    vector<pair<string, int>> final_set = final_set_count(sets_counts);
    output(final_set);

    return 0;
}