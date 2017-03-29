#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include "Node.h"

using namespace std;

template<typename type> class linkedList{

	Node<type> *begin;
	Node<type> *end;
	Node<type> *curr;
	Node<type> *prev;
	int count;
		
	public:
	linkedList();
	void insert(type node);
	void remove(type **node);
	void resetCurrent();
	void getNode(type **data);
	void getCount(int &length);
	void increment();
	void removeCurrent();
};

template<typename type> linkedList<type>::linkedList(){
	begin = end = curr = prev = NULL;
	count = 0;
}

template<typename type> void linkedList<type>::resetCurrent(){
	curr = prev = NULL;
}

template<typename type> void linkedList<type>::getNode(type **data){
		if(curr == NULL)
			curr = begin;
		*data = &curr->data;
}

template<typename type> void linkedList<type>::increment(){
	prev = curr;
	curr = curr->next;
}

template<typename type> void linkedList<type>::removeCurrent(){
	if(prev == NULL){
		Node<type> *n = curr;
		begin = curr = curr->next;
		free(n);
	}else{
		prev->next = curr->next;
		free(curr);
		curr = prev->next;
	}
	count--;
}

template<typename type> void linkedList<type>::insert(type data){
	Node<type> *n = new Node<type>();
	n->data = data;
	n->next = NULL;
	if(begin == NULL){
		begin = end = n;
	}else{
		end->next = n;
		end = n;
	}
	count++;
}

template<typename type> void linkedList<type>::getCount(int &length){
	length = count;
}
