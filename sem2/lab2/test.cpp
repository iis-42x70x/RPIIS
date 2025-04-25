#include "pch.h"
#include <gtest/gtest.h>
#include "SetParser.h"

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(string_to_vector_OfSetElementsTest, BasicCases) {
    EXPECT_EQ(string_to_vector_OfSetElements("{a,b,c}"), (std::vector<std::string>{"a", "b", "c"}));
    EXPECT_EQ(string_to_vector_OfSetElements("{1,2,3}"), (std::vector<std::string>{"1", "2", "3"}));
    EXPECT_EQ(string_to_vector_OfSetElements("{<x,y>,z}"), (std::vector<std::string>{"<x,y>", "z"}));
    EXPECT_EQ(string_to_vector_OfSetElements("{a,b,c}"), (std::vector<std::string>{"a", "b", "c"}));
}

TEST(string_to_vector_OfSetElementsTest, EmptySet) {
    std::vector<std::string> expected = {};
    EXPECT_EQ(string_to_vector_OfSetElements("{}"), expected);
}

TEST(string_to_vector_OfSetElementsTest, EmptyElements) {
  
    std::vector<std::string> expected = {};
    EXPECT_EQ(string_to_vector_OfSetElements("{,,}"), expected);
}

TEST(string_to_vector_OfSetElementsTest, InvalidInput) {
   
    std::vector<std::string> expected = {};
    EXPECT_EQ(string_to_vector_OfSetElements("{a, b, c"), expected);
}

TEST(generateUniquePermutationsTest, BasicCases) {
    std::vector<std::string> set1 = { "a", "b", "c" };
    auto permutations1 = generateUniquePermutations(set1);
    EXPECT_EQ(permutations1.size(), 6); // 3! = 6

    std::vector<std::string> set2 = { "1", "2" };
    auto permutations2 = generateUniquePermutations(set2);
    EXPECT_EQ(permutations2.size(), 2); // 2! = 2
    EXPECT_TRUE(std::find(permutations2.begin(), permutations2.end(), std::vector<std::string>{"1", "2"}) != permutations2.end());
    EXPECT_TRUE(std::find(permutations2.begin(), permutations2.end(), std::vector<std::string>{"2", "1"}) != permutations2.end());
}