#include "pch.h"
#include "gtest/gtest.h"
#include "sets.hpp"
#include <sstream>
#include <fstream>

//==================== printElement ====================
TEST(PrintTest, PrintInt) {
    SetElement elem = 42;
    std::stringstream ss;
    testing::internal::CaptureStdout();
    printElement(elem);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "42");
}

TEST(PrintTest, PrintString) {
    SetElement elem = "hello";
    testing::internal::CaptureStdout();
    printElement(elem);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "hello");
}

TEST(PrintTest, PrintNestedSet) {
    Set innerSet = parseSet("{1, 2}");
    SetElement elem = make_shared<Set>(innerSet);
    testing::internal::CaptureStdout();
    printElement(elem);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{1, 2}");
}

//==================== validateInput ====================
TEST(ValidationTest, ValidNestedSet) {
    EXPECT_NO_THROW(validateInput("{1, {2, <3, 4>}, 5}"));
}

TEST(ValidationTest, InvalidBrackets) {
    EXPECT_THROW(validateInput("{1, 2}}"), std::runtime_error);
}

TEST(ValidationTest, InvalidComma) {
    EXPECT_THROW(validateInput("{, b, c}"), std::runtime_error);
}

//==================== generateProduct ====================
TEST(GenerateProductTest, TwoSets) {
    Set setA = parseSet("{a, b}");
    Set setB = parseSet("{1, 2}");
    Set result;
    generateProduct({ setA, setB }, 0, {}, result);
    EXPECT_EQ(result.elements.size(), 4);
}

TEST(GenerateProductTest, EmptySet) {
    Set emptySet = parseSet("{}");
    Set result;
    generateProduct({ emptySet }, 0, {}, result);
    EXPECT_TRUE(result.elements.empty());
}

TEST(GenerateProductTest, NestedSets) {
    Set setA = parseSet("{<1, 2>}");
    Set setB = parseSet("{x}");
    Set result;
    generateProduct({ setA, setB }, 0, {}, result);
    EXPECT_EQ(result.elements.size(), 1);
}

//==================== DecartProduct ====================
TEST(CartesianProductTest, BasicProduct) {
    Set setA = parseSet("{a, b}");
    Set setB = parseSet("{1, 2}");
    Set product = DecartProduct({ setA, setB });
    EXPECT_EQ(product.elements.size(), 4);
}

TEST(CartesianProductTest, SingleSet) {
    Set set = parseSet("{1, 2, 3}");
    Set product = DecartProduct({ set });
    EXPECT_EQ(product.elements.size(), 3);
}

TEST(CartesianProductTest, EmptyInput) {
    Set setA = parseSet("{}");
    Set product = DecartProduct({setA});
    EXPECT_EQ(product.elements.size(), 0);
}

//==================== parseSet ====================
TEST(ParseSetTest, SimpleSet) {
    Set s = parseSet("{1, 2, 3}");
    EXPECT_EQ(s.elements.size(), 3);
}

TEST(ParseSetTest, NestedSet) {
    Set s = parseSet("{a, {b, c}, <>}");
    EXPECT_EQ(s.elements.size(), 3);
}

TEST(ParseSetTest, EmptySet) {
    Set s = parseSet("{}");
    EXPECT_TRUE(s.elements.empty());
}

//==================== ParseFile ====================
TEST(ParseFileTest, ReadMultipleSets) {
    std::ofstream testFile("test.txt");
    testFile << "{1, 2}\n{A, B}\n";
    testFile.close();

    vector<Set> sets = ParseFile("test.txt");
    EXPECT_EQ(sets.size(), 2);
}

TEST(ParseFileTest, EmptyFile) {
    std::ofstream testFile("empty.txt");
    testFile.close();

    vector<Set> sets = ParseFile("empty.txt");
    EXPECT_TRUE(sets.empty());
}

TEST(ParseFileTest, InvalidFile) {
    EXPECT_THROW(ParseFile("nonexistent.txt"), std::runtime_error);
}

//==================== readFile ====================
TEST(ReadFileTest, ReadContent) {
    std::ofstream testFile("test.txt");
    testFile << "Hello, World!";
    testFile.close();

    std::string content = readFile("test.txt");
    EXPECT_EQ(content, "Hello, World!");
}

TEST(ReadFileTest, EmptyFile) {
    std::ofstream testFile("empty.txt");
    testFile.close();

    std::string content = readFile("empty.txt");
    EXPECT_TRUE(content.empty());
}

TEST(ReadFileTest, FileNotFound) {
    EXPECT_THROW(readFile("nonexistent.txt"), std::runtime_error);
}

//==================== parseElement ====================
TEST(ParseElementTest, ParseInt) {
    SetElement elem = parseElement("42");
    EXPECT_TRUE(std::holds_alternative<int>(elem));
}

TEST(ParseElementTest, ParseTuple) {
    SetElement elem = parseElement("<a, 1>");
    EXPECT_TRUE(std::holds_alternative<shared_ptr<Tuple>>(elem));
}

TEST(ParseElementTest, ParseString) {
    SetElement elem = parseElement("hello");
    EXPECT_TRUE(std::holds_alternative<string>(elem));
}

//==================== parseTuple ====================
TEST(ParseTupleTest, SimpleTuple) {
    Tuple t = parseTuple("<a, 1, b>");
    EXPECT_EQ(t.elements.size(), 3);
}

TEST(ParseTupleTest, NestedTuple) {
    Tuple t = parseTuple("<1, <2, 3>>");
    EXPECT_EQ(t.elements.size(), 2);
}

TEST(ParseTupleTest, EmptyTuple) {
    Tuple t = parseTuple("<>");
    EXPECT_TRUE(t.elements.empty());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}