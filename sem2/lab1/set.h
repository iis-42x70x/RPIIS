#ifndef Set_h
#define Set_h

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class Set {
private:
    class Node {
    public:
        std::string value;
        Node* next;
    };
};

std::string normalize(const std::string& s)
bool contains(const std::string& element) 
void push(std::string str)
bool find(const std::string& str) 
void push_back(std::string str)
void del(std::string str) 
void print()
Set Union(Set other) 
Set Intersection(Set other)


#endif
