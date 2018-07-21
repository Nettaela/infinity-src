/* Test Created By Evgeny */
/* printf functions for debuging are commented out. enable if needed */

#include "sort.h"
#include "stdio.h"
#include <assert.h>
#include <stdlib.h>
#include <sys/time.h> /* for using difftime */

#define DEVIDE_BY 1
#define ARR_SIZE 10

typedef struct demo
{
	size_t num;
	size_t dummy1;
	size_t dummy2;
}demo_t;

static int IsBubbleSorted(const void *data1, const void *data2)
{
	demo_t *strct1 = (demo_t*)data1;
	demo_t *strct2 = (demo_t*)data2;
	
	return (strct1->num <= strct2->num);
}

static int IsIntSortedUp(const void *data1, const void *data2)
{
	int num1 = *(int*)data1;
	int num2 = *(int*)data2;
	
	return (num1 <= num2);
}

static int IsIntSortedDown(const void *data1, const void *data2)
{
	int num1 = *(int*)data1;
	int num2 = *(int*)data2;
	
	return (num1 >= num2);
}


void UnitestBubble(void)
{
	struct timeval before = {0};
	struct timeval after = {0};
	static demo_t arr[ARR_SIZE] = {0};
	size_t idx = 0;
	/*puts("\nbefore:\n");*/
	for (idx = 0; idx < ARR_SIZE; ++idx)
	{
		arr[idx].num = rand() / DEVIDE_BY;
		/*printf("%li\n", arr[idx].num);*/
	}	
	gettimeofday(&before, NULL);
	BubbleSort(arr, sizeof(demo_t), ARR_SIZE, IsBubbleSorted); 
	gettimeofday(&after, NULL);
	/*puts("\nafter:\n");*/
	/*printf("%li\n", arr[0].num);*/
	for (idx = 0; idx < ARR_SIZE - 1; ++idx)
	{
		/*printf("%li\n", arr[idx + 1].num);*/
		assert(IsBubbleSorted(&arr[idx], &arr[idx + 1]) == 1); 
	}
	puts("Bubble passed!");
	printf("after: %lu\n", after.tv_usec);
	printf("before: %lu\n", before.tv_usec);
	printf("durition in ms: %lu\n\n", after.tv_usec - before.tv_usec);
}

void UnitestInsertion(void)
{
	/* TEST 1 */
	struct timeval before = {0};
	struct timeval after = {0};
	static int arr[ARR_SIZE] = {0};
	size_t idx = 0;
	/*puts("\nbefore:\n");*/
	for (idx = 0; idx < ARR_SIZE; ++idx)
	{
		arr[idx] = rand() / DEVIDE_BY;
		/*printf("%li\n", arr[idx]);*/
	}	
	gettimeofday(&before, NULL);
	InsertionSort(arr, ARR_SIZE, IsIntSortedUp); 
	gettimeofday(&after, NULL);
	/*puts("\nafter:\n");*/
	/*printf("%li\n", arr[0]);*/
	for (idx = 0; idx < ARR_SIZE - 1; ++idx)
	{
		/*printf("%li\n", arr[idx + 1]);*/
		assert(IsIntSortedUp(&arr[idx], &arr[idx + 1]) == 1); 
	}
	
	/* TEST 2 */
	/*puts("\nbefore:\n");*/
	for (idx = 0; idx < ARR_SIZE; ++idx)
	{
		arr[idx] = rand() / DEVIDE_BY;
		/*printf("%li\n", arr[idx]);*/
	}	
	InsertionSort(arr, ARR_SIZE, IsIntSortedDown); 
	/*puts("\nafter:\n");*/
	/*printf("%li\n", arr[0]);*/
	for (idx = 0; idx < ARR_SIZE - 1; ++idx)
	{
		/*printf("%li\n", arr[idx + 1]);*/
		assert(IsIntSortedDown(&arr[idx], &arr[idx + 1]) == 1); 
	}
	puts("Insertion passed!");
	printf("after: %lu\n", after.tv_usec);
	printf("before: %lu\n", before.tv_usec);
	printf("durition in ms: %lu\n\n", after.tv_usec - before.tv_usec);
}

void UnitestSelection(void)
{
	/* TEST 1 */
    struct timeval before = {0};
	struct timeval after = {0};
	static int arr[ARR_SIZE] = {0};
	size_t idx = 0;
	/*puts("\nbefore:\n");*/
	for (idx = 0; idx < ARR_SIZE; ++idx)
	{
		arr[idx] = rand() / DEVIDE_BY;
		/*printf("%li\n", arr[idx]);*/
	}	
	gettimeofday(&before, NULL);
	SelectionSort(arr, ARR_SIZE, IsIntSortedUp); 
	gettimeofday(&after, NULL);
	/*puts("\nafter:\n");*/
	/*printf("%li\n", arr[0]);*/
	for (idx = 0; idx < ARR_SIZE - 1; ++idx)
	{
		/*printf("%li\n", arr[idx + 1]);*/
		assert(IsIntSortedUp(&arr[idx], &arr[idx + 1]) == 1); 
	}
	
	/* TEST 2 */
	/*puts("\nbefore:\n");*/
	for (idx = 0; idx < ARR_SIZE; ++idx)
	{
		arr[idx] = rand() / DEVIDE_BY;
		/*printf("%li\n", arr[idx]);*/
	}	
	SelectionSort(arr, ARR_SIZE, IsIntSortedDown); 
	/*puts("\nafter:\n");*/
	/*printf("%li\n", arr[0]);*/
	for (idx = 0; idx < ARR_SIZE - 1; ++idx)
	{
		/*printf("%li\n", arr[idx + 1]);*/
		assert(IsIntSortedDown(&arr[idx], &arr[idx + 1]) == 1); 
	}
	printf("after: %lu\n", after.tv_usec);
	printf("before: %lu\n", before.tv_usec);
	puts("Selection passed!");
	printf("durition in ms: %lu\n\n", after.tv_usec - before.tv_usec);
}

static void FindMinMax(int* min, int *max, int *arr, size_t arr_size)
{
	size_t idx = 0;
	
	*min = arr[0];
	*max = arr[0];
	for (idx = 1; idx < arr_size; ++idx)
	{
		if (arr[idx] < *min)
		{
			*min = arr[idx];
		}
		else if (arr[idx] > *max)
		{
			*max = arr[idx];
		}
	}
}

typedef struct digit
{
	size_t digit;
	size_t sort_base_bits;
}digit_t;

static int GetVal(const void *val, void *param)
{
	int int_val = *(int*)val;
	digit_t *digit_strct = (digit_t*)param;
	
	if (NULL == param)
	{
		return int_val;
	}
	int_val >>= digit_strct->digit * digit_strct->sort_base_bits;
	int_val &= (1 << digit_strct->sort_base_bits) - 1;
	
	return int_val;
}
void UnitestCounting(void)
{
    struct timeval before = {0};
	struct timeval after = {0};
	static int arr[ARR_SIZE] = {0};
	static int sorted_arr[ARR_SIZE] = {0};
	size_t idx = 0;
	int range_min = 0;
	int range_max = 0;
	
	/*puts("\nbefore:\n");*/
	for (idx = 0; idx < ARR_SIZE; ++idx)
	{
		arr[idx] = rand() / DEVIDE_BY;
		/*printf("%d\n", arr[idx]);*/
	}
	
	FindMinMax (&range_min, &range_max, arr, ARR_SIZE);
	gettimeofday(&before, NULL);
	CountingSort(arr, sizeof(int), ARR_SIZE, sorted_arr, range_min, range_max, &GetVal, NULL);
	gettimeofday(&after, NULL);
	
	/*printf("\n\n%d\n", sorted_arr[0]);*/
	for (idx = 0; idx < ARR_SIZE - 1; ++idx)
	{
		/*printf("%d\n", sorted_arr[idx + 1]);*/
		assert(sorted_arr[idx] <= sorted_arr[idx + 1]); 
	}
	puts("Counting passed!");
	printf("after: %lu\n", after.tv_usec);
	printf("before: %lu\n", before.tv_usec);
	printf("durition in ms: %lu\n\n", after.tv_usec - before.tv_usec);
}

void UnitestRadix(void)
{
    struct timeval before = {0};
	struct timeval after = {0};
	static unsigned int arr[ARR_SIZE] = {0};
	static unsigned int sorted_arr[ARR_SIZE] = {0};
	size_t idx = 0;
	
	/*puts("\nbefore:\n");*/
	for (idx = 0; idx < ARR_SIZE; ++idx)
	{
		arr[idx] = rand() / DEVIDE_BY;
		/*printf("%d\n", arr[idx]);*/
	}
	
	
	/*gettimeofday(&before, NULL);*/
	RadixSort(arr, ARR_SIZE, sorted_arr, 3);
	/*gettimeofday(&after, NULL);*/
	
	/*printf("\n\n%d\n", sorted_arr[0]);*/
	for (idx = 0; idx < ARR_SIZE - 1; ++idx)
	{
		/*printf("%d\n", sorted_arr[idx + 1]);*/
		assert(sorted_arr[idx] <= sorted_arr[idx + 1]); 
	}
	puts("Counting passed!");
	/*printf("after: %lu\n", after.tv_usec);
	printf("before: %lu\n", before.tv_usec);
	printf("durition in ms: %lu\n\n", after.tv_usec - before.tv_usec);*/
}
int main()
{
	/*UnitestBubble();
	UnitestInsertion();
	UnitestSelection();
	UnitestCounting();*/
	UnitestRadix();
	
	puts("NICE JOB!");
	return EXIT_SUCCESS;
}
