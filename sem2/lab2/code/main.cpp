// main.cpp
#include "parser.hpp"
#include "element.hpp"
#include "operations.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>

int main() {
    // Открываем input.txt
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла input.txt" << std::endl;
        return 1;
    }

    std::string line;
    std::string rawFirst, rawSecond;     // будут хранить две первые непустые строки
    bool gotFirstLine = false, gotSecondLine = false;

    // 1) Считываем файл, пока не нашли две «непустые» строки или не кончился файл
    while (std::getline(file, line) && (!gotFirstLine || !gotSecondLine)) {
        // Проверяем, состоит ли строка только из пробелов/табуляций/переводов строки
        bool onlySpaces = true;
        for (char c : line) {
            if (!std::isspace(static_cast<unsigned char>(c))) {
                onlySpaces = false;
                break;
            }
        }
        if (onlySpaces) {
            // Строка «пустая» (либо только пробелы) → пропускаем
            continue;
        }

        if (!gotFirstLine) {
            rawFirst = line;
            gotFirstLine = true;
        }
        else if (!gotSecondLine) {
            rawSecond = line;
            gotSecondLine = true;
        }
    }
    file.close();

    // 2) Показываем то, что прочитали, как «Входные множества»
    //    Если какой-то raw* остался пустым (файл закончился раньше), всё равно выведем его как пустую строку.
    std::cout << "Входные множества:" << std::endl;
    std::cout << rawFirst << std::endl;
    std::cout << rawSecond << std::endl;

    // 3) Парсим первое множество: если не удалось распарсить (или строка отсутствует), 
    //    выводим «Неправильное множество» и выходим.
    Element firstSet;
    try {
        if (!gotFirstLine) {
            throw std::runtime_error("Нет первой непустой строки");
        }
        Parser parser1(rawFirst);
        firstSet = parser1.parse();
    }
    catch (const std::exception &) {
        std::cout << "Неправильное множество" << std::endl;
        return 0;
    }

    // 4) Парсим второе множество: аналогично
    Element secondSet;
    try {
        if (!gotSecondLine) {
            throw std::runtime_error("Нет второй непустой строки");
        }
        Parser parser2(rawSecond);
        secondSet = parser2.parse();
    }
    catch (const std::exception &) {
        std::cout << "Неправильное множество" << std::endl;
        return 0;
    }

    

    std::cout << "\nСравнение первого и второго: "
              << (firstSet.equals(secondSet) ? "равны" : "не равны") << std::endl;

    Element result = symmetricDifference(firstSet, secondSet);
    std::cout << "\nСимметрическая разность:\n" << result << std::endl;

    return 0;
}
