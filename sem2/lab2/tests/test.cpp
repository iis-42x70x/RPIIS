#include "pch.h"
#include "../Lab2/Header.h"
#include "../Lab2/realisation.cpp"
#include <vector>
#include <string>

TEST(set_set, TestSetSet) {
    vector<string> test = {
      "1", "{2,3,<1,2>}", "3", "A", "srkmlfl"
    };

    Union set;
    set.setSet(test);

    EXPECT_EQ(set.getSet().size(), 5);
    EXPECT_EQ(set.getSet()[0], "1");
    EXPECT_EQ(set.getSet()[1], "{2,3,<1,2>}");
    EXPECT_EQ(set.getSet()[2], "3");
    EXPECT_EQ(set.getSet()[3], "A");
    EXPECT_EQ(set.getSet()[4], "srkmlfl");
}

TEST(setsUnion, TestSetsUnion)
{
    vector<Union> sets(3);

    vector<string> first = {
      "a", "b", "{1,2,3}", "abc"
    };

    sets[0].setSet(first);

    vector<string> second = {
      "12", "32", "{<1,2>,3}", "<3,4,5>", "a", "b"
    };

    sets[1].setSet(second);

    vector<string> third = {
      "{{acbhjc},5}", "12", "<1,2>"
    };

    sets[2].setSet(third);

    vector<string> result = sets[0].getSet();
    for (int i = 1; i < sets.size(); i++)
    {
        result = sets[i].setsUnion(result);
    }

    EXPECT_EQ(result.size(), 10);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "b");
    EXPECT_EQ(result[2], "{1,2,3}");
    EXPECT_EQ(result[3], "abc");
    EXPECT_EQ(result[4], "12");
    EXPECT_EQ(result[5], "32");
    EXPECT_EQ(result[6], "{3,<1,2>}");
    EXPECT_EQ(result[7], "<3,4,5>");
    EXPECT_EQ(result[8], "{5,{acbhjc}}");
    EXPECT_EQ(result[9], "<1,2>");
}

TEST(Correct_Set, TestSetCorrect)
{
    Union set;
    string test1 = "{a, b, {1,2,3}, abc}";
    string test2 = "{a,b, 12, 58, <1, 2, 3>}";

    EXPECT_EQ(set.Correct_Set(test1), true);
    EXPECT_EQ(set.Correct_Set(test2), true);
}

TEST(add, TestAddSet)
{
    Union set;
    string test1 = "{a, b, {1,2,3}, abc}";

    set.add(test1);

    EXPECT_EQ(set.getSet().size(), 4);
    EXPECT_EQ(set.getSet()[0], "a");
    EXPECT_EQ(set.getSet()[1], "b");
    EXPECT_EQ(set.getSet()[2], "{1,2,3}");
    EXPECT_EQ(set.getSet()[3], "abc");
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}