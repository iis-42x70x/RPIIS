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

/**
 * @brief Разбирает строку на элементы, игнорируя запятые внутри скобок
 * @param input - входная строка
 * @param elementsArray - массив для хранения элементов
 * @param maxElements - максимальное количество элементов
 * @return int - количество найденных элементов
 */
int parseElements(const string& input, string* elementsArray, int maxElements) {
    string current;
    int count = 0;

    int bracketDepth = 0;     // {}
    int angleBracketDepth = 0;
    size_t angleStart = 0;

    for (size_t i = 0; i <= input.size(); ++i) {
        char c = (i < input.size()) ? input[i] : ',';

        if (c == '<') {
            angleBracketDepth++;
            angleStart = i + 1;
        }

        if (c == '>') {
            angleBracketDepth--;
            if (angleBracketDepth == 0 && i > angleStart) {
                string content = input.substr(angleStart, i - angleStart);
                content.erase(0, content.find_first_not_of(" \t"));
                content.erase(content.find_last_not_of(" \t") + 1);

                if (content.empty()) {
                    cerr << "Ошибка: внутри <> не может быть пустого элемента" << endl;
                    return -1;
                }
            }
        }

        if (c == '{') {
            bracketDepth++;
        }
        else if (c == '}') {
            bracketDepth--;
            if (bracketDepth < 0) {
                cerr << "Ошибка: незакрытые фигурные скобки" << endl;
                return -1;
            }
        }

        if (c == ',' && angleBracketDepth == 0 && bracketDepth == 0) {
            // Удаляем пробелы по краям
            current.erase(current.find_last_not_of(" \t") + 1);
            current.erase(0, current.find_first_not_of(" \t"));

            if (current.empty()) {
                cerr << "Ошибка: элемент пропущен (пустой элемент между запятыми)" << endl;
                return -1;
            }

            if (count < maxElements) {
                elementsArray[count++] = current;
            }
            else {
                cerr << "Ошибка: слишком много элементов" << endl;
                return -1;
            }

            current.clear();
        }
        else {
            if (c != ',' || angleBracketDepth > 0 || bracketDepth > 0)
                current += c;
        }

        // Отслеживание фигурных скобок
        if (c == '{') bracketDepth++;
        if (c == '}') bracketDepth--;

        // Отслеживание угловых скобок
        if (c == '<') angleBracketDepth++;
        if (c == '>') angleBracketDepth--;

        // Проверка на непарные скобки
        if (bracketDepth < 0 || angleBracketDepth < 0) {
            cerr << "Ошибка: незакрытые скобки" << endl;
            return -1;
        }
    }

    // Проверяем, все ли фигурные скобки закрыты
    if (bracketDepth != 0) {
        cerr << "Ошибка: незакрытые фигурные скобки" << endl;
        return -1;
    }

    // Проверяем, все ли угловые скобки закрыты
    if (angleBracketDepth != 0) {
        cerr << "Ошибка: незакрытые угловые скобки" << endl;
        return -1;
    }

    // Если остались символы после последней запятой — это ошибка
    if (!current.empty()) {
        current.erase(current.find_last_not_of(" \t") + 1);
        current.erase(0, current.find_first_not_of(" \t"));

        if (current.empty()) {
            cerr << "Ошибка: элемент пропущен (запятая без следующего элемента)" << endl;
            return -1;
        }
    }

    return count;
}

/**
 * @brief Проверяет, является ли массив уникальным (нет повторяющихся элементов)
 * @param arr - массив строк
 * @param size - размер массива
 * @return true, если все элементы уникальны
 */
bool isUnique(string* arr, int size) {
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size; ++j)
            if (arr[i] == arr[j])
                return false;
    return true;
}

/**
 * @brief Считывает данные из файла input.txt по указанному пути
 * @return true, если успешно
 */
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

    // Убираем начальные и конечные пробелы
    line.erase(line.begin(), find_if(line.begin(), line.end(), [](char c) { return !isspace(c); }));
    line.erase(find_if(line.rbegin(), line.rend(), [](char c) { return !isspace(c); }).base(), line.end());

    // Проверяем, что множество окружено фигурными скобками
    if (line.empty() || line.front() != '{' || line.back() != '}') {
        cerr << "Ошибка: множество должно быть обрамлено фигурными скобками '{...}' или без них" << endl;
        return false;
    }

    elements = new string[n];
    int parsedCount = parseElements(line, elements, n);

    if (parsedCount == -1) {
        delete[] elements;
        elements = nullptr;
        return false;
    }

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

/**
 * @brief Записывает все перестановки в файл output.txt
 */
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