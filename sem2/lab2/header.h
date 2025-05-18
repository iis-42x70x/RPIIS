#ifndef SET_H
#define SET_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Set {
private:
    class Node {
    public:
        std::string value;
        Node* next;
    };

    Node* head;

public:
    Set();
    ~Set();

    std::string normalize(std::string s);
    bool contains(std::string element);
    void push(std::string str);
    void print();
    Set SymmetricalDifference(std::vector<Set> sets);
    void push_back(std::string str);
};

#endif
