#include "pch.h"
#include <locale>
int main(int argc, char* argv[]) {
    string filename;
    if (argc > 1) filename = argv[1];
    else {
        while (true) {
            if (filename.empty()) {
                cout << "Enter file name: ";
                cin >> filename;
            }
            ifstream file(filename);
            if (file) {
                file.close();
                break;
            }
            cerr << "Error: we can't open this file. Try again\n";
            filename.clear();
        }
    }
    findAllCombinations(filename);
    cout << "You can see results in output.txt" << endl;
    return 0;
}