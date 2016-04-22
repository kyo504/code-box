#ifndef STACK_H_
#define STACK_H_

#include "../DoubleLinkedList/DoubleLinkedList.h"

class Stack
{
	DoubleLinkedList dl;

public:
	void push(int input) { dl.push_back(new Node(input)); }
	void pop() { dl.pop_back(); }
	int top() { return dl.back()->m_nData; }
};

#endif // STACK_H_