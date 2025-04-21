#include "Header.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    
    std::string filename = "input.txt"; 
    std::vector<std::string> elements;
    int n;
    
    // Считываем данные из файла
    if (!readInput(filename, elements, n)) {
        return 1;
    }
    
    DirectedSetGenerator generator(elements);
    if (generator.size() != static_cast<size_t>(n)) {
        std::cerr << "Ошибка: несоответствие внутреннего размера\n";
        return 1;
    }
    
    std::cout << "Сгенерированные ориентированные множества (перестановки):\n";
    generator.generateDirectedSets();
    
    return 0;
}
