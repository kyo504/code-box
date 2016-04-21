#include <iostream>
using namespace std;

struct Node{

	Node() : m_nData(0), m_pNext(0) {}
	Node(int newData) : m_nData(newData), m_pNext(0) {}

	int m_nData;
	Node* m_pNext;

};

class SingleLinkedList
{
public:
	SingleLinkedList() : m_pHead(0) {
		m_pHead = new Node();
	}

	virtual ~SingleLinkedList() {
		clear();
	}

	void push_back(Node* newNode) {
		Node* pTemp = m_pHead;
		while (pTemp->m_pNext) {
			pTemp = pTemp->m_pNext;
		}
		pTemp->m_pNext = newNode;
	}

	void push_front(Node* newNode) {
		if (m_pHead->m_pNext == NULL) {
			m_pHead->m_pNext = newNode;
		} else {
			Node* pTemp = m_pHead->m_pNext;
			m_pHead->m_pNext = newNode;
			newNode->m_pNext = pTemp;
		}
	}

	void pop_back() {
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

	void pop_front() {
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

	void clear() {
		while (m_pHead->m_pNext) {
			pop_front();
		}
	}


	void PrintList() {
		Node* pTemp = m_pHead->m_pNext;

		while (pTemp) {
			cout << pTemp->m_nData << " ";
			pTemp = pTemp->m_pNext;
		}
		cout << endl;
	}

private:
	Node* m_pHead;

};

int main()
{
	SingleLinkedList* sList = new SingleLinkedList();

	sList->push_back(new Node(5));
	sList->push_back(new Node(3));
	sList->push_back(new Node(1));
	sList->push_back(new Node(4));
	sList->push_back(new Node(9));

	sList->PrintList();

	sList->push_front(new Node(11));
	sList->push_front(new Node(22));
	sList->PrintList();

	sList->pop_back();
	sList->pop_back();
	sList->PrintList();

	sList->pop_front();
	sList->pop_front();
	sList->PrintList();





	delete sList;

	return 0;
}