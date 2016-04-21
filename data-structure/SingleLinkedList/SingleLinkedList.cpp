#include "SingleLinkedList.h"
#include <iostream>
#include <cstddef>
using namespace std;

SingleLinkedList::SingleLinkedList() : m_pHead(0) {
	m_pHead = new Node();
}

SingleLinkedList::~SingleLinkedList() {
	clear();
}

void SingleLinkedList::push_back(Node* newNode) {
	Node* pTemp = m_pHead;
	while (pTemp->m_pNext) {
		pTemp = pTemp->m_pNext;
	}
	pTemp->m_pNext = newNode;
}

void SingleLinkedList::push_front(Node* newNode) {
	if (m_pHead->m_pNext == NULL) {
		m_pHead->m_pNext = newNode;
	} else {
		Node* pTemp = m_pHead->m_pNext;
		m_pHead->m_pNext = newNode;
		newNode->m_pNext = pTemp;
	}
}

void SingleLinkedList::pop_back() {
	if (m_pHead->m_pNext == NULL) {
		cout << "There exists no item in the list." << endl;
		return;
	} else {
		Node* pPrev = m_pHead;
		Node* pCurrent = m_pHead->m_pNext;

		while (pCurrent->m_pNext != NULL) {
			pPrev = pCurrent;
			pCurrent = pCurrent->m_pNext;
		}

		pPrev->m_pNext = NULL;
		delete pCurrent;

	}
}

void SingleLinkedList::pop_front() {
	if (m_pHead->m_pNext == NULL) {
		cout << "There exists no item in the list." << endl;
		return;
	} else {

		Node* pTemp = m_pHead->m_pNext;
		if (pTemp->m_pNext == NULL) {
			m_pHead->m_pNext = NULL;
		} else {
			m_pHead->m_pNext = pTemp->m_pNext;
		}

		delete pTemp;
	}
}

void SingleLinkedList::clear() {
	while (m_pHead->m_pNext) {
		pop_front();
	}
}


void SingleLinkedList::PrintList() {
	Node* pTemp = m_pHead->m_pNext;

	while (pTemp) {
		cout << pTemp->m_nData << " ";
		pTemp = pTemp->m_pNext;
	}
	cout << endl;
}
