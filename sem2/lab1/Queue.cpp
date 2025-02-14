#include "Queue.hpp"
#include <iostream>

Queue::Queue() : head(nullptr), lastNode(nullptr){
    std::cout << "Queue was created" << std::endl;
}

void Queue::addNode(std::string newData){
    Node* newNode = new Node(newData);
    if(head == nullptr){
        head = newNode;
        lastNode = newNode;
    }
    else {
        lastNode->next = newNode;
        lastNode = newNode;
    }
    std::cout << "New data was successfully added!" << std::endl;
}

std::string Queue::takeNode(){
    if(head == nullptr){
        std::cout << "Impossible to take node. The queue is empty!" << std::endl;
        return "";
    }

    Node* nextNode = head->next;
    std::string lastNodeData = head->data; 

    delete head;
    head = nextNode;

    std::cout << "Node was successfully taken!" << std::endl;
    return lastNodeData;
}

void Queue::displayData(){
    if(head == nullptr){
        std::cout << "Queue is empty!" << std::endl;
        return ;
    }

    Node* currentNode = head;
    std::cout << "Queue data: ";
    while(currentNode != nullptr){
        std::cout << currentNode->data << " ";
        currentNode = currentNode->next;
    }
    std::cout << std::endl;
}


