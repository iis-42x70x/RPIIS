#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head; 

public:
    SinglyLinkedList(); // Конструктор
    ~SinglyLinkedList(); // освоб пам

    void insert(int value); // Вставка 
    void remove(int value); // Удаление 
    void sort(); // Сортировка
    Node* search(int value); // Поиск 
    void merge(SinglyLinkedList& other); // Объединение 
    SinglyLinkedList intersect(SinglyLinkedList& other); // Пересечение 

    void display() const; // Вывод 
};

#endif
