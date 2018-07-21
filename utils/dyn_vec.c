#include <stdlib.h> /*exit success*/
#include <string.h> /*memcpy*/
#include <assert.h> /*assert*/
#include "dyn_vec.h"

/* upon creation of the vector, size is equal to capacity, updating values
 inside should only be done using GetItemAdress for efficiency. using pushback 
 will result in increasing capacity two fold*/

struct vector
{
	size_t element_size;
	size_t capacity;
	char * vector_ptr;
	char * last_ptr;
};


dyn_vec_t *DynVecCreate(size_t element_size, size_t capacity)
{
	dyn_vec_t *vector_struct = NULL; 
	assert(0 != element_size);

	vector_struct = (dyn_vec_t*)malloc(sizeof(dyn_vec_t));
	if(vector_struct == NULL)
	{
		return NULL;
	}
	vector_struct->vector_ptr = NULL; /*if capacity is zero, vector _ptr points to NULL and will be allocated when pushing or reserving.*/
	
	if(0 < capacity)
	{
		vector_struct->vector_ptr = (char*)malloc(capacity * element_size);
		if(vector_struct->vector_ptr == NULL)
		{
			return NULL;
		}
	}
		
	vector_struct->element_size = element_size;
	vector_struct->capacity = capacity;

	vector_struct->last_ptr = vector_struct->vector_ptr + (element_size * capacity);
	return vector_struct; 

}

void DynVecDestroy(dyn_vec_t *vector)
{
	assert(vector);
	free(vector->vector_ptr);
	vector->vector_ptr = NULL;
	free(vector);

}

size_t DynVecSize(const dyn_vec_t *vector)
{
	assert(NULL != vector);	
	return ((vector->last_ptr - vector->vector_ptr) / vector->element_size);
}

size_t DynCapacity(const dyn_vec_t *vector)
{
	assert(NULL != vector);
	return vector->capacity;
}

int DynVecReserve(dyn_vec_t *vector, size_t capacity)
{
	size_t el_num = DynVecSize(vector); /*essential for when user calls function and capacity != el_num like in pushback*/ 
	assert(NULL != vector);	
	if (capacity > vector->capacity)
	{
	
		vector->vector_ptr = (char*)realloc(vector->vector_ptr, (capacity * vector->element_size));
		
		if(vector->vector_ptr == NULL)
		{
			return 1;
		}
		vector->last_ptr = vector->vector_ptr + (el_num * vector->element_size);
		vector->capacity = capacity;
	}
	return 0;
}


int DynVecPushBack(dyn_vec_t *vector, const void *data)
{
	int result = 0;
	assert(NULL != data);
	assert(NULL != vector);
	
	if(DynVecSize(vector) == vector->capacity)
	{
		if (0 == vector->capacity) 
		{
			++vector->capacity;
		}
		result = DynVecReserve(vector, (vector->capacity * 2));
		
	}
	memcpy(vector->last_ptr , data, vector->element_size);
	vector->last_ptr += vector->element_size;
	return result;

}

void DynVecPopBack(dyn_vec_t *vector)
{
	assert(NULL != vector);
	vector->last_ptr -= vector->element_size;
}

void *DynVecGetItemAddress(const dyn_vec_t *vector, size_t index)
{
	assert(NULL != vector);	
	return (vector->vector_ptr + (index * vector->element_size));
}	

