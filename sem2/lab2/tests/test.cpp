#include "pch.h"
#include "C:\Users\Redmi\Desktop\legend\tests\tests\Header.h"
#include "C:\Users\Redmi\Desktop\legend\tests\tests\source.cpp"
#include <vector>
#include <string>


TEST(TestCaseName, Peresechenie) {
	vector <Set> test(2);
	vector <string> first = {
		"a", "{a,s,d,f,g,h}", "{a,s,d,f,g,h,j,{a,s,d}}", "{{a}}"
	};
	test[0].set_of_vector(first);
	vector <string> second = {
		"a", "1", "{a,s,d,f,g,h,k,i,u,o}", "{a,s,d,f,h,h,g,j,{a,s,d}}", "{{a,a}}"
	};
	test[1].set_vector(second);

	for (auto& el : test[0].get_vector()) {
		string result = sort_set(el);
		el = result;
	}
	for (auto& el : test[1].get_vector()) {
		string result = sort_set(el);
		el = result;
	}
	vector <string> resulti = test[0].get_vector();

	main_intersection(test, resulti);
	EXPECT_EQ(resulti.size(), 3);
	EXPECT_EQ(resulti[0], "a");
	EXPECT_EQ(resulti[1], "{a,d,f,g,h,j,s,{a,d,s}}");
	EXPECT_EQ(resulti[2], "{{a}}");

}

TEST(TestCaseName2, Intersection) {
	vector <Set> test(3);
	vector <string> first = {
		"a", "{a,s,d,f,g,h}", "{a,s,d,f,g,h,j,{a,{{s,s,d}},d}}", "{{a}}", "{}", "{{}}"
	};
	test[0].set_vector(first);
	vector <string> second = {
		"a", "1", "{a,s,d,f,g,h,k,i,u,o}", "{a,s,d,f,h,h,g,j,{a,s,d}}" ,"{a,s,d,f,g,h,j,{a,{{s,s,d,d}},d}}", "{{a,a}}","{}", "{{}}"
	};
	test[1].set_vector(second);
	vector <string> third = {
		"{a,s,d,f,g,h,j,{a,{{s,s,d,d}},d}}", "{{a,a}}","{}", "{{}}", "a", "2"
	};
	test[2].set_vector(third);

	for (auto& el : test[0].get_vector()) {
		string result = sort_set(el);
		el = result;
	}
	for (auto& el : test[1].get_vector()) {
		string result = sort_set(el);
		el = result;
	}
	for (auto& el : test[2].get_vector()) {
		string result = sort_set(el);
		el = result;
	}
	vector <string> resulti = test[0].get_vector();

	main_intersection(test, resulti);
	EXPECT_EQ(resulti.size(), 5);
	EXPECT_EQ(resulti[0], "{a,d,f,g,h,j,s,{a,d,{{d,s}}}}");
	EXPECT_EQ(resulti[1], "{{a}}");
	EXPECT_EQ(resulti[2], "{}");
	EXPECT_EQ(resulti[3], "{{}}");;
	EXPECT_EQ(resulti[4], "a");


}



TEST(bubble_sort, sort_test) {
	vector <string> test{
		"a", "{a,s,d,f,g,h}", "{a,s,d,f,g,h,j,{a,{{s,s,d}},d}}", "{{a}}", "{}", "{{}}"
	};

	for (auto& el : test) {
		el = sort_set(el);
	}
	EXPECT_EQ(test[0], "a");
	EXPECT_EQ(test[1], "{a,d,f,g,h,s}");
	EXPECT_EQ(test[2], "{a,d,f,g,h,j,s,{a,d,{{d,s}}}}");
	EXPECT_EQ(test[3], "{{a}}");
	EXPECT_EQ(test[4], "{}");
	EXPECT_EQ(test[5], "{{}}");

}


TEST(RemoveDuplicatesTest, RemovesDuplicates) {
	std::vector<std::string> test_unique = {
		"a","b","d","c","s","d","e","d","a","s","d","f","s","d","s","g"
	};

	remove_duplicates(test_unique);


	EXPECT_EQ(test_unique.size(), 8);

	EXPECT_EQ(test_unique[0], "a");
	EXPECT_EQ(test_unique[1], "b");
	EXPECT_EQ(test_unique[2], "d");
	EXPECT_EQ(test_unique[3], "c");
	EXPECT_EQ(test_unique[4], "s");
	EXPECT_EQ(test_unique[5], "e");
	EXPECT_EQ(test_unique[6], "f");
	EXPECT_EQ(test_unique[7], "g");


	std::vector<std::string> expected = { "a", "b", "d", "c", "s", "e", "f", "g" };
	EXPECT_EQ(test_unique, expected);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}