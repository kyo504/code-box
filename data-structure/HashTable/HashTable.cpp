#include "HashTable.h"
#include <cstdio>
#include <unistd.h>

#define MAX_TABLE 100

HashTable::HashTable()
{

}

HashTable::~HashTable()
{

}

void HashTable::Init(HashFunc* f)
{
	pFP = f;

	for(int i=0; i<MAX_TABLE; i++) {
		LSlot slot_list;
		m_Table.push_back(slot_list);
	}
}

void HashTable::Insert(int key, string str)
{
	int hash = pFP(key);
	Slot newSlot = { key, str };

	if(Search(key) != NULL) {
		printf("Duplicate key error\n");
		return;
	} else {
		m_Table[hash].push_back(newSlot);
	}
}

string HashTable::Delete(int key)
{
	int hash = pFP(key);
	Slot cSlot;

	LSlot::iterator it = m_Table[hash].begin();

	for(; it != m_Table[hash].end(); ++it) {
		cSlot = *it;

		if(cSlot.key == key) {
			m_Table[hash].erase(it);
			return cSlot.value;
		}
	}

	return cSlot.value;
}

string* HashTable::Search(int key)
{
	int hash = pFP(key);

	LSlot::iterator it = m_Table[hash].begin();

	for(; it != m_Table[hash].end(); ++it) {
		if((*it).key == key) {
			return &((*it).value);
		}
	}

	return NULL;
}
