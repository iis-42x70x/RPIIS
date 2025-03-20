#pragma once

struct Node {

	int info;
	Node* next;
	Node* prev;

	Node(int value) {
		info = value;
		next = nullptr;
		prev = nullptr;
	}
};

void push_head(Node*& head, Node*& tail, int value);
void push_tail(Node*& head, Node*& tail, int value);
void push(Node*& head, Node*& tail, int value, int element);
void push_element(Node*& head, Node*& tail, int value);
void deleteNode(Node*& head, Node*& tail, Node* node);
Node* Find(Node*& head, Node*& tail, int value);
int Find_num(Node*& head, Node*& tail, int value);
bool exist_in(Node* head, int value);
void unification(Node*& unihead, Node*& unitail, Node*& head1, Node*& tail1, Node*& head2, Node*& tail2);
void intersection(Node*& interhead, Node*& intertail, Node*& head1, Node*& tail1, Node*& head2, Node*& tail2);
void clear(Node*& head, Node*& tail);
void create(Node*& head, Node*& tail);
void View(Node*& head, Node*& tail);
void Sort(Node*& head, Node*& tail);
void operations_with_two_lists(Node*& head1, Node*& tail1, Node*& head2, Node*& tail2, Node*& unihead, Node*& unitail, Node*& interhead, Node*& intertail);
void add(Node*& head, Node*& tail);