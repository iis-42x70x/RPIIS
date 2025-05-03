#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "header.h"
// Тесты парсинга (parseElements)
TEST(ParseTest, EmptyInput) 
{
    vector<string> res = parseElements("");
    EXPECT_TRUE(res.empty());
}
TEST(ParseTest, SingleElement) 
{
    vector<string> res = parseElements("{A}");
    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], "A");
}
TEST(ParseTest, ComplexSetParsing) 
{
    vector<string> res = parseElements("{ A , {A}, B , {C,< D,{E, E,F }>,G}, <A, A>, <A>}");
    ASSERT_EQ(res.size(), 6);
    EXPECT_EQ(res[0], "A");
    EXPECT_EQ(res[1], "{A}");
    EXPECT_EQ(res[2], "B");
    EXPECT_EQ(res[3], "{C,< D,{E, E,F }>,G}");
    EXPECT_EQ(res[4], "<A, A>");
    EXPECT_EQ(res[5], "<A>");
}
// Тесты валидации (isValidSet)
TEST(ValidationTest, InvalidSets) {
    EXPECT_FALSE(isValidSet("{A"));       
    EXPECT_FALSE(isValidSet("A}"));       
    EXPECT_FALSE(isValidSet("{A,,B}"));   
}

TEST(ValidationTest, EdgeCases) {
    EXPECT_TRUE(isValidSet("{}"));        
    EXPECT_TRUE(isValidSet("{ }"));       
    EXPECT_TRUE(isValidSet("{{}}"));      
}
// Тесты пересечения(Intersection)
TEST(Intersect, EmptySetCases) {
    char result[1024];
    Intersection("{}", "{A,B}", result);
    EXPECT_STREQ(result, "{}");

    Intersection("{A,B}", "{}", result);
    EXPECT_STREQ(result, "{}");
}
TEST(Intersection, ComplexCases) {
    char result[1024];

   
    Intersection(
        "{A, B, {X,Y}, <1,2>}",
        "{B, C, {X,Z}, <2,3>}",
        result
    );
    EXPECT_STREQ(result, "{B}");

    
    Intersection(
        "{<A,B>, <B,A>}",
        "{<B,A>, {A,B}}",
        result
    );
    EXPECT_STREQ(result, "{<B,A>}");

    
    Intersection(
        "{A, {B, {C, <D,E>}}}",
        "{A, {B, {C, <E,D>}}}",
        result
    );
    EXPECT_STREQ(result, "{A}");

    
    Intersection(
        "{}",
        "{X, Y, {}}",
        result
    );
    EXPECT_STREQ(result, "{}");
    Intersection(
        "{A, B, C,<D,E,{G,H}>}",
        "{X, Y, Z,<D,E,{G,H}>}",
        result
    );
    EXPECT_STREQ(result, "{<D,E,{G,H}>}");
}
// Тесты нормализации (normalizeElement)
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
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
