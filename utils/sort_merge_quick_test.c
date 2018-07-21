#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sort.h"
#include <time.h>
#define SIZE 100000
void CreateRandArray(int *array, size_t size);
void unitestMerge(int *array, size_t size);
void unitestQuick(int *array, size_t size);
void unitestHeap(int *array, size_t size);
int IsSortSuccess(int *array, size_t arr_size);
int IsSorted(int data1, int data2);
int IsBefore(const void *data1, const void *data2, void *param);
int main()
{

	int array1[SIZE];
	int array2[SIZE];
	int array3[SIZE];
	CreateRandArray(array1, SIZE);
	unitestMerge(array1, sizeof(array1)/sizeof(array1[0]));
	CreateRandArray(array2, SIZE);
	unitestQuick(array2, sizeof(array2)/sizeof(array2[0]));
	
	CreateRandArray(array3, SIZE);
	unitestHeap(array3, sizeof(array3)/sizeof(array3[0]));
	return 0;
}


int IsSortSuccess(int *array, size_t arr_size)
{
	size_t i = 0;
	for(i = 0 ; i < arr_size - 1 ; ++i)
	{
		if(array[i] > array[i + 1])
		{
			return 0;
		}
	}
	return 1;
}


void CreateRandArray(int *array, size_t size)
{
	size_t i = 0;
	srand(time(NULL)); 
	
	for(i = 0; i < size ; ++i)
	{
		array[i] = rand()%SIZE;
	}

}

void unitestMerge(int *array, size_t size)
{
	size_t i = 0;
	assert(0 == MergeSort(array, size));
	
	for(i = 0 ; i < size-1 ; ++i)
	{
		/*printf("i:%lu   %d\n", i, array[i]);*/
		assert(IsSorted(array[i], array[i+1]));
	}
	puts("merge passed");
}

void unitestQuick(int *array, size_t size)
{
	size_t i = 0;
	
	QuickSort(array, size);
	
	for(i = 0 ; i < size-1 ; ++i)
	{
		/*printf("i:%lu   %d\n", i, array[i]);*/
		assert(IsSorted(array[i], array[i+1]));
	}
	puts("quick passed");

}

void unitestHeap(int *array, size_t size)
{
	size_t i = i;
    HeapSort(array, sizeof(int), size, IsBefore);

	for(i = 0 ; i < size-1 ; ++i)
	{
		/*printf("i:%lu   %d\n", i, array[i]);*/
		assert(IsSorted(array[i], array[i+1]));
	}
	
    puts("heap sort success");
}

int IsBefore(const void *data1, const void *data2, void *param)
{
	(void)param;
    return (*(int*)data1 >= *(int*)data2);
}

int IsSorted(int data1, int data2)
{
    return (data1 <= data2);
}
