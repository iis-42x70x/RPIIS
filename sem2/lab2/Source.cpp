#include "Source.hpp"

bool checkBrackets(const string& input) {
    int open = 0, close = 0;
    for (char c : input) {
        if (c == '{' || c == '<') open++;
        if (c == '}' || c == '>') close++;
    }
    return open == close;
}

vector<string> parseSet(const string& input) {
    vector<string> elements;
    size_t pos = 1; 
    string buffer;
    int openBraces = 1;
    bool inTuple = false;

    for (; pos < input.length(); pos++) {
        char c = input[pos];

        if (c == '<') {
            inTuple = true;
            buffer += c;
        }
        else if (c == '>') {
            inTuple = false;
            buffer += c;
            elements.push_back(buffer);
            buffer.clear();
        }
        else if (c == '{' && !inTuple) {
            openBraces++;
            buffer += c;
        }
        else if (c == '}' && !inTuple) {
            openBraces--;
            buffer += c;
            if (openBraces == 1) {
                elements.push_back(buffer);
                buffer.clear();
            }
        }
        else if (c == ',' && openBraces == 1 && !inTuple) {
            if (!buffer.empty()) {
                elements.push_back(buffer);
            }
            buffer.clear();
        }
        else {
            buffer += c;
        }
    }

    if (!buffer.empty()) {
        elements.push_back(buffer);
    }

    for (auto& element : elements) {
        if (element.front() != '<' && element.front() != '{') {
            element.erase(remove_if(element.begin(), element.end(), ::isspace), element.end());
        }
    }

    vector<string> simpleElements;
    vector<string> complexElements;

    for (const auto& element : elements) {
        if (element.front() == '<' || element.front() == '{') {
            complexElements.push_back(element);
        }
        else {
            simpleElements.push_back(element);
        }
    }

    sort(simpleElements.begin(), simpleElements.end());

    elements.clear();
    elements.insert(elements.end(), simpleElements.begin(), simpleElements.end());
    elements.insert(elements.end(), complexElements.begin(), complexElements.end());

    return elements;
}

string unionSets(vector<string>& set1, vector<string>& set2) {
    unordered_set<string> unionSet;

    for (const auto& element : set1) {
        if (!element.empty()) {
            unionSet.insert(element);
        }
    }
    for (const auto& element : set2) {
        if (!element.empty()) {
            unionSet.insert(element);
        }
    }

    string result = "{";
    bool isFirstElement = true;
    for (const auto& element : unionSet) {
        if (!isFirstElement) {
            result += ",";
        }
        result += element;
        isFirstElement = false;
    }
    result += "}";
    return result;
}

vector<string> readSets(const string& path) {
    ifstream f(path);
    if (!f.is_open()) {
        cout << "Error while opening file!" << endl;
        return {};
    }

    vector<string> sets;
    string buff;
    while (getline(f, buff)) {
        size_t found = buff.find('=');
        if (found != string::npos) {
            string dataAfterEqualSign = buff.substr(found + 1);
            if (!checkBrackets(dataAfterEqualSign)) {
                cout << "Error: unbalanced brackets in the set: " << dataAfterEqualSign << endl;
                continue;
            }
            sets.push_back(dataAfterEqualSign);
        }
    }
    f.close();
    return sets;
}

void openFile(string& path) {
    cout << "Enter the name of the file (e.g., input.txt): ";
    cin >> path;

    ifstream checkFile(path);
    if (checkFile.good()) {
        cout << "File " << path << " is opened." << endl;
        checkFile.close();
        return;
    }
    cout << "File not found!" << endl;
    checkFile.close();
}

void unionAllSets(const string& inputPath, const string& outputPath) {
    vector<string> sets = readSets(inputPath);
    if (sets.size() < 2) {
        cout << "Not enough sets for union (need at least 2)." << endl;
        return;
    }

    vector<vector<string>> subsetsList;
    for (const auto& set : sets) {
        subsetsList.push_back(parseSet(set));
    }

    string result = unionSets(subsetsList[0], subsetsList[1]);
    for (size_t i = 2; i < subsetsList.size(); i++) {
        auto help_union = parseSet(result);
        result = unionSets(help_union, subsetsList[i]);
    }

    cout << "Union result: " << result << endl;

    ofstream f(outputPath);
    if (!f.is_open()) {
        cout << "Error while opening file for writing union result!" << endl;
        return;
    }
    f << "union_result=" << result << endl;
    f.close();
    cout << "Union result has been written to the file: " << outputPath << endl;
}
