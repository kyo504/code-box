#ifndef SINGLELINKEDLIST_H_
#define SINGLELINKEDLIST_H_

#include "Node.h"

class SingleLinkedList
{
public:
	SingleLinkedList();
	virtual ~SingleLinkedList();
	
	void push_back(Node* newNode);
	void push_front(Node* newNode);
	void pop_back();
	void pop_front();
	void clear();
	
	void PrintList();
	
private:
	Node* m_pHead;
};

#endif // SINGLELINKEDLIST_H_

