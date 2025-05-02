#include "Header.hpp"

using namespace std;

bool is_correct(string str) {

	size_t pos = str.find('=');
	string name = str.substr(0, pos);
	bool corname = false;
	for (int i = 0; i < name.size(); i++) {
		int el = name[i];
		if (!isspace(el)) {
			corname = true;
			break;
		}
	}
	if (!corname) return false;

	if (pos != string::npos) {
		str = str.substr(pos + 1);
		str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
	}

	if (str.front() != '{' || str.back() != '}') return false;
	str = str.substr(1, str.size() - 2);

	size_t last_symb = str.find_last_not_of(" \t");
	if (last_symb != string::npos && str[last_symb] == ',') {
		return false;
	}

	stack<char> skobki;
	string current;

	for (int i = 0; i < str.size(); i++) {
		char element = str[i]; 
		
		if(element == '{' || element == '<') {
			skobki.push(element);
			current += element;
		}
		else if (element == '}' || element == '>') {
			if (skobki.empty()) return false;
			char begin = skobki.top();
			if (element == '}' && begin != '{' || element == '>' && begin != '<') return false;
			skobki.pop();
			current += element;
		}

		else if (element == ',') {
			if (current.empty()) return false;
			current.clear();
		}
		else if (!isspace(element)) {
			current += element;
		}
	}

	vector<string> str_parse = parse(str);
	for (auto& elem : str_parse) {
		if (elem.empty() || elem == "," || elem == "{,}" || elem == "<,>") {
			return false;
		}
	}

	string value = str.substr(pos+1);
	value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());

	for (size_t i = 1; i < value.size(); ++i) {
		if ((value[i - 1] == '}' || value[i - 1] == '>') &&
			(value[i] == '{' || value[i] == '<')) {
			return false;
		}
	}

	if (!skobki.empty()) return false;

	return true;
}

vector<string> parse(string str) {
	vector<string> str_elements;
	string current;
	int vlozh = 0;

	size_t pos = str.find('=');
	if (pos != string::npos) {
		str = str.substr(pos+1);

		size_t start = str.find_first_not_of(" \t");
		if (start != string::npos) {
			str = str.substr(start);
		}
	}

	if (str[0] == '{' && str[str.size()-1] == '}') {
		str = str.substr(1, str.size()-2);
	}

	for (int i = 0; i < str.size(); i++) {
		char el = str[i];

		if (el == '{' || el == '<') {
			if (vlozh == 0 && !current.empty()) {
				str_elements.push_back(current);
				current.clear();
			}
			vlozh++;
			current += el;
		}
		else if (el == '}' || el == '>') {
			current += el;
			vlozh--;
			if (vlozh == 0 && !current.empty()) {
				str_elements.push_back(current);
				current.clear();
			}
		}
		else if (el == ',' && vlozh == 0) {
			if (!current.empty()) {
				current.erase(remove_if(current.begin(), current.end(), ::isspace), current.end());
				str_elements.push_back(current);
				current.clear();
			}
		}
		else if (!isspace(el)) {
			current += el;
		}
	}
	if (!current.empty()) {
		str_elements.push_back(current);
	}

	return str_elements;

}

set<set<string>> combinations(vector<string>& elements, int n, int start, vector<string> current) {
	set<set<string>> result;

	if (current.size() == n) {
		result.insert(set<string>(current.begin(), current.end()));
		return result;
	}

	for (int i = start; i < elements.size(); i++) {
		current.push_back(elements[i]);
		set<set<string>> partial = combinations(elements, n, i + 1, current);
		result.insert(partial.begin(), partial.end());
		current.pop_back();
	}

	return result;
}

