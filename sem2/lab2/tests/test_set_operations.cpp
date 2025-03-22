#include <gtest/gtest.h>
#include "../set_operations.h" 

TEST(SetOperationsTest, SimpleIntersectionTest) {
    std::vector<std::vector<std::string>> sets = {
        {"A", "B", "C"},  
        {"B", "C", "D"},  
        {"C", "D", "E"}   
    };

    std::vector<std::string> result = intersection(sets);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "C");
}
