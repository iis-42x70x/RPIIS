#include "pch.h"

std::string formatSet(const std::vector<std::string>& elements) {
    std::ostringstream result;
    result << "<";
    for (size_t i = 0; i < elements.size(); ++i) {
        result << elements[i];
        if (i < elements.size() - 1) {
            result << ",";
        }
    }
    result << ">";
    return result.str();
}


void generateOrientations(std::vector<std::string> elements, std::set<std::string>& result) {
    std::sort(elements.begin(), elements.end());
    do {
        result.insert(formatSet(elements));
    } while (std::next_permutation(elements.begin(), elements.end()));
}

std::set<std::string> generateAllOrientations(const std::vector<std::string>& inputElements) {
    std::set<std::string> result;
    if (inputElements.empty()) {
        return result; 
    }
    generateOrientations(inputElements, result);
    return result;
}

void writeInput(const std::string& filename, const std::set<std::string>& inputSet) {
    std::ofstream outFile(filename, std::ios::trunc); 
    for (const auto& elem : inputSet) {
        outFile << elem << std::endl;
    }
}

std::set<std::string> readInput(const std::string& filename) {
    std::ifstream inFile(filename);
    std::set<std::string> inputSet;
    std::string line;

    while (std::getline(inFile, line)) {
        inputSet.insert(line);
    }
    return inputSet;
}

std::vector<std::string> parseInput(const std::string& inputLine) {
    std::vector<std::string> elements;
    std::string currentElement;
    int bracketCount = 0;

    for (char c : inputLine) {
        if (c == '<' || c == '{') {
            bracketCount++;
            currentElement += c;
        }
        else if (c == '>' || c == '}') {
            bracketCount--;
            currentElement += c;
        }
        else if (c == ',' && bracketCount == 0) {
            if (!currentElement.empty()) {
                currentElement.erase(0, currentElement.find_first_not_of(' '));
                currentElement.erase(currentElement.find_last_not_of(' ') + 1);
                if (!currentElement.empty()) {
                    elements.push_back(currentElement);
                }
                currentElement.clear();
            }
        }
        else {
            currentElement += c;
        }
    }

    if (!currentElement.empty()) {
        currentElement.erase(0, currentElement.find_first_not_of(' '));
        currentElement.erase(currentElement.find_last_not_of(' ') + 1);
        if (!currentElement.empty()) {
            elements.push_back(currentElement);
        }
    }

    return elements;
}