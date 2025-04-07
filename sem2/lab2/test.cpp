#include <gtest/gtest.h>
#include "pch.h" 

TEST(FormatSetTest, BasicTest) {
    std::vector<std::string> elements = { "1", "2", "3" };
    EXPECT_EQ(formatSet(elements), "<1,2,3>");
}

TEST(GenerateAllOrientationsTest, NonDirectedSetToDirected) {
    std::vector<std::string> inputElements = { "1", "2", "3" };
    std::set<std::string> orientations = generateAllOrientations(inputElements);

    EXPECT_EQ(orientations.size(), 6);
    EXPECT_TRUE(orientations.count("<1,2,3>"));
    EXPECT_TRUE(orientations.count("<1,3,2>"));
    EXPECT_TRUE(orientations.count("<2,1,3>"));
    EXPECT_TRUE(orientations.count("<2,3,1>"));
    EXPECT_TRUE(orientations.count("<3,1,2>"));
    EXPECT_TRUE(orientations.count("<3,2,1>"));
}

TEST(GenerateAllOrientationsTest, CountUniqueOrientations) {
    std::vector<std::string> inputElements = { "A", "B", "<C,D>" };
    std::set<std::string> orientations = generateAllOrientations(inputElements);

    EXPECT_EQ(orientations.size(), 6);
}

TEST(GenerateAllOrientationsTest, OrientationABCD) {
    std::vector<std::string> inputElements = { "A", "B", "<C,D>" };
    std::set<std::string> orientations = generateAllOrientations(inputElements);

    EXPECT_TRUE(orientations.count("<A,B,<C,D>>"));
}


TEST(GenerateAllOrientationsTest, OrientationBCAD) {
    std::vector<std::string> inputElements = { "A", "B", "<C,D>" };
    std::set<std::string> orientations = generateAllOrientations(inputElements);

    EXPECT_TRUE(orientations.count("<B,<C,D>,A>"));
}

TEST(GenerateAllOrientationsTest, OrientationCDAB) {
    std::vector<std::string> inputElements = { "A", "B", "<C,D>" };
    std::set<std::string> orientations = generateAllOrientations(inputElements);

    EXPECT_TRUE(orientations.count("<<C,D>,A,B>"));
}

TEST(GenerateAllOrientationsTest, OrientationWithEmpty) {
    std::vector<std::string> inputElements = { "A", "B", "<C,D>", "{}"};
    std::set<std::string> orientations = generateAllOrientations(inputElements);

    EXPECT_TRUE(orientations.count("<A,B,{},<C,D>>"));
}
TEST(GenerateAllOrientationsTest, OrientationWithSubsets) {
    std::vector<std::string> inputElements = { "A", "B", "<C,D,{y,k},8>", "{6,9}" };
    std::set<std::string> orientations = generateAllOrientations(inputElements);

    EXPECT_TRUE(orientations.count("<A,B,{6,9},<C,D,{y,k},8>>"));
}
TEST(GenerateAllOrientationsTest, EmptySet) {
    std::vector<std::string> inputElements = {}; 
    std::set<std::string> orientations = generateAllOrientations(inputElements);

    EXPECT_TRUE(orientations.empty());
}
TEST(GenerateAllOrientationsTest, Orientation) {
    std::vector<std::string> inputElements = { "<>" };
    std::set<std::string> orientations = generateAllOrientations(inputElements);

    EXPECT_TRUE(orientations.count("<<>>"));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

