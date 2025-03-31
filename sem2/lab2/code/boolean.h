//
// Created by Bibko Vladislav on 30.03.2025.
//

#ifndef BOOLEAN_H
#define BOOLEAN_H

#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

class boolean{
private:
  static const int max_length = 100;
  static const int max_element = 100;
  char inputSet[max_element][max_length];
  int elementCount;
  vector<vector<int>> powerSet;

  bool checkelement(const char* element);
public:
  boolean();
  bool readInputFromFile(const char* filename);
  void generateBoolean();
  void printResult() const;
  bool writeOutputFile(const char* filename) const;
};
#endif //BOOLEAN_H
