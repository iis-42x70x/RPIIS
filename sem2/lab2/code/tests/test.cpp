#include "pch.h"
#include"C:\Users\555\Desktop\учЄба\ѕиќ»в»—\2 семестр\ConsoleApplication1\ConsoleApplication1\Set.h"
#include"C:\Users\555\Desktop\учЄба\ѕиќ»в»—\2 семестр\ConsoleApplication1\ConsoleApplication1\Set.cpp"

// --- CustomSet Tests ---

TEST(CustomSetTest, AddElementAndSize) {
    CustomSet set;
    set.addElement(5);
    set.addElement(std::string("abc"));
    EXPECT_EQ(set.size(), 2);
}

TEST(CustomSetTest, ContainsElement) {
    CustomSet set;
    set.addElement(42);
    set.addElement(std::string("xyz"));
    EXPECT_TRUE(set.contains(42));
    EXPECT_FALSE(set.contains(17));
    EXPECT_TRUE(set.contains(std::string("xyz")));
}

TEST(CustomSetTest, DifferenceWithDuplicates) {
    CustomSet set1;
    set1.addElement(1);
    set1.addElement(2);
    set1.addElement(2);
    set1.addElement(3);

    CustomSet set2;
    set2.addElement(2);

    CustomSet diff = set1.difference(set2);
    EXPECT_EQ(diff.size(), 3);
    EXPECT_TRUE(diff.contains(1));
    EXPECT_TRUE(diff.contains(2)); // одна 2 остаЄтс€
    EXPECT_TRUE(diff.contains(3));
}

TEST(CustomSetTest, ToStringOutput) {
    CustomSet set;
    set.addElement(1);
    set.addElement(std::string("abc"));
    set.addElement(std::vector<int>{1, 2});
    set.addElement(std::unordered_set<std::string>{"a", "b"});

    std::string result = set.toString();
    EXPECT_TRUE(result.find("1") != std::string::npos);
    EXPECT_TRUE(result.find("abc") != std::string::npos);
    EXPECT_TRUE(result.find("<1, 2>") != std::string::npos);
    EXPECT_TRUE(result.find("{a, b}") != std::string::npos || result.find("{b, a}") != std::string::npos);
}

TEST(CustomSetTest, ParseSimpleSet) {
    std::string input = "{1, 2, <3, 4>, {a, b}}";
    CustomSet set = CustomSet::parseFromString(input);
    EXPECT_EQ(set.size(), 4);
}

// --- isValid Tests ---

TEST(IsValidTest, ValidSimple) {
    EXPECT_TRUE(isValid("{1, 2, 3}"));
    EXPECT_TRUE(isValid("{1, {2, 3}, <4, 5>}"));
    EXPECT_TRUE(isValid("{{1, 2}, {3, <4>}}"));
    EXPECT_TRUE(isValid("{<1, 2>, {}, 3}"));
}

TEST(IsValidTest, ValidComplexNested) {
    EXPECT_TRUE(isValid("{1, 2, 3, 56, {}, {3, <34, 28>}, {4, 5}, <>, <1, 2>, <8, 9>, 1, 2, 3, 56, {}}"));
    EXPECT_TRUE(isValid("{1, 1, 2, 2, 3, 3, 56, {}, {3, <34, 28>}, {4, 5}, <>, <1, 2>, <8, 9>, 56, {}}"));
}

TEST(IsValidTest, InvalidMissingBrackets) {
    EXPECT_FALSE(isValid("{1, 2, 3"));
    EXPECT_FALSE(isValid("1, 2, 3}"));
    EXPECT_FALSE(isValid("{{1, 2}, {3, 4}")); 
}

TEST(IsValidTest, InvalidMalformed) {
    EXPECT_FALSE(isValid("{<}>"));          
    EXPECT_FALSE(isValid("{1,,2}"));     
}

