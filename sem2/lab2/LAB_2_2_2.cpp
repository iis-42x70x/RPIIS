#include <gtest/gtest.h>
#include "SetParser.h"

TEST(ParseTest, BasicParsing) {
    auto result = string_to_vector("{a,b,c}");
    EXPECT_EQ(result, (std::vector<std::string>{"a", "b", "c"}));
}

TEST(CartesianProductTest, TwoSets) {
    std::vector<std::vector<std::string>> sets = {
        {"1", "2"},
        {"x", "y"}
    };
    auto result = cartesianProduct(sets);
    EXPECT_EQ(result.size(), 4);
    EXPECT_TRUE(std::find(result.begin(), result.end(), std::vector<std::string>{"1", "x"}) != result.end());
    EXPECT_TRUE(std::find(result.begin(), result.end(), std::vector<std::string>{"2", "y"}) != result.end());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
