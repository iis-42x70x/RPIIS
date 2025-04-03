```
//
// pch.h
//

#pragma once

#include "gtest/gtest.h"
#ifndef HEADER-H
#define HEADER_H

#include <vector>

namespace ArrayLib {
    void inputArray(std::vector<int>& arr);

    void sortArray(std::vector<int>& arr);

    int searchElement(const std::vector<int>& arr, int element);

    void insertIntoSortedArray(std::vector<int>& arr, int element);

    std::vector<int> unionSortedArrays(const std::vector<int>& arr1, const std::vector<int>& arr2);

    std::vector<int> intersectionSortedArrays(const std::vector<int>& arr1, const std::vector<int>& arr2);

    void printArray(const std::vector<int>& arr);

}

#endif // HEADER_H
```
