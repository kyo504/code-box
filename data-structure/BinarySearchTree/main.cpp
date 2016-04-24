#include "BinarySearchTree.h"
#include <cstdio>
#include <iostream>
using namespace std;

void traverse(BinarySearchTree& pBST)
{
	cout << endl;
	cout << "In-order traverse : ";
	pBST.traverse_in_order(pBST.get_root());
	cout << endl;
	cout << "Pre-order traverse : ";
	pBST.traverse_pre_order(pBST.get_root());
	cout << endl;
	cout << "Post-order traverse : ";
	pBST.traverse_post_order(pBST.get_root());
	cout << endl;	
}

int main()
{
	BinarySearchTree pBST;

	int arr[5] = {3,2,5,4,6};
	//int arr[1] = {3};

	for( int i=0; i<sizeof(arr)/sizeof(int); i++) {
		pBST.insert_node(arr[i]);
	}

	for( int i=0; i<sizeof(arr)/sizeof(int); i++) {
		if(pBST.search(pBST.get_root(), arr[i]))
			printf("%d is in the list\n", arr[i]);
		else
			printf("%d is NOT in the list\n", arr[i]);
	}

	// if( pBST->search(pBST->get_root(), 10) )
	// 	printf("10 is in the list\n");
	// else
	// 	printf("10 is NOT in the list\n");

	//printf("0x%x\n", pBST.get_root());
	//printf("0x%x\n", pBST.get_root()->m_pRight);

	//traverse(pBST);

	// // Remove leaf node
	// if( pBST->remove_node(2) ) {
	// 	printf("leaf node is removed\n");
	// } else {
	// 	printf("leaf node is NOT removed\n");
	// }

	// traverse(pBST);

	//Remove a node having left and right node
	pBST.remove_node(5);
	traverse(pBST);

	pBST.remove_node(2);
	traverse(pBST);

	pBST.remove_node(6);
	traverse(pBST);

	pBST.remove_node(4);
	traverse(pBST);

	pBST.remove_node(3);
	traverse(pBST);

	return 0;
}
