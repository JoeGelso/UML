#include "status.h"
#include "generic.h"

#ifndef GENERIC_VECTOR_H
#define GENERIC_VECTOR_H

typedef void* GENERIC_VECTOR;

GENERIC_VECTOR generic_vector_init_default(
	Status (*assignment)(ITEM* phLeft, ITEM hRight),
	void (*destroy)(ITEM* phItem)
);


//add elements to the container
Status generic_vector_push_back(GENERIC_VECTOR hVector, ITEM item);

//accessor functions
int generic_vector_get_size(GENERIC_VECTOR hVector);
int generic_vector_get_capacity(GENERIC_VECTOR hVector);

//This guy needs to change START HERE
//use the item_destroy function to destroy the object being removed.
Status generic_vector_pop_back(GENERIC_VECTOR hVector);

Boolean generic_vector_empty(GENERIC_VECTOR hVector);

//change the value of elements of the container
//look at the value of elements of the container
ITEM generic_vector_at(GENERIC_VECTOR hVector, int index);

//destroy
void generic_vector_destroy(GENERIC_VECTOR* phVector);

#endif
