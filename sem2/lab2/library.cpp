#define _CRT_SECURE_NO_WARNINGS
#include "library.h"         

string readSets(const char* filename) { 
    FILE* file = fopen(filename, "r"); 
    
    if (!file) {
        cout << "Ошибка открытия файла!\n";
        return NULL;
    }

    string content;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file)) {
        content += buffer;
    }

    fclose(file);
    return content;

}

int checkString(string sets){
    int size = sets.length();
    int openF=0;
    int closeF=0;
    int openS=0;
    int closeS=0;
    int numSets=0;
    stack<char> skob;

    for(int i = 0; i<size; i++){
        if(sets[i] == '{')      openF++;
        if(sets[i] == '}')      closeF++;
        if(sets[i] == '<')      openS++;
        if(sets[i] == '>')      closeS++;
	if(sets[i] == '\n') 	numSets++;

        if(sets[i]==' ')        return -1;
    }

    if(openF!=closeF || openS!=closeS)  return -1;

    for(int i = 0; i<size; i++){
	    if(sets[i]=='{' || sets[i]=='<'){
		    skob.push(sets[i]);
	    } else if(sets[i]=='}' || sets[i]=='>'){
		    if(skob.empty()) return -1;
		    char top = skob.top();
		    if((sets[i]=='}' && top!='{') || (sets[i]=='>' && sets[i]=='<')) return -1;
		    skob.pop();
	    } else if(sets[i]==','){
		    if(i==0 || i==sets.length()-1 || sets[i-1]==','|| sets[i+1]==','){
			    return -1;
		    }
	    }
    }

    return numSets;
}

vector<string> parseString(int num, string str){
	vector<string> sets;
	
	str.erase(0, 1);
	for(int i = 0; str[i]!='\0'; i++){
		if(str[i+1]=='\n' || str[i-1]=='\n')
			str.erase(i, 1);
	}


	char* temp = strtok(str.data(), "\n");
	while(temp){
		sets.push_back(temp);
		temp=strtok(NULL, "\n");
	}

	return sets;
}

vector<string> addSets(string str){
    vector<string> set;
    string temp;
    int setCount = 0;
    int tupleCount = 0;

    for(char c : str){
        if(c == '{') {
            setCount++;
        } else if (c == '}') {
            setCount--;
        } else if(c == '<') {
            tupleCount++;
        } else if (c == '>') {
            tupleCount--;
        }

        if (c == ',' && setCount == 0 && tupleCount == 0) {
            // Разделяем элемент только если запятая ВНЕ множества/кортежа
            if (!temp.empty()) {
                set.push_back(temp);
                temp.clear();
            }
        } else {
            temp += c;
        }
    }

    if (!temp.empty()) {
        set.push_back(temp);
    }
    
    return set;
}


vector<string> parseElements(const string& element) {
    vector<string> elements;
    if (element.empty() || element.size() < 2) return elements;

    int depth = 0, start = 1;

    for (int i = 1; i < element.size() - 1; i++) {
        char c = element[i];
        if (c == '{' || c == '<') depth++;
        else if (c == '}' || c == '>') depth--;

        if (depth == 0 && c == ',') {
            string elem = element.substr(start, i - start);
            elem.erase(0, elem.find_first_not_of(" \t"));
            elem.erase(elem.find_last_not_of(" \t") + 1);
            if (!elem.empty())
                elements.push_back(elem);
            start = i + 1;
        }
    }

    string lastElem = element.substr(start, element.size() - 1 - start);
    lastElem.erase(0, lastElem.find_first_not_of(" \t"));
    lastElem.erase(lastElem.find_last_not_of(" \t") + 1);
    if (!lastElem.empty())
        elements.push_back(lastElem);

    return elements;
}

string normalizeElement(const string& elem) {       // приводит строку в приличный вид
    if (elem.empty()) return "";

    if (elem.front() == '<' && elem.back() == '>') {
        vector<string> inner = parseElements(elem);
        for (auto& it : inner) {
            it = normalizeElement(it);
        }

        string res = "<";
        for (int i = 0; i < inner.size(); ++i) {
            if (i > 0) res += ",";
            res += inner[i];
        }
        res += ">";
        return res;
    }
    else if (elem.front() == '{' && elem.back() == '}') {
        vector<string> inner = parseElements(elem);
        vector<string> normalized;

        for (auto& it : inner)
            normalized.push_back(normalizeElement(it));

        sort(normalized.begin(), normalized.end(), [](const string& a, const string& b) {
            char first_a = a.front();
            char first_b = b.front();

            if (first_a == first_b) return a < b;
            if (first_a == '{') return false;
            if (first_b == '{') return true;
            if (first_a == '<') return false;
            if (first_b == '<') return true;
            return a < b;
        });

        if (normalized.size() == 1) {
            return normalized[0];
        }

        string result = "{";
        for (int i = 0; i < normalized.size(); i++) {
            if (i > 0) result += ",";
            result += normalized[i];
        }
        result += "}";
        return result;
    }
    else {
        string simple = elem;
        simple.erase(remove_if(simple.begin(), simple.end(), ::isspace), simple.end());
        return simple;
    }
}




vector<string> cross(vector<string> set1, vector<string> set2){
	vector<string> cross;
	int num1 = set1.size();
	int num2 = set2.size();

	for(int i = 0; i<num1; i++){
		for(int j =  0; j<num2; j++){
			if(set1[i].front() == '{' || set1[i].front()=='<'){
				set1[i] = normalizeElement(set1[i]);
			}

			if(set2[j].front() == '{' || set2[j].front()=='<'){
				set2[j] = normalizeElement(set2[j]);
			}

			if(!strcmp(set1[i].data(), set2[j].data()))
				cross.push_back(set1[i]);
		}
	}
	return cross;
}
