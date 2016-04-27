#ifndef HEAP_H_
#define HEAP_H_

#include <vector>
using namespace std;

typedef char HeapData;
typedef int Priority;

typedef struct _HeapElem
{
	Priority pr;
	HeapData data;
}HeapElem;

class Heap
{
	vector<HeapElem> m_vArr;

public:
	Heap();
	virtual ~Heap();

	int GetLChildIndex(int idx);
	int GetRChildIndex(int idx);
	int GetParentIndex(int idx);
	int GetHigherPriorityChildIndex(int idx);

	void Insert(HeapData data, Priority pr);
	HeapData Delete();

	bool IsEmpty();
	int GetSize();

	void PrintList();
};

#endif // HEAP_H_