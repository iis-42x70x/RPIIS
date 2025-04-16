#include"pch.h"
#include <gtest/gtest.h>


TEST(ElementCompareTest, EqualStrings) {
    element el1 = { STRING, "abc", {} };
    element el2 = { STRING, "abc", {} };
    EXPECT_TRUE(ElementCompare(el1, el2));
}

TEST(ElementCompareTest, UnequalStrings) {
    element el1 = { STRING, "abc", {} };
    element el2 = { STRING, "def", {} };
    EXPECT_FALSE(ElementCompare(el1, el2));
}

TEST(ElementCompareTest, EqualSets) {
    element el1 = { SET, "", {{STRING, "x", {}}, {STRING, "y", {}}} };
    element el2 = { SET, "", {{STRING, "y", {}}, {STRING, "x", {}}} };
    EXPECT_TRUE(ElementCompare(el1, el2));
}

TEST(ElementCompareTest, UnequalSets) {
    element el1 = { SET, "", {{STRING, "x", {}}} };
    element el2 = { SET, "", {{STRING, "y", {}}} };
    EXPECT_FALSE(ElementCompare(el1, el2));
}

TEST(ElementCompareTest, EqualOrsets) {
    element el1 = { ORSET, "", {{STRING, "x", {}}, {STRING, "y", {}}} };
    element el2 = { ORSET, "", {{STRING, "x", {}}, {STRING, "y", {}}} };
    EXPECT_TRUE(ElementCompare(el1, el2));
}

TEST(ElementCompareTest, UnequalOrsets) {
    element el1 = { ORSET, "", {{STRING, "x", {}}, {STRING, "y", {}}} };
    element el2 = { ORSET, "", {{STRING, "y", {}}, {STRING, "x", {}}} };
    EXPECT_FALSE(ElementCompare(el1, el2));
}

TEST(IntersectionTest, SetsIntersection) {
    element el1 = { SET, "", {{STRING, "x", {}}, {STRING, "y", {}}, {STRING, "z", {}}} };
    element el2 = { SET, "", {{STRING, "y", {}}, {STRING, "z", {}}} };
    element result = intersection(el1, el2);
    EXPECT_EQ(result.setik.size(), 2);
    EXPECT_TRUE(ElementCompare(result.setik[0], { STRING, "y", {} }));
    EXPECT_TRUE(ElementCompare(result.setik[1], { STRING, "z", {} }));
}

TEST(IntersectionTest, OrsetsIntersection) {
    element el1 = { ORSET, "", {{STRING, "a", {}}, {STRING, "b", {}}} };
    element el2 = { ORSET, "", {{STRING, "a", {}}, {STRING, "c", {}}} };
    element result = intersection(el1, el2);
    EXPECT_EQ(result.setik.size(), 1);
    EXPECT_TRUE(ElementCompare(result.setik[0], { STRING, "a", {} }));
}

TEST(ElementCoutTest, PrintString) {
    element el = { STRING, "hello", {} };
    testing::internal::CaptureStdout();
    ElementCout(el);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "hello");
}

TEST(ElementCoutTest, PrintSet) {
    element el = { SET, "", {{STRING, "a", {}}, {STRING, "b", {}}} };
    testing::internal::CaptureStdout();
    ElementCout(el);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{a, b}");
}

TEST(ElementCoutTest, PrintOrset) {
    element el = { ORSET, "", {{STRING, "x", {}}, {STRING, "y", {}}} };
    testing::internal::CaptureStdout();
    ElementCout(el);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "<x, y>");
}

TEST(StringToElementTest, ParseStringToSet) {
    element el;
    StringToElement(el, "{a, b}", 0, 6);
    EXPECT_EQ(el.type, SET);
    EXPECT_EQ(el.setik.size(), 2);
    EXPECT_TRUE(ElementCompare(el.setik[0], { STRING, "a", {} }));
    EXPECT_TRUE(ElementCompare(el.setik[1], { STRING, "b", {} }));
}

TEST(StringToElementTest, ParseStringToOrset) {
    element el;
    StringToElement(el, "<x, y>", 0, 6);
    EXPECT_EQ(el.type, ORSET);
    EXPECT_EQ(el.setik.size(), 2);
    EXPECT_TRUE(ElementCompare(el.setik[0], { STRING, "x", {} }));
    EXPECT_TRUE(ElementCompare(el.setik[1], { STRING, "y", {} }));
}

TEST(StringToElementTest, ParseNestedSet) {
    element el;
    StringToElement(el, "{a, {b, c}}", 0, 11);
    EXPECT_EQ(el.type, SET);
    EXPECT_EQ(el.setik.size(), 2);
    EXPECT_TRUE(ElementCompare(el.setik[0], { STRING, "a", {} }));
    EXPECT_EQ(el.setik[1].type, SET);
    EXPECT_EQ(el.setik[1].setik.size(), 2);
    EXPECT_TRUE(ElementCompare(el.setik[1].setik[0], { STRING, "b", {} }));
    EXPECT_TRUE(ElementCompare(el.setik[1].setik[1], { STRING, "c", {} }));
}

TEST(SetUniqueCheckTest, UniqueElements) {
    element el = { SET, "", {{STRING, "x", {}}, {STRING, "y", {}}} };
    EXPECT_TRUE(SetUniqueCheck(el));
}

TEST(SetUniqueCheckTest, DuplicateElements) {
    element el = { SET, "", {{STRING, "x", {}}, {STRING, "x", {}}} };
    EXPECT_FALSE(SetUniqueCheck(el));
}

TEST(StringCheckTest, CorrectStringFormat) {
    std::string str = "{a, b, {c, d}}";
    EXPECT_TRUE(StringCheck(str));
}

TEST(StringCheckTest, IncorrectStringFormat) {
    std::string str = "{a, b, <c, d}";
    EXPECT_FALSE(StringCheck(str));
}
