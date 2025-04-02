#include "element.hpp"
#include <iostream>

int main() {
    int numSets;
    std::cout << "Введите количество множеств: ";
    std::cin >> numSets;

    Element** sets = new Element*[numSets];
    int* counts = new int[numSets];

    for (int i = 0; i < numSets; i++) {
        std::cout << "Множество " << i+1 << ":\n";
        sets[i] = readSet(counts[i]);
    }

    int resultCount;
    Element* result = calculateSymmetricDifference(sets, counts, numSets, resultCount);

    std::cout << "Симметрическая разность всех множеств: {";
    for (int i = 0; i < resultCount; i++) {
        printElement(result[i]);
        if (i < resultCount - 1) std::cout << ", ";
    }
    std::cout << "}\n";

    // Освобождение памяти
    for (int i = 0; i < numSets; i++) {
        delete[] sets[i];
    }
    delete[] sets;
    delete[] counts;
    delete[] result;

    return 0;
}
