
#ifndef PIOVIS_LABA2
#define PIOVIS_LABA2

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <stack>

const char bracket1 = '{';
const char bracket2 = '}';
const char bracket3 = '<';
const char bracket4 = '>';
using namespace std;
class Set {
private:
    vector<string> test;

public:

    void reading();
    void set_of_vector(vector <string> tests);
    void print();
    vector<string>& get_vector();
    string first_str_in_vector();
    vector <string>& set_vector(vector<string> tests);

};



bool is_set(const string& str);

bool is_tupple(const string& str);

bool compare_strings(const string& a, const string& b);


void bubble_sort(vector<string>& elements);

void remove_duplicates(vector<string>& elements);

vector<string> get_elements(string& set);

string sort_set(string& str);
void peresechenie(vector <string> res, vector<string>& result);
void main_intersection(vector <Set>& tests, vector<string>& result);
void checking_symbol(string& str);

bool checking_correct_str(string str);

bool checking_next(string str);

void reading_file(vector <Set>& intersection);

#endif
