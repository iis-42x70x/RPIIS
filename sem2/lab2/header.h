#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>
#include <iostream>

class DirectedSetGenerator {
private:
    std::vector<std::string> elements;  

    bool hasDuplicates() const;

    void generateRecursively(std::vector<std::string>& current, std::vector<bool>& used, int level) const;
public:

    DirectedSetGenerator(const std::vector<std::string>& input);

    void generateDirectedSets() const;

    size_t size() const;
};

std::vector<std::string> parseSet(const std::string& input);

bool readInput(const std::string& filename, std::vector<std::string>& elements, int& n);

#endif // HEADER_H
