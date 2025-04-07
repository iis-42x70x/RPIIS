#ifndef HEADER_H
#define HEADER_H
#pragma once

#include "gtest/gtest.h"
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>


std::string formatSet(const std::vector<std::string>& elements);
void generateOrientations(std::vector<std::string> elements, std::set<std::string>& result);
std::set<std::string> generateAllOrientations(const std::vector<std::string>& inputElements);
void writeInput(const std::string& filename, const std::set<std::string>& inputSet);
std::set<std::string> readInput(const std::string& filename);
std::vector<std::string> parseInput(const std::string& inputLine);

#endif 