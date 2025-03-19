#include <iostream>
#include "bid_list.hpp"
using namespace std;

void push_head(Node*& head, Node*& tail, int value) {
	Node* newnode = new Node(value);
	if (!head) {
		head = tail = newnode;
	}
	else {
		newnode->next = head;
		head->prev = newnode;
		head = newnode;
	}
}

void push_tail(Node*& head, Node*& tail, int value) {
	Node* newnode = new Node(value);
	if (!tail) {
		head = tail = newnode;
	}
	else {
		newnode->prev = tail;
		tail->next = newnode;
		tail = newnode;
	}
}

void push(Node*& head, Node*& tail, int value, int element) {
	Node* newnode = new Node(value);
	Node* temp = head;
	int num = 0;
	if (element == 1) {
		push_head(head, tail, value);
		return;
	}
	while (temp) {
		++num;
		if (num == element) {
			newnode->prev = temp->prev;
			temp->prev->next = newnode;
			temp->prev = newnode;
			newnode->next = temp;
			return;
		}
		temp = temp->next;
	}
}

void push_element(Node*& head, Node*& tail, int value) {
	int n = 0;
	cout << "¬ведите номер элемент на место которого вы желаете вставить элемент " << value <<": ";
	cin >> n;
	if(!exist_in(head,n)){
		cout << "ƒанного элемента не существует в списке." << endl;
		return;
	}
	push(head, tail, value, n);
}

void deleteNode(Node*& head, Node*& tail, Node* node) {
	if (!node) {
		cout << "Ёлемента с данным номером не существует в списке." << endl;
		return;
	}
	if (head == tail) {
		head = tail = nullptr;
	}
	else if (node == head) {
		head = head->next;
		head->prev = nullptr;
	}
	else if (node == tail) {
		tail = tail->prev;
		tail->next = nullptr;
	}
	else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	delete node;
}

Node* Find(Node*& head, Node*& tail, int element) {
	Node* temp = head;
	int num = 0;
	while (temp) {
		++num;
		if (num == element) {
			return temp;
		}
		temp = temp->next;
	}
	return nullptr;
}

int Find_num(Node*& head, Node*& tail, int value) {
	Node* temp = head;
	int num = 0;
	while (temp) {
		++num;
		if (temp->info == value) {
			return num;
		}
		temp = temp->next;
	}
	return 0;
}

bool exist_in(Node* head, int value) {
	Node* temp = head;
	while (temp) {
		if (temp->info == value) {
			return true;
		}
		temp = temp->next;
	}
	return false;
}

void View(Node*& head, Node*& tail) {
	Node* temp = head;
	while (temp) {
		cout << temp->info << endl;
		temp = temp->next;
	}
	cout << endl;
}


void unification(Node*& unihead, Node*& unitail, Node*& head1, Node*& tail1, Node*& head2, Node*& tail2) {
	if (!head1 && !head2) {
		unihead = unitail = nullptr;
		return;
	}
	if (!head1) {
		unihead = head2;
		unitail = tail2;
		return;
	}
	if (!head2) {
		unihead = head1;
		unitail = tail1;
		return;
	}
	Node* temp1 = head1;
	unihead = new Node(temp1->info);
	unitail = unihead;
	temp1 = temp1->next;
	while (temp1) {
		push_tail(unihead, unitail, temp1->info);
		temp1 = temp1->next;
	}

	Node* temp2 = head2;
	while (temp2) {
		//if (!exist_in(head1, temp2->info)) {
			push_tail(unihead, unitail, temp2->info);
		//}
		temp2 = temp2->next;
	}
}

void intersection(Node*& interhead, Node*& intertail, Node*& head1, Node*& tail1, Node*& head2, Node*& tail2) {
	Node* temp = head2;
	while (temp) {
		if (exist_in(head1, temp->info)) {
			push_tail(interhead, intertail, temp->info);
		}
		temp = temp->next;
	}
}

void clear(Node*& head, Node*& tail) {
	while (head) {
		deleteNode(head, tail, head);
	}
}

void create(Node*& head, Node*& tail) {
	clear(head, tail);
	int size;
	cout << "¬ведите количество элементов списка: ";
	cin >> size;
	for (int i = 0; i < size; i++) {
		int n = 0;
		cout << "¬ведите " << i + 1 << " элемент списка: ";
		cin >> n;
		push_tail(head, tail, n);
	}
}

void Sort(Node*& head, Node*& tail) {
	if (!head || !head->next) {
		return;
	}
	bool swap = true;
	while (swap) {
		Node* temp = head;
		swap = false;
		while (temp && temp->next) {
			if (temp->info > temp->next->info) {
				int t = temp->info;
				temp->info = temp->next->info;
				temp->next->info = t;
				swap = true;
			}
			temp = temp->next;
		}
	}
}
