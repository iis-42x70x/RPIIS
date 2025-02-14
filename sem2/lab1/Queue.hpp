#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Node.hpp"

class Queue{
    private:
        Node* head;
        Node* lastNode;
    public:
        Queue();
        void addNode(std::string newData);
        std::string takeNode();
        void displayData();
};

#endif
