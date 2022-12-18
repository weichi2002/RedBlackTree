
#include "linked_list.h"
#include <stdexcept>
//#include <iostream>
using namespace std;


template <typename T> 
void LinkedList<T>::push_back(T item){
	Node<T> *n = new Node<T>;
	n->data = item;
	numItems++;
	
	if(head == nullptr){
		head = n;
		tail = n;
		return;
	}

	tail->next = n;
	n->prev = tail;
	tail = n;	
}

template <typename T> 
LinkedList<T>::~LinkedList(){
	Node<T>* current = head;
	while( current != nullptr ) {
		Node<T>* next = current->next;
		delete current;
		current = next;
	}
	delete head;
	numItems = 0;
}

template <typename T> 
void LinkedList<T>::insert(size_t pos, T item){

	if (pos > numItems) throw invalid_argument("Invalid position");

	Node<T> *add = new Node<T>;
	size_t insert = pos - 1;
    Node<T> cur = head;
    for (size_t i = 0; i < numItems; i++) {
      if(i == insert) {
        add->next = cur->next;
        cur->next = add;
      }
      cur = cur->next;
    }
   numItems++;

}


template <typename T>
void LinkedList<T>::push_front(T item){
	Node<T> *n = new Node<T>;
	n->data = item;
	numItems++;

	if(head == nullptr){
		head = n;
		tail = n;
		return;
	}

	head->prev = n;
	n->next = head;
	head = n;
}


template <typename T>
T LinkedList<T>::at(size_t idx){
	if(idx >= numItems){
		throw std::invalid_argument("List index out of range: " + std::to_string(idx));
	}

	Node<T> *n = get_node(idx);
	return n->data;
}


template <typename T>
Node<T> *LinkedList<T>::get_node(size_t idx){

	size_t i = 0;
	Node<T> *cur = head;
	while(i < idx){
		cur = cur->next;
		i++;
	}

	return cur;
}



