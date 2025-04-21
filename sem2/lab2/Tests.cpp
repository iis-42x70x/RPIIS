#include <gtest/gtest.h>
#include "C:\Users\expla\source\repos\bogdanchik\tests.cpp\functions.cpp" 
#include <sstream>
#include <fstream>

// Тесты для parseSet
TEST(ParseSet, SimpleSet) {
    std::vector<std::string> result = parseSet("{1,2,3}");
    std::vector<std::string> expected = { "1", "2", "3" };
    EXPECT_EQ(result, expected);
}

TEST(ParseSet, NestedSet) {
    std::vector<std::string> result = parseSet("{a,b,{c,d}}");
    std::vector<std::string> expected = { "a", "b", "{c,d}" };
    EXPECT_EQ(result, expected);
}

// Тесты для DirectedSetGenerator
TEST(DirectedSetGenerator, GeneratePermutations) {
    DirectedSetGenerator generator({ "1", "2" });
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    generator.generateDirectedSets();
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("{ 1 2 }") != std::string::npos);
    EXPECT_TRUE(output.find("{ 2 1 }") != std::string::npos);
}

TEST(DirectedSetGenerator, Size) {
    DirectedSetGenerator generator({ "a", "b", "c" });
    EXPECT_EQ(generator.size(), 3);
}

// Тесты для readInput
TEST(ReadInput, ValidFile) {
    std::ofstream file("test.txt");
    file << "3\n{1,2,3}\n";
    file.close();

    std::vector<std::string> elements;
    int n;
    bool success = readInput("test.txt", elements, n);
    EXPECT_TRUE(success);
    EXPECT_EQ(n, 3);
    EXPECT_EQ(elements, std::vector<std::string>({ "1", "2", "3" }));

    std::remove("test.txt");
}

TEST(ReadInput, FileNotFound) {
    std::vector<std::string> elements;
    int n;
    bool success = readInput("nonexistent.txt", elements, n);
    EXPECT_FALSE(success);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
