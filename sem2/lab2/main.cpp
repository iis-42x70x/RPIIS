#include <iostream>
#include "lab2.h"
#include <windows.h>

/**
 * @brief Главная функция программы
 * @return 0 - успех, 1 - ошибка
 */
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::setlocale(LC_ALL, ".UTF-8");

    // Шаг 1: Считываем входные данные
    if (!readInput()) {
        std::cerr << "Программа завершена из-за некорректных входных данных." << std::endl;
        return 1;
    }

    // Шаг 2: Генерируем перестановки и записываем результат
    writePermutations();

    // Шаг 3: Освобождаем память
    if (elements != nullptr) {
        delete[] elements;
        elements = nullptr;
    }

    return 0;
}