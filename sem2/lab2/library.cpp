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
	int tupeCount = 0;

	for(char c: str){
		if(c=='{'){
			setCount++;
			temp+=c;
		} else if (c=='}'){
			setCount--;
			temp+=c;
			if(setCount ==0){
				set.push_back(temp);
				temp.clear();
			}
		} 

		if(c=='<'){
			tupeCount++;
			temp+=c;
		} else if (c=='>'){
			tupeCount--;
			temp+=c;
			if(setCount == 0){
				set.push_back(temp);
				temp.clear();
			}
		} else if(c==',' && setCount == 0 && tupeCount == 0){
			if(!temp.empty()){
				set.push_back(temp);
				temp.clear();
			}
		} else {
			temp+=c;
		}
	}
	if(!temp.empty()){
		set.push_back(temp);
	}
	return set;
}

string normalize(string& elem) { 
    if (elem.empty()) return "";

    if (elem.front() == '<' && elem.back() == '>') {
        vector<string> inner = addSets(elem);
        for (auto& it : inner) {
            it = normalize(it);
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
        vector<string> inner = addSets(elem);
        vector<string> normalized; 

        for (auto& it : inner)
            normalized.push_back(normalize(it));

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
	    cout << normalized[0] << endl;
            return normalized[0];
        }

        string result = "{";
        for (int i = 0; i < normalized.size(); i++) {
            if (i > 0) result += ",";
            result += normalized[i];
        }
        result += "}";
	cout << result << endl;
        return result;
    }
    else {
        string simple = elem;
        simple.erase(remove_if(simple.begin(), simple.end(), ::isspace), simple.end());
	cout << simple << endl;
        return simple;
    }
}

string sortSet(string& input) {
    vector<std::string> elements;
    string temp;
    int bracketCount = 0;  
    int parenthesisCount = 0;  

    for (char c : input) {
        if (c == '{') {
            bracketCount++;
            if (bracketCount == 1 && !temp.empty()) {
                elements.push_back(temp);
                temp.clear();
            }
        } 
        
        temp += c;
        
        if (c == '}') {
            bracketCount--;
            if (bracketCount == 0) {
                elements.push_back(temp);
                temp.clear();
            }
        } else if (c == '(') {
            parenthesisCount++;
        } else if (c == ')') {
            parenthesisCount--;
        } else if (c == ',' && bracketCount == 0 && parenthesisCount == 0) {
            elements.push_back(temp);
            temp.clear();
        }
    }

    if (!temp.empty()) {
        elements.push_back(temp);
    }

    sort(elements.begin(), elements.end(), [](const std::string& a, const std::string& b) {
        bool isSetA = a.front() == '{' && a.back() == '}';
        bool isSetB = b.front() == '{' && b.back() == '}';
        if (isSetA != isSetB) return isSetB;
        return a < b; 
    });

    std::string result;
    for (const auto& elem : elements) {
        if (!result.empty()) result += ",";
        result += elem;
    }

    return result;
}

vector<string> cross(vector<string> set1, vector<string> set2){
	vector<string> cross;
	int num1 = set1.size();
	int num2 = set2.size();

	for(int i = 0; i<num1; i++){
		for(int j =  0; j<num2; j++){
			if(set1[i].front() == '{' || set1[i].front()=='<'){
				sortSet(set1[i]);
			}

			if(set2[j].front() == '{' || set2[j].front()=='<'){
				sortSet(set1[i]);
			}

			if(!strcmp(set1[i].data(), set2[j].data()))
				cross.push_back(set1[i]);
		}
	}
	return cross;
}
