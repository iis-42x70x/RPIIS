#include "Header.h"
#include <iostream>
#include <string>
#include <fstream>

//  удаления пробелов из строки
std::string removeSpaces(const std::string& s) {
    std::string result;
    for (char ch : s) {
        if (ch != ' ') {
            result += ch;
        }
    }
    return result;
}

// сортировки в строке 
std::string sortString(std::string s) {
    for (size_t i = 0; i < s.length(); ++i) {
        for (size_t j = i + 1; j < s.length(); ++j) {
            if (s[i] > s[j]) {
                char temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }
    return s;
}

//сортировки элементов во вложенном множестве
std::string sortNestedSet(const std::string& s) {
    std::string result;
    int depth = 0;
    std::string currentElement;

    for (size_t i = 0; i < s.length(); ++i) {
        char ch = s[i];

        if (ch == '{' || ch == '<') {
            depth++;
            currentElement += ch;
        }
        else if (ch == '}' || ch == '>') {
            depth--;
            currentElement += ch;
        }
        else if (ch == ',' && depth == 0) {
            result += sortString(currentElement) + ",";
            currentElement.clear();
        }
        else {
            currentElement += ch;
        }
    }

    // Добавляем последний элемент
    if (!currentElement.empty()) {
        result += sortString(currentElement);
    }

    // Удаляем последнюю запятую
    if (!result.empty() && result.back() == ',') {
        result.pop_back();
    }

    return result;
}

// проверки равенства двух элементов
bool areElementsEqual(const std::string& elem1, const std::string& elem2) {
    return sortNestedSet(elem1) == sortNestedSet(elem2);
}

//  извлечения элементов из строки множества
void extractElements(const std::string& s, std::string* elements, int& count) {
    int depth = 0;
    int start = 1;
    count = 0;

    for (size_t i = 1; i < s.length() - 1; ++i) {
        char ch = s[i];

        if (ch == '{' || ch == '<') {
            depth++;
        }
        else if (ch == '}' || ch == '>') {
            depth--;
        }
        else if (ch == ',' && depth == 0) {
            elements[count++] = s.substr(start, i - start);
            start = i + 1;
        }
    }

    // Добавляем последний элемент
    if (start < s.length() - 1) {
        elements[count++] = s.substr(start, s.length() - 1 - start);
    }
}

void removeDuplicates(int& resultCount, std::string* result) {
    for (int i = 0; i < resultCount; ++i) {
        for (int j = i + 1; j < resultCount; ++j) {
            if (areElementsEqual(result[i], result[j])) {
                // Сдвиг элементы влево
                for (int k = j; k < resultCount - 1; ++k) {
                    result[k] = result[k + 1];
                }
                resultCount--;
                j--;
            }
        }
    }
}

//вычисления симметрической разности
void symmetricDifference(std::string* set1, int count1, std::string* set2, int count2, std::string* result, int& resultCount) {
    resultCount = 0;

    
    for (int i = 0; i < count1; ++i) {
        bool found = false;
        for (int j = 0; j < count2; ++j) {
            if (areElementsEqual(set1[i], set2[j])) {
                found = true;
                break;
            }
        }
        if (!found) {
            result[resultCount++] = set1[i];
        }
    }

   
    for (int i = 0; i < count2; ++i) {
        bool found = false;
        for (int j = 0; j < count1; ++j) {
            if (areElementsEqual(set2[i], set1[j])) {
                found = true;
                break;
            }
        }
        if (!found) {
            result[resultCount++] = set2[i];
        }
    }

    
    removeDuplicates(resultCount, result);
}

void save(const std::string* sets, int sets_count, const std::string* elements1, int count1, const std::string& filename) {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cout << "Ошибка открытия файла для записи\n";
        return;
    }

    fout << "Количество множеств: " << sets_count << std::endl;

    for (int i = 0; i < sets_count; i++) {
        std::string set_content = sets[i];
        std::string* elements = new std::string[100];
        int elements_count = 0;
        extractElements(set_content, elements, elements_count);
        removeDuplicates(elements_count, elements);
        std::string new_set = "{";
        for (int j = 0; j < elements_count; j++) {
            new_set += elements[j];
            if (j < elements_count - 1) {
                new_set += ",";
            }
        }
        new_set += "}";

        // Сохраняем новое множество в файл
        fout << "Множество " << (i + 1) << " = {" << new_set << "}" << std::endl;

        delete[] elements;
    }

    // Сохраняем симметрическую разность
    fout << "Симметрическая разность = {";
    for (int i = 0; i < count1; i++) {
        fout << elements1[i];
        if (i < count1 - 1) {
            fout << ", ";
        }
    }
    fout << "}" << std::endl;

    fout.close();
    std::cout << "Данные сохранены в файл " << filename << std::endl;
}

void load(std::string* sets, int& sets_count, std::string* elements1, int& count1, const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cout << "Ошибка открытия файла для чтения\n";
        return;
    }

    std::string line;
    std::getline(fin, line); 
    sets_count = std::stoi(line.substr(line.find(":") + 1));

   
    for (int i = 0; i < sets_count; i++) {
        std::getline(fin, line);
        std::string set_content = line.substr(line.find("{") + 1);

        int brace_count = 0;
        size_t start = 0;
        for (size_t j = 0; j < set_content.size(); j++) {
            if (set_content[j] == '{') {
                brace_count++;
            }
            else if (set_content[j] == '}') {
                brace_count--;
            }
            // Если количество открывающих и закрывающих скобок совпадает, мы завершили считывание множества
            if (brace_count == 0) {
                sets[i] = set_content.substr(0, j + 1); // Извлекаем полное множество
                break;
            }
        }
    }

    // Чтение элементов
    std::getline(fin, line);
    line = line.substr(line.find("{") + 1, line.find("}") - line.find("{") - 1); // Извлечение элементов

    int pos = 0;
    count1 = 0;

    while ((pos = line.find(',')) != std::string::npos) {
        std::string element = line.substr(0, pos);
        elements1[count1++] = element; // Сохраняем элемент
        line.erase(0, pos + 1);
    }
    // Добавляем последний элемент
    if (!line.empty()) {
        elements1[count1++] = line;
    }

    // Удаляем пробелы из элементов
    for (int i = 0; i < count1; i++) {
        elements1[i].erase(remove(elements1[i].begin(), elements1[i].end(), ' '), elements1[i].end());
    }

    fin.close();
    std::cout << "Данные загружены из файла " << filename << std::endl;
}
