#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "slist.h"
#include "queue.h"

struct queue
{
    sl_node_t *head;
    sl_node_t *tail;
};

queue_t *QueueCreate (void) /*returns pointer to queue*/
{
    queue_t *queue = (queue_t*)malloc(sizeof(queue_t));
    sl_node_t *stub = NULL; 
   
    if(NULL == queue)
    {
        return NULL;
    }
	
	stub = SListCreateNode(NULL, NULL);

    queue->head = stub;
    queue->tail = stub;
    
    return queue;
}

void QueueDestroy (queue_t *queue)
{
    SListFreeAll(queue->head);
    free(queue);
    
}

size_t QueueSize (const queue_t *queue) /* returns number of elements of queue*/
{
    return SListCount(queue->head) -1 ;
}

int QueueIsEmpty (const queue_t *queue) /*returns 0 - not empty 1 - empty*/
{
    return (queue->head == queue->tail);
}

int QueueEnqueue (queue_t *queue, void *data) /*returns 0 - success 1 - failure*/
{
   	sl_node_t *new_node = NULL;
	new_node = SListCreateNode(NULL, data);
    
    if(new_node == NULL)
    {
    	return 1;
    }
    queue->tail->next = new_node;
    queue->tail = new_node;
    
    return 0;
}

void *QueueDequeue (queue_t *queue) /* returns data of the dequeued memeber*/
{
	sl_node_t *to_remove = NULL;
    void *data = NULL;
    sl_node_t *new_head = NULL;
    
    if(queue->head->next == NULL)
    {
    	return NULL;
    }

    to_remove = queue->head->next;
    data = queue->head->next->data;
    new_head = to_remove->next;
    
    free(to_remove);
    
    to_remove = NULL;
    
    queue->head->next = new_head;
    
    if(new_head == NULL)
    {
		queue->tail = queue->head;
    }
    
    return data;
}

void *QueuePeek (const queue_t *queue)	/*returns data of the top member*/
{
    void *data = queue->head->next->data;
    return data;
}

void QueueAppend(queue_t *dest, queue_t *src)  
{
	
   	dest->tail->next = src->head->next;
   	dest->tail = src->tail;
   	src->head->next = NULL;

}



