#include "heap.h"       /*heap API*/
#include "my_decs.h"    /*macros and more funcs*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


int IsBefore(const void *num1, const void *num2, void *param)
{
	
    const int num1_int = *(int*)num1;
    const int num2_int = *(int*)num2;
	(void)param;
	
    return (num1_int < num2_int);
}


void HeapSort(void *arr, size_t num_of_elem, size_t elem_size, int (*is_before)(const void *data1, const void *data2, void *param))
{
	char *byte_arr = (char*)arr;
	size_t tmp_num_of_elem = 2;
	
	while (tmp_num_of_elem <= num_of_elem)
	{
		HeapifyUp(arr, tmp_num_of_elem, elem_size, is_before, NULL);
		++tmp_num_of_elem;
	}
	
	while (num_of_elem > 1)	
	{
		SwapVoid(byte_arr, (byte_arr + (num_of_elem - 1) * elem_size), elem_size);
		HeapifyDown (byte_arr, num_of_elem - 1, elem_size, 0, is_before, NULL);
		--num_of_elem;
	}	
}




/*make a new is_before_heap*/

void HeapingTest()
{
	int arr1[] = {4, 3, 2, 0, 20, 27, 14, 18};
	int heap[] = {27, 18, 20, 4, 3, 2, 14, 0};
	int one[] = {2};	
	
	puts("---------------before heap----------");
	PrintArr(arr1, INT_ARR_SIZE(arr1));
	
	HeapSort(arr1, INT_ARR_SIZE(arr1), INT_SIZE, IsBefore);
	puts("---------------after heap----------");
	PrintArr(arr1, INT_ARR_SIZE(arr1));
	
	puts("---------------before heap----------");
	PrintArr(heap, INT_ARR_SIZE(heap));
	
	HeapSort(heap, INT_ARR_SIZE(heap), INT_SIZE, IsBefore);
	puts("---------------after heap----------");
	PrintArr(heap, INT_ARR_SIZE(heap));
	
	HeapSort(one, INT_ARR_SIZE(one), INT_SIZE, IsBefore);
	puts("---------------after heap----------");
	PrintArr(one, INT_ARR_SIZE(one));	
}


void SwapTest()
{
	int arr1[] = {27, 18, 20, 4, 3, 2, 14, 0};
	int arr2[] = {30, 20, 15, 18, 10, 0, 10, 3};
	
	
	puts("--------------1.before swap----------");
	PrintArr(arr1, INT_ARR_SIZE(arr1));
	HeapSort(arr1, INT_ARR_SIZE(arr1), INT_SIZE, IsBefore);
	
	
	puts("---------------1.after swap----------");
	PrintArr(arr1, INT_ARR_SIZE(arr1));

	puts("--------------2.-before swap----------");
	PrintArr(arr2, INT_ARR_SIZE(arr2));
	
	HeapSort(arr2, INT_ARR_SIZE(arr2), INT_SIZE, IsBefore);
	
	
	puts("--------------2.-after swap----------");
	PrintArr(arr2, INT_ARR_SIZE(arr2));

}


void SortTest()
{
	int random[100]; 
	size_t i = 0;
	
	
	for (i = 0; i < INT_ARR_SIZE(random); ++i)
	{
		random[i] = rand() / 1000;
	}
	
	
	
	HeapSort(random, INT_ARR_SIZE(random), INT_SIZE, IsBefore);
/*	PrintArr(random, INT_ARR_SIZE(random));*/
	
	
	
	for (i = 1; i < INT_ARR_SIZE(random); ++i)
	{
		assert (random[i] > random[i - 1]);
	}
	
	/*
	puts("--------------1.before sort----------");
	PrintArr(arr1, INT_ARR_SIZE(arr1));
	HeapSort(arr1, INT_ARR_SIZE(arr1), INT_SIZE, IsBefore);

	puts("---------------1.after sort----------");
	PrintArr(arr1, INT_ARR_SIZE(arr1));
*/


	puts("Finally!!!);


}


int main()
{

	SortTest();
/*	SwapTest();*/
/*	HeapingTest();*/
	
	return 0;
}












