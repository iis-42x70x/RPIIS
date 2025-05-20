#include "multiset.hpp"
#include <iostream>
#include <Windows.h>
#include <filesystem>

int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Текущий каталог: " << std::filesystem::current_path() << std::endl;

    std::string filename;
    std::cout << "Введите путь к файлу: ";
    std::getline(std::cin, filename);

    try {
        auto sets = parse_input(filename);
        if (sets.size() > 2)
        {
            throw std::runtime_error("Файл содержит более двух множеств");
        }
        if (sets.empty()) {
            std::cout << "{}" << std::endl;
            return 0;
        }
        Element uni = union_multisets(sets);
        std::cout << to_string(uni) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}