#include "pch.h"
#include <iostream>
#include <limits>

using namespace std;

Set::Set() : data(nullptr), size(0) {}

Set::~Set() {
    delete[] data;
}

bool Set::contains(int value) const {
    for (int i = 0; i < size; ++i)
        if (data[i] == value)
            return true;
    return false;
}

int Set::inputInteger() const {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: Введите целое число: ";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int Set::indexOf(int value) const {
    for (int i = 0; i < size; ++i)
        if (data[i] == value)
            return i;
    return -1;
}

void Set::create() {
    cout << "Введите размер множества: ";
    size = inputInteger();
    while (size <= 0) {
        cout << "Размер не должен быть отрицательным: ";
        size = inputInteger();
    }

    delete[] data;
    data = new int[size];

    for (int i = 0; i < size; ++i) {
        int val;
        cout << "Введите элемент #" << i + 1 << ": ";
        val = inputInteger();

        while (contains(val)) {
            cout << "Элемент уже существует. Введите другой: ";
            val = inputInteger();
        }

        data[i] = val;
    }

    cout << "Множество создано." << endl;
    display();
}

void Set::add() {
    if (isEmpty()) {
        cout << "Множество пустое!" << endl;
        return;
    }
    int val;
    cout << "Введите новый элемент: ";
    val = inputInteger();

    if (contains(val)) {
        cout << "Элемент уже существует." << endl;
        return;
    }

    int* newData = new int[size + 1];
    for (int i = 0; i < size; ++i)
        newData[i] = data[i];
    newData[size] = val;

    delete[] data;
    data = newData;
    ++size;

    cout << "Элемент добавлен." << endl;
    display();
}

void Set::remove() {
    if (isEmpty()) {
        cout << "Множество пустое!" << endl;
        return;
    }
    int val;
    cout << "Введите элемент для удаления: ";
    val = inputInteger();

    int index = -1;
    for (int i = 0; i < size; ++i)
        if (data[i] == val) {
            index = i;
            break;
        }

    if (index == -1) {
        cout << "Элемент не найден." << endl;
        return;
    }

    for (int i = index; i < size - 1; ++i)
        data[i] = data[i + 1];

    --size;
    cout << "Элемент удалён." << endl;
    display();
}

void Set::search() {
    if (isEmpty()) {
        cout << "Множество пустое!" << endl;
        return;
    }
    int val;
    cout << "Введите элемент для поиска: ";
    val = inputInteger();

    int index = indexOf(val);
    if (index != -1)
        cout << "Элемент найден в множестве на позиции " << index << "." << endl;
    else
        cout << "Элемент не найден в множестве." << endl;
}

void Set::display() {
    if (isEmpty()) {
        cout << "Множество пустое!" << endl;
        return;
    }
    cout << "Множество: ";
    for (int i = 0; i < size; ++i)
        cout << data[i] << " ";
    cout << endl << endl;
}

void Set::unionWith(const Set& other) {
    if (isEmpty()) {
        cout << "Множество пустое!" << endl;
        return;
    }

    cout << "Объединение: ";
    for (int i = 0; i < size; ++i)
        cout << data[i] << " ";
    for (int i = 0; i < other.size; ++i)
        if (!contains(other.data[i]))
            cout << other.data[i] << " ";
    cout << endl << endl;
}

void Set::intersectWith(const Set& other) {
    if (isEmpty()) {
        cout << "Множество пустое!" << endl;
        return;
    }
    cout << "Пересечение: ";
    for (int i = 0; i < size; ++i)
        if (other.contains(data[i]))
            cout << data[i] << " ";
    cout << endl << endl;
}

bool Set::isEmpty() const {
    return data == nullptr;
}
