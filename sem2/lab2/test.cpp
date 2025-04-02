#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

TEST(TestNotSpace, TestNotSpace1) {
	string str1 = "B = { o , < 1, 2 > , A2 ,c 3 ,B ,b3 _ A, { } , {o , { } , A} }";
	string str2 = "B={o,<1,2>,A2,c3,B,b3_A,{},{o,{},A}}";
	EXPECT_EQ(NotSpace(str1), str2);
}
TEST(TestCheckStr, TestCheckStr1) {
	string str = "{o,<1,2>,A2,c3,B,b3_A,{},{o,{},A}}";
	EXPECT_EQ(CheckStr(str), true);
}
TEST(TestCheckStr, TestCheckStr2) {
	string str = "{o,><1,2>,A2,c3,B,b3_A,{},{o,{},A}}";
	EXPECT_EQ(CheckStr(str), false);
}
TEST(TestCheckStr, TestCheckStr3) {
	string str = "{o<1,2>,A2,c3,B,b3_A,{},{o,{},A}}";
	EXPECT_EQ(CheckStr(str), false);
}
TEST(TestCheckStr, TestCheckStr4) {
	string str = "{o,<<1,2>,A2,c3,B,b3_A,{},{o,{},A}}";
	EXPECT_EQ(CheckStr(str), false);
}
TEST(TestCheckStr, TestCheckStr5) {
	string str = "{{o,<1,2>,A2,c3,B,b3_A,{},{o,{},A}}";
	EXPECT_EQ(CheckStr(str), false);
}
TEST(TestCheckStr, TestCheckStr6) {
	string str = "";
	EXPECT_EQ(CheckStr(str), false);
}
TEST(TestPermutation, TestPermutation1) {
	vector<string> a = { "f","e","d","c","b","a" };
	EXPECT_EQ(Permutation(a), false);
}
TEST(TestPermutation, TestPermutation2) {
	vector<string> a = { "f","e","d","c","b","a","b"};
	EXPECT_EQ(Permutation(a), true);
}
TEST(TestFragmentation, TestFragmentation1) {
	string str = "{f,{e,d},c,<b,a>,b}";
	vector<string> a = { "f","{e,d}","c","<b,a>","b" };
	EXPECT_EQ(Fragmentation(str), a);
}
TEST(TestFragmentation, TestFragmentation2) {
	string str = "f,{e,d},c,<b,a>,b";
	vector<string> a = { "f","{e,d}","c","<b,a>","b" };
	EXPECT_EQ(Fragmentation(str), a);
}
int main(int argc, char** argv) {
	setlocale(LC_ALL, "RU");
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
