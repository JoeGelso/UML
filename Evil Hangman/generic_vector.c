#include <stdio.h>
#include <stdlib.h>
#include "generic_vector.h"

//Known type
struct generic_vector
{
	int size; //how many elements the container holds now.
	int capacity; //how many elements the container can hold without resize.
	ITEM* data;
	Status(*item_assignment)(ITEM* phLeft, ITEM hRight);
	void(*item_destroy)(ITEM* phItem);
};

typedef struct generic_vector Generic_vector;

GENERIC_VECTOR generic_vector_init_default(
	Status(*assignment)(ITEM* phLeft, ITEM hRight),
	void(*destroy)(ITEM* phItem)
)
{
	Generic_vector* pVector;
	pVector = (Generic_vector*)malloc(sizeof(Generic_vector));
	int i;
	if (pVector != NULL)
	{
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->data = (ITEM*)malloc(sizeof(ITEM) * pVector->capacity);
		if (pVector->data == NULL)
		{
			free(pVector);
			return NULL;
		}
		pVector->item_assignment = assignment;
		pVector->item_destroy = destroy;
		for (i = 0; i < pVector->capacity; i++)
		{
			pVector->data[i] = NULL;
		}
	}
	return (GENERIC_VECTOR)pVector;
}

Status generic_vector_push_back(GENERIC_VECTOR hVector, ITEM item)
{
	//casting to the known type
	Generic_vector* pVector = (Generic_vector*)hVector;
	ITEM* temp;
	int i;

	//if there is not enough room...then make room
	if (pVector->size >= pVector->capacity)
	{
		temp = (ITEM*) malloc(sizeof(ITEM) * 2 * pVector->capacity);
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i < pVector->size; i++)
		{
			temp[i] = pVector->data[i];
		}
		pVector->capacity *= 2;
		for (;i<pVector->capacity; i++)
		{
			temp[i] = NULL;
		}
		free(pVector->data);
		pVector->data = temp;
	}

	//Deep copy
	if (pVector->item_assignment(&(pVector->data[pVector->size]), item) == SUCCESS)
	{
		pVector->size++;
		return SUCCESS;
	}
	return FAILURE;
}

Status generic_vector_pop_back(GENERIC_VECTOR hVector)
{
	Generic_vector* pVector = (Generic_vector*)hVector;

	if (pVector->size <= 0)
	{
		return FAILURE;
	}
	pVector->item_destroy(&pVector->data[pVector->size - 1]);
	pVector->size--;
	return SUCCESS;
}

Boolean generic_vector_empty(GENERIC_VECTOR hVector)
{
	Generic_vector* pVector = (Generic_vector*)hVector;

	return (Boolean) (pVector->size == 0);
}

int generic_vector_get_size(GENERIC_VECTOR hVector)
{
	Generic_vector* pVector = (Generic_vector*)hVector;
	if (pVector == NULL)
		return 0;
	return pVector->size;
}

int generic_vector_get_capacity(GENERIC_VECTOR hVector)
{
	Generic_vector* pVector = (Generic_vector*)hVector;
	return pVector->capacity;
}

ITEM generic_vector_at(GENERIC_VECTOR hVector, int index)
{
	Generic_vector* pVector = (Generic_vector*)hVector;

	//is the element of interest out of bounds?
	if (index < 0 ||index >= pVector->size)
	{
		return NULL;
	}
	return pVector->data[index];
}

void generic_vector_destroy(GENERIC_VECTOR* phVector)
{
	Generic_vector* pVector = (Generic_vector*)*phVector;
	int i;

	for (i = 0; i < pVector->size; i++)
	{
		pVector->item_destroy(&(pVector->data[i]));
	}
	free(pVector->data);
	free(pVector);

	*phVector = NULL;
}
