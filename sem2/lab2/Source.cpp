#include "pch.h"

bool CheckParentheses(const std::string& input) {
    std::vector<char> stack;
    for (char c : input) {
        if (c == '{' || c == '<' || c == '(') {
            stack.push_back(c);
        }
        else if (c == '}' || c == '>' || c == ')') {
            if (stack.empty()) return false;
            char openBracket = stack.back();
            stack.pop_back();
            if ((c == '}' && openBracket != '{') ||
                (c == '>' && openBracket != '<') ||
                (c == ')' && openBracket != '(')) {
                return false;
            }
        }
    }
    return stack.empty();
}

bool IsValidSymbol(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || c == '{' || c == '}' ||
        c == '<' || c == '>' || c == '(' || c == ')' ||
        c == ',' || c == ' ';
}

bool ValidateInputString(const std::string& input) {
    // Проверяем наличие скобок только если они есть в строке
    bool hasBraces = (input.find('{') != std::string::npos ||
        input.find('<') != std::string::npos);

    if (hasBraces) {
        if (input.empty() ||
            (input.front() != '{' && input.front() != '<') ||
            (input.back() != '}' && input.back() != '>')) {
            return false;
        }
    }

    for (char c : input) {
        if (!IsValidSymbol(c)) {
            std::cerr << "Error: Invalid character '" << c << "'\n";
            return false;
        }
    }

    if (hasBraces) {
        return CheckParentheses(input);
    }
    return true; // Если скобок нет, считаем валидным
}

int ParseElements(std::vector<std::string>& resultSet, const std::string& inputStr) {
    std::string currentElement;
    int braceCount = 0, angleCount = 0, roundCount = 0;

    for (char s : inputStr) {
        switch (s) {
        case '{': braceCount++; break;
        case '}': braceCount--; break;
        case '<': angleCount++; break;
        case '>': angleCount--; break;
        case '(': roundCount++; break;
        case ')': roundCount--; break;
        }

        if (s == ',' && braceCount == 0 && angleCount == 0 && roundCount == 0) {
            if (!currentElement.empty()) {
                resultSet.push_back(currentElement);
                currentElement.clear();
            }
        }
        else {
            currentElement.push_back(s);
        }
    }

    if (!currentElement.empty()) {
        resultSet.push_back(currentElement);
    }

    return (braceCount != 0 || angleCount != 0 || roundCount != 0) ? 1 : 0;
}

bool HasDuplicates(const std::vector<std::string>& elements) {
    std::unordered_set<std::string> uniqueElements;
    for (const auto& elem : elements) {
        if (uniqueElements.count(elem)) {
            std::cerr << "Error: Duplicate element '" << elem << "'\n";
            return true;
        }
        uniqueElements.insert(elem);
    }
    return false;
}

void TrimOuterBraces(std::string& line) {
    if (line.empty()) return;

    if ((line.front() == '{' && line.back() == '}') ||
        (line.front() == '<' && line.back() == '>')) {
        line = line.substr(1, line.size() - 2);
    }
}

std::vector<std::string> ProcessInput(const std::string& input) {
    std::string noSpaces;
    for (char c : input) {
        if (c != ' ') noSpaces += c;
    }

    size_t equalPos = noSpaces.find('=');
    std::string line = (equalPos != std::string::npos) ?
        noSpaces.substr(equalPos + 1) : noSpaces;

    if (!ValidateInputString(line)) {
        std::cerr << "Structure error in: " << line << "\n";
        return {};
    }

    TrimOuterBraces(line);
    std::vector<std::string> elements;

    if (ParseElements(elements, line) != 0 || HasDuplicates(elements)) {
        return {};
    }
    return elements;
}

void GenerateAllPermutations(const std::vector<std::string>& elements,
    std::vector<std::vector<std::string>>& result) {
    std::vector<std::string> temp = elements;
    do {
        result.push_back(temp);
    } while (std::next_permutation(temp.begin(), temp.end()));
}
