#include "pch.h"

int main() {
    std::set<std::string> inputSet = readInput("input.txt");
    std::vector<std::string> newSets(inputSet.begin(), inputSet.end());
    std::set<std::string> orientations = generateAllOrientations(newSets);
    writeInput("output.txt", orientations);
    for (const auto& result : orientations) {
        std::cout << result << std::endl;
    }

    return 0;
}
