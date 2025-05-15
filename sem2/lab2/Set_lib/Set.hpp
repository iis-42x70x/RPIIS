#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Element {
    string value; //значение элемента
    int count; //счётчик значений элементов в множестве
};

class Set {
public:
    Set() = default; // конструктор без параметров
    Set(const vector<Element> &elements); // конструктор с параметрами

    const vector<Element>& get_elements() const;
    Set difference(const Set& other) const;

    static bool read_input(const string &filename, string &line1, string &line2);
    static bool process_set_line(const string &line, string &name, vector<Element> &set);
    static void output_results(const Set &set1, const Set &set2, const Set &result,
                               const string &name1, const string &name2, const string &result_name);
    vector<Element> elements;
    bool is_correct_char(char c);
    bool is_correct_name(const string &s);
    bool parse_element(const string &input, size_t &pos, string &element);
    bool find_element(vector<Element> &elements, const string &value, size_t &index);
    bool parse_set(const string &input, size_t &pos, vector<Element> &elements);
    void print_set(const vector<Element> &elements, const string &name);
    static string normalize_set_string(const string& set_str);
};
#endif

