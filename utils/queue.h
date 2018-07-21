#ifndef QUEUE_H
#define QUEUE_H
typedef struct queue queue_t;

queue_t *QueueCreate (void); /*returns pointer to queue*/
void QueueDestroy (queue_t *queue); 
size_t QueueSize (const queue_t *queue); /* returns number of elements of queue*/
int QueueIsEmpty (const queue_t *queue); /*returns 0 - not empty 1 - empty*/
int QueueEnqueue (queue_t *queue, void *data); /*returns 0 - success 1 - failure*/
void *QueueDequeue (queue_t *queue); /* returns data of the dequeued memeber*/
void *QueuePeek (const queue_t *queue);	/*returns data of the top member*/
void QueueAppend(queue_t *dest, queue_t *src);

#endif

