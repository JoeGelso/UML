#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include "status.h"
#include"my_string.h"
#include "generic_vector.h"
#include "associative_array.h"

//known type
typedef struct node Node;

struct node
{
	int height;					//height of node in AVL tree			
	Node* left;
	Node* right;
	MY_STRING key;				//used as an associative index
	GENERIC_VECTOR keyWords;	//vector of strings that fit into the "string family" denoted by the key
};

//utility functions:
//
int get_height(NODE node)//function to get height of node
{
	Node* n = (Node*)node;
	if (n == NULL)
		return 0;
	return n->height;
}
int max(int a, int b)//function to get max of 2 itegers
{
	if (a > b)
		return a;
	return b;//return b even if a == b
}

//function to allocate a new node with given key and data
NODE newNode(MY_STRING key, MY_STRING data)
{
	Node* pnode = (Node*)malloc(sizeof(Node));

	pnode->key = NULL;
	my_string_assignment(&(pnode->key), (MY_STRING)key);

	pnode->keyWords = generic_vector_init_default(my_string_assignment, my_string_destroy);

	if (data != NULL)
	{
		
		generic_vector_push_back(pnode->keyWords, data);
	}
	pnode->left = NULL;
	pnode->right = NULL;
	pnode->height = 1;
	return pnode;
}

//perform right rotation on a node
NODE right_Rotate(NODE node)
{
	Node* node1 = (Node*)node;

	Node* node2 = node1->left;
	Node* node3 = node2->right;

	//swap nodes around
	node2->right = node1;
	node1->left = node3;

	node1->height = max(get_height(node1->left), get_height(node1->right)) + 1;
	node2->height = max(get_height(node2->left), get_height(node2->right)) + 1;

	return node2;//node 2 has become new root
}

//perform left rotation on a node
NODE left_rotate(NODE node)
{
	Node* node1 = (Node*)node;
	Node* node2 = node1->right;
	Node* node3 = (Node*)node2->left;

	node2->left = node1;
	node1->right = node3;

	node1->height = max(get_height(node1->left), get_height(node1->right)) + 1;
	node2->height = max(get_height(node2->left), get_height(node2->right)) + 1;

	return node2;
}

//get the balance factor of a node
int get_balance_factor(NODE n)
{
	Node* node = (Node*)n;

	if (node == NULL)
		return 0;
	return (get_height(node->left) - get_height(node->right));
}

NODE node_insert(NODE n, MY_STRING key, MY_STRING data)
{
	Node* node = (Node*)n;
	//int i;
	int balance_factor;
	if (node == NULL)
	{
		//printf("new node:  %s\n", my_string_c_str(key));
		node = newNode(key, data);
		return node;
	}
		
	//printf("%s :: %s == %d\n", my_string_c_str(key), my_string_c_str(node->key), my_string_compare(key, node->keyWords));
	//use my_string_compare for placing keys
	if (my_string_compare(key, node->key) < 0)//if key < node->keywords
	{
		node->left = node_insert(node->left, key, data);
	}
	else if (my_string_compare(key, node->key) > 0)//if key > keyWords
	{
		node->right = node_insert(node->right, key, data);
	}
	else //keys are equivalent
	{
		//will push word from data into current node's keyWords g-vector will free data after
			generic_vector_push_back(node->keyWords, data);
		
		//destroy duplicate key
		//my_string_destroy((ITEM*)&data);
		//my_string_destroy((ITEM*)&key);
	}

	node->height = max(get_height(node->left),
		get_height(node->right) ) +1;

	//after insertion into an avl tree, must make sure avl balance property is retained, and fix it
	//if it isn't

	balance_factor = get_balance_factor(node);
	
	if (balance_factor > 1)//left-x cases
	{
		//if balance factor > 1, there are 2 cases that need to be fixed
		
		if (my_string_compare(key, node->left->key) < 0)//left-left case
		{
			return right_Rotate(node);
		}//end left-left case
		else if (my_string_compare(key, node->left->key) > 0)//left-right case
		{
			node->left = left_rotate(node->left);
			return right_Rotate(node);
		}//end left-right case
	}
	else if (balance_factor < -1)//right-x cases
	{
		//if balance factor < -1 there are 2 other cases to be addressed
		//right-right case
		if (my_string_compare(key, node->right->key) > 0)//key > node->reight->key
		{
			return left_rotate(node);
		}//end right-right case
		else if (my_string_compare(key, node->right->key) < 0)//key < node->right->key
		{
			//right-left case
			node->right = right_Rotate(node->right);
			return left_rotate(node);
		}//end right-left case
	}
	return node;
}//end node insertion function


NODE find_node_with_largest_vector(NODE nroot)//function to find and return node containing largest vector of words in a given tree 
{
	Node* root = (Node*)nroot;

	Node* vleft = NULL;
	Node* vright = NULL;
	Node* max = NULL;

	if (root != NULL)
	{
		//printf("size of root == %d with %s\n", generic_vector_get_size(root->keyWords), my_string_c_str(root->key));
		//root has no children
		if (root->left == NULL && root->right == NULL)
			return root;

		//find largest vector in left sub tree
		if(root->left != NULL)
			vleft = (Node*)find_node_with_largest_vector(root->left);

		//find largest vector in right sub tree
		if(root->right != NULL)
			vright = (Node*)find_node_with_largest_vector(root->right);

		if (vleft != NULL && vright != NULL)
		{
			if ((int)generic_vector_get_size(vleft->keyWords) > (int)generic_vector_get_size(vright->keyWords))
				max = vleft;
			else
				max = vright;
		}
		else
		{
			if (vleft == NULL && vright == NULL)
				max = root;
			else if (vright == NULL)
				max = vleft;
			else if (vleft == NULL)
				max = vright;

		}
		//compare the max of left and right with the root
		if ((int)generic_vector_get_size(root->keyWords) > (int)generic_vector_get_size(max->keyWords))
		max = root;
		//printf("Key ");
		//my_string_insertion(max->key, stdout);
		//printf("\t Size %d\n",generic_vector_get_size(max->keyWords));
		return max;
	}
	//base case root == null
	
	return root;
}//end find_node_with_largest_vector

MY_STRING get_node_key(NODE node)// a function that returns the key of a node
{
	Node* pnode = (Node*)node;
	if (pnode == NULL)
		return NULL;
	return (MY_STRING)pnode->key;
}

GENERIC_VECTOR get_node_vec(NODE node)//a function to return a nodes data vector
{
	Node* pnode = (Node*)node;

	if (pnode == NULL)
		return NULL;
	return pnode->keyWords;
}

//void node_vector_assignment(Node* node, GENERIC_VECTOR vec)//assign the vector of a node to the vector passed
//{
//	int i;
//	Node* pnode = (Node*)node;
//	if (pnode->keyWords == NULL)
//	{
//		pnode->keyWords = vec;
//	}
//	else
//	{
//		//empty original vector in node and replace it with one passed
//		while (generic_vector_pop_back(pnode->keyWords) == SUCCESS);
//	}
//	//copy vec into pnode->keyWords
//	for (i = 0; i < generic_vector_get_size(vec); i++)
//	{
//		generic_vector_push_back(pnode->keyWords,
//			generic_vector_at(vec,i) );
//	}
//	generic_vector_destroy(vec);
//	return;
//}

void node_destroy(NODE* pnode)//a function to destroy a node and it's left and right subtree
{
	
	Node* phnode = (Node*)*pnode;
	//base case
	if (phnode == NULL)
		return;
	

	//destroy left and right subtree
	node_destroy((NODE*)&(phnode->left));
	node_destroy((NODE*)&(phnode->right));

	//destroy this nodes objects
	if(phnode->key != NULL)
		my_string_destroy(&(phnode->key));
	//if(phnode->keyWords != NULL)
		generic_vector_destroy(&(phnode->keyWords));
	//destroy root
	free((NODE)phnode);
	*pnode = NULL;
	return;
}

