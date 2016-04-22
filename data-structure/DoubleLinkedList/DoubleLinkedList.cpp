#include "DoubleLinkedList.h"
#include <iostream>

DoubleLinkedList::DoubleLinkedList()
:m_pHead(0)
,m_pTail(0)
{
	m_pHead = new Node();
	m_pTail = new Node();
	m_pHead->m_pNext = m_pTail;
	m_pTail->m_pPrev = m_pHead;
}

DoubleLinkedList::~DoubleLinkedList()
{
	clear();

	if(m_pHead) {
		delete m_pHead;
		m_pHead = 0;
	}

	if(m_pTail) {
		delete m_pTail;
		m_pTail = 0;
	}
    
}

void DoubleLinkedList::push_back(Node* newNode)
{
	newNode->m_pNext = m_pTail;
	newNode->m_pPrev = m_pTail->m_pPrev;
	m_pTail->m_pPrev->m_pNext = newNode;
	m_pTail->m_pPrev = newNode;
}

void DoubleLinkedList::push_front(Node* newNode)
{
	newNode->m_pPrev = m_pHead;
	newNode->m_pNext = m_pHead->m_pNext;
	m_pHead->m_pNext->m_pPrev = newNode;
	m_pHead->m_pNext = newNode;
}

void DoubleLinkedList::erase(Node* delNode)
{
	delNode->m_pPrev->m_pNext = delNode->m_pNext;
	delNode->m_pNext->m_pPrev = delNode->m_pPrev;
}

void DoubleLinkedList::pop_back()
{
	Node* pTemp = m_pTail->m_pPrev;
	if (pTemp == m_pHead) {
		std::cout << "There is no item to pop" << std::endl;
		return;
	}

	erase(pTemp);
}

void DoubleLinkedList::pop_front()
{
	Node* pTemp = m_pHead->m_pNext;
	if (pTemp == m_pTail) {
		std::cout << "There is no item to pop" << std::endl;
		return;
	}

	erase(pTemp);
}

void DoubleLinkedList::clear()
{
	Node* pTemp = m_pHead->m_pNext;
	while(pTemp != m_pTail) {
		erase(pTemp);
		pTemp = pTemp->m_pNext;
	}
}

void DoubleLinkedList::print_list()
{
	Node* pTemp = m_pHead->m_pNext;
	std::cout << "Output: ";
	while(pTemp != m_pTail) {
		std::cout << pTemp->m_nData << " ";
		pTemp = pTemp->m_pNext;
	}
	std::cout << std::endl;
}

Node* DoubleLinkedList::back() 
{
	if (m_pTail->m_pPrev == m_pHead) {
		std::cout << "There is no item in the list" << std::endl;
		return 0;
	} else {
		return m_pTail->m_pPrev;
	}
}