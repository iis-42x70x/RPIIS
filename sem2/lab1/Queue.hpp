#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>

class Queue{
    private:
        struct Node {
            std::string data;
            Node* next;
            
            Node(std::string newData) 
            : data(newData), next(nullptr){}
        };
        Node* head;
        Node* lastNode;
    public:
        Queue();
        void addNode(std::string newData);
        std::string takeNode();
        void displayData();
};

#endif
