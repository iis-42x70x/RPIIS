#include "header.h"
#include <gtest/gtest.h>

TEST(ExampleTest, BasicTest1){
    EXPECT_EQ(result("abracadabra"), "10110101001100010110101");
}

TEST(ExampleTest, BasicTest2){
    EXPECT_EQ(result("pioivis"), "011101010011000");
}

TEST(ExampleTest, BasicTest3){
    EXPECT_EQ(result("manchester"), "11011100011010001111000101111100");
}

TEST(ExampleTest, BasicTest4){
    EXPECT_EQ(result("matematica"), "0111101100011110100100011");
}

TEST(ExampleTest, BasicTest5){
    EXPECT_EQ(result("crocodil"), "01111000100110101100");
}

TEST(ExampleTest, BasicTest6){
    EXPECT_EQ(result("herobrine"), "1100111100100011110110001");
}

TEST(ExampleTest, BasicTest7){
    EXPECT_EQ(result("perpendiculyarnost'"), "00111111110001111111011100000100001011101010011000111011010111011001010100");
}

TEST(ExampleTest, BasicTest8){
    EXPECT_EQ(result("electroneiromiographiya"), "011110001100110010010101000101110001010100001001011111101011011111011101100111001101");
}

TEST(ExampleTest, ErrorTest1){
    EXPECT_EQ(result("nnnnn"), "error");
}

TEST(ExampleTest, ErrorTest2){
    EXPECT_EQ(result(""), "error");
}

int main(int argc,char *argv[]){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
