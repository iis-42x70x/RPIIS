#include "header.h"


bool check(const string& input) {
    if (input.empty() || input[0] != '{' || input.back() != '}') return false;
    int index = 0;
    vector<char> uniqueChars;
    vector<string> uniqueSubsets;
    return checkSet(input, index, uniqueChars, uniqueSubsets);
}

bool checkSet(const string& input, int& index, vector<char>& uniqueChars, vector<string>& uniqueSubsets) {
    index++;
    vector<char> localUniqueChars;
    vector<string> localUniqueSubsets;

    int bracketBalance = 1;

    while (index < input.size()) {
        while (isspace(input[index])) index++;

        if (input[index] == '}') {
            index++;
            return true;
        }

        if (input[index] == '{') {
            int start = index;
            vector<char> nestedUniqueChars;
            vector<string> nestedUniqueSubsets;
            if (!checkSet(input, index, nestedUniqueChars, nestedUniqueSubsets))
                return false;

            string subsetStr = input.substr(start, index - start);
            if (find(localUniqueSubsets.begin(), localUniqueSubsets.end(), subsetStr) != localUniqueSubsets.end()) {
                return false;
            }
            localUniqueSubsets.push_back(subsetStr);
        }
        else if (input[index] == '<') {
            int start = index;
            vector<char> tupleUniqueChars;
            if (!checkTuple(input, index, tupleUniqueChars))
                return false;

            string tupleStr = input.substr(start, index - start);
            if (find(localUniqueSubsets.begin(), localUniqueSubsets.end(), tupleStr) != localUniqueSubsets.end()) {
                return false;
            }
            localUniqueSubsets.push_back(tupleStr);
        }
        else if (isalpha(input[index])) {
            char c = input[index];
            if (find(localUniqueChars.begin(), localUniqueChars.end(), c) != localUniqueChars.end())
                return false;
            localUniqueChars.push_back(c);
            uniqueChars.push_back(c);
            index++;
        }
        else if (input[index] == ',') {
            index++;
            while (isspace(input[index])) index++;
        }
        else {
            return false;
        }
    }
    return false;
}


bool checkTuple(const string& input, int& index, vector<char>& uniqueChars) {
    index++;
    int elements = 0;
    vector<string> tupleElements;

    while (index < input.size()) {
        while (isspace(input[index])) index++;
        if (input[index] == '>') {
            index++;
            if (elements != 2 and elements != 0) {
                cerr << "Ошибка: кортеж должен содержать  2 или 0 элементов\n";
                return false;
            }
            return true;
        }
        if (input[index] == '{') {
            vector<char> nestedUnique;
            vector<string> dummy;
            if (!checkSet(input, index, nestedUnique, dummy)) return false;
            elements++;
        }
        else if (input[index] == '<') {
            if (!checkTuple(input, index, uniqueChars)) return false;
            elements++;
        }
        else if (isalpha(input[index])) {
            char c = input[index];
            uniqueChars.push_back(c);
            index++;
            elements++;
        }
        else if (input[index] == ',') {
            index++;
            while (isspace(input[index])) index++;
        }
        else {
            cerr << "Ошибка: недопустимый символ в кортеже\n";
            return false;
        }
        if (elements > 2) {
            cerr << "Ошибка: кортеж содержит более 2 элементов\n";
            return false;
        }
    }
    return false;
}

void parse(const string& input, vector<string>& output){
    int index = 1;
    while (index < input.size()) {
        if (input[index] == '}') break;
        if (isspace(input[index])) { index++; continue; }

        output.push_back(parseElement(input, index));
    }
}

string parseElement(const string& input, int& index) {
    string element;
    if (input[index] == '{') {
        element += "{";
        index++;
        while (input[index] != '}') {
            if (input[index] == ',') {
                element += ",";
                index++;
            }
            element += parseElement(input, index);
        }
        element += "}";
        index++;
    }
    else if (input[index] == '<') {
        element += "<";
        index++;
        while (input[index] != '>') {
            if (input[index] == ',') {
                element += ",";
                index++;
            }
            element += parseElement(input, index);
        }
        element += ">";
        index++;
    }
    else {
        element += input[index++];
    }
    return element;
}


bool isElementFound(const string& elemA, const vector<string>& B) {
    for (const string& elemB : B) {
        if (elemA == elemB) {
            return true;
        }
    }
    return false;
}

bool isSubset(const vector<string>& A, const vector<string>& B, const string& a, const string& b) {
    for (const string& elemB : B)
    {
        if (a == elemB) {
            return true;
        }
    }
    for (const string& elemA : A) {
        if (!isElementFound(elemA, B)) {
            return false;
        }
    }
    for (const string& elemA : A) {

    }
    return true;
}

bool isElement(const string& A, const string& B) {
    vector<string> elementsB;
    string tempB = B;
    parse(tempB, elementsB);

    for (const string& elemB : elementsB) {
        if (elemB == A) {
            return true;
        }
    }

    if (A.size() >= 3 && A[0] == '{' && A.back() == '}' && A.find(',') == string::npos) {
        string singleElement = A.substr(1, A.size() - 2);
        for (const string& elemB : elementsB) {
            if (elemB == singleElement) {
                return true;
            }
        }
    }
    return false;
}