#include "pch.h"
#include "Header.h"
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
TEST(SetOperationsTest, UnionSets) {

    vector<string> sets = { "1,2", "2,3" };
    string result;
    differenceSets(sets, result);
    EXPECT_EQ(result, "{1}");

    vector<string> nestedSets = { "1,{4,3}", "2,{3,4}" };
    differenceSets(nestedSets, result);
    EXPECT_EQ(result, "{1,{4,3}}");
}
TEST(SetOperationsTest, UnionSets) {

    vector<string> sets = { "5,n,{h,6},{2,t},k", "5,{2,t},k,l,3,17" };
    string result;
    differenceSets(sets, result);
    EXPECT_EQ(result, "n,{h,6}");

    vector<string> nestedSets = { "1,{a,b}", "2,{b,a}" };
    differenceSets(nestedSets, result);
    EXPECT_EQ(result, "{a,b}}");
}
