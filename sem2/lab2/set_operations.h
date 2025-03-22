#ifndef SET_OPERATIONS_H
#define SET_OPERATIONS_H

#include <iostream>
#include <vector>
#include <string>
std::vector<std::string> tokenize(const std::string& s);

void processSet(const std::string& input, std::vector<std::string>& elements);

void createAndFillFile(const std::string& filename);

std::vector<std::string> intersection(const std::vector<std::vector<std::string>>& sets);

#endif 
