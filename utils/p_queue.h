#ifndef P_QUEUE_H
#define P_QUEUE_H
#include "sorted_list.h"/*for sorted_list functions*/
typedef struct  pqueue pqueue_t;
typedef int (*p_queue_is_before_t)(void *data1, void *data2);
typedef int (*p_queue_is_match_t)(const void *data, void *params, const void *data_to_match);

pqueue_t* PQueueCreate(p_queue_is_before_t is_smaller);

void PQueueDestroy(pqueue_t *pqueue);

int PQueueEnqueue(pqueue_t *pqueue, void *data);

void *PQueueDequeue(pqueue_t *pqueue); /*returns data*/

void *PQueuePeek(pqueue_t *pqueue);

int PQueueIsEmpty(pqueue_t *pqueue);

size_t PQueueSize(pqueue_t *pqueue);

void PQueueClear(pqueue_t *pqueue);


 /*returns pointer to first found data, null if not found*/
void *PQueueEraseMatching(pqueue_t *pqueue, p_queue_is_match_t is_match, void *params, void *data_to_match);
 


#endif
