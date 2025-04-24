#include "Lab2_set_2.0_tests.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    try {
        const string sourceFile = "source.txt";
        const string resultFile = "result.txt";
        // Чтение из файла
        vector<vector<SetOperations::Element>> sets = SetOperations::readSetsFromFile(sourceFile);

        if (sets.empty()) {
            cout << "No sets found in the input file." << endl;
            return 0;
        }

        // Нахождение персечения
        vector<SetOperations::Element> intersection = SetOperations::findIntersection(sets);

        // Запись результата в файл
        SetOperations::writeIntersectionToFile(intersection, resultFile);

        cout << "Intersection calculated and written to result.txt" << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}