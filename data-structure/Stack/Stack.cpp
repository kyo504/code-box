#include "Stack.h"

Stack::Stack()
:m_nCount(0)
{

}

Stack::~Stack()
{
	
}

void Stack::push(int input) 
{ 
	dl.push_back(new Node(input));
	m_nCount++;
}

void Stack::pop() 
{ 
	if( dl.pop_back() == true )
	{
		m_nCount--;
		//dl.print_list();
	}
}

int Stack::top() 
{ 
	if (dl.back() == 0) 
		throw -1;

	return dl.back()->m_nData; 
}

int Stack::get_count()
{
	return m_nCount;
}
