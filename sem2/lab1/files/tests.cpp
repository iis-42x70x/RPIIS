```
#include "pch.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
#include <gtest/gtest.h>
#include <vector>

using namespace ArrayLib;


TEST(ArrayLibTest, SortArray) {
    std::vector<int> arr = { 5, 3, 8, 1, 2 };
    sortArray(arr);
    EXPECT_EQ(arr, (std::vector<int>{1, 2, 3, 5, 8}));
}

TEST(ArrayLibTest, SearchElement) {
    std::vector<int> arr = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(searchElement(arr, 3), 2);
    EXPECT_EQ(searchElement(arr, 6), -1);
}

TEST(ArrayLibTest, InsertIntoSortedArray) {
    std::vector<int> arr = { 1, 3, 5, 7 };
    insertIntoSortedArray(arr, 4);
    EXPECT_EQ(arr, (std::vector<int>{1, 3, 4, 5, 7}));
}

TEST(ArrayLibTest, UnionSortedArrays) {
    std::vector<int> arr1 = { 1, 3, 5 };
    std::vector<int> arr2 = { 2, 3, 6 };
    std::vector<int> result = unionSortedArrays(arr1, arr2);
    EXPECT_EQ(result, (std::vector<int>{1, 2, 3, 5, 6}));
}

TEST(ArrayLibTest, IntersectionSortedArrays) {
    std::vector<int> arr1 = { 1, 2, 3, 4, 5 };
    std::vector<int> arr2 = { 3, 4, 5, 6, 7 };
    std::vector<int> result = intersectionSortedArrays(arr1, arr2);
    EXPECT_EQ(result, (std::vector<int>{3, 4, 5}));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

```
