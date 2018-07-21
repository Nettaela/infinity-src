#include "heap.h"
#include "dyn_vec.h"
#include "p_queue.h"
#include "my_decs.h"

#include <stdlib.h>
#include <assert.h>

int IsBeforHeap(const void *data1, const void *data2, void *param);

struct pqueue
{
	dyn_vec_t *heap;   
	p_queue_is_before_t is_before;
	size_t num_elements;
	size_t elem_size;	
};


pqueue_t *PQueueCreate(p_queue_is_before_t is_before)
{
	pqueue_t *pqueue = NULL;
	
	assert (is_before != NULL);
	
	pqueue = (pqueue_t*)malloc(sizeof(*pqueue));
	if (NULL == pqueue)
	{
		return NULL;
	}
	
	pqueue->heap = DynVecCreate(VOID_PTR_SIZE, 0);	/*capacity is 0!!!!!!!*/
	if (NULL == pqueue->heap)
	{
		free(pqueue);
		return NULL;
	}
	
	pqueue->is_before = is_before;
	pqueue->num_elements = 0;
	pqueue->elem_size = VOID_PTR_SIZE;
	
	return pqueue;
}



void PQueueDestroy(pqueue_t *pqueue)
{
	assert (pqueue != NULL);
	assert (pqueue->heap != NULL);
	
	DynVecDestroy(pqueue->heap);
	free(pqueue);
}


int PQueueIsEmpty(pqueue_t *pqueue)
{
	assert (pqueue != NULL);
	assert (pqueue->heap != NULL);

	return (pqueue->num_elements == 0);
}


size_t PQueueSize(pqueue_t *pqueue)
{
	assert (pqueue != NULL);
	assert (pqueue->heap != NULL);
	
	return pqueue->num_elements;
}


void* PQueuePeek(pqueue_t *pqueue)
{
	assert (pqueue != NULL);
	assert (pqueue->heap != NULL);

	return *(void**)DynVecGetItemAddress(pqueue->heap, 0);
}

/*array of void pointers*/
int PQueueEnqueue(pqueue_t *pqueue, void *data)
{
	int insert_status = 0;
	void *arr = NULL;
	
	assert (pqueue != NULL);
	assert (pqueue->heap != NULL);
	
	insert_status = DynVecPushBack(pqueue->heap, &data);
	++pqueue->num_elements;
	
	if (1 == PQueueSize(pqueue))
	{
		return insert_status;
	}
	
	arr = DynVecGetItemAddress(pqueue->heap, 0);
	
	HeapifyUp(arr, pqueue->num_elements, pqueue->elem_size, IsBeforHeap,
	 *(void**)&pqueue->is_before);
	
	
	return insert_status;
}


void* PQueueDequeue(pqueue_t *pqueue)
{
	void *data_removed = NULL;
	void *arr = NULL;

	assert (pqueue != NULL);
	assert (pqueue->heap != NULL);
	
	if (PQueueIsEmpty(pqueue))
	{
		return NULL;
	}
	
	data_removed = *(void **)DynVecGetItemAddress(pqueue->heap, 0);
	
	if (1 == PQueueSize(pqueue))
	{
		DynVecPopBack(pqueue->heap);
		--pqueue->num_elements;
		return data_removed;
	}
	
	SwapVoidPtr(DynVecGetItemAddress(pqueue->heap, 0), 
				DynVecGetItemAddress(pqueue->heap, pqueue->num_elements - 1));
	
	
	DynVecPopBack(pqueue->heap);
	--pqueue->num_elements;
	arr = DynVecGetItemAddress(pqueue->heap, 0);
	
	HeapifyDown(arr, pqueue->num_elements, pqueue->elem_size, 0, IsBeforHeap, 
													*(void**)&pqueue->is_before);
	
	return data_removed;
}


void PQueueClear(pqueue_t *pqueue)
{
	assert (pqueue != NULL);
	assert (pqueue->heap != NULL);
	
	while (!PQueueIsEmpty(pqueue))/*CR - u could save a function call if u compare with num of elem != 0... but this is not so critical in my opinion*/
	{
		DynVecPopBack(pqueue->heap);
		--pqueue->num_elements;
	}
}


void *PQueueEraseMatching(pqueue_t *pqueue, p_queue_is_match_t is_match,
								void *params, void *data_to_match)
{
	void *data_to_find = NULL;
	void *current = NULL;
	void *arr = NULL;
	size_t index = 0;
	int result = 0;
	
	(void)params;
	assert (pqueue != NULL);
	assert (pqueue->heap != NULL);
	/*CR - assert is match?*/
	
	if (PQueueIsEmpty(pqueue))
	{
		return NULL;
	}
	
	while (index <= (pqueue->num_elements - 1) && !PQueueIsEmpty(pqueue))
	{
		current = *(void **)DynVecGetItemAddress(pqueue->heap, index);
		result = is_match(data_to_match, NULL, current);
		if (1 == result)
		{
			data_to_find = current;
			SwapVoidPtr(DynVecGetItemAddress(pqueue->heap, index), 
				DynVecGetItemAddress(pqueue->heap, pqueue->num_elements - 1));
				
			DynVecPopBack(pqueue->heap);
			--pqueue->num_elements;
			arr = DynVecGetItemAddress(pqueue->heap, 0);/*CR since this doesnt change ever, i should save it as a variable in the begining. calling the function each time is redundant*/
			
			HeapifyDown(arr, pqueue->num_elements, pqueue->elem_size, index,
								IsBeforHeap, *(void**)&pqueue->is_before);	
								/*CR - this code is repeated in dequeue, u should use 1 function for both*/
		
		}
		else 
		{
			++index;
		}
	
	}
/*after erasing the index is not the same caues we have less elements!!!!!!!!!!!*/

	return data_to_find;


}



