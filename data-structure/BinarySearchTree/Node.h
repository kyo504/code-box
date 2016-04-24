#ifndef NODE_H_
#define NODE_H_

struct Node
{
	Node(int data):m_pLeft(0), m_pRight(0), m_nData(data) {}
	virtual ~Node() {}

	Node* m_pLeft;
	Node* m_pRight;
	int m_nData;
};

#endif // NODE_H_

