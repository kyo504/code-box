#ifndef DEQUE_H_
#define DEQUE_H_

#include "../DoubleLinkedList/DoubleLinkedList.h"

/*
	Deque

	Features:
	1. Insert and remove data from both front and end of the list
	2. Dynamic list size

*/

class Deque
{
	DoubleLinkedList dl;

public:
	Deque();
	virtual ~Deque();

	int front();
	int back();

};

#endif // DEQUE_H_