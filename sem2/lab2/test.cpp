#include "pch.h"
#include "lab2.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(SetOperationsTest, UnionSets) {
    
    vector<string> sets = { "1,2", "2,3" };
    string result;
    unionSets(sets, result);
    EXPECT_EQ(result, "{1,2,3}");

   
    vector<string> nestedSets = { "1,{4,3}", "2,{3,4}" };
    unionSets(nestedSets, result);
    EXPECT_EQ(result, "{1,{4,3},2,{3,4}}");

    
}
TEST(SetOperationsTest, UnionSets2) {

    vector<string> sets = { "a,b", "b,c" };
    string result;
    unionSets(sets, result);
    EXPECT_EQ(result, "{a,b,c}");


    vector<string> nestedSets = { "a,{b,c}", "h,{c,b}" };
    unionSets(nestedSets, result);
    EXPECT_EQ(result, "{a,{b,c},h,{c,b}}");


}
