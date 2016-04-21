#ifndef DOUBLELINKEDLIST_H_
#define DOUBLELINKEDLIST_H_

#include "Node.h"

class DoubleLinkedList
{
public:
	DoubleLinkedList();
	virtual ~DoubleLinkedList();
	
	void push_back(Node* newNode);
	void push_front(Node* newNode);
	void pop_back();
	void pop_front();
	void clear();
	
	void PrintList();
	
private:
	Node* m_pHead;
};

#endif // DOUBLELINKEDLIST_H_



#endif