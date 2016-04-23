#ifndef QUEUE_H_
#define QUEUE_H_

#include "../DoubleLinkedList/DoubleLinkedList.h"

class Queue
{
	DoubleLinkedList dl;
	int m_nSize;

public:
	Queue();
	virtual ~Queue();

	void enqueue(int data);
	int dequeue();
	bool is_empty();
	int get_size();

	void print_list();
};

#endif // QUEUE_H_