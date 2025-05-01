#include "Header.h"
#include <algorithm>

using namespace std; 

SinglyLinkedList::SinglyLinkedList() : head(nullptr) {}

SinglyLinkedList::~SinglyLinkedList() { //освобождение памяти
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void SinglyLinkedList::insert(int value) { //вставка
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void SinglyLinkedList::remove(int value) { //удаление
    if (!head) return;

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    while (current->next && current->next->data != value) {
        current = current->next;
    }

    if (current->next) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

void SinglyLinkedList::sort() { //сортировка 
    if (!head || !head->next) return;

    vector<int> values;
    Node* current = head;
    while (current) {
        values.push_back(current->data);
        current = current->next;
    }

    std::sort(values.begin(), values.end());

    current = head;
    for (int val : values) {
        current->data = val;
        current = current->next;
    }
}

Node* SinglyLinkedList::search(int value) { //поиск
    Node* current = head;
    while (current) {
        if (current->data == value) return current;
        current = current->next;
    }
    return nullptr;
}

void SinglyLinkedList::merge(SinglyLinkedList& other) { // объединение
    if (!other.head) return;

    Node* current = other.head;
    while (current) {
        insert(current->data);
        current = current->next;
    }
}

SinglyLinkedList SinglyLinkedList::intersect(SinglyLinkedList& other) { //пересечение
    SinglyLinkedList result; 
    Node* current = head; 
    while (current) {
        if (other.search(current->data)) {
            result.insert(current->data);
        }
        current = current->next;
    }
    return result;
}

void SinglyLinkedList::display() const { //вывод
    Node* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}
