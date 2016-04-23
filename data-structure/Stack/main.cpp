#include "Stack.h"
#include <iostream>

int main()
{
	Stack* mystack = new Stack();

	mystack->push(5);
	mystack->push(1);
	mystack->push(3);
	mystack->push(2);
	mystack->push(9);
	mystack->push(0);

	std::cout << "Current top: " << mystack->top() << ", Total Items: " << mystack->get_count() << std::endl;
	mystack->pop();
	std::cout << "Current top: " << mystack->top() << ", Total Items: " << mystack->get_count() << std::endl;
	mystack->pop();
	std::cout << "Current top: " << mystack->top() << ", Total Items: " << mystack->get_count() << std::endl;
	mystack->pop();
	std::cout << "Current top: " << mystack->top() << ", Total Items: " << mystack->get_count() << std::endl;
	mystack->pop();
	std::cout << "Current top: " << mystack->top() << ", Total Items: " << mystack->get_count() << std::endl;
	mystack->pop();
	std::cout << "Current top: " << mystack->top() << ", Total Items: " << mystack->get_count() << std::endl;
	mystack->pop();

	try{
		int nTop = mystack->top();
	} catch(int e) {
		std::cout << "[Exception] No item in the list(" << e << ")" << std::endl;
	}

	delete mystack;

	return 0;
}