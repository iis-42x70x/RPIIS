#pragma once
#ifndef ORIENTED_SETS_H
#define ORIENTED_SETS_H
using namespace std;
#include <vector>
#include <stdexcept>

template <typename T>
class OrientedSetsGenerator {
public:
    static vector<vector<T>> generateAllOrientedSets(const vector<T>& inputSet, size_t n);

private:
    static void generatePermutations(const vector<T>& elements, size_t n,
        vector<bool>& used, vector<T>& current,
        vector<vector<T>>& result);
};

#include "OrientedSets.cpp"

#endif 
