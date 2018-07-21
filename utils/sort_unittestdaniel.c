#include "sort.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int master_arr_g[] = {1,1,4,4,5,5,6,6,7,7,8,8,9,13,23,39,39,47,75,87,93,436,526,562,576,756,948,2948};

/* ----------------------------------------------------- */
int SortingFunc(const void *data1, const void *data2) 
{
	return (*(int*)data1 <= *(int*)data2);
}
/* ----------------------------------------------------- */
static void PrintArr(void *arr, int len)
{
	int i;
	for (i = 0; i < len; ++i)
	{
		printf("0x%x ", *((int*)arr + i));
	}
	puts(" ");
}

/* ----------------------------------------------------- */
void BubbleTest()
{
	int arr[] = {47,562,39,87,526,39,576,23,4,5,7,6,13,948,5,7,6,2948,756,1,93,8,4,75,1,9,8,436};
	int len = (int)(sizeof(arr)/sizeof(arr[0]));
	BubbleSort(arr, sizeof(arr[0]), len, &SortingFunc);
	
	PrintArr(arr, len);
}
	
/* ----------------------------------------------------- */
void InsertionTest()
{
	int arr[] = {47,562,39,87,526,39,576,23,4,5,7,6,13,948,5,7,6,2948,756,1,93,8,4,75,1,9,8,436};
	int len = (int)(sizeof(arr)/sizeof(arr[0]));

	InsertionSort(arr, len, &SortingFunc);
	PrintArr(arr, len);
}

/* ----------------------------------------------------- */
void SelectionTest()
{
	int arr[] = {47,562,39,87,526,39,576,23,4,5,7,6,13,948,5,7,6,2948,756,1,93,8,4,75,1,9,8,436};
	int len = (int)(sizeof(arr)/sizeof(arr[0]));

	SelectionSort(arr, len, &SortingFunc);
	PrintArr(arr, len);
}

/* ---------------------------------------------------------------- */
/*static int Min(const int *arr, size_t tot_elements)
{
	size_t i = 0;
	int min = *arr;
	
	for (i = 0; i < tot_elements; ++i)
	{
		if (arr[i] < min)
		{
			min = arr[i];	
		}
	}
	return min;
}*/

/* ---------------------------------------------------------------- */
/*static int Max(const int *arr, size_t tot_elements)
{
	size_t i = 0;
	int max = *arr;
	
	for (i = 0; i < tot_elements; ++i)
	{
		if (arr[i] > max)
		{
			max = arr[i];	
		}
	}
	return max;
}
*/
/* ---------------------------------------------------------------- */
static int TestMin(const int *arr, size_t tot_elements)
{
	size_t i = 0;
	int min = *arr;
	
	for (i = 0; i < tot_elements; ++i)
	{
		if (arr[i] < min)
		{
			min = arr[i];	
		}
	}
	return min;	
}

/* ---------------------------------------------------------------- */
static int TestMax(const int *arr, size_t tot_elements)
{
	size_t i = 0;
	int max = *arr;
	
	for (i = 0; i < tot_elements; ++i)
	{
		if (arr[i] > max)
		{
			max = arr[i];	
		}
	}
	return max;
}

/* ----------------------------------------------------- */
int get_val(const void *val, void *param)
{
	(void)param;
	/*printf("i will return this: %d\n", (*(int*)val));*/
	return (*(int*)val);
}

/* ----------------------------------------------------- */
void CountingTest()
{
	int arr[] = {47,562,39,87,526,39,576,23,4,5,7,6,13,948,5,7,6,2948,756,1,93,8,4,75,1,9,8,436};
	int sorted_arr[28] = {0};
	/*int arr[] = {1,3,2,0,8,2};*/
	/*int arr[] = {3,6,20,7,8,7};*/
	/*int sorted_arr[6] = {0};*/
	
	int len = (int)(sizeof(arr)/sizeof(arr[0]));
	int min_val = TestMin(arr, len);
	int max_val = TestMax(arr, len);
	/*int max = Max(arr, len);*/
	/*CountingSort(arr, len, sorted_arr, 0, 0);*/
	CountingSort(arr, sizeof(int), len, sorted_arr, min_val, max_val, &get_val, NULL);
	/*PrintArr(arr, len);*/
	PrintArr(sorted_arr, len);
}

/* ----------------------------------------------------- */
void RadixTest()
{
	unsigned int arr[] = {47,562,39,87,526,39,576,23,4,5,7,6,13,948,5,7,6,2948,756,1,93,8,4,75,1,9,8,436};
	unsigned int sorted_arr[28] = {0};
	
	/*
	unsigned int arr[] = {0xAB,0x38,0xC5,0x90,0x81,0x2,0xFD};
	unsigned int sorted_arr[7] = {0};
	*/

/*	unsigned int arr[] = {0x4A,0x6C,1637,0xB,0xDE,0xF9,0x76,2};
	unsigned int sorted_arr[8] = {0};
*/
	
	int len = (int)(sizeof(arr)/sizeof(arr[0]));
	size_t sort_base_bits = 4;
	
	PrintArr(arr, len);
	RadixSort(arr, len, sorted_arr, sort_base_bits);
	PrintArr(arr, len);
	/*PrintArr(arr, len);*/
/*	PrintArr(sorted_arr, len);*/
}

/* ----------------------------------------------------- */
void QSortTest()
{
	int arr[] = {47,562,39,87,526,39,576,23,4,5,7,6,13,948,5,7,6,2948,756,1,93,8,4,75,1,9,8,436};
	int len = (int)(sizeof(arr)/sizeof(arr[0]));
	
	qsort(arr, len, sizeof(int), &SortingFunc);
	PrintArr(arr, len);
}

/* ----------------------------------------------------- */
void BubbleTimeTest()
{
	clock_t time1 = clock();
	clock_t time0 = clock();
	
	time0 = clock();
	BubbleTest();
	time1 = clock();
	printf("Bubble: %ld\n\n", time1 - time0);
}

/* ----------------------------------------------------- */
void InsertionTimeTest()
{
	clock_t time1 = clock();
	clock_t time0 = clock();
	
	time0 = clock();
	InsertionTest();
	time1 = clock();
	printf("Insertion: %ld\n\n", time1 - time0);
}

/* ----------------------------------------------------- */
void SelectionTimeTest()
{
	clock_t time1 = clock();
	clock_t time0 = clock();
	
	time0 = clock();
	SelectionTest();
	time1 = clock();
	printf("Selection: %ld\n\n", time1 - time0);
}

/* ----------------------------------------------------- */
void CountingTimeTest()
{
	clock_t time1 = clock();
	clock_t time0 = clock();
	
	time0 = clock();
	CountingTest();
	time1 = clock();
	printf("Counting: %ld\n\n", time1 - time0);
}

/* ----------------------------------------------------- */
void RadixTimeTest()
{
	clock_t time1 = clock();
	clock_t time0 = clock();
	
	time0 = clock();
	RadixTest();
	time1 = clock();
	printf("Radix: %ld\n\n", time1 - time0);
}

/* ----------------------------------------------------- */
void QSortTimeTest()
{
	clock_t time1 = clock();
	clock_t time0 = clock();
	
	time0 = clock();
	QSortTest();
	time1 = clock();
	printf("Q Sort: %ld\n\n", time1 - time0);
}

/* ----------------------------------------------------- */
int main()
{
	
/*	BubbleTimeTest();
	InsertionTimeTest();
	SelectionTimeTest();
	CountingTimeTest();
*/	RadixTimeTest();
/*	QSortTimeTest();*/

	return 0;
}


