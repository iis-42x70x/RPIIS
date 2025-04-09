
#ifndef SETS_H
#define SETS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_set>

using namespace std;

// Объявления функций
bool checkBrackets(const string& input);              // Проверка баланса скобок
vector<string> parseSet(const string& input);         // Разбор множества на элементы
string unionSets(vector<string>& set1, vector<string>& set2); // Объединение двух множеств
vector<string> readSets(const string& path);          // Чтение множеств из файла
void createFile(string& path);                        // Создание файла
void inputSets(const string& path);                   // Ввод множеств
void unionAllSets(const string& path);                // Объединение всех множеств

#endif
