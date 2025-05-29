#include "pch.h"
#include <gtest/gtest.h>

TEST(RemoveSpacesTest, HandlesEmptyString) {
    EXPECT_EQ(removeSpaces(""), "");
}

TEST(RemoveSpacesTest, RemovesAllSpaces) {
    EXPECT_EQ(removeSpaces(" A B C "), "ABC");
    EXPECT_EQ(removeSpaces("{A, B, {C, D}}"), "{A,B,{C,D}}");
    EXPECT_EQ(removeSpaces("  {  }  "), "{}");
}

TEST(InputSetTest, ValidatesOpeningBrace) {
    istringstream iss("A,B,C}");
    EXPECT_EXIT(inputSet(), ::testing::ExitedWithCode(1), "Ошибка: должно начинаться с");
}

TEST(CollectElementsTest, CollectsFromFlatSet) {
    SetElement set;
    set.is_subset = true;
    set.subset = {
        {false, 'A', {}},
        {false, 'B', {}},
        {false, 'C', {}}
    };

    vector<char> elements;
    collectElements(set, elements);

    ASSERT_EQ(elements.size(), 3);
    EXPECT_EQ(elements[0], 'A');
    EXPECT_EQ(elements[1], 'B');
    EXPECT_EQ(elements[2], 'C');
}

TEST(CollectElementsTest, CollectsFromNestedSet) {
    SetElement inner;
    inner.is_subset = true;
    inner.subset = {
        {false, 'B', {}},
        {false, 'C', {}}
    };

    SetElement set;
    set.is_subset = true;
    set.subset = {
        {false, 'A', {}},
        inner,
        {false, 'D', {}}
    };

    vector<char> elements;
    collectElements(set, elements);

    ASSERT_EQ(elements.size(), 4);
    EXPECT_EQ(elements[0], 'A');
    EXPECT_EQ(elements[1], 'B');
    EXPECT_EQ(elements[2], 'C');
    EXPECT_EQ(elements[3], 'D');
}

TEST(CountElementsTest, CountsFlatSet) {
    SetElement set;
    set.is_subset = true;
    set.subset = {
        {false, 'A', {}},
        {false, 'B', {}},
        {false, 'C', {}}
    };

    EXPECT_EQ(countElements(set), 3);
}

TEST(CountElementsTest, CountsNestedSet) {
    SetElement inner1;
    inner1.is_subset = true;
    inner1.subset = {
        {false, 'B', {}},
        {false, 'C', {}}
    };

    SetElement inner2;
    inner2.is_subset = true;
    inner2.subset = {
        {false, 'D', {}},
        {false, 'E', {}}
    };

    SetElement set;
    set.is_subset = true;
    set.subset = {
        {false, 'A', {}},
        inner1,
        inner2,
        {false, 'F', {}}
    };

    EXPECT_EQ(countElements(set), 6);
}

TEST(GenerateCombinationsTest, GeneratesCorrectCombinations) {
    vector<char> elements = { 'A', 'B', 'C' };
    vector<char> current;
    vector<vector<char>> result;

    generateCombinations(elements, 2, current, 0, result);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], vector<char>({ 'A', 'B' }));
    EXPECT_EQ(result[1], vector<char>({ 'A', 'C' }));
    EXPECT_EQ(result[2], vector<char>({ 'B', 'C' }));
}

TEST(PrintSetTest, PrintsFlatSet) {
    SetElement set;
    set.is_subset = true;
    set.subset = {
        {false, 'A', {}},
        {false, 'B', {}},
        {false, 'C', {}}
    };

    ostringstream oss;
    streambuf* old_cout = cout.rdbuf(oss.rdbuf());
    printSet(set);
    cout.rdbuf(old_cout);

    EXPECT_EQ(oss.str(), "{A,B,C}");
}

TEST(PrintSetTest, PrintsNestedSet) {
    SetElement inner;
    inner.is_subset = true;
    inner.subset = {
        {false, 'B', {}},
        {false, 'C', {}}
    };

    SetElement set;
    set.is_subset = true;
    set.subset = {
        {false, 'A', {}},
        inner,
        {false, 'D', {}}
    };

    ostringstream oss;
    streambuf* old_cout = cout.rdbuf(oss.rdbuf());
    printSet(set);
    cout.rdbuf(old_cout);

    EXPECT_EQ(oss.str(), "{A,{B,C},D}");
}

TEST(InputDimensionTest, HandlesValidInput) {
    istringstream input("5\n");
    cin.rdbuf(input.rdbuf());

    EXPECT_EQ(inputDimension(10), 5);
}

TEST(InputDimensionTest, RejectsInvalidInput) {
    istringstream input("abc\n-5\n11\n5\n");
    cin.rdbuf(input.rdbuf());

    testing::internal::CaptureStdout();
    EXPECT_EQ(inputDimension(10), 5);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Ошибка: введите положительное число") != string::npos);
    EXPECT_TRUE(output.find("Ошибка: размерность не может превышать") != string::npos);
}