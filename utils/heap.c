#include "heap.h"
#include <stdlib.h> /* malloc*/
#include <string.h> /* memcpy*/
#include <assert.h>


static int GetParentIndex(void *arr, void *child, size_t elem_size)
{
	assert(arr);
	assert(child);
	
	return (((((char*)arr - (char*)child)/elem_size) - 1)/2);
}

static int GetLeftChildIndex(void *arr, void *parent, size_t elem_size)
{
	assert(arr);
	assert(parent);
	
	return (((((char*)parent - (char*)arr)/elem_size) * 2) + 1);
}

static int GetRightChildIndex(void *arr, void *parent, size_t elem_size)
{
	assert(arr);
	assert(parent);
	
	return (((((char*)parent - (char*)arr)/elem_size) * 2) + 2);
}

static void Swap(void *data1, void *data2, size_t elem_size)
{
	void *temp = malloc(elem_size);
	memcpy(temp, data1, elem_size);
	memcpy(data1, data2 , elem_size);
	memcpy(data2, temp, elem_size);
	free(temp);
}	

void HeapifyUp(void *arr, size_t nmemb, size_t elem_size, 
				int (*is_before)(const void *data1, const void *data2, void *param), void *param)
{
	/*after insert, assume the array is sorted except for the last item*/
	void *current_child = (char*)arr + (nmemb - 1) * elem_size;
	
	/*make sure that child is not the root*/
	void *current_parent = (char*)current_child + elem_size * GetParentIndex(arr, current_child, elem_size);
	
	
	while(current_parent >= arr && is_before(current_child, current_parent, param))/* is before: data1 below data2 in the tree*/
	{
		Swap(current_child, current_parent,elem_size); 
		
		current_child = current_parent;
		
		current_parent = (char*)current_parent + elem_size * GetParentIndex(arr, current_parent, elem_size);

	}
		
}
static void *GetMax(void *arr, int left_index, int right_index ,size_t elem_size,
	 size_t	nmemb, 	int (*is_before)(const void *data1, const void *data2, void *param), void *param)
{
/*assert*/
	
	int last_index = nmemb - 1;
	void *left = (char*)arr + left_index * elem_size;
	void *right = (char*)arr + right_index * elem_size;
	
	if(left_index > last_index)
	{
		return NULL;
	}
	if(right_index > last_index)
	{
		return left;
	}	
	
	if(is_before(right, left, param))
	{
		return right;
	}
	return left;
}

void HeapifyDown (void *arr, size_t nmemb, size_t elem_size, size_t idx, 
				int (*is_before)(const void *data1, const void *data2, void *param), 					void *param)
{
	/*after remove, assume the array is sorted except for the idx that has been removed and swapped with the last item*/
	void *current_parent = NULL;
	int current_left_child = 0, current_right_child = 0;
	void *max_child = NULL;
	
	assert(arr);
	assert(is_before);
	
	current_parent = (char*)arr + idx * elem_size;
	current_left_child = GetLeftChildIndex(arr, current_parent, elem_size);
	current_right_child = GetRightChildIndex(arr, current_parent, elem_size);
	max_child = GetMax(arr, current_left_child, current_right_child ,elem_size, 
		nmemb, is_before, param);
	
	while(max_child != NULL)
	{
		if(is_before(max_child,current_parent, param))
		{
			Swap(current_parent, max_child, elem_size);
			current_parent = max_child;
			current_left_child = GetLeftChildIndex(arr, current_parent, elem_size);
			current_right_child = GetRightChildIndex(arr, current_parent, elem_size);
			max_child = GetMax(arr, current_left_child, current_right_child, 
				elem_size, nmemb, is_before, param);
		}
		else
		{
			break;
		}
	}
}



