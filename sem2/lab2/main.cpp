#include "header.h"

int main() {
    std::string inputLine;

    std::cout << "Input elements: ";
    std::getline(std::cin, inputLine);

    std::vector<std::string> newSets = parseInput(inputLine);
    std::set<std::string> orientations = generateAllOrientations(newSets);
    writeInput("input.txt", orientations);

    std::set<std::string> inputSet = readInput("input.txt");
    for (const auto& result : inputSet) {
        std::cout << result << std::endl;
    }

    return 0;
}