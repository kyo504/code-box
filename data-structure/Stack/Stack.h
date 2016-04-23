#ifndef STACK_H_
#define STACK_H_

#include "../DoubleLinkedList/DoubleLinkedList.h"

class Stack
{
	DoubleLinkedList dl;
	int m_nCount;

public:
	Stack();
	virtual ~Stack();
	void push(int input);
	void pop();
	int top();
	int get_count();
};

#endif // STACK_H_