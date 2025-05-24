#include <gtest/gtest.h>
#include "SetParser.h"



TEST(ParseTest, SimpleSet) 
{
    auto result = string_to_vector("{a,b,c}");
    EXPECT_EQ(result, (std::vector<std::string>{"a", "b", "c"}));
}

TEST(ParseTest, EmptySet) 
{
    auto result = string_to_vector("{}");
    EXPECT_TRUE(result.empty());
}

TEST(ParseTest, SetWithWhitespace) // Лишние пробелы
{
    auto result = string_to_vector("{ a , b , c }");
    
    EXPECT_EQ(result, (std::vector<std::string>{" a ", " b ", " c "}));
}

TEST(ParseTest, NoBraces) // Нет фигурных скобок
{
    auto result = string_to_vector("a,b,c");
    EXPECT_TRUE(result.empty()); 
}

TEST(ParseTest, MalformedInput_UnclosedBrace) // нет закрытия
{ 
    auto result = string_to_vector("{a,b,c");
    EXPECT_TRUE(result.empty());
}

TEST(ParseTest, SingleElementSet) // словл
{
    auto result = string_to_vector("{solo}");
    EXPECT_EQ(result, (std::vector<std::string>{"solo"}));
}

TEST(CartesianTest, TwoSets) {
    std::vector<std::vector<std::string>> sets = {
        {"1", "2"},
        {"a", "b"}
    };
    auto result = cartesianProduct(sets);
    EXPECT_EQ(result.size(), 4);
    EXPECT_TRUE(std::find(result.begin(), result.end(), std::vector<std::string>{"1", "a"}) != result.end());
    EXPECT_TRUE(std::find(result.begin(), result.end(), std::vector<std::string>{"2", "b"}) != result.end());
}

TEST(CartesianTest, ThreeSetsWithSingleElement) {
    std::vector<std::vector<std::string>> sets = {
        {"x"},
        {"y"},
        {"z"}
    };
    auto result = cartesianProduct(sets);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], (std::vector<std::string>{"x", "y", "z"}));
}

TEST(CartesianTest, OneEmptySet) {
    std::vector<std::vector<std::string>> sets = {
        {"1", "2"},
        {},
        {"a", "b"}
    };
    auto result = cartesianProduct(sets);
    EXPECT_TRUE(result.empty());
}

TEST(CartesianTest, AllEmptySets) {
    std::vector<std::vector<std::string>> sets = {
        {},
        {},
        {}
    };
    auto result = cartesianProduct(sets);
    EXPECT_TRUE(result.empty());
}

TEST(CartesianTest, LargeSetCombination) {
    std::vector<std::vector<std::string>> sets = {
        {"a", "b", "c", "d", "e"},
        {"1", "2", "3"},
        {"x", "y"}
    };
    auto result = cartesianProduct(sets);
    EXPECT_EQ(result.size(), 5 * 3 * 2);
}

TEST(CartesianTest, SingleSet) {
    std::vector<std::vector<std::string>> sets = {
        {"a", "b", "c"}
    };
    auto result = cartesianProduct(sets);
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0].size(), 1);
}

TEST(CartesianTest, NoSets) {
    std::vector<std::vector<std::string>> sets = {};
    auto result = cartesianProduct(sets);
    EXPECT_EQ(result.size(), 1); 
    EXPECT_TRUE(result[0].empty());
}
