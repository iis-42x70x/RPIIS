#include "h.h"
#include <gtest/gtest.h>

// test balance in brackets
TEST(BracketsBalanceTest, BracketsBalance1) {
    EXPECT_TRUE(bracketsBalance("{1,2,3}"));
}
TEST(BracketsBalanceTest, BracketsBalance2) {
    EXPECT_TRUE(bracketsBalance("<1,2,3>"));
}
TEST(BracketsBalanceTest, BracketsBalance3) {
    EXPECT_FALSE(bracketsBalance("{1,2,3"));
}
TEST(BracketsBalanceTest, BracketsBalance4) {
    EXPECT_FALSE(bracketsBalance("1,2,3}"));
}
TEST(BracketsBalanceTest, BracketsBalance5) {
    EXPECT_FALSE(bracketsBalance("<1,2,3"));
}
TEST(BracketsBalanceTest, BracketsBalance6) {
    EXPECT_FALSE(bracketsBalance("1,2,3>"));
}
TEST(BracketsBalanceTest, BracketsBalance7) {
    EXPECT_FALSE(bracketsBalance("1,2,3><"));
}

// test without nested sets
TEST(IntersectionTest, ValidIntersection1) {
    const std::string filename = "tempTestFile.txt";

    std::ofstream file(filename);
    file << "A={1,2,3}\n";
    file << "B={2,3,4}\n";
    file << "C={3,4,5}\n";
    file.close();

    std::vector<std::string> result = intersection(filename);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "3");

    std::remove(filename.c_str());
}
// test with nested tests and repeated elements
TEST(IntersectionTest, ValidIntersection2) {
    const std::string filename = "tempTestFile.txt";

    std::ofstream file(filename);
    file << "A={<2,3>,7,S_d,{ws,99},1_}\n";
    file << "B={{2,3},S_d,{99,ws},1,7}\n";
    file << "C={S_d,S_d,S_d}\n";
    file.close();

    std::vector<std::string> result = intersection(filename);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "S_d");

    std::remove(filename.c_str());
}

// test with different names of sets
TEST(IntersectionTest, ValidIntersection3) {
    const std::string filename = "tempTestFile.txt";

    std::ofstream file(filename);
    file << "ACS={1,2,3}\n";
    file << "B_0={2,3,4}\n";
    file << "CSADJASJFAS={3,4,5}\n";
    file.close();

    std::vector<std::string> result = intersection(filename);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "3");

    std::remove(filename.c_str());
}

//test with a lot of brackets
TEST(IntersectionTest, ValidIntersection4) {
    const std::string filename = "tempTestFile.txt";

    std::ofstream file(filename);
    file << "A={<>,{<>},{}}\n";
    file << "B={{{}},<0>,<>}\n";
    file << "C={<>}\n";
    file.close();

    std::vector<std::string> result = intersection(filename);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "<>");

    std::remove(filename.c_str());
}

TEST(IntersectionTest, ValidIntersection5) {
    const std::string filename = "tempTestFile.txt";

    std::ofstream file(filename);
    file << "A={{A,{B,{C,{D},{E}}}}}\n";
    file << "B={{A,{B,{C,{E},{D}}}}}\n";
    file.close();

    std::vector<std::string> result = intersection(filename);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "{A,{B,{C,{D},{E}}}}");

    std::remove(filename.c_str());
}

TEST(IntersectionTest, ValidIntersection6) {
    const std::string filename = "tempTestFile.txt";

    std::ofstream file(filename);
    file << "A={{1,2,3},<7,3>,2}\n";
    file << "B={{2,3,1},{7,3}}\n";
    file << "C={{1,3,2},{7,3}}\n";
    file.close();



    std::vector<std::string> result = intersection(filename);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "{1,2,3}");

    std::remove(filename.c_str());
}

// test with directed set
TEST(ExeptionsTest, InvalidArgument1) {
    const std::string filename = "tempTestFile.txt";

    std::ofstream file(filename);
    file << "A={<1>,2}\n";
    file << "B=<2,3>\n";
    file << "C={4,7m}\n";
    file.close();

    EXPECT_THROW(read(filename), std::invalid_argument);

    std::remove(filename.c_str());
}

// test with wrong brackets balance
TEST(ExeptionsTest, InvalidArgument2) {
    const std::string filename = "tempTestFile.txt";

    std::ofstream file(filename);
    file << "A={<1>,2}\n";
    file << "B={2,{3}\n";
    file << "C={4,7m}\n";
    file.close();

    EXPECT_THROW(read(filename), std::invalid_argument);

    std::remove(filename.c_str());
}

// test with unresolved characters
TEST(ExeptionsTest, InvalidArgument3) {
    const std::string filename = "tempTestFile.txt";

    std::ofstream file(filename);
    file << "A={<1>,2}\n";
    file << "B={2,*3}\n";
    file << "C={4,7m}\n";
    file.close();

    EXPECT_THROW(read(filename), std::invalid_argument);

    std::remove(filename.c_str());
}

// test with wrong(non-existent) file path
TEST(ExeptionsTest, InvalidArgument4) {
    const std::string filename = "tempTestFile.txt";

    EXPECT_THROW(read(filename), std::invalid_argument);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}