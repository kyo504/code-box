#include "Queue.h"
#include <iostream>
using namespace std;

Queue::Queue()
:m_nSize(0)
{

}

Queue::~Queue()
{

}

void Queue::enqueue(int data)
{
	dl.push_back(new Node(data));
	m_nSize++;
}

int Queue::dequeue()
{
	int ret = dl.front()->m_nData;
	if( dl.pop_front() == true ) {
		m_nSize--;
	}

	return ret;
}

bool Queue::is_empty()
{
	return dl.is_empty();
}

int Queue::get_size()
{
	return m_nSize;
}

void Queue::print_list()
{
	dl.print_list();
}