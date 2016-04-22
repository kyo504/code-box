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
	Node* back();
	void erase(Node* delNode);
	
	void print_list();
	
private:
	Node* m_pHead;
	Node* m_pTail;
};

#endif // DOUBLELINKEDLIST_H_
