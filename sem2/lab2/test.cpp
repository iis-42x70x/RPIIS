#include "Header.h"
#include <gtest/gtest.h>

class SetOperationsTest : public ::testing::Test {
protected:
    std::vector<std::vector<std::string>> result;
};




TEST_F(SetOperationsTest, ValidStructure) {
    EXPECT_TRUE(check("{a,b}"));
    EXPECT_FALSE(check("{a,!b}"));
    EXPECT_TRUE(check("{1,2,3}"));
    EXPECT_FALSE(check("a,b}"));
    EXPECT_FALSE(check("{a,b"));
    EXPECT_TRUE(check("{}"));
    EXPECT_TRUE(check("{a}"));
}

TEST_F(SetOperationsTest, ProcessSetWithSortedCheck) {
    ProcessSetFromString("{a,b}", result);

    vector<vector<string>> expected = { {}, {"a"}, {"b"}, {"a", "b"} };
    normalize(result);
    normalize(expected);

    ASSERT_EQ(result.size(), expected.size());
    EXPECT_EQ(result, expected);
}

TEST_F(SetOperationsTest, EmptySet) {
    ProcessSetFromString("{}", result);
    EXPECT_EQ(result.size(), 1);
    EXPECT_TRUE(result[0].empty());
}

TEST_F(SetOperationsTest, SingleElementSet) {
    ProcessSetFromString("{x}", result);
    vector<vector<string>> expected = { {}, {"x"} };
    ASSERT_EQ(result.size(), expected.size());
    EXPECT_EQ(result, expected);
}

TEST_F(SetOperationsTest, ThreeElementsSet) {
    ProcessSetFromString("{a,b,c}", result);
    EXPECT_EQ(result.size(), 8);
}

TEST_F(SetOperationsTest, DuplicateElements) {
    ProcessSetFromString("{a,a,b}", result);
    vector<vector<string>> expected = { {}, {"a"}, {"b"}, {"a", "b"} };
    normalize(result);
    normalize(expected);
    EXPECT_EQ(result, expected);
}

TEST_F(SetOperationsTest, NumericElements) {
    ProcessSetFromString("{1,2}", result);
    vector<vector<string>> expected = { {}, {"1"}, {"2"}, {"1", "2"} };
    normalize(result);
    normalize(expected);
    EXPECT_EQ(result, expected);
}

TEST_F(SetOperationsTest, MixedTypeElements) {
    ProcessSetFromString("{a,1,2b}", result);
    bool has_all = all_of(result.begin(), result.end(), [](const auto& subset) {
        return all_of(subset.begin(), subset.end(), [](const auto& elem) {
            return elem == "a" || elem == "1" || elem == "2b";
            });
        });
    EXPECT_TRUE(has_all);
}

TEST_F(SetOperationsTest, SpecialCharactersInElements) {
    ProcessSetFromString("{a_b,c-d,123}", result);
    bool has_all = all_of(result.begin(), result.end(), [](const auto& subset) {
        return all_of(subset.begin(), subset.end(), [](const auto& elem) {
            return elem == "a_b" || elem == "c-d" || elem == "123";
            });
        });
    EXPECT_TRUE(has_all);
}

TEST_F(SetOperationsTest, InvalidInputs) {
    EXPECT_FALSE(check(""));
    EXPECT_FALSE(check("a,b"));
    EXPECT_FALSE(check("{a,b"));
    EXPECT_FALSE(check("a,b}"));
    EXPECT_FALSE(check("{{a,b}}"));
    EXPECT_FALSE(check("{a, b, }"));
    EXPECT_FALSE(check("{a,,b}"));
    EXPECT_FALSE(check("{a, !b}"));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
