#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

enum ElementType { STRING, SET, ORSET };

struct SetElement {
    ElementType type;
    string strValue;
    vector<SetElement> setValue;
};

// Тест для функции SpaceCheck
TEST(SpaceCheckTest, HandlesSpaces) {
    EXPECT_TRUE(SpaceCheck(' '));
    EXPECT_TRUE(SpaceCheck('\n'));
    EXPECT_TRUE(SpaceCheck('\t'));
    EXPECT_FALSE(SpaceCheck('a'));
}

// Тест для функции DigitCheck
TEST(DigitCheckTest, HandlesDigits) {
    EXPECT_TRUE(DigitCheck('0'));
    EXPECT_TRUE(DigitCheck('9'));
    EXPECT_FALSE(DigitCheck('a'));
}

// Тест для функции LetterCheck
TEST(LetterCheckTest, HandlesLetters) {
    EXPECT_TRUE(LetterCheck('a'));
    EXPECT_TRUE(LetterCheck('Z'));
    EXPECT_FALSE(LetterCheck('1'));
}

// Тест для функции EqualSets
TEST(EqualSetsTest, HandlesEqualSets) {
    SetElement set1 = { SET, "", { { STRING, "a", {} }, { STRING, "b", {} } } };
    SetElement set2 = { SET, "", { { STRING, "a", {} }, { STRING, "b", {} } } };
    EXPECT_TRUE(EqualSets(set1.setValue, set2.setValue));
    SetElement set3 = { ORSET, "", { { STRING, "b", {} }, { STRING, "b", {} } } };
    EXPECT_FALSE(EqualSets(set1.setValue, set3.setValue));
}

// Тест для функции EqualOrsets
TEST(EqualOrsetsTest, HandlesEqualOrsets) {
    vector<SetElement> orset1 = { { STRING, "a", {} }, { STRING, "b", {} } };
    vector<SetElement> orset2 = { { STRING, "a", {} }, { STRING, "b", {} } };
    EXPECT_TRUE(EqualOrsets(orset1, orset2));
    vector<SetElement> orset3 = { { STRING, "a", {} }, { STRING, "c", {} } };
    EXPECT_FALSE(EqualOrsets(orset1, orset3));
}

// Тест для функции SymmetricDifferenceSet
TEST(SymmetricDifferenceTest, HandlesDifferences) {
    vector<SetElement> setA = { { STRING, "a", {} }, { STRING, "b", {} } };
    vector<SetElement> setB = { { STRING, "b", {} }, { STRING, "c", {} } };
    vector<SetElement> expected = { { STRING, "a", {} }, { STRING, "c", {} } };

    vector<SetElement> result = SymmetricDifferenceSet(setA, setB);
    EXPECT_EQ(result.size(), expected.size());
    for (int i = 0; i < result.size(); i++) {
        EXPECT_EQ(result[i].strValue, expected[i].strValue);
    }
}

// Тест для SymmetricDifferenceOrset
TEST(SymmetricDifferenceOrsetTest, HandlesDifferencesInOrset) {
    vector<SetElement> orsetA = { { STRING, "a", {} }, { STRING, "b", {} } };
    vector<SetElement> orsetB = { { STRING, "b", {} }, { STRING, "c", {} } };
    vector<SetElement> result = SymmetricDifferenceOrset(orsetA, orsetB);

    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result[0].strValue, "a");
    EXPECT_EQ(result[1].strValue, "b");
    EXPECT_EQ(result[2].strValue, "b");
    EXPECT_EQ(result[3].strValue, "c");
}

// Тест для функции Contains
TEST(ContainsTest, HandlesContainsLogic) {
    vector<SetElement> set = { { STRING, "a", {} }, { STRING, "b", {} } };
    SetElement element = { STRING, "a", {} };

    EXPECT_TRUE(Contains(set, element));

    SetElement notPresent = { STRING, "c", {} };
    EXPECT_FALSE(Contains(set, notPresent));
}

// Тест для функции ParsingElement
TEST(ParsingElementTest, HandlesParsing) {
    string input = "abc";
    int pos = 0;

    SetElement result = ParsingElement(input, pos);
    EXPECT_EQ(result.type, STRING);
    EXPECT_EQ(result.strValue, "abc");
}

// Тест для ParsingSet
TEST(ParsingSetTest, HandlesSimpleSet) {
    string input = "{a, b, c}";
    int pos = 0;

    SetElement result = ParsingSet(input, pos);
    EXPECT_EQ(result.type, SET);
    ASSERT_EQ(result.setValue.size(), 3);
    EXPECT_EQ(result.setValue[0].strValue, "a");
    EXPECT_EQ(result.setValue[1].strValue, "b");
    EXPECT_EQ(result.setValue[2].strValue, "c");
}


int main(int argc, char** argv) {
	setlocale(LC_ALL, "RU");
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
