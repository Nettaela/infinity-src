#include "sort.h"
#include <string.h> /* for memcpy */
#include <assert.h>
#include <stdlib.h> /* for EXIT_SUCCESS */
#include <stdio.h>

/*
void BubbleSort(
	void *arr_to_sort, 
	size_t elem_size, 
	size_t num_of_elem,
	is_sorted_t is_sorted)*/
	
/*typedef int (*is_sorted_t)(const void *data1, const void *data2)*/

int IsSortInts(const void *data1, const void *data2)
{
	int num1 = *(int*)data1;
	int num2 = *(int*)data2;	
	
	return (num1 < num2);
}

void BubbleSortUritest(void)
{
	static int arr[] = {0, 1, 3, 9, 6, 5, 4, 7, 2 ,8};
	static int target_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int idx = 0;
	
	BubbleSort(arr, 4, 10, IsSortInts);
	
	for (idx = 0; idx < 10; ++idx)
	{
		assert(arr[idx] == target_arr[idx]);
	}
	
	puts("that was a nice bubble sort dude!");
	puts("BOOM BOOM medabrim paka paka!");
}

/*
void InsertionSort(
	void *arr, 
	size_t elem_size, 
	size_t num_of_elem)*/
void InsertionSortUritest(void)
{
	static int arr[] = {0, 1, 3, 9, 6, 5, 4, 7, 2 ,8};
	static int target_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int idx = 0;
	
	InsertionSort(arr, 10, IsSortInts);
	
	for (idx = 0; idx < 10; ++idx)
	{
		assert(arr[idx] == target_arr[idx]);
	}
	
	puts("that was a nice Insertion sort dude!");
	puts("BOOM BOOM medabrim paka paka!");
}


void SelectionSortUritest(void)
{
	static int arr[] = {0, 1, 3, 9, 6, 5, 4, 7, 2 ,8};
	static int target_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int idx = 0;
	
	SelectionSort(arr, 10, IsSortInts);
	
	for (idx = 0; idx < 10; ++idx)
	{
		printf("%d, ",arr[idx]);

	}
	putchar(10);
	for (idx = 0; idx < 10; ++idx)
	{

		printf("%d, ", target_arr[idx]);
	}
	
	puts("that was a nice Selection sort dude!");
	puts("BOOM BOOM medabrim paka paka!");
}
/*
void CountingSort(
	const int *arr, 
	size_t arr_size, 
	int *sorted_arr,	
	int range_min, 
	int range_max);*/
	
void CountingSortUritest(void)
{
	/*static int arr[] =		  {-2, 1, 3, -2, 0, 4, 1, 1, 2 ,-3};
	static int target_arr[] = {-3, -2, -2, 0, 1, 1, 1, 2, 3, 4};
	static int result_arr[10] = {0};
	int idx = 0;
	
	CountingSort(arr, 10, result_arr, -3, 4);
	
	for (idx = 0; idx < 10; ++idx)
	{
		assert(result_arr[idx] == target_arr[idx]);
	puts("that was a nice Counting Sort dude!");
	puts("BOOM BOOM medabrim paka paka!");*/
}

int main()
{
	BubbleSortUritest();
	InsertionSortUritest();
	SelectionSortUritest();
	/*CountingSortUritest();*/
	
	return EXIT_SUCCESS;
}
