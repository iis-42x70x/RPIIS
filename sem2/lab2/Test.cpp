#include <gtest/gtest.h>

#include "UnionOfSets.h" 

using namespace std;

TEST(RunTestcaseTest, SubsetPermutation) {
    int num_sets = 0;
    vector<vector<string>> sets;
    run_testcase("permutation.txt", num_sets, sets);
    vector<vector<string>> expected_sets = { {"{a b}", "{a b}"}, {"{a b}"} };
    ASSERT_EQ(num_sets, expected_sets.size());

    for (int i = 0; i < num_sets; ++i) {
        ASSERT_EQ(sets[i], expected_sets[i]);
    }
}

TEST(RunTestcaseTest, FileNotFoundTest) {
    int num_sets = 0;
    vector<vector<string>> sets;
    run_testcase("non_existent_file.txt", num_sets, sets);
    ASSERT_EQ(num_sets, 0);
    ASSERT_TRUE(sets.empty());
}

TEST(CountMultiplicitiesTest, SingleSetTest) {
    vector<vector<string>> sets = { {"aa", "b", "b", "{}"} };
    vector<vector<pair<string, int>>> expected_counts = { {{"aa", 1}, {"b", 2}, {"{}", 1}} };
    ASSERT_EQ(CountMultiplicities(sets), expected_counts);
}

TEST(CountMultiplicitiesTest, MultipleSetsTest) {
    vector<vector<string>> sets = { {"a", "b", "b", "c"}, {"x", "y", "z", "x", "y"} };
    vector<vector<pair<string, int>>> expected_counts = { {{"a", 1}, {"b", 2}, {"c", 1}}, {{"x", 2}, {"y", 2}, {"z", 1}} };
    ASSERT_EQ(CountMultiplicities(sets), expected_counts);
}

TEST(FindMaxMultiplicitiesTest, SingleSetTest) {
    vector<vector<pair<string, int>>> counts = { {{"a", 1}, {"b", 2}, {"c", 1}} };
    vector<pair<string, int>> expected_max_counts = { {"a", 1}, {"b", 2}, {"c", 1} };
    ASSERT_EQ(FindMaxMultiplicities(counts), expected_max_counts);
}

TEST(FindMaxMultiplicitiesTest, MultipleSets) {
    vector<vector<pair<string, int>>> counts = {
        {{"a", 1}, {"b", 2}, {"c", 3}},
        {{"a", 2}, {"b", 4}, {"d", 5}},
        {{"b", 3}, {"c", 1}, {"e", 2}}
    };
    vector<pair<string, int>> expected = { {"a", 2}, {"b", 4}, {"c", 3}, {"d", 5}, {"e", 2} };
    vector<pair<string, int>> result = FindMaxMultiplicities(counts);
    ASSERT_EQ(result, expected);
}

TEST(FindMaxMultiplicitiesTest, MultipleSetsTest) {
    vector<vector<pair<string, int>>> counts = { {{"a", 1}, {"b", 2}, {"c", 1}}, {{"x", 2}, {"y", 2}, {"z", 1}} };
    vector<pair<string, int>> expected_max_counts = { {"a", 1}, {"b", 2}, {"c", 1}, {"x", 2}, {"y", 2}, {"z", 1} };
    ASSERT_EQ(FindMaxMultiplicities(counts), expected_max_counts);
}

TEST(OutputResultTest, SingleSetTest) {
    vector<pair<string, int>> max_counts = { {"a", 1}, {"b", 2}, {"c", 1} };
    testing::internal::CaptureStdout();
    OutputResult(max_counts);
    string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "The union of the sets: \na b b c \n");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
