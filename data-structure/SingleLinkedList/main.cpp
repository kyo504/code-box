#include "SingleLinkedList.h"

#include <iostream>
using namespace std;

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