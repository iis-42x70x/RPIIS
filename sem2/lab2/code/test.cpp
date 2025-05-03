#include "pch.h"
#include "C:\œËŒ»‚»—\sem2\lab2\lab2\Header.h"
#include "C:\œËŒ»‚»—\sem2\lab2\lab2\source.cpp"
#include <vector>
#include <string>

TEST(TestCaseName, Peresechenie) {
	vector <Set> test(2);
	vector <string> first = {
		"x", "{x,y,z}", "{x,y,z,{m,n}}", "{{x,y}}"
	};
	test[0].set_vector(first);

	vector <string> second = {
		"x", "2", "{x,y,z,p,q,r}", "{x,y,z,{m,n,p}}", "{{x,y,y}}"
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
	EXPECT_EQ(resulti.size(), 2);
	EXPECT_EQ(resulti[0], "x");
	EXPECT_EQ(resulti[1], "{{x,y}}");
}

TEST(TestCaseName2, Peresechenie) {
	vector <Set> test(4);
	vector <string> first = {
		"p", "{p,q,r}", "{p,r,s,{t,u}}", "{{p,q}}"
	};
	test[0].set_vector(first);

	vector <string> second = {
		"p", "3", "{p,q,r,s}", "{p,r,{v,w}}", "{{p,q,q}}"
	};
	test[1].set_vector(second);

	vector <string> third = {
		"p", "{p,s,t}", "{p,q,{x,y}}", "{{p}}"
	};
	test[2].set_vector(third);

	vector <string> fourth = {
		"p", "4", "{p,q,x}", "{p,s,{v}}", "{{p,q,r}}"
	};
	test[3].set_vector(fourth);

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
	for (auto& el : test[3].get_vector()) {
		string result = sort_set(el);
		el = result;
	}

	vector <string> resulti = test[0].get_vector();
	main_intersection(test, resulti);

	EXPECT_EQ(resulti.size(), 1);
	EXPECT_EQ(resulti[0], "p");
}
	

TEST(bublesort, sort_test) {
	vector <string> test{

		"f", "{m, z, l, l, f, f}", "<z, y, x>", "{a,s,d,f,g,h,j,{a,{{x,x,d}},d}}", "{}", "{{}}"
	};

	for (auto& el : test) {
		el = sort_set(el);
	}
	EXPECT_EQ(test[0], "f");
	EXPECT_EQ(test[1], "{f,l,m,z}");
	EXPECT_EQ(test[2], "<z,y,x>");
	EXPECT_EQ(test[3], "{a,d,f,g,h,j,s,{a,d,{{d,x}}}}");
	EXPECT_EQ(test[4], "{}");
	EXPECT_EQ(test[5], "{{}}");

}


TEST(RemoveDuplicatesTest, RemovesDuplicates) {
	std::vector<std::string> test_unique = {

		"b", "r", "f", "f", "i", "s", "a", "i", "d", "g", "g"
	};

	remove_duplicates(test_unique);


	EXPECT_EQ(test_unique.size(), 8);

	EXPECT_EQ(test_unique[0], "b");
	EXPECT_EQ(test_unique[1], "r");
	EXPECT_EQ(test_unique[2], "f");
	EXPECT_EQ(test_unique[3], "i");
	EXPECT_EQ(test_unique[4], "s");
	EXPECT_EQ(test_unique[5], "a");
	EXPECT_EQ(test_unique[6], "d");
	EXPECT_EQ(test_unique[7], "g");


	std::vector<std::string> expected = {"b", "r", "f", "i", "s", "a", "d", "g"};
	EXPECT_EQ(test_unique, expected);
}


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}