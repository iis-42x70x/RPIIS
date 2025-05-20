#include "pch.h"
#include "D:\”чеба\пио\2 сем\лабы\lab 2\Source.cpp"

TEST(SplitElementsTest, BasicSplit) {
    auto result = split_elements("a,b,c");
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "b");
    EXPECT_EQ(result[2], "c");
}

TEST(SplitElementsTest, AngleBrackets) {
    auto result = split_elements("a,<b,c>,d");
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "<b,c>"); 
    EXPECT_EQ(result[2], "d");
} 

TEST(SplitElementsTest, EmptyString) {
    auto result = split_elements("");
    EXPECT_TRUE(result.empty());
}

TEST(ProcessLineTest, SimpleSet) {
    vector<string> result;
    process_line("a,b,c", result);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "b");
    EXPECT_EQ(result[2], "c");
}

TEST(ProcessLineTest, NestedSet) {
    vector<string> result;
    process_line("a,{b,c}", result);

    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "{b c}");  
}

TEST(SetElementCountTest, BasicCount) {
    vector<vector<string>> sets = { {"a", "a", "b"} };
    auto result = set_element_count(sets);

    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result[0].size(), 2);
    EXPECT_EQ(result[0][0].first, "a");
    EXPECT_EQ(result[0][0].second, 2); 
    EXPECT_EQ(result[0][1].first, "b");
    EXPECT_EQ(result[0][1].second, 1);
}

TEST(FileInputTest, ReadsCorrectly) {
    ofstream tmp("test_file.txt");
    tmp << "{a,b}\n{c,d}";
    tmp.close();

    vector<vector<string>> sets;
    open_and_sets("test_file.txt", sets);

    ASSERT_EQ(sets.size(), 2);
    EXPECT_EQ(sets[0], vector<string>({ "a", "b" }));
    EXPECT_EQ(sets[1], vector<string>({ "c", "d" }));

    remove("test_file.txt");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}