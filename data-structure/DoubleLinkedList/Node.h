#ifndef NODE_H_
#define NODE_H_

struct Node{

	Node() : m_pPrev(0), m_nData(0), m_pNext(0) {}
	Node(int newData) : m_pPrev(0), m_nData(newData), m_pNext(0) {}

	Node* m_pPrev;
	int m_nData;
	Node* m_pNext;

};

#endif // NODE_H_