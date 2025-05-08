#include "Header.h"
#include <gtest/gtest.h>

class SetOperationsTest : public ::testing::Test {
protected:
    std::vector<std::vector<std::string>> result;
};


TEST_F(SetOperationsTest, ValidStructure) {
    EXPECT_TRUE(check("{a,b}"));
    EXPECT_FALSE(check("{a,!b}"));
}
TEST_F(SetOperationsTest, ProcessSetWithSortedCheck) {
    ProcessSetFromString("{a,b}", result);

    
    auto sort_subsets = [](const vector<vector<string>>& subsets) {
        vector<vector<string>> sorted = subsets;
        for (auto& subset : sorted) {
            sort(subset.begin(), subset.end());
        }
        sort(sorted.begin(), sorted.end());
        return sorted;
        };

    vector<vector<string>> expected = {
        {},
        {"a"},
        {"b"},
        {"a", "b"}
    };

    auto sorted_result = sort_subsets(result);
    auto sorted_expected = sort_subsets(expected);

    ASSERT_EQ(sorted_result.size(), sorted_expected.size());
    EXPECT_EQ(sorted_result, sorted_expected);
}


TEST_F(SetOperationsTest, EmptySet) {
    ProcessSetFromString("{}", result);
    EXPECT_EQ(result.size(), 1); 
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
