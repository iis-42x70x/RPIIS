//
// Created by Bibko Vladislav on on 30.03.2025.
//

#include "boolean.h"

boolean :: boolean() : elementCount(0){
  for(int i = 0; i < max_element; i++){
    inputSet[i][0] = '\0';
  }
}

bool boolean :: checkelement(const char* element){
  if(element[0] == '\0'){
    cout << "Error! Empty element on data!" << endl;
    return false;
  }
  if(strlen(element) > max_length){
    cout << "Error: Maximum length exceeded!" << endl;
    return false;
  }
  return true;
}

bool boolean :: readInputFromFile(const char* filename){
  ifstream inputFile(filename);
  if(!inputFile.is_open()){
    cout << "Error! Can't open file!" << filename << endl;
    return false;
  }
  char element[max_length];
  elementCount = 0;

  while (inputFile >> element && elementCount < max_element){
    if(!checkelement(element)){
      inputFile.close();
      return false;
    }
    strncpy(inputSet[elementCount], element, max_element - 1);
    inputSet[elementCount][max_length - 1] = '\0';
    elementCount++;
  }
  inputFile.close();
  return true;
}

void boolean :: generateBoolean(){
  powerSet.clear();
  if (elementCount == 0) {  // Если элементов нет
    cout << "NON DATA" << endl;
    return;
  }
  int totalSubSets = 1 << elementCount;
  for(int i = 0; i < totalSubSets; i++){
    vector<int> indexSubSets;
    for(int j = 0; j < elementCount; j++){
      if(i & (1 << j)){
        indexSubSets.push_back(j);
      }
    }
    powerSet.push_back(indexSubSets);
  }
}

void boolean :: printResult() const{
  cout << "ELEM " << elementCount << endl;
  cout << "Boolean contains " << powerSet.size() << " subsets." << endl;
  for(size_t i = 0; i < powerSet.size(); i++){
    const vector<int>& indexSubSets = powerSet[i];
    cout << "{ ";
    for (size_t j = 0; j < indexSubSets.size(); j++){
      cout << inputSet[indexSubSets[j]] << " ";
    }
    cout << "}" << endl;
  }
}

bool boolean :: writeOutputFile(const char* filename) const{
  ofstream outputFile(filename);
  if(!outputFile.is_open()){
    cout << "Error: Can't create file!" << filename << endl;
    return false;
  }

  outputFile << powerSet.size() << endl;
  for(size_t i = 0; i < powerSet.size(); i++){
    const vector<int>& indexSubSets = powerSet[i];
    for (size_t j = 0; j < indexSubSets.size(); j++){
      int Index = indexSubSets[j];
      outputFile << inputSet[indexSubSets[j]] << " ";
    }
    outputFile << endl;
  }
  outputFile.close();
  return true;
}