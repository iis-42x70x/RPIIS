#include "Header.h"

int main() {
    string inputPath, outputPath;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1 - Open a file\n";
        cout << "2 - Show file contents\n";
        cout << "3 - Combine sets and show the result\n";
        cout << "0 - Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            openFile(inputPath);
            break;
        case 2:
            if (inputPath.empty()) {
                cout << "First create a file!" << endl;
            }
            else {
                vector<string> sets = readSets(inputPath);
                if (sets.empty()) {
                    cout << "File is empty or contains invalid sets!" << endl;
                }
                else {
                    cout << "File contents:" << endl;
                    for (size_t i = 0; i < sets.size(); i++) {
                        cout << "set" << (i + 1) << "=" << sets[i] << endl;
                    }
                }
            }
            break;
        case 3:
            if (inputPath.empty()) {
                cout << "First create a file!" << endl;
            }
            else {
                cout << "Enter the name of the output file (e.g., output.txt): ";
                cin >> outputPath;
                unionAllSets(inputPath, outputPath);
            }
            break;
        case 0:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 0);

    return 0;
}