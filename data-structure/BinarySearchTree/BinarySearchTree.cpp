#include "BinarySearchTree.h"
#include <cstddef>
#include <iostream>
#include <cstdio>

BinarySearchTree::BinarySearchTree()
:m_pRoot(0)
{

}

BinarySearchTree::~BinarySearchTree()
{

}

Node*& BinarySearchTree::insert_node(int data)
{
	return internal_insert_node(m_pRoot, data);
}

Node*& BinarySearchTree::internal_insert_node(Node*& root, int data)
{
	if(root == NULL) {
		root = new Node(data);
	} else {
		if(root->m_nData > data)
			root->m_pLeft =  internal_insert_node(root->m_pLeft, data);
		else if(root->m_nData < data)
			root->m_pRight =  internal_insert_node(root->m_pRight, data);
	}

	return root;
}

bool BinarySearchTree::search(Node* root, int data)
{
	if( root == NULL ) 
		return false;
	else if(root->m_nData > data)
		return search(root->m_pLeft, data);
	else if(root->m_nData < data)
		return search(root->m_pRight, data);
	else
		return true;
}

Node* BinarySearchTree::find_left_most_child(Node* current)
{
	while(current->m_pLeft) {
		// printf("---------------------\n");
		// printf("data: %d, addr: 0x%x\n", current->m_nData, current);
		// printf("0x%x\n", current->m_pLeft);
		// printf("---------------------\n");
		current = current->m_pLeft;
	}

	// printf("---------------------\n");
	// std::cout << "left most" << std::endl;
	// printf("data: %d, addr: 0x%x\n", current->m_nData, current);
	// printf("0x%x\n", current->m_pLeft);
	// printf("---------------------\n");


	return current;
}

Node*& BinarySearchTree::remove_node(int data)
{
	return internal_remove_node(m_pRoot, data);
}

Node*& BinarySearchTree::internal_remove_node(Node*& root, int data)
{
	if(root == NULL) return root;
	else if(root->m_nData > data) root->m_pLeft = internal_remove_node(root->m_pLeft, data);
	else if(root->m_nData < data) root->m_pRight = internal_remove_node(root->m_pRight, data);
	else {
		// Case 1: No Child
		if(root->m_pLeft == NULL && root->m_pRight == NULL){
			printf("AAA\n");
			delete root;
			root = NULL;
		// Case 2: one child
		} else if(root->m_pLeft == NULL){
			Node *temp = root;
			root = root->m_pRight;
			delete temp;
		} else if(root->m_pRight == NULL){
			Node *temp = root;
			root = root->m_pLeft;
			delete temp;
		} else{
			Node *temp = find_left_most_child(root->m_pRight);
			root->m_nData = temp->m_nData;
			root->m_pRight = internal_remove_node(root->m_pRight, temp->m_nData);
		}		
	}


	printf("0x%x\n", root);
	return root;	
}

/*
void BinarySearchTree::replace_node(Node*& replaced, Node*& newone)
{
	if ( replaced == NULL || newone == NULL ) return;

	// traverse_in_order(m_pRoot);
	// printf("\n");

	printf("[replaced      ] data: %d, 0x%x\n", replaced->m_nData, replaced);
	printf("[replaced-left ] data: %d, 0x%x\n", replaced->m_pLeft->m_nData, replaced->m_pLeft);
	printf("[replaced-right] data: %d, 0x%x\n", replaced->m_pRight->m_nData, replaced->m_pRight);
	printf("[replaced-right-right] 0x%x\n", replaced->m_pRight->m_pRight);
	printf("[replaced-right-left] 0x%x\n", replaced->m_pRight->m_pLeft);

	if (replaced->m_pLeft != NULL && replaced->m_pRight != NULL) {

		if(replaced->m_pLeft != newone)
		{
			std::cout << "left is not newone" << std::endl;
			newone->m_pLeft = replaced->m_pLeft;
		} else {
			std::cout << "left is newone" << std::endl;
		}

		if(replaced->m_pRight != newone) {
			std::cout << "right is not newone" << std::endl;
			newone->m_pRight = replaced->m_pRight;
		} else {
			std::cout << "right is newone : " << replaced->m_pRight->m_nData << std::endl;
			std::cout << "right is newone : " << replaced->m_pLeft->m_nData << std::endl;
		}
	}

	Node* temp = replaced;
	replaced = newone;

	delete temp;
}

bool BinarySearchTree::remove_node(int data)
{
	return m_pRoot == NULL ? false : internal_remove_node(m_pRoot, data);
}

bool BinarySearchTree::internal_remove_node(Node*& current, int data)
{
	printf("Current value : %d\n", current->m_nData);
	printf("input value : %d\n", data);

	if(current->m_nData == data) {

		if(current->m_pLeft == NULL && current->m_pRight == NULL) {
			printf("AAA\n");
			// if current is leaf node
			delete current;
			current = NULL;
		} else if(current->m_pLeft != NULL && current->m_pRight == NULL) {
			printf("BBB\n");
			// if current has only left node
			replace_node(current, current->m_pLeft);
		} else if(current->m_pLeft == NULL && current->m_pRight != NULL) {
			printf("CCC\n");
			// if current has only left node
			replace_node(current, current->m_pRight);
		} else {

			//traverse_in_order(m_pRoot);
			//printf("\n");

			//printf("[current      ] data: %d, addr: 0x%x\n", current->m_nData, current);
			//printf("[current-right] data: %d, addr: 0x%x\n", current->m_pRight->m_nData, current->m_pRight);


			// if current has left and right node	
			Node* leftmost = find_left_most_child(current->m_pRight);
			//printf("[LeftMost      ] data: %d, addr: 0x%x\n", leftmost->m_nData, leftmost);
//			printf("[LeftMost-right] data: %d, addr: 0x%x\n", leftmost->m_pRight->m_nData, leftmost->m_pRight);
			//Node* temp = find_left_most_child(current->m_pRight);

			replace_node(current, leftmost);

		}

	} else if(current->m_nData > data) {
		// if the variable value is less than current node's data
		return internal_remove_node(current->m_pLeft, data);
	} else {
		// if the variable value is less than current node's data
		return internal_remove_node(current->m_pRight, data);
	}

	return true;
}
/**/

void BinarySearchTree::traverse_in_order(Node* root)
{
	if(root == NULL) return;

	traverse_in_order(root->m_pLeft);
	std::cout << root->m_nData << " ";
	traverse_in_order(root->m_pRight);
}

void BinarySearchTree::traverse_pre_order(Node* root)
{
	if(root == NULL) return;

	std::cout << root->m_nData << " ";
	traverse_pre_order(root->m_pLeft);
	traverse_pre_order(root->m_pRight);
}

void BinarySearchTree::traverse_post_order(Node* root)
{
	if(root == NULL) return;

	traverse_post_order(root->m_pLeft);
	traverse_post_order(root->m_pRight);
	std::cout << root->m_nData << " ";
}

Node* BinarySearchTree::get_root()
{
	return m_pRoot;
}