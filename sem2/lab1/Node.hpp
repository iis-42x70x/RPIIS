#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

struct Node {
    std::string data;
    Node* next;
    
    Node(std::string newData) 
    : data(newData), next(nullptr){}
};

#endif