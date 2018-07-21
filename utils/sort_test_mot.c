#include <stdio.h>     /* printf */
#include <stdlib.h>    /* rand */
#include <time.h>      /* time */
#include <unistd.h>    /* sleep */
#include <sys/time.h>  /* gettimeofday */

#include "sort.h" 


void test1();
void test2();
void test3();
void test4();
void test5();
void test6();

void Timer(void (*test)())
{
	struct timeval before = {0};
	struct timeval after = {0};
	double time_diff = 0;	

	gettimeofday(&before, NULL);
	test();
	gettimeofday(&after, NULL);

	time_diff = after.tv_sec - before.tv_sec 
				+ (after.tv_usec / 1000000.0) - (before.tv_usec / 1000000.0);

	printf("Run time: %f\n\n", time_diff);
}

int main()
{
	Timer(test1);
	sleep(1);
	Timer(test2);
	sleep(1);
	Timer(test3);
	sleep(1);
	Timer(test4);
	sleep(1); 
	Timer(test5);
	sleep(1);
	Timer(test6); 

	return 0;
}

static int GetVal(const void *val, void *param)
{
	(void)param;

	return (*(int *)val);
}

static int IsBefore(const void *data1, const void *data2)
{
	return (*(int *)data1 < *(int *)data2);
}

static int IsBeforeForQsort(const void *data1, const void *data2)
{
	return (*(int *)data1 > *(int *)data2);
}

static void IsSortedPrint(int *arr, size_t size)
{
	size_t count = 1;
	size_t i = 0;

	for (i = 0; i < (size - 1); ++i)
	{
		count += !IsBefore(&arr[i + 1], &arr[i]);
		/* printf("%d\n", arr[i]); */
	}
	
	if(count == size)
	{
		printf("List is sorted!\n");
	}
	else
	{
		printf("Failed!!!!!!!!!!!!!!!!!\n");
	}	
}

static void Random(int *arr, size_t size)
{
	size_t i = 0;

	srand(time(NULL));

	for(i = 0; i < size; ++i)
	{
		arr[i] = rand();
	}
}

static void RandomWithNeg(int *arr, size_t size)
{
	size_t i = 0;

	srand(time(NULL));

	for(i = 0; i < size; ++i)
	{
		arr[i] = rand()%10000000 - 5000000;
	}
}

void InfoPrint(int *arr, size_t size)
{
	printf("array size:  %lu\n", size);
	printf("first:       %d\n", arr[0]);
	printf("last:        %d\n", arr[size-1]);
}

void test1()
{
	/*size_t size = 10000;
	int *arr = (int *)calloc(size, sizeof(unsigned int));

	RandomWithNeg(arr, size);

	printf("Bubble Sort\n");

	BubbleSort(arr, sizeof(int), size, IsBefore);
	
	IsSortedPrint(arr, size);

	InfoPrint(arr, size);

	free(arr);*/
}

void test2()
{
	size_t size = 10000;
	int *arr = (int *)calloc(size, sizeof(unsigned int));

	RandomWithNeg(arr, size);

	printf("Selection Sort\n");

	SelectionSort(arr, size, IsBefore);
	
	IsSortedPrint(arr, size);

	InfoPrint(arr, size);

	free(arr);
}

void test3()
{
	size_t size = 10000;
	int *arr = (int *)calloc(size, sizeof(unsigned int));

	RandomWithNeg(arr, size);

	printf("Insertion Sort\n");

	InsertionSort(arr, size, IsBefore);
	
	IsSortedPrint(arr, size);

	InfoPrint(arr, size);

	free(arr);
}

void test4()
{
	size_t i = 0;
	size_t size = 10;
	int *arr = (int *)calloc(size, sizeof(int));
	int *ret = (int *)calloc(size, sizeof(int));

	int min = 0;
	int max = 0;

	RandomWithNeg(arr, size);

	min = arr[0];
	max = arr[0];

	for(i = 0; i < size; ++i)
	{
		if (min > arr[i])
		{
			min = arr[i];
		}
		else if (max < arr[i])
		{
			max = arr[i];
		}
	}

	printf("Counting Sort\n");

	CountingSort(arr, sizeof(int),  size, ret,min, max, GetVal, NULL); 

	IsSortedPrint(ret, size);

	InfoPrint(ret, size);


	free(arr);
	free(ret);
}

void test5()
{
/*
	size_t size = 10000000;
	unsigned int *arr = (unsigned int *)calloc(size, sizeof(unsigned int));
	unsigned int *ret = (unsigned int *)calloc(size, sizeof(unsigned int));

	Random((int *)arr, size);

	printf("Radix Sort\n");

	RadixSort(arr, size, ret, 16);

	IsSortedPrint((int *)ret, size);

	InfoPrint((int *)ret, size);


	free(ret);
	free(arr);*/
}

void test6()
{

	/*size_t size = 10000000;
	unsigned int *arr = (unsigned int *)calloc(size, sizeof(unsigned int));

	Random((int *)arr, size);

	printf("Qsort function\n");

	qsort(arr, size, sizeof(int), IsBeforeForQsort);

	IsSortedPrint((int *)arr, size);

	InfoPrint((int *)arr, size);

	free(arr);*/
}




