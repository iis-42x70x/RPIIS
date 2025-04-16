#pragma once
#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <stack>

using namespace std;

enum ElementType { STRING, SET, ORSET };

struct element {
    ElementType type;
    string value;
    vector<element> setik;
};

bool letter(char);
bool digit(char);
bool space(char);
bool ElementCompare(const element, const element);
element intersection(const element, const element);
void ElementCout(const element);
void StringToElement(element&, string, int, int);
bool SetUniqueCheck(element);
bool StringCheck(string&);

#endif
