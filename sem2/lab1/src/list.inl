#ifndef LIST_INL
#define LIST_INL

#include "list.h"


template<typename T>
List<T>::List(){ 
	size = 0;
	head = NULL;
}

template<typename T>
List<T>::List(const List<T> &other) : size{other.size}, head{NULL} {
	if (other.head != NULL) {
		head = new Node(other.head->data);
		Node *current_other = other.head->next;
		Node *current_this = head;

		while (current_other != NULL) {
			current_this->next = new Node(current_other->data);
			current_this = current_this->next;
			current_other = current_other->next;
		}
	}
}


template<typename T>
List<T>::~List(){
	while (size)
		this->Del();
}


template<typename T>
void List<T>::Add(T data, int position){

	if (position > size || position < 0)
		throw invalid_argument("Incorrect index");
	

	if (position == 0){
		head = new Node(data, this->head);

	} else{
		Node *current = this->head;

		for (int i{1}; i < position; i++){
			current = current->next;
		}

		current->next = new Node(data, current->next);
	}
	

	size++;
}

template<typename T>
void List<T>::Del(int position){

	if (position >= size || position < 0)
		throw invalid_argument("Incorrect index");


	if (position == 0){

		if (size == 1){
			delete head;
		} else {
			Node *temp = head;
			head = head->next;
			delete temp;
		}

	} else{
		Node *current = head;

		for (int i{1}; i < position; i++){
			current = current->next;
		}

		Node *temp = current->next;
		current->next = temp->next;
		delete temp;

	}


	size--;
}


template<typename T>
void List<T>::Sort(){
	Node *current;
	Node *next_node;

	for (int i{0}; i < size - 1; i++){
		current = head;
		next_node = head->next;
		for (int j{0}; j < size - 1 - i; j++){
			if (current->data > next_node->data){
				T temp = current->data;
				current->data = next_node->data;
				next_node->data = temp;
			}
			current = current->next;
			next_node = next_node->next;
		}
	}
}

template<typename T>
int List<T>::Search(T data){
	Node *current = head;
	int index = 0;

	while (current != NULL){
		if constexpr (is_floating_point_v<T>){
			if (current->data - data < 0.000001 && current->data - data > -0.000001)
				return index;
		}else if (current->data == data){
			return index;
		}
		
		current = current->next;
		index++;
	}
	return -1;
}

template<typename T>
List<T> List<T>::operator+(List list){

	Sort();
	list.Sort();

	List<T> result;
	Node *current_1 = head;
	Node *current_2 = list.head;


	while (current_1 != NULL && current_2 != NULL){
		if (current_1->data < current_2->data){
			result.Add(current_1->data);
			current_1 = current_1->next;

		} else if (current_1->data > current_2->data){
			result.Add(current_2->data);
			current_2 = current_2->next;

		} else {
			int count_1{1}, count_2{1};

			if constexpr (is_floating_point_v<T>){
				while(current_1->next != NULL && abs(current_1->data - current_1->next->data) < 0.000001){
					count_1++;
					current_1 = current_1->next;
				}
	
				while(current_2->next != NULL && abs(current_2->data - current_2->next->data) < 0.000001){
					count_2++;
					current_2 = current_2->next;
				}

			} else {
				while(current_1->next != NULL && current_1->data == current_1->next->data){
					count_1++;
					current_1 = current_1->next;
				}
	
				while(current_2->next != NULL && current_2->data == current_2->next->data){
					count_2++;
					current_2 = current_2->next;
				}
			}

			for (int i{0}; i < max(count_1, count_2); i++)
				result.Add(current_1->data);

			current_1 = current_1->next;
			current_2 = current_2->next;
		}
	}

	while (current_1 != NULL) {
		result.Add(current_1->data);
		current_1 = current_1->next;
	}

	while (current_2 != NULL) {
		result.Add(current_2->data);
		current_2 = current_2->next;
	}
	

	return result;
}

template<typename T>
List<T> List<T>::operator^(List list){

	this->Sort();
	list.Sort();

	List<T> result;
	Node *current_1 = this->GetHead();
	Node *current_2 = list.GetHead();


	while (current_1 != NULL && current_2 != NULL){
		if (current_1->data < current_2->data){
			current_1 = current_1->next;

		} else if (current_1->data > current_2->data){
			current_2 = current_2->next;

		} else {
			int count_1{1}, count_2{1};

			if constexpr (is_floating_point_v<T>){
				while(current_1->next != NULL && (current_1->data - current_1->next->data < 0.000001) && (current_1->data - current_1->next->data > -0.000001)){
					count_1++;
					current_1 = current_1->next;
				}
	
				while(current_2->next != NULL && (current_2->data - current_2->next->data < 0.000001) && (current_2->data - current_2->next->data > -0.000001)){
					count_2++;
					current_2 = current_2->next;
				}

			} else {
				while(current_1->next != NULL && current_1->data == current_1->next->data){
					count_1++;
					current_1 = current_1->next;
				}
	
				while(current_2->next != NULL && current_2->data == current_2->next->data){
					count_2++;
					current_2 = current_2->next;
				}
			}

			for (int i{0}; i < min(count_1, count_2); i++)
				result.Add(current_1->data);

			current_1 = current_1->next;
			current_2 = current_2->next;
		}
	}

	return result;
}


template<typename T>
void List<T>::View(){
	cout << ">> ";
	Node *current = this->head;
	while (current != NULL){
		cout << current->data << " ";
		current = current->next;
	}
	cout << "<<\n";
}


template<typename T>
int List<T>::GetSize(){
	return size;
};


template<typename T>
typename List<T>::Node *List<T>::GetHead(){
	return head;
}


template<typename T>
T &List<T>::operator[](const int index){
	if (index >= size || index < 0)
		throw invalid_argument("Incorrect index");

	Node *current = this->head;
	for (int i{0}; i < index; i++){
		current = current->next;
	}
	return current->data;
}

template<typename T>
List<T> &List<T>::operator=(const List &other){
	if (this == &other)
		return *this;

	while(size)
		Del();

	Node *current = other.head;
	while(current != NULL){
		Add(current->data);
		current = current->next;
	}

	return *this;
}


template<typename T>
List<T>::Node::Node(T data, Node *next){
	this->data = data;
	this->next = next;
}




#endif
