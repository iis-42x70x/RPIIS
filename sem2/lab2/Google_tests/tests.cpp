#include "gtest/gtest.h"
#include "Set_lib/Set.hpp"
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void CreateTestFile(const string& filename, const string& content) {
    ofstream file(filename);
    file << content;
    file.close();
}

void RemoveTestFile(const string& filename) {
    remove(filename.c_str());
}

class FileReadTest : public ::testing::Test {
protected:
    const string test_filename = "input.txt";

    void SetUp() override {

    }

    void TearDown() override {
        RemoveTestFile(test_filename);
    }
};

class ComparisonTest : public ::testing::Test {
protected:
    vector<string> s1, s2;
    int k1 = 0, k2 = 0;
};

TEST_F(FileReadTest, ReadsValidSingleLine) {
    CreateTestFile(test_filename, "{a, b, c}\n");

    vector<string> s1, s2;
    bool success = file_read(s1, s2);

    ASSERT_TRUE(success);
    ASSERT_EQ(s1.size(), 3);
    EXPECT_EQ(s1[0], "a");
    EXPECT_EQ(s1[1], "b");
    EXPECT_EQ(s1[2], "c");
    EXPECT_EQ(s2.size(), 0);
}

TEST_F(FileReadTest, ReadsValidTwoLines) {
    CreateTestFile(test_filename, "{a, b, c}\n{d, e, f}\n");

    vector<string> s1, s2;
    bool success = file_read(s1, s2);

    ASSERT_TRUE(success);
    ASSERT_EQ(s1.size(), 3);
    ASSERT_EQ(s2.size(), 3);
    EXPECT_EQ(s1[0], "a");
    EXPECT_EQ(s1[1], "b");
    EXPECT_EQ(s1[2], "c");
    EXPECT_EQ(s2[0], "d");
    EXPECT_EQ(s2[1], "e");
    EXPECT_EQ(s2[2], "f");
}

TEST_F(FileReadTest, HandlesEmptyFile) {
    CreateTestFile(test_filename, "");

    vector<string> s1, s2;
    bool success = file_read(s1, s2);

    EXPECT_TRUE(success);
    EXPECT_TRUE(s1.empty());
    EXPECT_TRUE(s2.empty());
}

TEST_F(FileReadTest, HandlesInvalidFormat) {
    CreateTestFile(test_filename, "{a, b, c\n");

    vector<string> s1, s2;
    bool success = file_read(s1, s2);

    EXPECT_FALSE(success);
    EXPECT_TRUE(s1.empty());
    EXPECT_TRUE(s2.empty());
}

TEST_F(ComparisonTest, equal_strWithGenerics) {
    EXPECT_NE(equal_str("a<b>c", "a<b>c", 0, 0), -1);
    EXPECT_NE(equal_str("a<b<c>>d", "a<b<c>>d", 0, 0), -1);
    EXPECT_EQ(equal_str("a<b>c", "a<d>c", 0, 0), -1);
    EXPECT_EQ(equal_str("a<b<c>>d", "a<b<d>>d", 0, 0), -1);
}

TEST_F(ComparisonTest, equal_strNestedSets) {
    EXPECT_NE(equal_str("{a,<b>{c,<d>{e}}}", "{a,<b>{c,<d>{e}}}", 0, 0), -1);
    EXPECT_NE(equal_str("{x,<y>}", "{x,<y>}", 0, 0), -1);
    EXPECT_EQ(equal_str("{a,<b>{c}}", "{a,<b>{d}}", 0, 0), -1);
    EXPECT_EQ(equal_str("{a}", "<a>", 0, 0), -1);
}

TEST_F(ComparisonTest, EqSetSimpleSets) {
    EXPECT_NE(eq_set("{a,b,c}", "{a,b,c}", 1, 1), -1);
    EXPECT_NE(eq_set("{a,b,c}", "{c,b,a}", 1, 1), -1);
    EXPECT_EQ(eq_set("{a,b,c}", "{a,b,d}", 1, 1), -1);
    EXPECT_EQ(eq_set("{a,b,c}", "{a,b}", 1, 1), -1);
}

TEST_F(ComparisonTest, EqSetNestedSets) {
    EXPECT_NE(eq_set("{a{bc}d}", "{a{bc}d}", 1, 1), -1);
    EXPECT_NE(eq_set("{a{bc}d}", "{d{cb}a}", 1, 1), -1);
    EXPECT_EQ(eq_set("{a,{b,c},d}", "{a,{b,d},c}", 1, 1), -1);
    EXPECT_EQ(eq_set("{a,{b,c},d}", "{a,{b},d}", 1, 1), -1);
}

TEST_F(ComparisonTest, EqSetWithGenerics) {
    EXPECT_NE(eq_set("{a,<b>,c}", "{a,<b>,c}", 1, 1), -1);
    EXPECT_NE(eq_set("{a,<b<c>>,d}", "{a,<b<c>>,d}", 1, 1), -1);
    EXPECT_EQ(eq_set("{a,<b>,c}", "{a,<d>,c}", 1, 1), -1);
    EXPECT_EQ(eq_set("{a,<b<c>>,d}", "{a,<b<d>>,d}", 1, 1), -1);
}

TEST_F(ComparisonTest, DifferenceEmptySets) {
    s1 = {};
    s2 = {};
    testing::internal::CaptureStdout();
    difference(s1, s2);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("пустое множество"), string::npos);
}

TEST_F(ComparisonTest, DifferenceFirstSetEmpty) {
    s1 = {};
    s2 = {"a", "b", "c"};
    testing::internal::CaptureStdout();
    difference(s1, s2);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("пустое множество"), string::npos);
}

TEST_F(ComparisonTest, DifferenceSecondSetEmpty) {
    s1 = {"a", "b", "c"};
    s2 = {};
    testing::internal::CaptureStdout();
    difference(s1, s2);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Разность: { a, b, c, }"), string::npos);
}

TEST_F(ComparisonTest, DifferenceNoCommonElements) {
    s1 = {"a", "b", "c"};
    s2 = {"d", "e", "f"};
    testing::internal::CaptureStdout();
    difference(s1, s2);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Разность: { a, b, c, }"), string::npos);
}

TEST_F(ComparisonTest, DifferenceSomeCommonElements) {
    s1 = {"a", "b", "c", "d"};
    s2 = {"b", "d", "e", "f"};
    testing::internal::CaptureStdout();
    difference(s1, s2);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Разность: { a, c, }"), string::npos);
}

TEST_F(ComparisonTest, DifferenceAllCommonElements) {
    s1 = {"a", "b", "c"};
    s2 = {"a", "b", "c"};
    testing::internal::CaptureStdout();
    difference(s1, s2);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("пустое множество"), string::npos);
}

TEST_F(ComparisonTest, DifferenceWithComplexElements) {
    s1 = {"a{b}c", "<d>e", "f{g{h}}i"};
    s2 = {"a{b}c", "f{g{i}}h"};
    testing::internal::CaptureStdout();
    difference(s1, s2);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Разность: { <d>e, f{g{h}}i, }"), string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
