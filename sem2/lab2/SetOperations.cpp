#include "SetOperations.h"

void displaySets(vector<string> sets) {
    if (sets.empty()) {
        cout << "Нет загруженных множеств" << endl;
        return;
    }
    
    for (size_t i = 0; i < sets.size(); i++) {
        cout << "Множество " << i + 1 << " :" << endl;
        cout << "{" << sets[i] << "}" << endl;
    }
    cout << "Всего множеств: " << sets.size() << endl;
    cout << "----------------------" << endl;
}

void readFile(vector<string>& sets, ifstream& inputFile) {
    if (!inputFile.is_open()) {
        return;
    }
    
    string line;
    while (getline(inputFile, line)) {
        if (!line.empty()) {
            sets.push_back(line);
        }
    }
    inputFile.close();
}

vector<string> extractElements(const string& setString) {
    vector<string> elements;
    string currentElement;
    int braceDepth = 0;
    int angleDepth = 0; 

    for (char c : setString) {
        if (c == '{' || c == '<') {
            if (c == '{') braceDepth++;
            if (c == '<') angleDepth++;
            currentElement += c;
        }
        else if (c == '}' || c == '>') {
            if (c == '}') braceDepth--;
            if (c == '>') angleDepth--;
            currentElement += c;
            if (braceDepth < 0 || angleDepth < 0) {
                cerr << "Ошибка: неверная вложенность скобок" << endl;
                return elements;
            }
        }
        else if (c == ' ' && braceDepth == 0 && angleDepth == 0) {
            if (!currentElement.empty()) {
                elements.push_back(currentElement);
                currentElement.clear();
            }
        }
        else {
            currentElement += c;
        }
    }
    if (!currentElement.empty()) {
        elements.push_back(currentElement);
    }
    return elements;
}

void unionSets(vector<string>& sets, string& initialResult) {
    if (sets.empty()) {
        cout << "Нет множеств для объединения" << endl;
        initialResult = "{}";
        return;
    }

    map<string, int> elementMultiplicity;

    for (const string& set : sets) {
        vector<string> elements = extractElements(set);
        map<string, int> currentSetMultiplicity;
        for (const string& element : elements) {
            currentSetMultiplicity[element]++;
        }
        
        for (const auto& pair : currentSetMultiplicity) {
            if (elementMultiplicity[pair.first] < pair.second) {
                elementMultiplicity[pair.first] = pair.second;
            }
        }
    }

    string finalResult;
    bool firstElement = true;
    
    for (const auto& pair : elementMultiplicity) {
        string element = pair.first;
        int count = pair.second;
        
        for (int i = 0; i < count; i++) {
            if (!firstElement) {
                finalResult += " ";
            }
            finalResult += element;
            firstElement = false;
        }
    }

    cout << "Результат объединения (" << sets.size() << " множеств):" << endl;
    cout << "{" << finalResult << "}" << endl;
    initialResult = "{" + finalResult + "}";
}
