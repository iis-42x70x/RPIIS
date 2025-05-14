#include "pch.h"
#include <gtest/gtest.h>

class SetOperationsTest : public ::testing::Test {
protected:
    void SetUp() override {
        permutations.clear();
        elements.clear();
    }
    std::vector<std::vector<std::string>> permutations;
    std::vector<std::string> elements;
};

TEST_F(SetOperationsTest, ParenthesesValidation) {
    EXPECT_TRUE(CheckParentheses("{}"));
    EXPECT_TRUE(CheckParentheses("{a,b}"));
    EXPECT_TRUE(CheckParentheses("<a,(b,c)>"));
    EXPECT_FALSE(CheckParentheses("{"));
    EXPECT_FALSE(CheckParentheses("}"));
    EXPECT_FALSE(CheckParentheses("{a,b))"));
    EXPECT_FALSE(CheckParentheses("{(})"));
}

TEST_F(SetOperationsTest, SymbolValidation) {
    EXPECT_TRUE(IsValidSymbol('a'));
    EXPECT_TRUE(IsValidSymbol('Z'));
    EXPECT_TRUE(IsValidSymbol('0'));
    EXPECT_TRUE(IsValidSymbol('{'));
    EXPECT_TRUE(IsValidSymbol(' '));
    EXPECT_FALSE(IsValidSymbol('!'));
    EXPECT_FALSE(IsValidSymbol('@'));
    EXPECT_FALSE(IsValidSymbol('\n'));
}

TEST_F(SetOperationsTest, InputValidation) {
    EXPECT_TRUE(ValidateInputString("{a,b}")); 
    EXPECT_TRUE(ValidateInputString("a,b"));   
    EXPECT_TRUE(ValidateInputString("<1,2,3>")); 
    EXPECT_FALSE(ValidateInputString("{a,!b}"));
    EXPECT_FALSE(ValidateInputString("{a\nb}")); 
}

TEST_F(SetOperationsTest, ElementParsing) {
    EXPECT_EQ(ParseElements(elements, "a,b"), 0);
    ASSERT_EQ(elements.size(), 2);
    EXPECT_EQ(elements[0], "a");
    EXPECT_EQ(elements[1], "b");

    elements.clear();
    EXPECT_EQ(ParseElements(elements, "<1,2>,3"), 0);
    ASSERT_EQ(elements.size(), 2);
    EXPECT_EQ(elements[0], "<1,2>");
    EXPECT_EQ(elements[1], "3");
}

TEST_F(SetOperationsTest, DuplicateDetection) {
    std::vector<std::string> unique = { "a", "b" };
    std::vector<std::string> duplicates = { "a", "a" };
    EXPECT_FALSE(HasDuplicates(unique));
    EXPECT_TRUE(HasDuplicates(duplicates));
}

TEST_F(SetOperationsTest, BraceTrimming) {
    std::string s1 = "{a}";
    std::string s2 = "<b>";
    std::string s3 = "plain";
    TrimOuterBraces(s1);
    TrimOuterBraces(s2);
    TrimOuterBraces(s3);
    EXPECT_EQ(s1, "a");
    EXPECT_EQ(s2, "b");
    EXPECT_EQ(s3, "plain");
}

TEST_F(SetOperationsTest, InputProcessing) {
    auto result = ProcessInput("{a,b}");
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "b");

    result = ProcessInput("{}");
    EXPECT_TRUE(result.empty());
}

TEST_F(SetOperationsTest, PermutationGeneration) {
    std::vector<std::string> input = { "a", "b" };
    GenerateAllPermutations(input, permutations);
    ASSERT_EQ(permutations.size(), 2);
    EXPECT_EQ(permutations[0], std::vector<std::string>({ "a", "b" }));
    EXPECT_EQ(permutations[1], std::vector<std::string>({ "b", "a" }));
}

