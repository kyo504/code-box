#include "Heap.h"

#include <cstdio>


int main(int argc, char* argv[])
{
	Heap heap;

	heap.Insert('A', 1);
	heap.Insert('B', 2);
	heap.Insert('C', 3);
	// heap.Insert('D', 4);
	// heap.Insert('E', 5);
	// heap.Insert('F', 6);
	// heap.Insert('G', 7);

	heap.PrintList();
//	printf("%c is deleted\n", heap.Delete());
//	heap.PrintList();

	heap.Insert('A', 1);
	heap.Insert('B', 2);
	heap.Insert('C', 3);
	//heap.Insert('D', 4);

	heap.PrintList();

	// printf("%c is deleted\n", heap.Delete());





	// while(!heap.IsEmpty())
	// 	printf("%c is deleted\n", heap.Delete());

	return 0;
}