#include <iostream>
#include "SetUnion.hpp"
#include <fstream>
#include <clocale>
#include <windows.h>

using namespace std;

string findInputFile(const string& filename) {
    // Check current directory
    ifstream test1(filename);
    if (test1.good()) return filename;

    // Check common paths
    vector<string> paths = {
        "../" + filename,
        "../../" + filename,
        "./data/" + filename
    };

    for (const auto& path : paths) {
        ifstream test(path);
        if (test.good()) return path;
    }

    return "";
}

int main() {
    setlocale(LC_ALL, "Russian");  // Для вывода
    SetConsoleCP(1251);            // Для ввода (если нужно)
    SetConsoleOutputCP(1251);      // Для вывода

    cout << "Programm for sets union\n";
    cout << "Allowed:\n";
    cout << "- Empty sets: {}\n";
    cout << "- Included sets: {{a,b},c}\n";
    cout << "- Tuples: <1,2>\n";
    cout << "- Numbers: 1, 42\n";
    cout << "- Names: a, b_2\n\n";

    string filename;
    while (true) {
        cout << "Enter file name (or 'exit' for exit): ";
        getline(cin, filename);

        if (filename == "exit") break;

        string foundPath = findInputFile(filename);
        if (foundPath.empty()) {
            cerr << "File '" << filename << "' is not found!\n\n";
            continue;
        }

        try {
            SetUnion setUnion;
            setUnion.performUnion(foundPath);

            set<string> result = setUnion.getUnionResult();
            if (result.empty()) {
                cout << "Result: {}\n\n";
            } else {
                cout << "Result of union:\n{";
                bool first = true;
                for (const auto& elem : result) {
                    if (!first) cout << ", ";
                    cout << elem;
                    first = false;
                }
                cout << "}\n\n";
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << "\n\n";
        }
    }

    return 0;
}
