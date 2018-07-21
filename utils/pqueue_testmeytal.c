#include "p_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int IntimLowtoHigh(const void *data1, const void *data2) 
{
	return (*(int*)data1 < *(int*)data2);
}

int TimesTwo(void *data, void *params)
{
	(void)params;	
	*(int*)data = *(int*)(data)*2;
	return 0;
}


int FindIsMatch(const void *data, void *params, const void *data_to_match)
{
	(void)params;	
	return (*(int*)data == *(int*)data_to_match);
}

void SimpleTest(void)
{
	
	pqueue_t *queue = NULL;
	
	queue = PQueueCreate(IntimLowtoHigh);
	printf("%d\n",PQueueSize(queue));
	assert(PQueueSize(queue) == 0);
	assert(PQueueIsEmpty(queue) == 1);
	
	PQueueDestroy(queue);
	puts("Passed Simple Test");
}

void EnqueueTest(void)
{
	pqueue_t *queue = NULL;
	int data1 = 10;
	int data2 = 20;
	int data3 = 30;
	int data4 = 40;

	queue = PQueueCreate(IntimLowtoHigh);
	assert(PQueueSize(queue) == 0);
	assert(PQueueIsEmpty(queue) == 1);
	
	/* first insert check */
	PQueueEnqueue(queue, &data3);
	assert(PQueueSize(queue) == 1);
	assert(PQueueIsEmpty(queue) == 0);
	assert(*(int*)PQueuePeek(queue) == data3);
	
	/* second insert check  */	
	PQueueEnqueue(queue, &data2);
	assert(PQueueSize(queue) == 2);
	assert(PQueueIsEmpty(queue) == 0);	
	printf("%d\n",*(int*)PQueuePeek(queue));
	assert(*(int*)PQueuePeek(queue) == data3);
	
	
	PQueueDestroy(queue);
	puts("Passed Enqueue Test");
}
void DequeueTest(void)
{
	/*create*/
	pqueue_t *queue = NULL;
	int data1 = 1;
	int data2 = 2;
	int data5 = 5;
	int data3 = 3;

	queue = PQueueCreate(IntimLowtoHigh);
	assert(PQueueSize(queue) == 0);
	assert(PQueueIsEmpty(queue) == 1);
	
	
	/*enqueue*/
	PQueueEnqueue(queue, &data3);
	/*check size changed*/
	assert(PQueueSize(queue) == 1);
	assert(PQueueIsEmpty(queue) == 0);
	
	
	/*get data*/
	assert(*(int*)PQueuePeek(queue) == data3);
	
	
	PQueueEnqueue(queue, &data2);
	/*check size changed*/
	assert(PQueueSize(queue) == 2);
	assert(PQueueIsEmpty(queue) == 0);
	
	assert(*(int*)PQueuePeek(queue) == data3);
	
	assert(*(int*)PQueueDequeue(queue) == data3);

	assert(PQueueSize(queue) == 1);
	
	assert(*(int*)PQueuePeek(queue) == data2);
	
	assert(*(int*)PQueueDequeue(queue) == data2);
	assert(PQueueSize(queue) == 0);
	assert(PQueueIsEmpty(queue) == 1);
	
		
	/*destroy*/
	PQueueDestroy(queue);
	puts("Passed Dequeue Test");


}

void ClearTest(void)
{
	/*create*/
	pqueue_t *queue = NULL;
	int data1 = 1;
	int data2 = 2;
	int data5 = 5;
	int data3 = 3;


	queue = PQueueCreate(IntimLowtoHigh);
	assert(PQueueSize(queue) == 0);
	assert(PQueueIsEmpty(queue) == 1);
	
	
	/*enqueue*/
	PQueueEnqueue(queue, &data3);
	/*check size changed*/
	assert(PQueueSize(queue) == 1);
	assert(PQueueIsEmpty(queue) == 0);
	
	
	/*get data*/
	assert(*(int*)PQueuePeek(queue) == data3);
	
	
	PQueueEnqueue(queue, &data2);
	/*check size changed*/
	assert(PQueueSize(queue) == 2);
	assert(PQueueIsEmpty(queue) == 0);
	
	assert(*(int*)PQueuePeek(queue) == data3);
	
	/*clear*/
	
	PQueueClear(queue);
	assert(PQueueSize(queue) == 0);
	assert(PQueueIsEmpty(queue) == 1);
	
	/*enqueue*/
	PQueueEnqueue(queue, &data5);
	/*check size changed*/
	assert(PQueueSize(queue) == 1);
	assert(PQueueIsEmpty(queue) == 0);
	/*clear again*/
		
	PQueueClear(queue);
	assert(PQueueSize(queue) == 0);
	assert(PQueueIsEmpty(queue) == 1);
	
	
	/*destroy*/
	PQueueDestroy(queue);
	puts("Passed Clear Test");
}

void EraseMatchingTest(void)
{
	pqueue_t *queue = NULL;
	int data1 = 10;
	int data2 = 20;
	int data3 = 30;
	int data4 = 40;


	queue = PQueueCreate(IntimLowtoHigh);
	assert(PQueueSize(queue) == 0);
	assert(PQueueIsEmpty(queue) == 1);
	
	
	/* first enqueue */
	PQueueEnqueue(queue, &data3);
	assert(PQueueSize(queue) == 1);
	assert(PQueueIsEmpty(queue) == 0);
	assert(*(int*)PQueuePeek(queue) == data3);
	
	
	PQueueEnqueue(queue, &data2);
	assert(PQueueSize(queue) == 2);
	assert(PQueueIsEmpty(queue) == 0);
	
	assert(*(int*)PQueuePeek(queue) == data3);
	
	/*enqueue more*/
	
	PQueueEnqueue(queue, &data1);
	PQueueEnqueue(queue, &data1);
	PQueueEnqueue(queue, &data4);
	/*40 30 10 10 20 */
	assert(*(int*)PQueuePeek(queue) == data4);
	assert(PQueueSize(queue) == 5);
	
	/*erase matching - data1*/
	PQueueEraseMatching(queue, FindIsMatch, NULL, &data1);
	/* pqueue is : 40 30 10 20 */  
	assert(PQueueSize(queue) == 3);
	assert(*(int*)PQueuePeek(queue) == data4);
	
	/*erase matching - nothing to find and erase*/
	
	PQueueEraseMatching(queue, FindIsMatch, NULL, &data1);
	/* pqueue is : 20 20 30 30 40 */  
	assert(PQueueSize(queue) == 2);
	assert(*(int*)PQueuePeek(queue) == data4);
	
	/*printf("%d\n",*(int*)PQueuePeek(queue));*/
	/*erase matching - find two data5*/
	PQueueEraseMatching(queue, FindIsMatch, NULL, &data4);
	/* pqueue is : 20 20 30 30*/  
	assert(PQueueSize(queue) == 1);
	/*printf("%d\n",*(int*)PQueuePeek(queue));*/
	assert(*(int*)PQueuePeek(queue) == data3);
	
	
	/*erase first one*/
	PQueueEraseMatching(queue, FindIsMatch, NULL, &data2);
	/* pqueue is : 30 30*/  
	assert(PQueueSize(queue) == 1);
	assert(*(int*)PQueuePeek(queue) == data3);
	
	/*erase last one*/
	
	PQueueEraseMatching(queue, FindIsMatch, NULL, &data3);
	/* pqueue is : empty */  
	assert(PQueueSize(queue) == 0);
	assert(PQueueIsEmpty(queue) == 1);
	
	/*nothing tEnqueueTesto erase*/
	PQueueEraseMatching(queue, FindIsMatch, NULL ,&data3);
	assert(PQueueSize(queue) == 0);
	assert(PQueueIsEmpty(queue) == 1);
	
	/*destroy*/
	PQueueDestroy(queue);
	puts("Passed Erase Matching Test");

}

int main()
{
	/*SimpleTest();
	EnqueueTest();
	DequeueTest();
	ClearTest();*/
	EraseMatchingTest();
	
	return EXIT_SUCCESS;
}
