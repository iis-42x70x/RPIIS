#include "element.hpp"
#include <iostream>

// Реализация методов структуры Element
Element::Element() : type(VALUE) { data.value = 0; }

Element::Element(int val) : type(VALUE) { data.value = val; }

Element::Element(Element* elems, int cnt) : type(SET) {
    data.set.elements = new Element[cnt];
    for (int i = 0; i < cnt; i++) {
        data.set.elements[i] = elems[i];
    }
    data.set.count = cnt;
}

Element::Element(const Element& other) {
    type = other.type;
    if (type == VALUE) {
        data.value = other.data.value;
    } else {
        data.set.count = other.data.set.count;
        data.set.elements = new Element[data.set.count];
        for (int i = 0; i < data.set.count; i++) {
            data.set.elements[i] = other.data.set.elements[i];
        }
    }
}

Element& Element::operator=(const Element& other) {
    if (this != &other) {
        if (type == SET) {
            delete[] data.set.elements;
        }
        
        type = other.type;
        if (type == VALUE) {
            data.value = other.data.value;
        } else {
            data.set.count = other.data.set.count;
            data.set.elements = new Element[data.set.count];
            for (int i = 0; i < data.set.count; i++) {
                data.set.elements[i] = other.data.set.elements[i];
            }
        }
    }
    return *this;
}

Element::~Element() {
    if (type == SET) {
        delete[] data.set.elements;
    }
}

bool Element::operator==(const Element& other) const {
    if (type != other.type) return false;
    if (type == VALUE) return data.value == other.data.value;
    if (data.set.count != other.data.set.count) return false;
    for (int i = 0; i < data.set.count; i++) {
        if (!(data.set.elements[i] == other.data.set.elements[i])) return false;
    }
    return true;
}

// Реализация функций для работы с множествами
Element* readSet(int& count) {
    std::cout << "Введите количество элементов в множестве: ";
    std::cin >> count;
    
    Element* elements = new Element[count];
    for (int i = 0; i < count; i++) {
        std::cout << "Элемент " << i+1 << " - число (1) или множество (2)? ";
        int choice;
        std::cin >> choice;
        
        if (choice == 1) {
            int val;
            std::cout << "Введите значение: ";
            std::cin >> val;
            elements[i] = Element(val);
        } else {
            int subCount;
            Element* subElements = readSet(subCount);
            elements[i] = Element(subElements, subCount);
            delete[] subElements;
        }
    }
    return elements;
}

bool contains(const Element* arr, int count, const Element& item) {
    for (int i = 0; i < count; i++) {
        if (arr[i] == item) return true;
    }
    return false;
}

Element* calculateSymmetricDifference(Element** sets, int* counts, int setCount, int& resultCount) {
    if (setCount == 0) {
        resultCount = 0;
        return nullptr;
    }

    Element* currentDiff = new Element[counts[0]];
    for (int i = 0; i < counts[0]; i++) {
        currentDiff[i] = sets[0][i];
    }
    int currentCount = counts[0];

    for (int i = 1; i < setCount; i++) {
        Element* temp = new Element[currentCount + counts[i]];
        int tempCount = 0;

        for (int j = 0; j < currentCount; j++) {
            if (!contains(sets[i], counts[i], currentDiff[j])) {
                temp[tempCount++] = currentDiff[j];
            }
        }

        for (int j = 0; j < counts[i]; j++) {
            if (!contains(currentDiff, currentCount, sets[i][j])) {
                temp[tempCount++] = sets[i][j];
            }
        }

        delete[] currentDiff;
        currentDiff = temp;
        currentCount = tempCount;
    }

    Element* result = new Element[currentCount];
    resultCount = 0;
    for (int i = 0; i < currentCount; i++) {
        if (!contains(result, resultCount, currentDiff[i])) {
            result[resultCount++] = currentDiff[i];
        }
    }

    delete[] currentDiff;
    return result;
}

void printElement(const Element& e) {
    if (e.type == Element::VALUE) {
        std::cout << e.data.value;
    } else {
        std::cout << "{";
        for (int i = 0; i < e.data.set.count; i++) {
            printElement(e.data.set.elements[i]);
            if (i < e.data.set.count - 1) std::cout << ", ";
        }
        std::cout << "}";
    }
}
