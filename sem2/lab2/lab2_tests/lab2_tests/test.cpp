#include "pch.h"
#include "gtest/gtest.h"

TEST(SetIntersectionTest, OneCommonElement) {
    std::vector<std::string> sets = {
        "a,b",
        "b,c"
    };
    auto result = intersect_sets(sets);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result["b"], 1);
}

TEST(SetIntersectionTest, DuplicateElementCounts) {
    std::vector<std::string> sets = {
        "a,a,b",
        "a,b,b",
        "a,a,b"
    };
    auto result = intersect_sets(sets);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result["a"], 1);
    EXPECT_EQ(result["b"], 1);
}

TEST(SetIntersectionTest, SetAsElementEqualUnordered) {
    std::vector<std::string> sets = {
        "{a,b},{b,a}",
        "{b,a},{a,b}",
        "{a,b}"
    };
    auto result = intersect_sets(sets);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result["{a,b}"], 1);
}

TEST(SetIntersectionTest, SetInsideMixedOrder) {
    std::vector<std::string> sets = {
        "a,{b,c}",
        "{c,b},a",
        "a,{b,c}"
    };
    auto result = intersect_sets(sets);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result["a"], 1);
    EXPECT_EQ(result["{b,c}"], 1);
}

TEST(SetIntersectionTest, MixedFlatNestedUnordered) {
    std::vector<std::string> sets = {
        "{x,y,{a,b}},{a,b},{b,a},z",
        "z,{b,a},{{b,a},x,y},{y,x,{b,a}}",
        "{a,b},z,{y,x,{a,b}}"
    };
    auto result = intersect_sets(sets);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result["z"], 1);
    EXPECT_EQ(result["{a,b}"], 1);
}