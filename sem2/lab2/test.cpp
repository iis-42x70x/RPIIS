#include "pch.h"

using namespace std;

TEST(RunTestcaseTest, SubsetPermutation) {
    vector<vector<string>> sets;
    open_and_sets("testic.txt", sets);
    vector<vector<string>> expected_sets = { {"{a b}", "{a b}"}, {"{a b}"} };
    ASSERT_EQ(sets.size(), expected_sets.size());

    for (int i = 0; i < sets.size() - 1; ++i) {
        ASSERT_EQ(sets[i], expected_sets[i]);
    }
}

TEST(RunTestcaseTest, FileNotFoundTest) {
    vector<vector<string>> sets;
    open_and_sets("non_existent_file.txt", sets);
    ASSERT_EQ(sets.size(), 0);
    ASSERT_TRUE(sets.empty());
}

TEST(CountMultiplicitiesTest, SingleSetTest) {
    vector<vector<string>> sets = { {"aa", "b", "b", "{}"} };
    vector<vector<pair<string, int>>> expected_counts = { {{"aa", 1}, {"b", 2}, {"{}", 1}} };
    ASSERT_EQ(set_element_count(sets), expected_counts);
}

TEST(CountMultiplicitiesTest, MultipleSetsTest) {
    vector<vector<string>> sets = { {"a", "b", "b", "c"}, {"x", "y", "z", "x", "y"} };
    vector<vector<pair<string, int>>> expected_counts = { {{"a", 1}, {"b", 2}, {"c", 1}}, {{"x", 2}, {"y", 2}, {"z", 1}} };
    ASSERT_EQ(set_element_count(sets), expected_counts);
}

TEST(FindMaxMultiplicitiesTest, SingleSetTest) {
    vector<vector<pair<string, int>>> counts = { {{"a", 1}, {"b", 2}, {"c", 1}} };
    vector<pair<string, int>> expected_max_counts = { {"a", 1}, {"b", 2}, {"c", 1} };
    ASSERT_EQ(final_set_count(counts), expected_max_counts);
}

TEST(FindMaxMultiplicitiesTest, MultipleSets) {
    vector<vector<pair<string, int>>> counts = {
        {{"a", 1}, {"b", 2}, {"c", 3}},
        {{"a", 2}, {"b", 4}, {"d", 5}},
        {{"b", 3}, {"c", 1}, {"e", 2}}
    };
    vector<pair<string, int>> expected = { {"a", 2}, {"b", 4}, {"c", 3}, {"d", 5}, {"e", 2} };
    vector<pair<string, int>> result = final_set_count(counts);
    ASSERT_EQ(result, expected);
}

TEST(FindMaxMultiplicitiesTest, MultipleSetsTest) {
    vector<vector<pair<string, int>>> counts = { {{"a", 1}, {"b", 2}, {"c", 1}}, {{"x", 2}, {"y", 2}, {"z", 1}} };
    vector<pair<string, int>> expected_max_counts = { {"a", 1}, {"b", 2}, {"c", 1}, {"x", 2}, {"y", 2}, {"z", 1} };
    ASSERT_EQ(final_set_count(counts), expected_max_counts);
}

TEST(OutputResultTest, SingleSetTest) {
    vector<pair<string, int>> max_counts = { {"a", 1}, {"b", 2}, {"c", 1} };
    testing::internal::CaptureStdout();
    output(max_counts);
    string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "The union of the sets: \na b b c \n");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}