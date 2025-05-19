#include "pch.h"
using namespace std;
TEST(TestNotSpace, TestNotSpace1) {
	const char* str1 = "B = { o , < 1, 2 > , A2 ,c 3 ,B ,b3 _ A, { } , {o , { } , A} }";
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