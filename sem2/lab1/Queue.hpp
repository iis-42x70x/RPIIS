#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <gtest/gtest.h>
using namespace std;

class Node {
public:
    string data;
    Node* next;
    Node(string s) : data(s), next(nullptr) {}
};

class Solution {
public:
    Solution() : head(nullptr) {}

    void Take(int n) {
        Node* temp = head;
        if (n <= 0) {
            cout << "Error\n";
            return;
        }
        int counter = 1;
        while (temp) {
            if (counter == n) {
                cout << temp->data << '\n';
                return;
            }
            else {
                counter++;
                temp = temp->next;
            }
        }
        cout << "Error\n";
    }

    void setQueue(string s) {
        Node* newnode = new Node(s);
        if (!head) {
            head = newnode;
        }
        else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newnode;
        }
    }

private:
    Node* head;
};
