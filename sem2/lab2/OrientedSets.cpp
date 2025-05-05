#ifndef ORIENTED_SETS_CPP
#define ORIENTED_SETS_CPP

#include "OrientedSets.h"
#include <algorithm>
using namespace std;

template <typename T>
vector<vector<T>> OrientedSetsGenerator<T>::generateAllOrientedSets(const vector<T>& inputSet, size_t n) {
    if (n == 0) {
        throw invalid_argument("n must be greater than 0");
    }
    
    if (inputSet.empty()) {
        return {};
    }
    
    vector<T> uniqueElements = inputSet;
    sort(uniqueElements.begin(), uniqueElements.end());
    uniqueElements.erase(unique(uniqueElements.begin(), uniqueElements.end()), uniqueElements.end());
    
    vector<vector<T>> result;
    vector<bool> used(uniqueElements.size(), false);
    vector<T> current;
    
    generatePermutations(uniqueElements, n, used, current, result);
    
    return result;
}

template <typename T>
void OrientedSetsGenerator<T>::generatePermutations(const vector<T>& elements, size_t n, 
                                                 vector<bool>& used, vector<T>& current, 
                                                 vector<vector<T>>& result) {
    if (current.size() == n) {
        result.push_back(current);
        return;
    }
    
    for (size_t i = 0; i < elements.size(); ++i) {
        if (!used[i]) {
            used[i] = true;
            current.push_back(elements[i]);
            
            generatePermutations(elements, n, used, current, result);
            
            current.pop_back();
            used[i] = false;
        }
    }
}

#endif 
