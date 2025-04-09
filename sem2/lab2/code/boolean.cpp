// boolean.cpp
#include "boolean.h"

boolean::boolean() : elementCount(0) {
    for (int i = 0; i < max_element; i++) {
        inputSet[i][0] = '\0';
    }
}

void boolean::extractElements(const char* input) {
    char temp[max_length];
    strncpy(temp, input, max_length - 1);
    temp[max_length - 1] = '\0';

    int braceLevel = 0;
    int angleBracketLevel = 0;
    int startPos = 0;
    bool inElement = false;

    for (int i = 0; temp[i] != '\0' && elementCount < max_element; i++) {
        if (temp[i] == '{') {
            braceLevel++;
            if (braceLevel == 1 && angleBracketLevel == 0) {
                startPos = i;
                inElement = true;
            }
        }
        else if (temp[i] == '}') {
            braceLevel--;
            if (braceLevel == 0 && angleBracketLevel == 0 && inElement) {
                strncpy(inputSet[elementCount], temp + startPos, i - startPos + 1);
                inputSet[elementCount][i - startPos + 1] = '\0';
                elementCount++;
                inElement = false;
            }
        }
        else if (temp[i] == '<') {
            angleBracketLevel++;
            if (angleBracketLevel == 1 && braceLevel == 0) {
                startPos = i;
                inElement = true;
            }
        }
        else if (temp[i] == '>') {
            angleBracketLevel--;
            if (angleBracketLevel == 0 && braceLevel == 0 && inElement) {
                strncpy(inputSet[elementCount], temp + startPos, i - startPos + 1);
                inputSet[elementCount][i - startPos + 1] = '\0';
                elementCount++;
                inElement = false;
            }
        }
        else if (temp[i] == ',' && braceLevel == 0 && angleBracketLevel == 0) {
            continue;
        }
        else if (braceLevel == 0 && angleBracketLevel == 0 && !inElement && temp[i] != ' ') {
            startPos = i;
            while (temp[i] != '\0' && temp[i] != ',' && temp[i] != ' ' &&
                   temp[i] != '{' && temp[i] != '<') {
                i++;
            }
            strncpy(inputSet[elementCount], temp + startPos, i - startPos);
            inputSet[elementCount][i - startPos] = '\0';
            elementCount++;
            if (temp[i] == '\0') break;
            i--; // компенсируем инкремент в цикле for
        }
    }
}

bool boolean::parseInput(const char* input) {
    if (input[0] == '{' && input[strlen(input)-1] == '}') {
        char temp[max_length];
        strncpy(temp, input + 1, strlen(input) - 2);
        temp[strlen(input) - 2] = '\0';
        extractElements(temp);
    }
    else {
        extractElements(input);
    }
    return true;
}

bool boolean::readInputFromFile(const char* filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error! Can't open file " << filename << endl;
        return false;
    }

    char line[max_length];
    elementCount = 0;

    if (inputFile.getline(line, max_length)) {
        parseInput(line);
    }

    inputFile.close();
    return true;
}

void boolean::generateBoolean() {
    powerSet.clear();
    int totalSubSets = 1 << elementCount;

    for (int i = 0; i < totalSubSets; i++) {
        vector<int> subset;
        for (int j = 0; j < elementCount; j++) {
            if (i & (1 << j)) {
                subset.push_back(j);
            }
        }
        powerSet.push_back(subset);
    }
}

void boolean::printResult() const {
    cout << "Boolean S = {";
    for (int i = 0; i < elementCount; i++) {
        cout << inputSet[i];
        if (i != elementCount - 1) cout << ", ";
    }
    cout << "}:\n{\n";

    cout << "  {},\n"; // Пустое множество
    for (const auto& subset : powerSet) {
        if (subset.empty()) continue; // Пропускаем пустое множество, так как уже вывели
        cout << "  {";
        for (size_t i = 0; i < subset.size(); i++) {
            cout << inputSet[subset[i]];
            if (i != subset.size() - 1) cout << ", ";
        }
        cout << "},\n";
    }
    cout << "}\n";
}

bool boolean::writeOutputFile(const char* filename) const {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cout << "Error: Can't create file " << filename << endl;
        return false;
    }

    outputFile << "Boolean S = {";
    for (int i = 0; i < elementCount; i++) {
        outputFile << inputSet[i];
        if (i != elementCount - 1) outputFile << ", ";
    }
    outputFile << "}:\n{\n";

    outputFile << "  {},\n"; // Пустое множество
    for (const auto& subset : powerSet) {
        if (subset.empty()) continue;
        outputFile << "  {";
        for (size_t i = 0; i < subset.size(); i++) {
            outputFile << inputSet[subset[i]];
            if (i != subset.size() - 1) outputFile << ", ";
        }
        outputFile << "},\n";
    }
    outputFile << "}\n";

    outputFile.close();
    return true;
}