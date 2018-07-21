#include <stdlib.h>/*for size_t*/
#include <string.h>/*for memcpy*/
#include <assert.h>/*for assert*/
#include <stdio.h>/*printf*/
#include "queue.h"/*for queue functions*/

void Unitest(void);


int main()
{
	Unitest();
	return EXIT_SUCCESS;

}

void Unitest(void)
{
	int data1 = 3;
	int data2 = 23;
	int data3 = 423;
	int data4 = 5432;
	
	queue_t *new_queue =  QueueCreate();
	queue_t *new_queue2 =  QueueCreate();
	assert(QueueIsEmpty(new_queue) == 1);
	assert(QueueSize(new_queue) == 0);
	assert(QueueIsEmpty(new_queue2) == 1);
	assert(QueueSize(new_queue2) == 0);
	
	QueueEnqueue (new_queue, &data1);
	assert(QueueIsEmpty(new_queue) == 0);
	assert(QueueSize(new_queue) == 1);
	assert(*(int*)QueuePeek(new_queue) == data1);	
	
	QueueEnqueue (new_queue, &data2);
	assert(QueueIsEmpty(new_queue) == 0);
	assert(QueueSize(new_queue) == 2);
	assert(*(int*)QueuePeek(new_queue) == data1);
	
	assert(*(int*)QueueDequeue(new_queue) == data1); /* returns data of the dequeued memeber*/
	assert(QueueIsEmpty(new_queue) == 0);
	assert(QueueSize(new_queue) == 1);
	assert(*(int*)QueuePeek(new_queue) == data2);
	
	QueueEnqueue (new_queue2, &data3);
	assert(QueueIsEmpty(new_queue2) == 0);
	assert(QueueSize(new_queue2) == 1);
	assert(*(int*)QueuePeek(new_queue2) == data3);	
	
	QueueAppend(new_queue2,new_queue);
	assert(QueueSize(new_queue2) == 2);
	assert(*(int*)QueuePeek(new_queue2) == data3);	
	
	
	QueueDestroy(new_queue);
	QueueDestroy(new_queue2);
	puts("u passed, check valgrind");
	



}
