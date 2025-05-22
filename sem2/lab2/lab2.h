#ifndef LAB2_H
#define LAB2_H

#include <string>

// Глобальные переменные
extern std::ifstream fin;         ///< Входной поток
extern std::ofstream fout;        ///< Выходной поток
extern int n;                     ///< Количество элементов
extern std::string* elements;     ///< Массив элементов (динамический)

/**
 * @brief Разбирает строку на элементы, игнорируя запятые внутри скобок
 * @param input - входная строка
 * @param elementsArray - массив для хранения элементов
 * @param maxElements - максимальное количество элементов
 * @return int - количество найденных элементов
 */
int parseElements(const std::string& input, std::string* elementsArray, int maxElements);

/**
 * @brief Проверяет, является ли массив уникальным (нет повторяющихся элементов)
 * @param arr - массив строк
 * @param size - размер массива
 * @return true, если все элементы уникальны
 */
bool isUnique(std::string* arr, int size);

/**
 * @brief Считывает данные из файла input.txt по указанному пути
 * @return true, если успешно
 */
bool readInput();

/**
 * @brief Записывает все перестановки в файл output.txt
 */
void writePermutations();

int parseElements(const std::string& input, std::string* elementsArray, int maxElements);
bool isUnique(std::string* arr, int size);
bool readInput();
void writePermutations();

#endif // LAB2_H