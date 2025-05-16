
#ifndef Header_h
#define Header_h

#include <iostream>
#include <string>

using namespace std;
std::string removeSpaces(const std::string& s);
std::string sortString(std::string s);
std::string sortNestedSet(const std::string& s);
bool areElementsEqual(const std::string& elem1, const std::string& elem2);
void extractElements(const std::string& s, std::string* elements, int& count);
void removeDuplicates(int& resultCount, std::string* result);
void symmetricDifference(std::string* set1, int count1, std::string* set2, int count2, std::string* result, int& resultCount);
void save(const std::string* sets, int sets_count, const std::string* elements1, int count1, const std::string& filename);
void load(std::string* sets, int& sets_count, std::string* elements1, int& count1, const std::string& filename);

#endif
