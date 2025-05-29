#include "Header.h"

int main() {
    setlocale(LC_ALL, "Russian");
    SetElement mySet = inputSet();

    cout << "\nВведенное множество: ";
    printSet(mySet);
    cout << endl;

    vector<char> elements;
    collectElements(mySet, elements);

    sort(elements.begin(), elements.end());
    elements.erase(unique(elements.begin(), elements.end()), elements.end());

    cout << "\nУникальные элементы: ";
    for (char el : elements) cout << el << " ";
    cout << endl;

    int total_elements = countElements(mySet);
    cout << "\nОбщее количество элементов: " << total_elements << endl;

    int n = inputDimension(elements.size());

    vector<vector<char>> combinations;
    vector<char> current;
    generateCombinations(elements, n, current, 0, combinations);

    cout << "\nВсе множества размера " << n << ":\n";
    for (const auto& combo : combinations) {
        cout << "{";
        for (size_t i = 0; i < combo.size(); ++i) {
            if (i > 0) cout << ",";
            cout << combo[i];
        }
        cout << "}\n";
    }

    cout << "\nВсего множеств: " << combinations.size() << endl;

    return 0;
}