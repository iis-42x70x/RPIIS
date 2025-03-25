#include <gtest/gtest.h>
#include "header.h"

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(StringToVectorOfSetElementsTest, BasicCases) {
    EXPECT_EQ(stringToVectorOfSetElements("{a, b, c}"), (std::vector<std::string>{"a", "b", "c"}));
    EXPECT_EQ(stringToVectorOfSetElements("{1,2,3}"), (std::vector<std::string>{"1", "2", "3"}));
    EXPECT_EQ(stringToVectorOfSetElements("{{x,y}, z}"), (std::vector<std::string>{"{x,y}", "z"}));
    EXPECT_EQ(stringToVectorOfSetElements("{  a , b  ,c  }"), (std::vector<std::string>{"a", "b", "c"}));
}

TEST(GeneratePermutationsTest, BasicCases) {
    std::vector<std::string> set1 = { "a", "b", "c" };
    auto permutations1 = generatePermutations(set1);
    EXPECT_EQ(permutations1.size(), 6); // 3! = 6

    std::vector<std::string> set2 = { "1", "2" };
    auto permutations2 = generatePermutations(set2);
    EXPECT_EQ(permutations2.size(), 2); // 2! = 2
    EXPECT_TRUE(std::find(permutations2.begin(), permutations2.end(), std::vector<std::string>{"1", "2"}) != permutations2.end());
    EXPECT_TRUE(std::find(permutations2.begin(), permutations2.end(), std::vector<std::string>{"2", "1"}) != permutations2.end());
}
