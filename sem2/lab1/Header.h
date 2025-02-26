#pragma once
struct Node {
    int data;
    Node* next;
    Node* prev;
};

void printList(Node* head);
void insert(Node** head, int data);
void insert_mesto(Node** head, int data, int position);
void generateRandomList(Node** head);
void deleting(Node** head, int value);
void swap(Node* a, Node* b);
void Sort(Node* head);
bool search(Node* head, int key);
Node* merge(Node** first, Node* second);
Node* per(Node** first, Node* second);
void menu();
void vybor(int k, Node** head1, Node** head2);


