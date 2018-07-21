#include "heap.h"


static void Swap(char *ch1, char *ch2, size_t elem_size)
{
	char tmp = 0;
	size_t i = 0;

	for (i = 0; i < elem_size; ++i)
	{
		tmp = ch1[i];
		ch1[i] = ch2[i];
		ch2[i] = tmp;
	}
}

/************************************************************************/

void HeapifyUp(
	void *arr,
	size_t nmemb, 
	size_t elem_size, 
	int (*is_before)(const void* data1, const void* data2, void *param),
	void *param)
{
	int curr_idx = nmemb - 1;
	int parent_idx = (curr_idx - 1) / 2;

	if (nmemb < 2)
	{
		return;
	}

	while ((curr_idx != parent_idx) &&
	       (1 != is_before((((char *)arr) + (curr_idx * elem_size)),
 	                       (((char *)arr) + (parent_idx * elem_size)),
	                       param)))
	{
		Swap((((char *)arr) + (curr_idx * elem_size)),
		     (((char *)arr) + (parent_idx * elem_size)),
			 elem_size);

		curr_idx = parent_idx;

		parent_idx = (curr_idx - 1) / 2;	
	}

}

/************************************************************************/

static int MaxSonIdx(
	int curr_idx, 
	void *arr, 
	size_t nmemb, 
	size_t elem_size,
	int (*is_before)(const void* data1, const void* data2, void *param),
	void *param)
{
	int right_son_idx = (2 * curr_idx) + 2; 
	int left_son_idx = (2 * curr_idx) + 1;

	if ((right_son_idx > (int)(nmemb - 1)) ||
		(1 == is_before(((char *)arr + (right_son_idx * elem_size)),
                        ((char *)arr + (left_son_idx * elem_size)),
	                    param)))
	{
		return (left_son_idx);
	}

	return (right_son_idx);
}

/************************************************************************/

void HeapifyDown(
	void *arr, 
	size_t nmemb, 
	size_t elem_size, 
	size_t idx,
	int (*is_before)(const void *data1, const void *data2, void *param),
	void *param)
{
	int curr_idx = idx;
	int max_son_idx = MaxSonIdx(curr_idx, arr, nmemb, elem_size, is_before, param);

	while ((max_son_idx <= (int)(nmemb - 1)) &&
		   (1 == is_before(((char *)arr + (curr_idx * elem_size)),
                           ((char *)arr + (max_son_idx * elem_size)),
	                       param)))
	{
		Swap(((char *)arr + (curr_idx * elem_size)),
		      ((char *)arr + (max_son_idx * elem_size)), 
		      elem_size);

		curr_idx = max_son_idx;

		max_son_idx = MaxSonIdx(curr_idx, arr, nmemb, elem_size, is_before, param);	
	}
}

/************************************************************************/







