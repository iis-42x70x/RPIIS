#include "set_operations.h"
#include <fstream>
#include <set>
#include <locale>
using namespace std;
// Функция для разбиения строки на элементы множества с учетом вложенных множеств
vector<string> tokenize(const string& s) {
    vector<string> tokens;
    string token;
    int braceCount = 0; // Для отслеживания вложенности

    for (char ch : s) {
        if (ch == '{' || ch == '<') {
            braceCount++;
            token += ch; // Добавляем открывающую скобку
        }
        else if (ch == '}' || ch == '>') {
            braceCount--;
            token += ch; // Добавляем закрывающую скобку
        }
        else if (ch == ',' && braceCount == 0) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        }
        else {
            token += ch; // Добавляем символ в текущий токен
        }
    }

    if (!token.empty()) {
        tokens.push_back(token); // Добавляем последний токен
    }

    return tokens;
}

// Функция обработки множества из строки с учетом вложенных множеств
void processSet(const string& input, vector<string>& elements) {
    // Удаляем внешние скобки
    string content = input.substr(1, input.size() - 2);
    vector<string> tokens = tokenize(content);

    for (const string& el : tokens) {
        elements.push_back(el); // Добавляем элемент в вектор
    }
}

// Функция для создания и заполнения файла input.txt, если он отсутствует или пуст
void createAndFillFile(const string& filename) {
    ofstream outFile(filename);
    if (outFile) {
        outFile << "{o, {}, A}\n";
        outFile << "{o, <1,2>, A2, c3, B, b3_A, {}, {o, {}, A}}\n";
        outFile << "{o, A2, b3, A, <1,2>, {}}\n";
        cout << "Файл " << filename << " был пуст или отсутствовал, и заполнен тестовыми данными.\n";
    }
    else {
        cout << "Ошибка: не удалось создать " << filename << std::endl;
    }
}
vector<string> intersection(const vector<vector<string>>& sets) {
    vector<string> result;

    if (sets.empty()) return result; // Если множества пустые, возвращаем пустой результат

    set<string> tempSet(sets[0].begin(), sets[0].end()); // Инициализируем результат первым множеством

    // Перебираем остальные множества и находим пересечение
    for (size_t i = 1; i < sets.size(); ++i) {
        set<string> currentSet(sets[i].begin(), sets[i].end());

        // Если текущее множество пустое, пересечение будет пустым
        if (currentSet.empty()) {
            return result; // Возвращаем пустое множество, если одно из множеств пустое
        }

        set<string> newSet;
        for (const string& el : tempSet) {
            if (currentSet.find(el) != currentSet.end()) {
                newSet.insert(el);
            }
        }

        tempSet = newSet; // Обновляем результат пересечения
    }

    // Преобразуем set обратно в vector
    result.assign(tempSet.begin(), tempSet.end());

    return result;
}
