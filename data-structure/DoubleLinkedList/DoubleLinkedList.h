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
	bool pop_back();
	bool pop_front();
	void clear();
	Node* front();
	Node* back();
	void erase(Node* delNode);
	bool is_empty();
	
	void print_list();
	
private:
	Node* m_pHead;
	Node* m_pTail;
};

#endif // DOUBLELINKEDLIST_H_
