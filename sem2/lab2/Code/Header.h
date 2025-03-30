#pragma once
#include <iostream>
#include <fstream>
#include <string>

#ifndef SYMM_DIFF_HPP
#define SYMM_DIFF_HPP

using namespace std;

struct Element {
    int multiplicity = 1;
    string element;
    int code_num = 0;
    bool IsAlone = false;
};

struct Set {
    Element Elem[123];
    int elem_count = 1;
    int set_count;
    int brackets_count;
};

void GetSets(Set[], string);
void SeeSets(Set[]);
void OneType(Set[]);
void SymmDiff(Set[]);
void Do_Symm_Diff(Set[], string);



#endif

