#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <list>
#include <vector>
#include <string>
using namespace std;

typedef struct _slot
{
	int key;
	string value;
}Slot;

typedef int HashFunc(int key);

class HashTable
{
public:
	HashTable();
	virtual ~HashTable();

	void Init(HashFunc* f);
	void Insert(int key, string value);
	string Delete(int key);
	string* Search(int key);

private:
	typedef list<Slot> LSlot;
	vector<LSlot> m_Table;
	HashFunc* pFP;

};

#endif // HASHTABLE_H_