#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
int IsBefore(const void *data1, const void *data2)
{
	return *(int*)data1 < *(int*)data2;
}

void UpTest(void)
{
	int i = 0;
	int array2[] = {30,10,20,9,8,15,16,40}; /* recently inserted*/ 
	int expected_result[] = {40,30,20, 10, 8 , 15, 16, 9};
	
	/*for(i = 0 ; i < 8 ; ++i)
	{
		printf("%d ,", array2[i]);
	}*/

	HeapifyUp(array2 , 8, sizeof(int), IsBefore);
	
	for(i = 0 ; i < 8 ; ++i)
	{
		assert(array2[i] == expected_result[i]);
	}

	puts("up works ok");

}

void DownTest(void)
{
	int i = 0;
	int array2[] = {16,10,20,9,8,15}; /* recently inserted*/ 
	int expected_result[] = {20, 10, 16, 9, 8, 15};

	int array44[] = {30,8,25,10,12,6,5,3,7,9};
	int expected_result44[] = {30,12,25,10,9,6,5,3,7,8};
	/*root removed*/
	HeapifyDown(array2 , 6, sizeof(int), 0, IsBefore);
	for(i = 0 ; i < 6 ; ++i)
	{
		assert(array2[i] == expected_result[i]);

	}
	puts("down root works ok");
	/*index 1 removed*/
	HeapifyDown(array44 , 10, sizeof(int), 1, IsBefore);
	for(i = 0 ; i < 10 ; ++i)
	{
		assert(array44[i] == expected_result44[i]);

	}
	puts("down middle works ok");

}

int main()
{
	UpTest();
	DownTest();
	return 0;

}
