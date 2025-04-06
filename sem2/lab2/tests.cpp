#include <gtest/gtest.h>
#include "C:/Users/anteiku/Documents/ПиОИвИС/sets/Header.h"

// =============================================
// Тесты парсинга (parseElements)
// =============================================

TEST(ParseTest, EmptyInput) {
    vector<string> res = parseElements("");
    EXPECT_TRUE(res.empty());
}

TEST(ParseTest, SingleElement) {
    vector<string> res = parseElements("{A}");
    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], "A");
}

TEST(ParseTest, ComplexSetParsing) {
    vector<string> res = parseElements("{ A , {A}, B , {C,< D,{E, E,F }>,G}, <A, A>, <A>}");
    ASSERT_EQ(res.size(), 6);
    EXPECT_EQ(res[0], "A");
    EXPECT_EQ(res[1], "{A}");
    EXPECT_EQ(res[2], "B");
    EXPECT_EQ(res[3], "{C,< D,{E, E,F }>,G}");
    EXPECT_EQ(res[4], "<A, A>");
    EXPECT_EQ(res[5], "<A>");
}

// ======================================
// Тесты нормализации (normalizeElement)
// ======================================

TEST(NormalizeTest, EmptySet) {
    EXPECT_EQ(normalizeElement("{}"), "{}");
}

TEST(NormalizeTest, DeeplyNested) {
    EXPECT_EQ(normalizeElement("{{{{A}}}}"), "A");
}

TEST(NormalizeTest, MixedTypes) {
    EXPECT_EQ(normalizeElement("{<B,A>, {A,B}}"), "{<B,A>,{A,B}}");
}

TEST(NormalizeTest, NormalizationResults) {
    EXPECT_EQ(normalizeElement("{ A , {A}, B , {C,< D,{E, E,F }>,G}, <A, A>, {<A>}, <A> }"),
        "{A,B,<A,A>,<A>,{C,G,<D,{E,F}>}}");
    EXPECT_EQ(normalizeElement("{C ,{ <D,{F ,E} >,C ,G}, <A, A, B>}"),
        "{C,<A,A,B>,{C,G,<D,{E,F}>}}");
    EXPECT_EQ(normalizeElement("{A , {A, A} , B, C, <D,{F,  E}>, G, G}"),
        "{A,B,C,G,<D,{E,F}>}");
}

// =============================
// Тесты валидации (isValidSet)
// =============================

TEST(ValidationTest, InvalidSets) {
    EXPECT_FALSE(isValidSet("{A"));       // Не закрытая скобка
    EXPECT_FALSE(isValidSet("A}"));       // Не открытая скобка
    EXPECT_FALSE(isValidSet("{A,,B}"));   // Двойная запятая
}

TEST(ValidationTest, EdgeCases) {
    EXPECT_TRUE(isValidSet("{}"));        // Пустое множество
    EXPECT_TRUE(isValidSet("{ }"));       // Пробелы
    EXPECT_TRUE(isValidSet("{{}}"));      // Пустое в пустом
}

// ====================================================
// Тесты симметрической разности (symmetricDifference)
// ====================================================

TEST(SymDiffTest, EmptySetCases) {
    char result[1024];
    symmetricDifference("{}", "{A,B}", result);
    EXPECT_STREQ(result, "{A,B}");

    symmetricDifference("{A,B}", "{}", result);
    EXPECT_STREQ(result, "{A,B}");
}

TEST(SymDiffTest, ComplexCases) {
    char result[1024];

   
    symmetricDifference(
        "{A, B, {X,Y}, <1,2>}",
        "{B, C, {X,Z}, <2,3>}",
        result
    );
    EXPECT_STREQ(result, "{A,{X,Y},<1,2>,C,{X,Z},<2,3>}");

    
    symmetricDifference(
        "{<A,B>, <B,A>}",
        "{<B,A>, {A,B}}",
        result
    );
    EXPECT_STREQ(result, "{<A,B>,{A,B}}");

    
    symmetricDifference(
        "{A, {B, {C, <D,E>}}}",
        "{A, {B, {C, <E,D>}}}",
        result
    );
    EXPECT_STREQ(result, "{{B,{C,<D,E>}},{B,{C,<E,D>}}}");

    
    symmetricDifference(
        "{}",
        "{X, Y, {}}",
        result
    );
    EXPECT_STREQ(result, "{X,Y,{}}");

    
    symmetricDifference(
        "{A, A, <A,A>, {A}}",
        "{<A,A>, A, {A,A}}",
        result
    );
    EXPECT_STREQ(result, "{}");
    symmetricDifference(
        "{A, B, C}",
        "{X, Y, Z}",
        result
    );
    EXPECT_STREQ(result, "{A,B,C,X,Y,Z}");
}

// ====================================
// Граничные случаи производительности
// ====================================

TEST(StressTest, LargeNestedSet) {
    string largeSet(1000, '{');
    largeSet += "A" + string(1000, '}');
    EXPECT_TRUE(isValidSet(largeSet.c_str()));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}