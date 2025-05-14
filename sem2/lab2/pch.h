#pragma once
#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

bool CheckParentheses(const std::string& input);
bool IsValidSymbol(char c);
bool ValidateInputString(const std::string& input);
int ParseElements(std::vector<std::string>& resultSet, const std::string& inputStr);
bool HasDuplicates(const std::vector<std::string>& elements);
void TrimOuterBraces(std::string& line);
std::vector<std::string> ProcessInput(const std::string& input);
void GenerateAllPermutations(const std::vector<std::string>& elements,
    std::vector<std::vector<std::string>>& result);

#endif
