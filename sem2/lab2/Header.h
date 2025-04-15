#ifndef SETS_H
#define SETS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_set>
using namespace std;

// Функция для проверки баланса скобок
bool checkBrackets(const string& input);

// Функция для разбора множества на элементы
vector<string> parseSet(const string& input);

// Функция для объединения двух множеств
string unionSets(vector<string>& set1, vector<string>& set2);

// Функция для чтения множеств из файла
vector<string> readSets(const string& path);

// Функция для открытия файла
void openFile(string& path);

// Функция для объединения всех множеств
void unionAllSets(const string& inputPath, const string& outputPath);

#endif 