#include "pch.h"
#include "lab2.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(SetOperationsTest, BubbleSort) {
    vector<string> items = { "c", "a", "b" };
    bubbleSort(items);
    vector<string> expected = { "a", "b", "c" };
    EXPECT_EQ(items, expected); 

    vector<string> empty;
    bubbleSort(empty);
    EXPECT_TRUE(empty.empty());
}
TEST(SetOperationsTest, SortSubset) {
    
    string subset = "{3,1,2}";
    string result = sortSubset(subset);
    EXPECT_EQ(result, "{1,2,3}");

    string nested = "{3,{5,4},1}";
    string nestedResult = sortSubset(nested);
    EXPECT_EQ(nestedResult, "{1,3,{4,5}}");

}
TEST(SetOperationsTest, ExtractAndSortElements) {

    string setString = "{3,1,2}";
    vector<string> result = extractAndSortElements(setString);
    vector<string> expected = { "{1,2,3}" };
    EXPECT_EQ(result, expected);

   
    string nestedSet = "{3,{5,4},1}";
    vector<string> nestedResult = extractAndSortElements(nestedSet);
    vector<string> nestedExpected = { "{1,3,{4,5}}" };
    EXPECT_EQ(nestedResult, nestedExpected);

}
TEST(SetOperationsTest, UnionSets) {
    
    vector<string> sets = { "1,2", "2,3" };
    string result;
    unionSets(sets, result);
    EXPECT_EQ(result, "{1,2,3}");

   
    vector<string> nestedSets = { "1,{4,3}", "2,{3,4}" };
    unionSets(nestedSets, result);
    EXPECT_EQ(result, "{1,{3,4},2}");

    
}
