#include <gtest/gtest.h>
#include "../set_operations.h"
#include <fstream>
#include <cstdio>

using namespace std;

TEST(TokenizeTest, Basic) {
    // Тест функции tokenize без внешних скобок
    string input = "A, {B, C}, D";
    vector<string> tokens = tokenize(input);
    ASSERT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0], "A");
    EXPECT_EQ(tokens[1], " {B, C}");
    EXPECT_EQ(tokens[2], " D");
}

TEST(ProcessSetTest, Basic) {
    // Тест функции processSet с внешними скобками
    string input = "{A, {B, C}, D}";
    vector<string> elements;
    processSet(input, elements);
    ASSERT_EQ(elements.size(), 3);
    EXPECT_EQ(elements[0], "A");
    EXPECT_EQ(elements[1], " {B, C}");
    EXPECT_EQ(elements[2], " D");
}

TEST(CreateAndFillFileTest, Basic) {
    // Тест функции createAndFillFile
    string filename = "test_input.txt";
    remove(filename.c_str());
    createAndFillFile(filename);

    ifstream file(filename);
    ASSERT_TRUE(file.is_open());

    int lineCount = 0;
    string line;
    while (getline(file, line)) {
        lineCount++;
    }
    file.close();

    EXPECT_EQ(lineCount, 3);
    remove(filename.c_str());
}

TEST(IntersectionTest, Simple) {
    // Тест функции intersection
    vector<vector<string>> sets = {
        {"A", "B", "C"},
        {"B", "C", "D"},
        {"C", "D", "E"}
    };
    vector<string> result = intersection(sets);
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "C");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
