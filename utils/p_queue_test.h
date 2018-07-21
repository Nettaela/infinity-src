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
void UnitestInsert(void)
{
	/*create*/
	pqueue_t *my_queue = NULL;
	int data1 = 1;
	int data2 = 2;
	int data5 = 5;
	int data3 = 3;
	printf("enqueue test...");

	my_queue = PQueueCreate(IntimLowtoHigh);
	assert(PQueueSize(my_queue) == 0);
	assert(PQueueIsEmpty(my_queue) == 1);
	
	
	/*enqueue*/
	PQueueEnqueue(my_queue, &data1);
	/*check size changed*/
	assert(PQueueSize(my_queue) == 1);
	assert(PQueueIsEmpty(my_queue) == 0);
	
	
	/*get data*/
	assert(*(int*)PQueuePeek(my_queue) == data1);
	
	
	/*destroy*/
	PQueueDestroy(my_queue);
}


void UnitestDequeue(void)
{



}

void Unitestclear(void)
{




}

void UnitestEraseMatching(void)
{




}



















int IntimLowtoHigh(void *data1, void *data2) 
{
	return (*(int*)data1 <= *(int*)data2);
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

