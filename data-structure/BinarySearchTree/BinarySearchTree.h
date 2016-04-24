#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include "Node.h"

class BinarySearchTree
{
public:
	BinarySearchTree();
	virtual ~BinarySearchTree();

	Node*& insert_node(int data);
	Node*& remove_node(int data);
	bool search(Node* root, int data);
	Node* find_left_most_child(Node* current);

	void traverse_in_order(Node* root); // Left-Visit-Right
	void traverse_pre_order(Node* root); // Visit-Left-Right
	void traverse_post_order(Node* root); // Left-Right-Visit
	Node* get_root();

private:
	Node*& internal_insert_node(Node*& root, int data);
	Node*& internal_remove_node(Node*& root, int data);
	Node* m_pRoot;
};

#endif // BINARYSEARCHTREE_H_