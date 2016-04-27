#include "Heap.h"
#include <cstdio>

Heap::Heap()
{
	// We add a dummy element to start index with 1, not 0
	HeapElem dummyElem;
	dummyElem.data = 'X';
	dummyElem.pr = -1;
	m_vArr.push_back(dummyElem);
}

Heap::~Heap()
{

}

int Heap::GetLChildIndex(int idx)
{
	return idx*2;
}

int Heap::GetRChildIndex(int idx)
{
	return idx*2 + 1;
}

int Heap::GetParentIndex(int idx)
{
	return static_cast<int>(idx/2);
}

int Heap::GetHigherPriorityChildIndex(int idx)
{
	if(GetLChildIndex(idx) > GetSize())
		return 0;
	else if(GetLChildIndex(idx) == GetSize())
		return GetLChildIndex(idx);
	else {
		if(m_vArr[GetLChildIndex(idx)].pr < m_vArr[GetRChildIndex(idx)].pr)
			return GetLChildIndex(idx);
		else
			return GetRChildIndex(idx);
	}
}

void Heap::Insert(HeapData data, Priority pr)
{
	// Add new element to the last position of list
	HeapElem tempElem;
	tempElem.data = data;
	tempElem.pr = pr;
	m_vArr.push_back(tempElem);

	int parentIdx;
	int childIdx = GetSize();

	// Trace priority from bottom to top
	// If child's priority is higher than parent's, we swap content.
	while(parentIdx = GetParentIndex(childIdx)) {

		if( m_vArr[parentIdx].pr > m_vArr[childIdx].pr ) {
			// Swap contents 
			HeapElem tempElem;
			tempElem.data = m_vArr[parentIdx].data;
			tempElem.pr = m_vArr[parentIdx].pr;

			m_vArr[parentIdx].data = m_vArr[childIdx].data;
			m_vArr[parentIdx].pr = m_vArr[childIdx].pr;

			m_vArr[childIdx].data = tempElem.data;
			m_vArr[childIdx].pr = tempElem.pr;
		}

		childIdx = parentIdx;
	}
}

HeapData Heap::Delete()
{
	int parentIdx = 1;
	int childIdx;
	int size = GetSize();
	int retData = m_vArr[1].data;

	// Replace the contents
	m_vArr[parentIdx].data = m_vArr[size].data;
	m_vArr[parentIdx].pr = m_vArr[size].pr;

	// Remove last element
	m_vArr.pop_back();

	while(childIdx = GetHigherPriorityChildIndex(parentIdx)) {
		if(m_vArr[parentIdx].pr > m_vArr[childIdx].pr) {
			// Swap contents 
			HeapElem tempElem;
			tempElem.data = m_vArr[parentIdx].data;
			tempElem.pr = m_vArr[parentIdx].pr;

			m_vArr[parentIdx].data = m_vArr[childIdx].data;
			m_vArr[parentIdx].pr = m_vArr[childIdx].pr;

			m_vArr[childIdx].data = tempElem.data;
			m_vArr[childIdx].pr = tempElem.pr;

			parentIdx = childIdx;
		}
	}

	return retData;
}

bool Heap::IsEmpty()
{
	return GetSize() <= 1 ? true : false;
}

int Heap::GetSize()
{
	// we subtract 1 from actual size because we start index with 1, not 0
	return static_cast<int>(m_vArr.size() -1);
}

void Heap::PrintList()
{
	vector<HeapElem>::iterator it = m_vArr.begin();

	printf("< Heap data >\n");
	for( ; it != m_vArr.end(); ++it ) {
		printf("Data: %c, Priority: %d\n", (*it).data, (*it).pr);
	}
}