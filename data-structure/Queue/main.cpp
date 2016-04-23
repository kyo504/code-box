#include "Queue.h"
#include <iostream>
using namespace std;

int main()
{
	Queue* myqueue = new Queue();

	myqueue->enqueue(5);
	myqueue->enqueue(1);
	myqueue->enqueue(3);
	myqueue->enqueue(2);
	myqueue->enqueue(9);
	myqueue->print_list();

	cout << endl;

	cout << "Dequeue: " << myqueue->dequeue() << ", Size : " << myqueue->get_size() << endl;
	myqueue->print_list();
	cout << "Dequeue: " << myqueue->dequeue() << ", Size : " << myqueue->get_size() << endl;
	myqueue->print_list();
	cout << "Dequeue: " << myqueue->dequeue() << ", Size : " << myqueue->get_size() << endl;
	myqueue->print_list();
	cout << "Dequeue: " << myqueue->dequeue() << ", Size : " << myqueue->get_size() << endl;
	myqueue->print_list();


	// If this code is executed, sementation fault is occurred.
	cout << "Dequeue: " << myqueue->dequeue() << endl;
	myqueue->print_list();

	delete myqueue;

	return 0;
}