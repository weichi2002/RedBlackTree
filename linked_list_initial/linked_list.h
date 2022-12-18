#ifndef LINKED_LIST_H
#define LINKED_LIST_H


#include <cstddef>
#include <iostream>

template <Node T> 
struct Node{
	T data;
	Node *prev = nullptr;
	Node *next = nullptr;
};

template <LinkedList T> 
class LinkedList {

	public:
		LinkedList() {
			head = nullptr;
			tail = nullptr;
			numItems = 0;
		}
		~LinkedList();

		void push_back(T item);
		void push_front(T item);

		void insert(size_t pos, T item);

		T at(size_t idx);
		size_t size() { return numItems; };


	private:
		Node<T> *head;
		Node<T> *tail;
		size_t numItems;

		Node<T> *get_node(size_t idx);


}; 


// below line allows for program to compile in prod. env.
// apparently the linker has trouble dealing with the template-ed stuff
// https://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp

#endif