#include "p_queue.h" /*for pqueue*/

#include <stdlib.h>	 /*for malloc*/
#include <assert.h>  /*for assert*/

struct  pqueue
{
	sorted_list_t *sorted_list;
};



pqueue_t* PQueueCreate(p_queue_is_before_t is_smaller)
{	
	pqueue_t *new_queue = (pqueue_t *)malloc(sizeof(*new_queue));/* change to *new_peueueq*/
	sorted_list_t *new_sorted_list = NULL;
	if (new_queue == NULL)
	{
		return NULL;
	}
	
	new_sorted_list = SortedListCreate(is_smaller);
	if (new_sorted_list == NULL)
	{
		free(new_queue);
		return NULL;
	}
	new_queue->sorted_list = new_sorted_list;
	
	return new_queue;
}



void PQueueDestroy(pqueue_t *pqueue)
{
	assert(pqueue != NULL);
	assert(pqueue->sorted_list != NULL);
	
	SortedListDestroy(pqueue->sorted_list);
	free(pqueue);
}


int PQueueIsEmpty(pqueue_t *pqueue)
{
	assert(pqueue != NULL);
	assert(pqueue->sorted_list != NULL);
	
	return SortedListIsEmpty(pqueue->sorted_list);
}


size_t PQueueSize(pqueue_t *pqueue)
{
	assert(pqueue != NULL);
	assert(pqueue->sorted_list != NULL);
	
	return SortedListSize(pqueue->sorted_list);
}


int PQueueEnqueue(pqueue_t *pqueue, void *data)
{
	sorted_list_iter_t iter1 = {0};
	
	assert(pqueue != NULL);
	assert(pqueue->sorted_list != NULL);
	
	iter1 = SortedListInsert(pqueue->sorted_list, data);
	return (SortedListIsSameIterator(iter1, SortedListEnd(pqueue->sorted_list)));
}

void* PQueueDequeue(pqueue_t *pqueue)
{	
	assert(pqueue != NULL);
	assert(pqueue->sorted_list != NULL);
	
	return SortedListPopFront(pqueue->sorted_list);
/*retrns data*/

}
	
void* PQueuePeek(pqueue_t *pqueue)
{
	assert(pqueue != NULL);
	assert(pqueue->sorted_list != NULL);
		
	return SortedListGetData(SortedListBegin(pqueue->sorted_list));
}
	

void PQueueClear(pqueue_t *pqueue)
{
	sorted_list_iter_t iterator = {NULL}; 
	
	assert(pqueue != NULL);
	assert(pqueue->sorted_list != NULL);	
	
	iterator = SortedListBegin(pqueue->sorted_list);
	
	while(!SortedListIsEmpty(pqueue->sorted_list))
	{
		iterator = SortedListErase(iterator);	
	}
}

void *PQueueEraseMatching(pqueue_t *pqueue, p_queue_is_match_t is_match, void *params, void *data_to_match) /*assert*/
{	
	
	sorted_list_iter_t to = {NULL};
	sorted_list_iter_t from = {NULL};
	sorted_list_iter_t find_to_remove = {NULL};
	void *data_to_return = NULL;

	
	assert(pqueue != NULL);
	assert(pqueue->sorted_list != NULL);	
	assert(is_match != NULL);
	
	to = SortedListEnd(pqueue->sorted_list);
	from = SortedListBegin(pqueue->sorted_list);
	find_to_remove = SortedListFind(from, to, is_match, params, data_to_match);
	
	while(!SortedListIsSameIterator(find_to_remove, to))
	{	
		data_to_return = SortedListGetData(find_to_remove);
		from = SortedListErase(find_to_remove);
		to = SortedListEnd(pqueue->sorted_list);
		find_to_remove = SortedListFind(from, to, is_match, params, data_to_match);
	}
	return data_to_return;
	
}

	
	
	
