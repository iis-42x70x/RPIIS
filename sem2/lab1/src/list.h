#ifndef LIST_H
#define LIST_H
 
#include <iostream>
#include <type_traits>
#include <stdexcept>

using namespace std;


template<typename T>
class List{
public:
	List();
	List(const List<T>& other);
	~List();

	void Add(T data, int position = 0);
	void Del(int position = 0);
	void Sort();
	int Search(T data);
	List<T> operator+(List list);
	List<T> operator^(List list);

	void View();
	int GetSize();
	

	T &operator[](const int index);
	List<T> &operator=(const List &other);

private:

	class Node{
	public:
		Node *next;
		T data;
	
		Node(T data, Node *next = NULL);
	};

	Node *head;
	int size;

public:

	Node *GetHead();
};


#include "list.inl"

#endif
