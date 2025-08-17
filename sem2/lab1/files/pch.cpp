```
//
// pch.cpp
//

#include "pch.h"
#include <iostream>
#include <algorithm> 

namespace ArrayLib {

    void inputArray(std::vector<int>& arr) {
        int n;
        std::cout << "Введите количество элементов массива: ";
        std::cin >> n;
        arr.resize(n);
        std::cout << "Введите элементы массива:\n";
        for (int i = 0; i < n; i++) {
            std::cout << "Элемент " << i << ": ";
            std::cin >> arr[i];
        }
    }

    void printArray(const std::vector<int>& arr) {
        for (int x : arr) {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }

    void sortArray(std::vector<int>& arr) {
        std::sort(arr.begin(), arr.end());
    }

    int searchElement(const std::vector<int>& arr, int element) {
        int left = 0;
        int right = (int)arr.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == element)
                return mid;
            else if (arr[mid] < element)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }

    void insertIntoSortedArray(std::vector<int>& arr, int element) {
        int pos = 0;
        while (pos < (int)arr.size() && arr[pos] < element) {
            pos++;
        }
        arr.insert(arr.begin() + pos, element);
    }

    std::vector<int> unionSortedArrays(const std::vector<int>& arr1, const std::vector<int>& arr2) {
        std::vector<int> result;
        size_t i = 0, j = 0;
        while (i < arr1.size() && j < arr2.size()) {
            if (arr1[i] < arr2[j]) {
                if (result.empty() || result.back() != arr1[i]) {
                    result.push_back(arr1[i]);
                }
                i++;
            }
            else if (arr1[i] > arr2[j]) {
                if (result.empty() || result.back() != arr2[j]) {
                    result.push_back(arr2[j]);
                }
                j++;
            }
            else {
                if (result.empty() || result.back() != arr1[i]) {
                    result.push_back(arr1[i]);
                }
                i++;
                j++;
            }
        }
        while (i < arr1.size()) {
            if (result.empty() || result.back() != arr1[i]) {
                result.push_back(arr1[i]);
            }
            i++;
        }
        while (j < arr2.size()) {
            if (result.empty() || result.back() != arr2[j]) {
                result.push_back(arr2[j]);
            }
            j++;
        }
        return result;
    }

    std::vector<int> intersectionSortedArrays(const std::vector<int>& arr1, const std::vector<int>& arr2) {
        std::vector<int> result;
        size_t i = 0, j = 0;
        while (i < arr1.size() && j < arr2.size()) {
            if (arr1[i] < arr2[j]) {
                i++;
            }
            else if (arr1[i] > arr2[j]) {
                j++;
            }
            else {
                if (result.empty() || result.back() != arr1[i]) {
                    result.push_back(arr1[i]);
                }
                i++;
                j++;
            }
        }
        return result;
    }
}
```
