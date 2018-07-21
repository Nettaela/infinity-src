#include "p_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void UnitestBasic(void);
void UnitestEnqueue(void);
void UnitestDequeue(void);
void Unitestclear(void);
void UnitestEraseMatching(void);

int IntimLowtoHigh(void *data1, void *data2); /*sorting function*/
int TimesTwo(void *data, void *params);		  /*for use in for each*/
int FindIsMatch(const void *data, void *params, const void *data_to_match); /*find*/


int main()
{

	UnitestBasic();
	UnitestEnqueue();
	UnitestDequeue();
	Unitestclear();
	UnitestEraseMatching();

	return EXIT_SUCCESS;
}

void UnitestBasic(void)
{
	
	/*testing create, size and is empty*/
	pqueue_t *my_queue = NULL;
	
	printf("basic test...");
	my_queue = PQueueCreate(IntimLowtoHigh);
	assert(PQueueSize(my_queue) == 0);
	assert(PQueueIsEmpty(my_queue) == 1);
	
	/*test destroy*/
	PQueueDestroy(my_queue);
	puts("passed");

}
void UnitestEnqueue(void)
{
	/*create*/
	pqueue_t *my_queue = NULL;
	int data1 = 1;
	int data2 = 
	2;
	int data5 = 5;
	int data3 = 3;
	printf("enqueue test...");

	my_queue = PQueueCreate(IntimLowtoHigh);
	assert(PQueueSize(my_queue) == 0);
	assert(PQueueIsEmpty(my_queue) == 1);
	
	
	/*enqueue*/
	PQueueEnqueue(my_queue, &data3);
	/*check size changed*/
	assert(PQueueSize(my_queue) == 1);
	assert(PQueueIsEmpty(my_queue) == 0);
	

	/*get data*/
	assert(*(int*)PQueuePeek(my_queue) == data3);

	
	PQueueEnqueue(my_queue, &data2);
	/*check size changed*/
	assert(PQueueSize(my_queue) == 2);
	assert(PQueueIsEmpty(my_queue) == 0);

	assert(*(int*)PQueuePeek(my_queue) == data2);

	/*destroy*/
	PQueueDestroy(my_queue);
	puts("passed");
}


void UnitestDequeue(void)
{
	/*create*/
	pqueue_t *my_queue = NULL;
	int data1 = 1;
	int data2 = 2;
	int data5 = 5;
	int data3 = 3;
	printf("dequeue test...");

	my_queue = PQueueCreate(IntimLowtoHigh);
	assert(PQueueSize(my_queue) == 0);
	assert(PQueueIsEmpty(my_queue) == 1);
	
	
	/*enqueue*/
	PQueueEnqueue(my_queue, &data3);
	/*check size changed*/
	assert(PQueueSize(my_queue) == 1);
	assert(PQueueIsEmpty(my_queue) == 0);
	
	
	/*get data*/
	assert(*(int*)PQueuePeek(my_queue) == data3);
	
	
	PQueueEnqueue(my_queue, &data2);
	/*check size changed*/
	assert(PQueueSize(my_queue) == 2);
	assert(PQueueIsEmpty(my_queue) == 0);
	
	assert(*(int*)PQueuePeek(my_queue) == data2);
	
	assert(*(int*)PQueueDequeue(my_queue) == data2);

	assert(PQueueSize(my_queue) == 1);
	
	assert(*(int*)PQueuePeek(my_queue) == data3);
	
	assert(*(int*)PQueueDequeue(my_queue) == data3);
	assert(PQueueSize(my_queue) == 0);
	assert(PQueueIsEmpty(my_queue) == 1);
	
		
	/*destroy*/
	PQueueDestroy(my_queue);
	puts("passed");


}

void Unitestclear(void)
{

	/*create*/
	pqueue_t *my_queue = NULL;
	int data1 = 1;
	int data2 = 2;
	int data5 = 5;
	int data3 = 3;
	printf("clear test...");
	my_queue = PQueueCreate(IntimLowtoHigh);
	assert(PQueueSize(my_queue) == 0);
	assert(PQueueIsEmpty(my_queue) == 1);
	
	
	/*enqueue*/
	PQueueEnqueue(my_queue, &data3);
	/*check size changed*/
	assert(PQueueSize(my_queue) == 1);
	assert(PQueueIsEmpty(my_queue) == 0);
	
	
	/*get data*/
	assert(*(int*)PQueuePeek(my_queue) == data3);
	
	
	PQueueEnqueue(my_queue, &data2);
	/*check size changed*/
	assert(PQueueSize(my_queue) == 2);
	assert(PQueueIsEmpty(my_queue) == 0);
	
	assert(*(int*)PQueuePeek(my_queue) == data2);
	
	/*clear*/
	
	PQueueClear(my_queue);
	assert(PQueueSize(my_queue) == 0);
	assert(PQueueIsEmpty(my_queue) == 1);
	
	/*enqueue*/
	PQueueEnqueue(my_queue, &data5);
	/*check size changed*/
	assert(PQueueSize(my_queue) == 1);
	assert(PQueueIsEmpty(my_queue) == 0);
	/*clear again*/
		
	PQueueClear(my_queue);
	assert(PQueueSize(my_queue) == 0);
	assert(PQueueIsEmpty(my_queue) == 1);
	
	
	/*destroy*/
	PQueueDestroy(my_queue);
	puts("passed");


}

void UnitestEraseMatching(void)
{

	pqueue_t *my_queue = NULL;
	int data1 = 1;
	int data2 = 2;
	int data5 = 5;
	int data3 = 3;
	int data_to_match = 1;
	printf("erase matching test...");


	my_queue = PQueueCreate(IntimLowtoHigh);
	assert(PQueueSize(my_queue) == 0);
	assert(PQueueIsEmpty(my_queue) == 1);
	
	
	/*enqueue*/
	PQueueEnqueue(my_queue, &data3);
	/*check size changed*/
	assert(PQueueSize(my_queue) == 1);
	assert(PQueueIsEmpty(my_queue) == 0);
	assert(*(int*)PQueuePeek(my_queue) == data3);
	
	
	PQueueEnqueue(my_queue, &data2);
	/*check size changed*/
	assert(PQueueSize(my_queue) == 2);
	assert(PQueueIsEmpty(my_queue) == 0);
	
	assert(*(int*)PQueuePeek(my_queue) == data2);
	
	/*enqueue more*/
	
	PQueueEnqueue(my_queue, &data5);
	PQueueEnqueue(my_queue, &data5);
	PQueueEnqueue(my_queue, &data1);
	assert(*(int*)PQueuePeek(my_queue) == data1);
	assert(PQueueSize(my_queue) == 5);
	
	/*assert(data1 == *(int*)PQueueDequeue(my_queue));
	assert(*(int*)PQueuePeek(my_queue) == data2);
	
	
	
	puts("-----");*/
	
	/*erase matching - data1*/
	PQueueEraseMatching(my_queue, FindIsMatch, &data1, &data_to_match);
	
	printf("%d\n", *(int*)PQueuePeek(my_queue));
	
	assert(PQueueSize(my_queue) == 4);
	assert(*(int*)PQueuePeek(my_queue) == data2);
	
	/*erase matching - nothing to find and erase*/
	
	PQueueEraseMatching(my_queue, FindIsMatch, &data1, &data_to_match);

	
	assert(PQueueSize(my_queue) == 4);
	assert(*(int*)PQueuePeek(my_queue) == data2);
	
	
	/*erase matching - find two data5*/
	PQueueEraseMatching(my_queue, FindIsMatch, &data5, &data_to_match);
	assert(PQueueSize(my_queue) == 2);
	assert(*(int*)PQueuePeek(my_queue) == data2);
	
	
	/*erase first one*/
	PQueueEraseMatching(my_queue, FindIsMatch, &data2, &data_to_match);
	assert(PQueueSize(my_queue) == 1);
	assert(*(int*)PQueuePeek(my_queue) == data3);
	
	/*erase last one*/
	
	PQueueEraseMatching(my_queue, FindIsMatch, &data3, &data_to_match);
	assert(PQueueSize(my_queue) == 0);
	assert(PQueueIsEmpty(my_queue) == 1);
	
	/*nothing to erase*/
	PQueueEraseMatching(my_queue, FindIsMatch, &data3, &data_to_match);
	assert(PQueueSize(my_queue) == 0);
	assert(PQueueIsEmpty(my_queue) == 1);
	
	/*destroy*/
	PQueueDestroy(my_queue);
	puts("passed");


}
int IntimHighToLow(void *data1, void *data2) 
{
	return (*(int*)data1 > *(int*)data2);
}


int IntimLowtoHigh(void *data1, void *data2) 
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
	(void)data_to_match;	
	return (*(int*)data == *(int*)params);
}

