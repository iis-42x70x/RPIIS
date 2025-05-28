/***********************************************************************************************************************
Название: Симметрическая разность множеств с учётом кратных вхождений
Разработчик: Перерва Павло Дмитриевич
Дата: 01.05.2025
Описание: программа читает из файла произвольное количество множеств и вычисляет их симметрическую разность.
Симметрическая разность множеств - это множество элементов, которые встречаются в нечётном количестве исходных множеств.
Программа обрабатывает как уникальные, так и кратные вхождения элементов
***********************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

const char* input_filename = "input.txt";
const char* output_filename = "output.txt";

struct IntSet {
    int* elements;
    int size;
};

bool readSetsFromFile(const char* filename, IntSet** sets, int* setCount) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    if (!(file >> *setCount) || *setCount <= 0) {
        file.close();
        return false;
    }

    *sets = (IntSet*)malloc(*setCount * sizeof(IntSet));
    if (*sets == nullptr) {
        file.close();
        return false;
    }

    for (int i = 0; i < *setCount; i++) {
        int k;
        if (!(file >> k) || k < 0) {
            for (int j = 0; j < i; j++) {
                free((*sets)[j].elements);
            }
            free(*sets);
            file.close();
            return false;
        }

        (*sets)[i].size = k;
        (*sets)[i].elements = (int*)malloc(k * sizeof(int));
        if (k > 0 && (*sets)[i].elements == nullptr) {
            for (int j = 0; j < i; j++) {
                free((*sets)[j].elements);
            }
            free(*sets);
            file.close();
            return false;
        }

        for (int j = 0; j < k; j++) {
            if (!(file >> (*sets)[i].elements[j])) {
                free((*sets)[i].elements);
                for (int m = 0; m < i; m++) {
                    free((*sets)[m].elements);
                }
                free(*sets);
                file.close();
                return false;
            }
        }
    }

    file.close();
    return true;
}

void symmetricDifference(IntSet* sets, int setCount, IntSet* result) {
    int totalElements = 0;
    for (int i = 0; i < setCount; i++) {
        totalElements += sets[i].size;
    }

    if (totalElements == 0) {
        result->size = 0;
        result->elements = nullptr;
        return;
    }

    int* allElements = (int*)malloc(totalElements * sizeof(int));
    if (allElements == nullptr) {
        result->size = 0;
        result->elements = nullptr;
        return;
    }

    int pos = 0;
    for (int i = 0; i < setCount; i++) {
        for (int j = 0; j < sets[i].size; j++) {
            allElements[pos++] = sets[i].elements[j];
        }
    }

    sort(allElements, allElements + totalElements);

    int* uniqueElements = (int*)malloc(totalElements * sizeof(int));
    int* counts = (int*)malloc(totalElements * sizeof(int));
    if (uniqueElements == nullptr || counts == nullptr) {
        free(allElements);
        free(uniqueElements);
        free(counts);
        result->size = 0;
        result->elements = nullptr;
        return;
    }

    int uniqueCount = 0;
    if (totalElements > 0) {
        uniqueElements[0] = allElements[0];
        counts[0] = 1;
        uniqueCount = 1;
    }

    for (int i = 1; i < totalElements; i++) {
        if (allElements[i] == allElements[i - 1]) {
            counts[uniqueCount - 1]++;
        }
        else {
            uniqueElements[uniqueCount] = allElements[i];
            counts[uniqueCount] = 1;
            uniqueCount++;
        }
    }

    int resultSize = 0;
    for (int i = 0; i < uniqueCount; i++) {
        if (counts[i] % 2 != 0) {
            resultSize++;
        }
    }

    result->size = resultSize;
    result->elements = (int*)malloc(resultSize * sizeof(int));
    if (result->elements == nullptr && resultSize > 0) {
        free(allElements);
        free(uniqueElements);
        free(counts);
        result->size = 0;
        return;
    }

    int resultPos = 0;
    for (int i = 0; i < uniqueCount; i++) {
        if (counts[i] % 2 != 0) {
            result->elements[resultPos++] = uniqueElements[i];
        }
    }

    free(allElements);
    free(uniqueElements);
    free(counts);
}

bool writeResultToFile(const char* filename, const IntSet* result) {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    if (result->size == 0) {
        file << "Empty set";
    }
    else {
        for (int i = 0; i < result->size; i++) {
            if (i > 0) file << " ";
            file << result->elements[i];
        }
    }

    file.close();
    return true;
}

int main() {
    IntSet* sets = nullptr;
    int setCount = 0;
    IntSet result;

    if (!readSetsFromFile(input_filename, &sets, &setCount)) {
        ofstream out(output_filename);
        out << "Invalid input";
        out.close();
        return 1;
    }

    symmetricDifference(sets, setCount, &result);

    if (!writeResultToFile(output_filename, &result)) {
        for (int i = 0; i < setCount; i++) {
            free(sets[i].elements);
        }
        free(sets);
        free(result.elements);
        return 1;
    }

    for (int i = 0; i < setCount; i++) {
        free(sets[i].elements);
    }
    free(sets);
    free(result.elements);

    return 0;
}
