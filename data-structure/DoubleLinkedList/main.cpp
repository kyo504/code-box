#include "DoubleLinkedList.h"
#include <iostream>
using namespace std;

int main()
{
	DoubleLinkedList* dList = new DoubleLinkedList();

	dList->print_list();

	dList->push_back(new Node(5));
	dList->push_back(new Node(3));
	dList->push_back(new Node(1));
	dList->push_back(new Node(4));
	dList->push_back(new Node(9));

	dList->print_list();

	dList->push_front(new Node(11));
	dList->push_front(new Node(22));
	dList->print_list();

	dList->pop_back();
	dList->pop_back();
	dList->print_list();

	dList->pop_front();
	dList->pop_front();
	dList->print_list();

	dList->clear();

	dList->pop_front();
	dList->pop_back();

	delete dList;

	return 0;
}