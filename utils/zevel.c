#include "p_queue.h" /*for pqueue*/
#include "dyn_vec.h"
#include "heap.h"
#include <stdlib.h>	 /*for malloc*/
#include <assert.h>  /*for assert*/
#include <string.h>

struct  pqueue
{
	dyn_vec_t *vector;
	size_t elem_size;
	size_t nmemb;
	p_queue_is_before_t is_before;
	/*int (*is_before)(const void *data1, const void *data2);*/
};

typedef struct func_container
{
    p_queue_is_before_t is_before;
    
}func_container_t;

static int IsBeforeWrapper(const void *data1, const void *data2, void *param)
{	
	func_container_t *func_container = NULL;
    void **auxdata1 = (void **)data1;
    void **auxdata2 = (void **)data2;
    assert (NULL != data1);
    assert (NULL != data2);
    assert (NULL != param);       
     
    func_container = param;
    
	return func_container->is_before((void*)data1,(void*)data2);
}

pqueue_t* PQueueCreate(p_queue_is_before_t is_smaller)
{	
	dyn_vec_t *vector = NULL;
	pqueue_t *new_queue = (pqueue_t *)malloc(sizeof(*new_queue));
	if (new_queue == NULL)
	{
		return NULL;
	}
	
	vector = DynVecCreate(sizeof(void*), 0);
	if(NULL == vector)
	{
		free(new_queue);
		return NULL;
	}
	
	new_queue->vector = vector;
	new_queue->elem_size = sizeof(void*);
	new_queue->nmemb = 0;
	new_queue->is_before = is_smaller;
	
	return new_queue;
}


void PQueueDestroy(pqueue_t *pqueue)
{
	assert(pqueue != NULL);
	assert(pqueue->vector != NULL);
	
	DynVecDestroy(pqueue->vector);
	free(pqueue);
}


int PQueueIsEmpty(pqueue_t *pqueue)
{
	assert(pqueue != NULL);
	
	return (pqueue->nmemb == 0);
}


size_t PQueueSize(pqueue_t *pqueue)
{
	assert(pqueue != NULL);
	
	return (pqueue->nmemb);
}


int PQueueEnqueue(pqueue_t *pqueue, void *data)
{
	int result = 0;
    func_container_t func_container = {0};
    void *array = NULL;
    
	assert(pqueue != NULL);
	assert(pqueue->vector != NULL);
	
	func_container.is_before = pqueue->is_before;
	result = DynVecPushBack(pqueue->vector, data);
	
	if(result)
	{
		return result;
	}
	
	++pqueue->nmemb;
	
	array = DynVecGetItemAddress(pqueue->vector, 0);
	
	if(pqueue->nmemb > 1)
	{
		HeapifyUp(array, pqueue->nmemb, pqueue->elem_size, IsBeforeWrapper,  &func_container);
	}
	
	return result;
}
static void Swap(void *front, void *back, size_t elem_size)
{
	void *temp = malloc(elem_size);
	memcpy(temp, front, elem_size);
	memcpy(front, back , elem_size);
	memcpy(back, temp, elem_size);
	free(temp);
}

static void *Remove(pqueue_t *pqueue, size_t index)
{
	void *front = NULL;
	void *back = NULL;
	void *data_to_return = NULL;
	func_container_t func_container = {0};
	void *array = NULL;
	
	assert(pqueue != NULL);
	assert(pqueue->vector != NULL); 
	
	func_container.is_before = pqueue->is_before;
	array = DynVecGetItemAddress(pqueue->vector, 0);
	front = DynVecGetItemAddress(pqueue->vector, index);
	back = DynVecGetItemAddress(pqueue->vector, pqueue->nmemb-1);
	/*save data*/
	data_to_return = *(void**)front;
	
	/*swap front and back*/
	Swap(front, back, pqueue->elem_size);
	/*pop back*/
	DynVecPopBack(pqueue->vector);
	--pqueue->nmemb;
	/*heapify down*/
	HeapifyDown(array, pqueue->nmemb, pqueue->elem_size, index, IsBeforeWrapper, &func_container);
/*retrns data*/
	return data_to_return;
}


void *PQueueDequeue(pqueue_t *pqueue)
{	
	return Remove(pqueue, 0);
}
	
void *PQueuePeek(pqueue_t *pqueue)
{
	assert(pqueue != NULL);
	assert(pqueue->vector != NULL);
	return DynVecGetItemAddress(pqueue->vector, 0);
}
	

void PQueueClear(pqueue_t *pqueue)
{
	assert(pqueue != NULL);
	assert(pqueue->vector != NULL);	
	while (!PQueueIsEmpty(pqueue))
	{
		PQueueDequeue(pqueue);
	}
}

void *PQueueEraseMatching(pqueue_t *pqueue, p_queue_is_match_t is_match, void *params, void *data_to_match) 
{	
	void *data_to_return = NULL;
	void *current_data = NULL;
	size_t i = 0;
	
	assert(pqueue != NULL);
	assert(pqueue->vector != NULL);	
	assert(is_match != NULL);
	
	for(i = 0 ; i < pqueue->nmemb ; ++i)
	{
		current_data = *(void**)DynVecGetItemAddress(pqueue->vector, i);
		if(is_match(current_data, params, data_to_match))
		{
			return Remove(pqueue, i);
		}
	}
	return data_to_return;
}

	
	
	
