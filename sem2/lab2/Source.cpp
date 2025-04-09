#include "sets.h"
int main() {
    string path;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1 - Create a file and open\n";
        cout << "2 - Enter sets\n";
        cout << "3 - Combine sets and show the result\n";
        cout << "0 - Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createFile(path);
            break;
        case 2:
            if (path.empty()) {
                cout << "First create a file (option 1)!" << endl;
            }
            else {
                inputSets(path);
            }
            break;
        case 3:
            if (path.empty()) {
                cout << "First create a file (option 1)!" << endl;
            }
            else {
                unionAllSets(path);
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