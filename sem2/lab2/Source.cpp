#include "Header.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>

bool check(string input) {
	if (input[0] != '{' || input[input.size() - 1] != '}') { return false; }
	int index = 0;
	return checkSet(input, index);
}

bool checkSet(string input, int& index) {
	index++;
	/*int tempindex = index;
	while (input[tempindex] == ' ') { tempindex++; }
	if (input[tempindex] == '}') { return false; }*/
	for (index; input[index] != '}'; index++) {

		if ((input[index] < 'A' || input[index]>'Z')
			&& input[index] != '{'
			&& input[index] != '}'
			&& input[index] != '<'
			&& input[index] != '>'
			&& input[index] != ','
			&& input[index] != ' ')
		{
			return false;
		}
		if (input[index] >= 'A' && input[index] <= 'Z') {
			int flag = 0;
			for (char i : input) {
				if (i == input[index]) { flag++; }
			}
			if (flag > 1) {
				return false;
			}

			for (int prev = index - 1; ; prev--) {
				if (input[prev] == '}' || input[prev] == '>' || (input[prev] >= 'A' && input[prev] <= 'Z')) { return false; }
				else if (input[prev] != ' ') { break; }
			}
			for (int next = index + 1; ; next++) {
				if (input[next] == '{' || input[next] == '<' || (input[next] >= 'A' && input[next] <= 'Z')) { return false; }
				else if (input[next] != ' ') { break; }
			}

		}
		if (input[index] == ',') {
			for (int prev = index - 1; ; prev--) {
				if (input[prev] == '{' || input[prev] == '<' || input[prev] == ',') { return false; }
				else if (input[prev] != ' ') { break; }
			}
			for (int next = index + 1; ; next++) {
				if (input[next] == '}' || input[next] == ',' || input[next] == '>') { return false; }
				else if (input[next] != ' ') { break; }
			}
		}
		if (input[index] == '{') {
			for (int prev = index - 1; ; prev--) {
				if (input[prev] == '}' || input[prev] == '>' || (input[prev] >= 'A' && input[prev] <= 'Z')) { return false; }
				else if (prev != ' ') { break; }
			}
			if (!checkSet(input, index)) { return false; }
		}
		if (input[index] == '<') {
			for (int prev = index - 1; ; prev--) {
				if (input[prev] == '}' || input[prev] == '>' || (input[prev] >= 'A' && input[prev] <= 'Z')) { return false; }
				else if (input[prev] != ' ') { break; }
			}
			if (!checkTuple(input, index)) { return false; }
		}
	}

	return true;
}

bool checkTuple(string input, int& index) {
	index++;

	while (input[index] == ' ') { index++; }

	if (input[index] == '{') {
		if (!checkSet(input, index)) { return false; }
		index++;
	}
	else if (input[index] == '<') {
		if (!checkTuple(input, index)) { return false; }
		index++;
	}
	else if (input[index] >= 'A' && input[index] <= 'Z') {
		int flag = 0;
		for (char i : input) {
			if (i == input[index]) { flag++; }
		}
		if (flag > 1) {
			return false;
		}
		index++;
	}

	while (input[index] == ' ') { index++; }

	if (input[index] != ',') { return false; }
	index++;

	while (input[index] == ' ') { index++; }

	if (input[index] == '{') {
		if (!checkSet(input, index)) { return false; }
		index++;
	}
	else if (input[index] == '<') {
		if (!checkTuple(input, index)) { return false; }
		index++;
	}
	else if (input[index] >= 'A' && input[index] <= 'Z') {
		int flag = 0;
		for (char i : input) {
			if (i == input[index]) { flag++; }
		}
		if (flag > 1) {
			return false;
		}
		index++;
	}

	while (input[index] == ' ') { index++; }

	if (input[index] != '>') { return false; }

	return true;
}

void createFile(string filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		ofstream file(filename);
		if (file.is_open()) {
			file.close();
		}
		else {
			cout << "Error file creating.\n";
		}
	}
	else {
		file.close();
	}
}

bool iselement() {
	string filename = "1.txt", strExpElement, strExpSet;
	createFile(filename);
	ifstream file(filename);
	getline(file, strExpElement);
	getline(file, strExpSet);
	if (!check(strExpElement) || !check(strExpSet)) {
		cout << "wrong set\n";
		return false;
	}

	vector<string> ExpSet;
	string ExpElement;
	int pointer = 0;
	ExpElement=returnset(strExpElement, pointer);
	parse(strExpSet, ExpSet);
	for (string element : ExpSet) {
		if (element == ExpElement) { return true; }
	}
	return false;
}

bool isunderset() {
	string filename = "1.txt", expUnderSet, expUpSet;
	createFile(filename);
	ifstream file(filename);
	getline(file, expUnderSet);
	getline(file, expUpSet);
	if (!check(expUnderSet) || !check(expUpSet)) {
		cout << "wrong set\n";
		return false;
	}

	vector<string> underset, upset;
	parse(expUnderSet, underset);
	parse(expUpSet, upset);
	
	for (string untemp : underset) {
		int flag = 0;
		for (string uptemp : upset) {
			if (uptemp == untemp) { flag++; }
		}
		if (flag == 0) { return false; }
	}
	return true;
}

void parse(string input, vector<string>& output) {
	int pointer = 1;
	for (pointer; input[pointer] != '}'; pointer++) {
		if (input[pointer] == '{') { output.push_back(returnset(input, pointer)); }
		if (input[pointer] == '<') { output.push_back(returntuple(input, pointer)); }
		if (input[pointer] >= 'A' && input[pointer] <= 'Z') { 
			string t; 
			t += input[pointer]; 
			output.push_back(t); 
		}
	}
}

string returnset(string input, int& pointer) {
	string output;
	output += input[pointer];
	pointer++;
	set<char> tempchar;
	set<string> tempstring;
	for (pointer; input[pointer] != '}'; pointer++) {
		if (input[pointer] == '{') { tempstring.insert(returnset(input, pointer)); }
		if (input[pointer] == '<') { tempstring.insert(returntuple(input, pointer)); }
		if (input[pointer] >= 'A' && input[pointer] <= 'Z') { tempchar.insert(input[pointer]); }
	}
	for (string i : tempstring) {
		output += i;
	}
	for (char i : tempchar) {
		output += i;
	}
	output += '}';
	return output;
}

string returntuple(string input, int& pointer) {
	string output;
	output += input[pointer];
	pointer++;
	set<char> tempchar;
	set<string> tempstring;
	for (pointer; input[pointer] != '>'; pointer++) {
		if (input[pointer] == '{') { tempstring.insert(returnset(input, pointer)); }
		if (input[pointer] == '<') { tempstring.insert(returntuple(input, pointer)); }
		if (input[pointer] >= 'A' && input[pointer] <= 'Z') { tempchar.insert(input[pointer]); }
	}
	for (string i : tempstring) {
		output += i;
	}
	for (char i : tempchar) {
		output += i;
	}
	output += '>';
	return output;
}