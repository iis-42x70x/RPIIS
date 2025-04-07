#include"pch.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <stack>
using namespace std;

enum ElementType { STRING, SET, ORSET };

struct element {
    ElementType type;
    string value;
    vector<element> setik;
};

bool letter(char);
bool digit(char);
bool space(char);
bool ElementCompare(const element, const element);
element intersection(const element, const element);
void ElementCout(const element);
void StringToElement(element&, string, int, int);
bool SetUniqueCheck(element);
bool StringCheck(string&);
bool letter(char k) {
    return (k >= 'а' && k <= 'я') || (k >= 'А' && k <= 'Я') ||
        (k >= 'a' && k <= 'z') || (k >= 'A' && k <= 'Z');
}

bool digit(char f) {
    return f >= '0' && f <= '9';
}

bool space(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r';
}

bool ElementCompare(const element el1, const element el2) {
    if (el1.type != el2.type) return false;

    if (el1.type == STRING) {
        if (el1.value == el2.value) return true;
        else return false;
    }

    else if (el1.type == ORSET) {
        if (el1.setik.size() != el2.setik.size()) return false;
        for (int i = 0; i < el1.setik.size(); i++) {
            if (!ElementCompare(el1.setik[i], el2.setik[i])) return false;
        }
    }

    else if (el1.type == SET) {
        if (el1.setik.size() != el2.setik.size()) return false;
        for (int i = 0; i < el1.setik.size(); i++) {
            bool find = false;
            for (int j = 0; j < el2.setik.size(); j++) {
                if (ElementCompare(el1.setik[i], el2.setik[j])) {
                    find = true;
                    break;
                }
            }
            if (!find) return false;
        }
    }
    return true;
}

element intersection(const element el1, const element el2) {
    element result;
    if (el1.type == SET && el2.type == SET) {
        result.type = SET;
        for (element c1 : el1.setik) {
            for (element c2 : el2.setik) {
                if (ElementCompare(c1, c2)) {
                    result.setik.push_back(c1);
                    break;
                }
            }
        }
    }

    else if (el1.type == ORSET && el2.type == ORSET) {
        result.type = ORSET;
        int size = (el1.setik.size() > el2.setik.size()) ? el2.setik.size() : el1.setik.size();
        for (int i = 0; i < size; i++) {
            if (ElementCompare(el1.setik[i], el2.setik[i]))result.setik.push_back(el1.setik[i]);
        }
    }
    return result;
}

void ElementCout(const element el) {
    if (el.type == STRING) cout << el.value;
    else if (el.type == SET) {
        cout << "{";
        for (int i = 0; i < el.setik.size(); i++) {
            ElementCout(el.setik[i]);
            if (i < el.setik.size() - 1) cout << ", ";
        }
        cout << "}";
    }
    else if (el.type == ORSET) {
        cout << "<";
        for (int i = 0; i < el.setik.size(); i++) {
            ElementCout(el.setik[i]);
            if (i < el.setik.size() - 1) cout << ", ";
        }
        cout << ">";
    }
}

void StringToElement(element& el, string s, int start, int end) {
    int k, skobka;
    string val;
    int count = 0;
    if (s[start] == '<') el.type = ORSET;
    else el.type = SET;
    for (int i = start + 1; i <= end - 1; i++) {
        if (letter(s[i])) {
            val = "";
            while ((letter(s[i]) || digit(s[i]) || s[i] == '_') && i <= end - 1) {
                val += s[i];
                i++;
            }
            i--;
            el.setik.resize(el.setik.size() + 1);
            el.setik[count].value = val;
            el.setik[count].type = STRING;
            count++;
        }

        else if (digit(s[i]) || s[i] == '-') {
            val = "";
            if (s[i] == '-') {
                val += s[i];
                i++;
            }
            while (digit(s[i]) && i <= end - 1) {
                val += s[i];
                i++;
            }
            i--;
            el.setik.resize(el.setik.size() + 1);
            el.setik[count].value = val;
            el.setik[count].type = STRING;
            count++;
        }

        else if (s[i] == '{') {
            skobka = 1;
            k = i + 1;
            while (k <= end && skobka != 0) {
                if (s[k] == '{') skobka++;
                else if (s[k] == '}') skobka--;
                k++;
            }
            el.setik.resize(el.setik.size() + 1);
            if (k - i == 2) {
                el.setik[count].type = SET;
                el.setik[count].setik.resize(el.setik[count].setik.size() + 1);
                el.setik[count].setik[0].value = "";
                el.setik[count].setik[0].type = STRING;
            }
            else StringToElement(el.setik[count], s, i, k--);
            count++;
            i = k--;
        }

        else if (s[i] == '<') {
            skobka = 1;
            k = i + 1;

            while (k <= end && skobka != 0) {
                if (s[k] == '<') skobka++;
                else if (s[k] == '>') skobka--;
                k++;
            }
            el.setik.resize(el.setik.size() + 1);
            if (k - i == 2) {
                el.setik[count].type = ORSET;
                el.setik[count].setik.resize(el.setik[count].setik.size() + 1);
                el.setik[count].setik[0].value = "";
                el.setik[count].setik[0].type = STRING;
            }
            else StringToElement(el.setik[count], s, i, k--);
            count++;
            i = k--;
        }
    }
}

bool SetUniqueCheck(element el) {
    if (el.type == SET) {
        for (int i = 0; i < el.setik.size() - 1; i++) {
            for (int j = i + 1; j < el.setik.size(); j++) {
                if (ElementCompare(el.setik[i], el.setik[j])) return false;
            }
        }
    }

    else if (el.type == ORSET) {
        for (int i = 0; i < el.setik.size(); i++) {
            if (el.setik[i].type == SET && !SetUniqueCheck(el.setik[i])) return false;
            else if (el.setik[i].type == ORSET) SetUniqueCheck(el.setik[i]);
        }
    }

    else exit(-3);

    return true;
}

bool StringCheck(string& str) {
    if (str.empty() || (str[0] != '{' && str[0] != '<')) return false;
    if ((str[0] == '{' && str[str.size() - 1] != '}') || (str[0] == '<' && str[str.size() - 1] != '>')) return false;

    for (int i = 0; i < str.size(); i++) {
        if (letter(str[i])) {
            i++;
            while ((letter(str[i]) || digit(str[i]) || str[i] == '_') && i < str.size()) i++;
            int j = i;
            i--;
            while (space(str[j]) && j < str.size()) j++;
            if (j == str.size()) return false;
            else if (str[j] != '}' && str[j] != '>' && str[j] != ',') return false;
        }
        else if (space(str[i])) {
            for (int j = i + 1; j < str.size(); j++)str[j - 1] = str[j];
            str.pop_back();
            i--;
        }
    }

    stack <char> bra;
    int count = 0;
    int count1 = 0;
    bool var = false;
    for (int j = 0; j < str.size(); j++) {
        if (j + 1 < str.size() && ((str[j] == '{' && str[j + 1] == ',') || (str[j] == '<' && str[j + 1] == ',') ||
            (str[j] == ',' && (str[j + 1] == '}' || str[j + 1] == '>')) || (str[j] == ',' && str[j + 1] == ',') ||
            (str[j] == '}' && str[j + 1] == '{') || (str[j] == '>' && str[j + 1] == '<'))) {
            return false;
        }

        if (letter(str[j])) {
            j++;
            if (!var) {
                while ((letter(str[j]) || digit(str[j]) || str[j] == '_') && j < str.size()) j++;
                j--;
                var = true;
            }
            else return false;


        }

        else if (digit(str[j]) || str[j] == '-') {
            j++;
            if (!var) {
                while ((letter(str[j]) || digit(str[j]) || str[j] == '_') && j < str.size()) j++;
                j--;
                var = true;
            }
            else return false;
        }
        else var = false;

        if (str[j] == '{' || str[j] == '<' || str[j] == '}' || str[j] == '>') {
            bra.push(str[j]);
            if (bra.top() == '}') {
                bra.pop();
                if (bra.empty() || bra.top() != '{') return false;
                bra.pop();
            }

            else  if (bra.top() == '>') {
                bra.pop();
                if (bra.empty() || bra.top() != '<') return false;
                bra.pop();
            }
        }
    }
    if (!bra.empty()) return false;
    return true;
}

TEST(ElementCompareTest, EqualStrings) {
    element el1 = { STRING, "abc", {} };
    element el2 = { STRING, "abc", {} };
    EXPECT_TRUE(ElementCompare(el1, el2));
}

TEST(ElementCompareTest, UnequalStrings) {
    element el1 = { STRING, "abc", {} };
    element el2 = { STRING, "def", {} };
    EXPECT_FALSE(ElementCompare(el1, el2));
}

TEST(ElementCompareTest, EqualSets) {
    element el1 = { SET, "", {{STRING, "x", {}}, {STRING, "y", {}}} };
    element el2 = { SET, "", {{STRING, "y", {}}, {STRING, "x", {}}} };
    EXPECT_TRUE(ElementCompare(el1, el2));
}

TEST(ElementCompareTest, UnequalSets) {
    element el1 = { SET, "", {{STRING, "x", {}}} };
    element el2 = { SET, "", {{STRING, "y", {}}} };
    EXPECT_FALSE(ElementCompare(el1, el2));
}

TEST(ElementCompareTest, EqualOrsets) {
    element el1 = { ORSET, "", {{STRING, "x", {}}, {STRING, "y", {}}} };
    element el2 = { ORSET, "", {{STRING, "x", {}}, {STRING, "y", {}}} };
    EXPECT_TRUE(ElementCompare(el1, el2));
}

TEST(ElementCompareTest, UnequalOrsets) {
    element el1 = { ORSET, "", {{STRING, "x", {}}, {STRING, "y", {}}} };
    element el2 = { ORSET, "", {{STRING, "y", {}}, {STRING, "x", {}}} };
    EXPECT_FALSE(ElementCompare(el1, el2));
}

TEST(IntersectionTest, SetsIntersection) {
    element el1 = { SET, "", {{STRING, "x", {}}, {STRING, "y", {}}, {STRING, "z", {}}} };
    element el2 = { SET, "", {{STRING, "y", {}}, {STRING, "z", {}}} };
    element result = intersection(el1, el2);
    EXPECT_EQ(result.setik.size(), 2);
    EXPECT_TRUE(ElementCompare(result.setik[0], { STRING, "y", {} }));
    EXPECT_TRUE(ElementCompare(result.setik[1], { STRING, "z", {} }));
}

TEST(IntersectionTest, OrsetsIntersection) {
    element el1 = { ORSET, "", {{STRING, "a", {}}, {STRING, "b", {}}} };
    element el2 = { ORSET, "", {{STRING, "a", {}}, {STRING, "c", {}}} };
    element result = intersection(el1, el2);
    EXPECT_EQ(result.setik.size(), 1);
    EXPECT_TRUE(ElementCompare(result.setik[0], { STRING, "a", {} }));
}

TEST(ElementCoutTest, PrintString) {
    element el = { STRING, "hello", {} };
    testing::internal::CaptureStdout();
    ElementCout(el);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "hello");
}

TEST(ElementCoutTest, PrintSet) {
    element el = { SET, "", {{STRING, "a", {}}, {STRING, "b", {}}} };
    testing::internal::CaptureStdout();
    ElementCout(el);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{a, b}");
}

TEST(ElementCoutTest, PrintOrset) {
    element el = { ORSET, "", {{STRING, "x", {}}, {STRING, "y", {}}} };
    testing::internal::CaptureStdout();
    ElementCout(el);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "<x, y>");
}

TEST(StringToElementTest, ParseStringToSet) {
    element el;
    StringToElement(el, "{a, b}", 0, 6);
    EXPECT_EQ(el.type, SET);
    EXPECT_EQ(el.setik.size(), 2);
    EXPECT_TRUE(ElementCompare(el.setik[0], { STRING, "a", {} }));
    EXPECT_TRUE(ElementCompare(el.setik[1], { STRING, "b", {} }));
}

TEST(StringToElementTest, ParseStringToOrset) {
    element el;
    StringToElement(el, "<x, y>", 0, 6);
    EXPECT_EQ(el.type, ORSET);
    EXPECT_EQ(el.setik.size(), 2);
    EXPECT_TRUE(ElementCompare(el.setik[0], { STRING, "x", {} }));
    EXPECT_TRUE(ElementCompare(el.setik[1], { STRING, "y", {} }));
}

TEST(StringToElementTest, ParseNestedSet) {
    element el;
    StringToElement(el, "{a, {b, c}}", 0, 11);
    EXPECT_EQ(el.type, SET);
    EXPECT_EQ(el.setik.size(), 2);
    EXPECT_TRUE(ElementCompare(el.setik[0], { STRING, "a", {} }));
    EXPECT_EQ(el.setik[1].type, SET);
    EXPECT_EQ(el.setik[1].setik.size(), 2);
    EXPECT_TRUE(ElementCompare(el.setik[1].setik[0], { STRING, "b", {} }));
    EXPECT_TRUE(ElementCompare(el.setik[1].setik[1], { STRING, "c", {} }));
}

TEST(SetUniqueCheckTest, UniqueElements) {
    element el = { SET, "", {{STRING, "x", {}}, {STRING, "y", {}}} };
    EXPECT_TRUE(SetUniqueCheck(el));
}

TEST(SetUniqueCheckTest, DuplicateElements) {
    element el = { SET, "", {{STRING, "x", {}}, {STRING, "x", {}}} };
    EXPECT_FALSE(SetUniqueCheck(el));
}

TEST(StringCheckTest, CorrectStringFormat) {
    std::string str = "{a, b, {c, d}}";
    EXPECT_TRUE(StringCheck(str));
}

TEST(StringCheckTest, IncorrectStringFormat) {
    std::string str = "{a, b, <c, d}";
    EXPECT_FALSE(StringCheck(str));
}
