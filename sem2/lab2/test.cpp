#include <gtest/gtest.h>
#include "Set.h"

class SetTest : public ::testing::Test {
protected:
};

//

TEST(SetTupleTest, NormalizeSimpleTuple) {
    Set set;
    EXPECT_EQ(set.normalize("<b,a>"), "<b,a>");
}

TEST(SetTupleTest, NormalizeMixedTupleAndSet) {
    Set set;
    EXPECT_EQ(set.normalize("{<b,a>, {d,c}}"), "{<b,a>,{c,d}}");
}

TEST(SetTupleTest, NormalizeNestedTuples) {
    Set set;
    EXPECT_EQ(set.normalize("<a,<b,c>>"), "<a,<b,c>>");
}

TEST(SetTupleTest, PushSimpleTuple) {
    Set set;
    set.push("{<a,b>}");
    EXPECT_TRUE(set.contains("<a,b>"));
    EXPECT_FALSE(set.contains("<b,a>"));
}

TEST(SetTupleTest, PushNestedTuple) {
    Set set;
    set.push("{<a,<b,c>>}");
    EXPECT_TRUE(set.contains("<a,<b,c>>"));
    EXPECT_FALSE(set.contains("<a,<c,b>>"));
}

TEST(SetTupleTest, PushMixedTypes) {
    Set set;
    set.push("{<a,b>, {c,d}, e}");
    EXPECT_TRUE(set.contains("<a,b>"));
    EXPECT_TRUE(set.contains("{c,d}"));
    EXPECT_TRUE(set.contains("e"));
}

TEST(SetTupleTest, SymDiffWithTuples) {
    Set set1, set2;
    set1.push("{<a,b>, c}");
    set2.push("{<b,a>, c}");
    
    std::vector<Set> sets = {set1, set2};
    Set result = set1.SymmetricalDifference(sets);
    
    EXPECT_TRUE(result.contains("<a,b>"));
    EXPECT_TRUE(result.contains("<b,a>"));
    EXPECT_FALSE(result.contains("c"));
}

TEST(SetTupleTest, SymDiffWithNestedTuples) {
    Set set1, set2;
    set1.push("{<a,<b,c>>}");
    set2.push("{<a,<c,b>>}");
    
    std::vector<Set> sets = {set1, set2};
    Set result = set1.SymmetricalDifference(sets);
    
    EXPECT_TRUE(result.contains("<a,<b,c>>"));
    EXPECT_TRUE(result.contains("<a,<c,b>>"));
}

//Set

TEST(SetOperationsTest, HandlesDeeplyNestedPush) {
    Set set;
    set.push("{{{{a}}}}");
    EXPECT_TRUE(set.contains("{{{a}}}"));
}

TEST(SetOperationsTest, DetectsMissingElements) {
    Set set;
    set.push("{a,b,{c,d}}");
    EXPECT_TRUE(set.contains("{d,c}"));
    EXPECT_TRUE(set.contains("{c,d}"));
}

TEST(SetOperationsTest, HandlesMixedTypes) {
    Set set;
    set.push("{<a,b>, {c,d}, e}");
    EXPECT_TRUE(set.contains("<a,b>"));
    EXPECT_TRUE(set.contains("{c,d}"));
    EXPECT_TRUE(set.contains("e"));
}

TEST(SetNormalizeTest, HandlesNestedSets) {
    Set set;
    EXPECT_EQ(set.normalize("{{d,c},{b,a}}"), "{{a,b},{c,d}}");
}

TEST(SetNormalizeTest, HandlesEmptySet) {
    Set set;
    EXPECT_EQ(set.normalize("{}"), "{}");
}

TEST(SetNormalizeTest, HandlesMultipleDuplicates) {
    Set set;
    EXPECT_EQ(set.normalize("{a,a,b,a,c,b}"), "{a,a,a,b,b,c}");
}

TEST(SetNormalizeTest, ComplexMixedNesting) {
    Set set;
    EXPECT_EQ(set.normalize("{{x,{y,z}},{a,{b,c}},d}"), "{d,{a,{b,c}},{x,{y,z}}}");
}

TEST(SetAdvancedTest, SymDiffWithMultipleDuplicates) {
    Set set1, set2, set3;
    set1.push("{a,a,b}");
    set2.push("{a,b,b}");
    set3.push("{a,a,a}");
    
    std::vector<Set> sets = {set1, set2, set3};
    Set result = set1.SymmetricalDifference(sets);
    
    EXPECT_TRUE(result.contains("a"));
    EXPECT_TRUE(result.contains("b"));
}

TEST(SetAdvancedTest, ComplexSymDiffWithNested) {
    Set set1, set2;
    set1.push("{{a,b},c}");
    set2.push("{{b,a},d}");
    
    std::vector<Set> sets = {set1, set2};
    Set result = set1.SymmetricalDifference(sets);
    
    EXPECT_TRUE(result.contains("c"));
    EXPECT_TRUE(result.contains("d"));
    EXPECT_FALSE(result.contains("{a,b}"));
}

TEST_F(SetTest, PrintTest) {

}

//

TEST(SetComplexStructuresTest, MixedNestedSetsAndTuples) {
    Set set;
    
    std::string complexInput = "{<{b,a},<d,c>>, {{f,e}}, <x,{y,z}>, <{a,b}>}";
    std::string normalized = set.normalize(complexInput);
    
    EXPECT_EQ(normalized, "{<x,{y,z}>,<{a,b}>,<{b,a},<d,c>>,{{e,f}}}");

    set.push(complexInput);
    
    EXPECT_TRUE(set.contains("{{e,f}}"));
    EXPECT_TRUE(set.contains("<x,{y,z}>"));
    
    EXPECT_FALSE(set.contains("<{a,b}, <d,c>>"));
    EXPECT_FALSE(set.contains("{<d,c>,{a,b}}"));
    
    EXPECT_FALSE(set.contains("{e,f}"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
