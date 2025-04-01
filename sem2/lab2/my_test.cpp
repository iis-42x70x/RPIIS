#include <gtest/gtest.h>
#include "header.h"

TEST(NormalizeSetTest, RemovesSpacesAndSortsElements) {
    std::string input = "  { c, b , a } ";
    std::string expected = "a,b,c";
    EXPECT_EQ(normalizeSet(input), expected);
}

TEST(NormalizeSetTest, HandlesNestedSets) {
    std::string input = "{ {1,2}, {3,4} }";
    std::string expected = "{1,2},{3,4}";
    EXPECT_EQ(normalizeSet(input), expected);
}



TEST(DifferenceSetsTest, CalculatesDifferenceBetweenSets) {
    std::vector<std::string> sets = { "{a,b,c}", "{b,c}" };
    std::string result;
    differenceSets(sets, result);
    EXPECT_EQ(result, "{a}");
}

TEST(DifferenceSetsTest, ReturnsEmptySetWhenNoDifference) {
    std::vector<std::string> sets = { "{b,c}", "{b,c}" };
    std::string result;
    differenceSets(sets, result);
    EXPECT_EQ(result, "{}");
}