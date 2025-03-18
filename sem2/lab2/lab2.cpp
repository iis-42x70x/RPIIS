#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void displaySets(vector<string> sets) {
    for (int i = 0; i <= sets.size(); i++) {
        if (i < sets.size()) {
            cout << "Множество " << i + 1 << " :" << endl;
            cout << "{" << sets[i] << "}" << endl;
        }
        else {
            cout << "Все множества записаны" << endl;
            cout << "----------------------" << endl;
            cout << "Объединить множества - 3" << endl;
        }
    }
}

void readFile(vector<string>& sets, ifstream& inputFile) {
    string line;
    while (!inputFile.eof()) {
        getline(inputFile, line);
        sets.push_back(line);
    }
    inputFile.close();
}

// Собственная функция сортировки пузырьком
void bubbleSort(vector<string>& items) {
    int count = items.size();
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (items[j] > items[j + 1]) {
                string temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}


string sortSubset(const string& subset) {
    if (subset.front() != '{' || subset.back() != '}') {
        return subset;
    }
    string content = subset.substr(1, subset.size() - 2);
    vector<string> elements;
    string currentElement;
    int braceDepth = 0;


    for (char c : content) {
        if (c == '{' && braceDepth == 0) {
            braceDepth++;
            currentElement += c;
        }
        else if (c == '}' && braceDepth > 0) {
            braceDepth--;
            currentElement += c;
            if (braceDepth == 0 && !currentElement.empty()) {
                elements.push_back(sortSubset(currentElement));
                currentElement.clear();
            }
        }
        else if (c == ',' && braceDepth == 0) {
            if (!currentElement.empty()) {
                elements.push_back(sortSubset(currentElement));
                currentElement.clear();
            }
        }
        else {
            currentElement += c;
            if (c == '{') braceDepth++;
            else if (c == '}') braceDepth--;
        }
    }
    if (!currentElement.empty()) {
        elements.push_back(sortSubset(currentElement));
    }


    bubbleSort(elements);


    string sortedSubset = "{";
    for (int i = 0; i < elements.size(); i++) {
        sortedSubset += elements[i];
        if (i < elements.size() - 1) {
            sortedSubset += ",";
        }
    }
    sortedSubset += "}";
    return sortedSubset;
}


vector<string> extractAndSortElements(const string& setString) {
    vector<string> elements;
    string currentElement;
    int braceDepth = 0;

    for (char c : setString) {
        if (c == '{' && braceDepth == 0) {
            braceDepth++;
            currentElement += c;
        }
        else if (c == '}' && braceDepth > 0) {
            braceDepth--;
            currentElement += c;
            if (braceDepth == 0 && !currentElement.empty()) {
                elements.push_back(sortSubset(currentElement));
                currentElement.clear();
            }
        }
        else if (c == ',' && braceDepth == 0) {
            if (!currentElement.empty()) {
                elements.push_back(sortSubset(currentElement));
                currentElement.clear();
            }
        }
        else {
            currentElement += c;
            if (c == '{') braceDepth++;
            else if (c == '}') braceDepth--;
        }
    }
    if (!currentElement.empty()) {
        elements.push_back(sortSubset(currentElement));
    }
    return elements;
}


void unionSets(vector<string>& sets, string& initialResult) {
    if (sets.size() == 0) return;

    vector<string> uniqueElements;


    for (int i = 0; i < sets.size(); i++) {
        vector<string> elements = extractAndSortElements(sets[i]);
        for (const string& element : elements) {
            bool isDuplicate = false;
            for (const string& existingElement : uniqueElements) {
                if (existingElement == element) {
                    isDuplicate = true;
                    break;
                }
            }
            if (!isDuplicate) {
                uniqueElements.push_back(element);
            }
        }
    }


    string finalResult;
    for (int i = 0; i < uniqueElements.size(); i++) {
        finalResult += uniqueElements[i];
        if (i < uniqueElements.size() - 1) {
            finalResult += ",";
        }
    }

    cout << "Результат объединения:" << endl;
    cout << "{" << finalResult << "}" << endl;
    initialResult = "{" + finalResult + "}";
}

