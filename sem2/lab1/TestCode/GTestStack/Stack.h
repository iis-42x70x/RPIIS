#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

bool isEmpty(Node* top) {
    return top == NULL;
}

void push(Node*& top, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = top;
    top = newNode;
}
void pop(Node*& top) {
    if (isEmpty(top)) {
        cout << "Stack underflow! Cannot pop from an empty stack." << endl;
        return;
    }
    Node* temp = top;
    top = top->next;
    delete temp;
}

int peek(Node* top) {
    if (isEmpty(top)) {
        cout << "Stack is empty!" << endl;
        return -1;
    }
    return top->data;
}

void display(Node* top) {
    if (isEmpty(top)) {
        cout << "Stack is empty!" << endl;
        return;
    }
    Node* temp = top;
    while (temp != NULL) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}
void printStack(Node*& top) {
    int size;
    int value;
    cout << "Enter stack size:";
    cin >> size;

    for (int i = 0; i < size; i++) {
        cout << "Enter element: ";
        cin >> value;
        push(top, value);
    }
}
#endif

