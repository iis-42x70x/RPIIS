#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>   // Для sort и next_permutation
#include <cstdlib>

using namespace std;

// Глобальные переменные
ifstream fin;                   ///< Входной поток
ofstream fout;                  ///< Выходный поток
int n = 0;                      ///< Количество элементов
string* elements = nullptr;     ///< Массив элементов (динамический)

int parseElements(const string& input, string* elementsArray, int maxElements) {
    string current;
    int bracketDepth = 0;
    int angleBracketDepth = 0;
    int count = 0;

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];

        if (c == ',' && bracketDepth == 0 && angleBracketDepth == 0) {
            if (!current.empty() && count < maxElements) {
                elementsArray[count++] = current;
                current.clear();
            }
        }
        else {
            current += c;
        }

        // Следим за уровнем вложенности скобок
        if (c == '{') ++bracketDepth;
        if (c == '}') --bracketDepth;
        if (c == '<') ++angleBracketDepth;
        if (c == '>') --angleBracketDepth;
    }

    // Добавляем последний элемент
    if (!current.empty() && count < maxElements)
        elementsArray[count++] = current;

    return count;
}

bool isUnique(string* arr, int size) {
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size; ++j)
            if (arr[i] == arr[j])
                return false;
    return true;
}

bool readInput() {
    const string filePath = "input.txt"; 

    fin.open(filePath);
    if (!fin.is_open()) {
        cerr << "Ошибка: не удалось открыть файл по пути: " << filePath << endl;
        return false;
    }

    if (!(fin >> n)) {
        cerr << "Ошибка: некорректный формат для n" << endl;
        fin.close();
        return false;
    }

    if (n <= 0) {
        cerr << "Ошибка: n должно быть натуральным числом (>0)" << endl;
        fin.close();
        return false;
    }

    fin.ignore(10000, '\n');

    string line;
    getline(fin, line);
    fin.close();

    if (line.empty()) {
        cerr << "Ошибка: отсутствует строка с элементами" << endl;
        return false;
    }

    elements = new string[n];

    int parsedCount = parseElements(line, elements, n);

    if (parsedCount != n) {
        cerr << "Ошибка: количество элементов (" << parsedCount
            << ") не совпадает с указанным n (" << n << ")" << endl;
        delete[] elements;
        elements = nullptr;
        return false;
    }

    if (!isUnique(elements, n)) {
        cerr << "Ошибка: элементы множества должны быть уникальными" << endl;
        delete[] elements;
        elements = nullptr;
        return false;
    }

    return true;
}

void writePermutations() {
    fout.open("output.txt");
    if (!fout.is_open()) {
        cerr << "Ошибка: не удалось создать файл output.txt" << endl;
        return;
    }

    // Создаем временный массив для перестановок
    string* temp = new string[n];
    for (int i = 0; i < n; ++i)
        temp[i] = elements[i];

    sort(temp, temp + n);

    do {
        for (int i = 0; i < n; ++i) {
            fout << temp[i];
            if (i != n - 1)
                fout << ",";
        }
        fout << endl;
    } while (next_permutation(temp, temp + n));

    delete[] temp;
    fout.close();

    cout << "Файл output.txt успешно создан." << endl;
    system("start notepad.exe output.txt"); // Только для Windows
}
