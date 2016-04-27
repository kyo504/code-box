#include "HashTable.h"

#include <iostream>
using namespace std;

int MyHashFunc(int k)
{
	return k % 100;
}

int main(int argc, char* argv[])
{
	HashTable hTable;

	hTable.Init(MyHashFunc);

	hTable.Insert(900254, string("jung"));
	hTable.Insert(900139, string("kim"));
	hTable.Insert(900827, string("song"));
	hTable.Insert(900821, string("json"));
	hTable.Insert(900822, string("choi"));
	hTable.Insert(900823, string("park"));

	string* pStr = NULL;
	pStr = hTable.Search(900254);
	if(pStr)
		cout << "Name: " << *pStr << endl;
	else
		cout << "Failed to search" << endl;

	pStr = hTable.Search(900139);
	if(pStr)
		cout << "Name: " << *pStr << endl;
	else
		cout << "Failed to search" << endl;

	pStr = hTable.Search(900827);
	if(pStr)
		cout << "Name: " << *pStr << endl;
	else
		cout << "Failed to search" << endl;

	pStr = hTable.Search(900821);
	if(pStr)
		cout << "Name: " << *pStr << endl;
	else
		cout << "Failed to search" << endl;

	pStr = hTable.Search(900822);
	if(pStr)
		cout << "Name: " << *pStr << endl;
	else
		cout << "Failed to search" << endl;

	pStr = hTable.Search(900823);
	if(pStr)
		cout << "Name: " << *pStr << endl;
	else
		cout << "Failed to search" << endl;


	pStr = hTable.Search(123);
	if(pStr)
		cout << "Name: " << *pStr << endl;
	else
		cout << "Failed to search" << endl;

	return 0;
}