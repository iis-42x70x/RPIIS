//
// pch.h
//

#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

class YoungTableau {
public:
    std::vector<std::vector<int>> getTable() const;
    void initialize(int row_number);
    void YoungTableau::initialize(const std::vector<std::vector<int>>& inputTable);
    bool YoungTableau::hasDuplicates() const;
    size_t width();
    void add(int line_number, int element);
    void remove(int position, int line_number);
    void removeAll(int element);
    void print();
    void printToFile(std::string filename);
    void add1(int element, int line_number);

private:
    std::vector<std::vector<int>> table;
    int row_number; // Добавлено поле для хранения количества элементов в строке
};