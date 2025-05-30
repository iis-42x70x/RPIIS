// main.cpp
#include "parser.hpp"
#include "element.hpp"
#include "operations.hpp"
#include <fstream>
#include <iostream>
#include <vector>

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла input.txt" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<Element> sets;

    while (std::getline(file, line)) {
        try {
            Parser parser(line);
            Element el = parser.parse();
            sets.push_back(el);
        } catch (const std::exception& ex) {
            std::cerr << "Ошибка парсинга: " << ex.what() << std::endl;
            return 1;
        }
    }

    file.close();

    std::cout << "Прочитанные множества:" << std::endl;
    for (const auto& s : sets) {
        std::cout << s << std::endl;
    }

    if (sets.size() >= 2) {
        std::cout << "\nСравнение множеств 0 и 1: "
                  << (sets[0].equals(sets[1]) ? "равны" : "не равны") << std::endl;

        Element result = symmetricDifference(sets[0], sets[1]);
        std::cout << "\nСимметрическая разность:\n" << result << std::endl;
    }

    return 0;
}
