#include "Header.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>

DirectedSetGenerator::DirectedSetGenerator(const std::vector<std::string>& input)
    : elements(input) {
    if (elements.empty()) {
        std::cerr << "Ошибка: входное множество не может быть пустым\n";
        exit(1);
    }
}

bool DirectedSetGenerator::hasDuplicates() const {
    std::vector<std::string> temp = elements;
    std::sort(temp.begin(), temp.end());
    for (size_t i = 1; i < temp.size(); ++i) {
        if (temp[i] == temp[i - 1])
            return true;
    }
    return false;
}

void DirectedSetGenerator::generateRecursively(std::vector<std::string>& current, std::vector<bool>& used, int level) const {
    if (level == static_cast<int>(elements.size())) {
        std::cout << "{ ";
        for (size_t i = 0; i < current.size(); ++i) {
            std::cout << current[i];
            if (i < current.size() - 1)
                std::cout << " ";
        }
        std::cout << " }" << std::endl;
        return;
    }
    for (size_t i = 0; i < elements.size(); i++) {
        if (!used[i]) {
            used[i] = true;
            current.push_back(elements[i]);
            generateRecursively(current, used, level + 1);
            current.pop_back();
            used[i] = false;
        }
    }
}

void DirectedSetGenerator::generateDirectedSets() const {
    if (hasDuplicates()) {
        std::cerr << "Ошибка: во входном множестве есть повторяющиеся элементы\n";
        return;
    }
    std::vector<std::string> current;
    std::vector<bool> used(elements.size(), false);
    generateRecursively(current, used, 0);
}

size_t DirectedSetGenerator::size() const {
    return elements.size();
}

std::vector<std::string> parseSet(const std::string& input) {
    std::vector<std::string> result;
    std::string str = input;

    while (!str.empty() && isspace(str.front()))
        str.erase(str.begin());
    while (!str.empty() && isspace(str.back()))
        str.pop_back();
        
    if (str.empty() || str.front() != '{' || str.back() != '}') {
        std::cerr << "Ошибка: неверный формат множества" << std::endl;
        exit(1);
    }

    str = str.substr(1, str.size() - 2);
    
    int braceCount = 0;
    std::string token;
    for (char ch : str) {
        if (ch == '{') {
            braceCount++;
            token.push_back(ch);
        } else if (ch == '}') {
            braceCount--;
            token.push_back(ch);
        } else if (ch == ',' && braceCount == 0) {
            if (!token.empty()) {
                result.push_back(token);
                token.clear();
            }
        } else {
            token.push_back(ch);
        }
    }
    if (!token.empty())
        result.push_back(token);
    return result;
}

bool readInput(const std::string& filename, std::vector<std::string>& elements, int& n) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << "\n";
        return false;
    }
    
    std::string line;
    // Читаем первую строку — число n
    if (!getline(file, line)) {
        std::cerr << "Ошибка: файл пуст\n";
        file.close();
        return false;
    }
    std::istringstream iss(line);
    if (!(iss >> n) || n <= 0) {
        std::cerr << "Ошибка: неверное количество элементов (n должно быть положительным)\n";
        file.close();
        return false;
    }
    
    // Читаем вторую строку — множество
    if (!getline(file, line)) {
        std::cerr << "Ошибка: множество не указано\n";
        file.close();
        return false;
    }
    file.close();
    
    elements = parseSet(line);
    if (elements.size() != static_cast<size_t>(n)) {
        std::cerr << "Ошибка: количество элементов (" << elements.size()
                  << ") не соответствует указанному количеству (" << n << ")\n";
        return false;
    }
    return true;
}
