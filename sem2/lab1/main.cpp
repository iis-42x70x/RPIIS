#include "Tree.h"

int main() {
    int n;

    cout << "=============================" << endl;
    cout << "          TREE DEMO          " << endl;
    cout << "=============================" << endl;

    
    do {
        cout << "Enter the size of the array (positive integer): ";
        cin >> n;

        if (cin.fail() || n <= 0) {
            cout << "Invalid input. Please enter a positive integer." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    } while (n <= 0);

    int* initialValues = new int[n];
    cout << "Enter the array elements (space-separated integers):" << endl;

    for (int i = 0; i < n; i++) {
        while (true) {
            cin >> initialValues[i];
            if (cin.fail()) {
                cout << "Invalid input. Please enter an integer: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }
    }

    Node* root = buildTree(0, n - 1, initialValues);

    int l, r, val;

    cout << "\n=============================" << endl;
    cout << "        MODIFY TREE          " << endl;
    cout << "=============================" << endl;

    while (true) {
        cout << "Enter the range [l, r] (0-indexed) and value to add (e.g., 1 3 5): ";
        cin >> l >> r >> val;

        if (cin.fail() || l < 0 || r >= n || l > r) {
            cout << "Invalid input. Ensure 0 <= l <= r < " << n  << " and enter integers." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }

    modify(root, l, r, val);

    int* updatedValues = new int[n];
    collectValues(root, 0, n - 1, updatedValues);

    cout << "\nUpdated array after modification:" << endl;
    for (int i = 0; i < n; i++) {
        cout << updatedValues[i] << " ";
    }
    cout << endl;

    cout << "\n=============================" << endl;
    cout << "         QUERY MAXIMUM       " << endl;
    cout << "=============================" << endl;

    while (true) {
        cout << "Enter the range [l, r] (0-indexed) to query the maximum value: ";
        cin >> l >> r;

        if (cin.fail() || l < 0 || r >= n || l > r) {
            cout << "Invalid input. Ensure 0 <= l <= r < " << n << " and enter integers." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }

    cout << "\nResult:" << endl;
    cout << "Maximum value in range [" << l << ", " << r << "]: " << query(root, l, r, 0) << endl;

    delete[] initialValues;
    delete[] updatedValues;

    cout << "\n=============================" << endl;
    cout << "      PROGRAM COMPLETED      " << endl;
    cout << "=============================" << endl;

    return 0;
}
