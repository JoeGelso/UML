//associative_array.h
#ifndef ASSOCIATIVE_ARRAY_H
#define ASSOCIATIVE_ARRAY_H
#include <stdlib.h>
#include"my_string.h"
#include "generic_vector.h"
#include "generic.h"


typedef void* NODE;



NODE newNode(MY_STRING key, GENERIC_VECTOR data);//function that will allocate a new node

//rotation functions for avl tree
NODE left_rotate(NODE node);
NODE right_Rotate(NODE node);

int get_balance_factor(NODE node);//function to calculate balance factor of a given node

NODE node_insert(NODE node, MY_STRING key, GENERIC_VECTOR data);//insert a node into a tree

NODE find_node_with_largest_vector(NODE root); //function to find the largest vector in a tree starting from the root

MY_STRING get_node_key(NODE node);//function to get the key of a node

GENERIC_VECTOR get_node_vec(NODE node);//a function to return a nodes data vector

void node_vector_assignment(NODE node, GENERIC_VECTOR vec);//assign the vector of a node to the vector passed

void node_destroy(NODE* pnode);//a function to destroy a node and it's left and right subtree

#endif