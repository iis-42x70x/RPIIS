#include "header.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 

using namespace std;

// вывод множеств 
void viewSets(vector<string> sets) {
    for (int i = 0; i <= sets.size(); i++) {
        if (i < sets.size()) {
            cout << "Множество " << i + 1 << " :" << endl;
            cout << "{" << sets[i] << "}" << endl;
        }
        else {
            cout << "Все множества записаны." << endl;
            cout << "----------------------" << endl;
        }
    }
}

//читает содержимое файла и добавляет строки в вектор
void readFile(vector<string>& sets, ifstream& inputFile) {
    string line; //для хранения каждой строки из файла
    while (getline(inputFile, line)) {
        sets.push_back(line);
    }
    inputFile.close();
}

string normalizeSet(const string& setStr) {
    string normalized = setStr;
    // Удаляем все пробелы
    normalized.erase(remove(normalized.begin(), normalized.end(), ' '), normalized.end());

    // Если строка не является множеством, возвращаем как есть
    if (normalized.empty()) {
        return normalized;
    }

    string inner; //строка без пробелов и без внешних скобок
    // Удаляем внешние скобки
    if (normalized.front() == '{' && normalized.back() == '}') {
        inner = normalized.substr(1, normalized.length() - 2);
    }
    else {
        inner = normalized; // если скобок нет, используем как есть
    }

    vector<string> elements;
    string currentElement;
    int braceDepth = 0;

    // разбиваем строку на элементы
    for (int i = 0; i < inner.length(); i++) {
        char c = inner[i];

        if (c == '{' || c == '<') {
            braceDepth++;
            currentElement += c;
        }
        else if (c == '}' || c == '>') {
            braceDepth--;
            currentElement += c;
            if (braceDepth == 0 && !currentElement.empty()) {
                elements.push_back(currentElement);
                currentElement.clear();
            }
        }
        else if (c == ',' && braceDepth == 0) {
            if (!currentElement.empty()) {
                elements.push_back(currentElement);
                currentElement.clear();
            }
        }
        else {
            currentElement += c;
        }
    }
    if (!currentElement.empty()) {
        elements.push_back(currentElement);
    }

    // Сортируем элементы, исключая те, что содержат "<" или ">"
    vector<string> elementsToSort;
    vector<string> nonSortedElements;

    for (const string& element : elements) {
        if (element.find('<') != string::npos || element.find('>') != string::npos) { //если элемент есть
            nonSortedElements.push_back(element);
        }
        else {
            elementsToSort.push_back(element);
        }
    }

    // Сортируем только элементы, не содержащие '<' и '>'
    sort(elementsToSort.begin(), elementsToSort.end());

    // Объединяем отсортированные элементы (в конец добавляем неотсортированные)
    elementsToSort.insert(elementsToSort.end(), nonSortedElements.begin(), nonSortedElements.end());

    // Собираем нормализованную строку
    string sortedInner;
    for (int i = 0; i < elementsToSort.size(); i++) {
        sortedInner += elementsToSort[i];
        if (i < elementsToSort.size() - 1) { //если это не последний элемент
            sortedInner += ",";
        }
    }

    return sortedInner;
}
vector<string> splitElements(const string& setStr) {
    vector<string> elements;
    string currentElement;
    int braceDepth = 0;

    string inner = setStr;

    for (char c : inner) {
        if (c == '{') braceDepth++;
        else if (c == '}') braceDepth--;
        else if (c == ',' && braceDepth == 0) {
            if (!currentElement.empty()) {
                elements.push_back(currentElement);
                currentElement.clear();
            }
            continue;
        }
        currentElement += c;
    }
    if (!currentElement.empty()) elements.push_back(currentElement);
    return elements;
}

void differenceSets(vector<string>& sets, string& initialResult) {
    if (sets.size() < 2) {
        cout << "Недостаточно множеств для вычисления разности." << endl;
        return;
    }

    string normalizedA = normalizeSet(sets[0]);
    string normalizedB = normalizeSet(sets[1]);

    vector<string> elementsA = splitElements(normalizedA);
    vector<string> elementsB = splitElements(normalizedB);

    vector<string> resultElements;
    for (const string& elementA : elementsA) {
        bool foundInB = false;
        string normA = normalizeSet(elementA);
        for (const string& elementB : elementsB) {
            string normB = normalizeSet(elementB);
            if (normA == normB) {
                foundInB = true;
                break;
            }
        }
        if (!foundInB) {
            resultElements.push_back(elementA);
        }
    }

    string finalResult;
    if (resultElements.empty()) {
        finalResult = "";
    }
    else {
        for (int i = 0; i < resultElements.size(); i++) {
            finalResult += resultElements[i];
            if (i < resultElements.size() - 1) {
                finalResult += ",";
            }
        }
    }

    initialResult = "{" + finalResult + "}";
    cout << "Результат разности:" << endl;
    cout << "{" << finalResult << "}" << endl;
}