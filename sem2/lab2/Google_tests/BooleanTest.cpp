#include "gtest/gtest.h"
#include "Set_lib/Set.hpp"
#include <iostream>
#include <vector>

TEST(SetTest, IsCorrectName) {
    Set arg;
    EXPECT_TRUE(arg.is_correct_name("Valid_Name123"));
    EXPECT_FALSE(arg.is_correct_name("Invalid-Name"));
    EXPECT_FALSE(arg.is_correct_name(""));
}

TEST(SetTest, ParseElementSimpleName) {
    string input = "Element1";
    size_t pos = 0;
    string result;
    EXPECT_TRUE(Set().parse_element(input, pos, result));
    EXPECT_EQ(result, "Element1");
}

TEST(SetTest, ParseElementNestedSet) {
    string input = "{a,b,c}";
    size_t pos = 0;
    string result;
    EXPECT_TRUE(Set().parse_element(input, pos, result));
    EXPECT_EQ(result, "{a,b,c}");
}

TEST(SetTest, ParseSetBasic) {
    string input = "{a,b,a}";
    size_t pos = 0;
    vector<Element> elements;
    EXPECT_TRUE(Set().parse_set(input, pos, elements));
    ASSERT_EQ(elements.size(), 2);
    EXPECT_EQ(elements[0].value, "a");
    EXPECT_EQ(elements[0].count, 2);
    EXPECT_EQ(elements[1].value, "b");
    EXPECT_EQ(elements[1].count, 1);
}

TEST(SetTest, DifferenceBasic) {
    vector<Element> a = {{"x", 2}, {"y", 1}};
    vector<Element> b = {{"x", 1}};
    Set setA(a);
    Set setB(b);
    Set result = setA.difference(setB);
    vector<Element> res_elements = result.get_elements();
    ASSERT_EQ(res_elements.size(), 2);
    EXPECT_EQ(res_elements[0].value, "x");
    EXPECT_EQ(res_elements[0].count, 1);
    EXPECT_EQ(res_elements[1].value, "y");
    EXPECT_EQ(res_elements[1].count, 1);
}
