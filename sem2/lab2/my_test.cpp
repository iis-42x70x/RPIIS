#include <gtest/gtest.h>
#include "header.h"

TEST(NormalizeSetTest, RemovesSpacesAndSortsElements) {
    string input = "  { c, b , a } ";
    string expected = "a,b,c";
    EXPECT_EQ(normalizeSet(input), expected);
}

TEST(NormalizeSetTest, HandlesNestedSets) {
    string input = "{ {1,2}, {3,4} }";
    string expected = "{1,2},{3,4}";
    EXPECT_EQ(normalizeSet(input), expected);
}

TEST(SplitElementsTest, NestedBraces) {
   string input = "a,{b,c},d";
   vector<string> expected = { "a", "{b,c}", "d" };
   vector<string> result = splitElements(input);
   ASSERT_EQ(result, expected);
}

TEST(DifferenceSetsTest, CalculatesDifferenceBetweenSets) {
    vector<string> sets = { "{a,b,c}", "{b,c}" };
    string result;
    differenceSets(sets, result);
    EXPECT_EQ(result, "{a}");
}

TEST(DifferenceSetsTest, ReturnsEmptySetWhenNoDifference) {
    vector<string> sets = { "{b,c}", "{b,c}" };
    string result;
    differenceSets(sets, result);
    EXPECT_EQ(result, "{}");
}
