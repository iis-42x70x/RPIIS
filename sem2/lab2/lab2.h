#ifndef LAB2_H
#define LAB2_H

#include <string>

// Глобальные переменные
extern std::ifstream fin;         ///< Входной поток
extern std::ofstream fout;        ///< Выходной поток
extern int n;                     ///< Количество элементов
extern std::string* elements;     ///< Массив элементов (динамический)


int parseElements(const std::string& input, std::string* elementsArray, int maxElements);

bool isUnique(std::string* arr, int size);

bool readInput();

void writePermutations();

int parseElements(const std::string& input, std::string* elementsArray, int maxElements);
bool isUnique(std::string* arr, int size);
bool readInput();
void writePermutations();

#endif // LAB2_H
