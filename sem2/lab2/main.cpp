#include "pch.h"

using namespace std;


int main(int argc, char** argv) {
    setlocale(LC_ALL, "");
    vector<SetElement> elements = ReadFromFile();
    
        int n;
        cout << "Введите размер подмножеств: ";
        cin >> n;
    
        if (n > elements.size() || n < 0) {
            cout << "Некорректный размер подмножества.\n";
            return 1;
        }
    vector<vector<SetElement>> subsets;
    vector<SetElement> current;
    GenerateCombinations(elements, n, 0, current, subsets);

    cout << "Все неупорядоченные подмножества размера " << n << ":\n";
    for (const auto& subset : subsets) {
        PrintSet(subset);
    }
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}