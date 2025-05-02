#include "pch.h"

//тесты isCorrect
TEST(TestCase, TestIsCorrect1) {
	string input = "{}";
	EXPECT_TRUE(is_correct(input));
}

TEST(TestCase, TestIsCorrect2) {
	string input = "Abacadabra    =   {<a,b,<c,d>, {b, asd, as10xc}>}";
	EXPECT_TRUE(is_correct(input));
}

TEST(TestCase, TestIsCorrect3) {
	string input = "A = {axcv, ZCXasd, <,    >, 1223}";
	EXPECT_FALSE(is_correct(input));
}

//тесты на индивидуальное задание
TEST(TestCase, TestCombinations1){
	string input = "A = {axcv, ZCXasd, 1223, <b,   c>}";
	vector<string> parsering = parse(input);
	int n = 2;
	EXPECT_EQ(numOfSets(combinations(parsering,n)), 6);
}

TEST(TestCase, TestCombinations2) {
	string input = "A = {321, asd,  554 ,ZCXasd, 1223, <b, {}   c>}";
	vector<string> parsering = parse(input);
	int n = 3;
	EXPECT_EQ(numOfSets(combinations(parsering,n)), 20);
}

TEST(TestCase, TestCombinations3) {
	string input = "A = {a,b,c   ,d,e,f,g,h,i,j}";
	vector<string> parsering = parse(input);
	int n = 1;
	EXPECT_EQ(numOfSets(combinations(parsering,n)), 10);
}

//тесты на contains

TEST(TestCase, TestContains1) {
	string input = "A = {axcv, ZCXasd, 1223, <b,   c>}";
	vector<string> parsering = parse(input);
	EXPECT_TRUE(contains(parsering, "<b,c>"));
}

TEST(TestCase, TestContains2) {
	string input = "A = {321, xui,  554 ,ZCXasd, 1223, <b, {}   c>}";
	vector<string> parsering = parse(input);
	EXPECT_FALSE(contains(parsering, "123"));
}

TEST(TestCase, TestContains3) {
	string input = "A = {a,b,c, {}   ,d,e,f,g,h,i,j}";
	vector<string> parsering = parse(input);
	EXPECT_TRUE(contains(parsering, "{}"));
}

//тест на чтение из файлов

TEST(TestCase, TestFileRead1) {
	ofstream File("test.txt");
	File << "A = {axcv, ZCXasd, {<}>, 1223}";
	File.close();
	string input = ReadFile("test.txt");
	vector<string> parsering = parse(input);
	EXPECT_FALSE(is_correct(input));
	remove("test.txt");
}

TEST(TestCase, TestFileRead2) {
	ofstream File("test.txt");
	File << "A = {1,asd,<1,{25}>,{<6,9>}}";
	File.close();
	string input = ReadFile("test.txt");
	vector<string> parsering = parse(input);
	int n = 3;
	EXPECT_EQ(numOfSets(combinations(parsering, n)), 4);
	remove("test.txt");
}

TEST(TestCase, TestFileRead3) {
	ofstream File("test.txt");
	File << "A = {ad,23,{ad,s},<7,3>}";
	File.close();
	string input = ReadFile("test.txt");
	vector<string> parsering = parse(input);
	EXPECT_TRUE(contains(parsering, "<7,3>"));
	remove("test.txt");
}