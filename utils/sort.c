#include "sort.h"
#include "heap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h> /*for CHAR_BIT*/

#define NEXT_EL(a) (char*)a+elem_size
#define IS_EVEN(a) ((a & 1) == 0)

typedef unsigned int uint;

typedef struct radix_params 
{
	uint mask;
	uint shift;
}radix_t;

static void SwitchPointers(unsigned int **arr, unsigned int **sorted_arr)
{
	unsigned int *temp = *arr;
	*arr = *sorted_arr;
	*sorted_arr = temp;
} 

int GetValRadix(const void *val, void *param)
{
	/*gets number in array and mask, returns number after & with mask*/
	radix_t *param_struct = (radix_t*)param;
	uint shift = param_struct->shift;
	uint mask = param_struct->mask;

	return ((*(uint*)val >> shift) & mask);
}

static void SwapElements(void *data1, void *data2, void* temp, size_t elem_size)
{
    /*save data 2 in temp*/
    memcpy(temp, data2, elem_size);
    /*copy data1 to data2 location*/
    memcpy(data2, data1, elem_size);
    /*copy temp to data 1*/
    memcpy(data1, temp, elem_size);
}

static void ShiftElements(int *from_here, size_t how_many)
{	
	int *dest = from_here + 1;
	memmove(dest, from_here, how_many*sizeof(int));
}

static size_t HowManyToShift(int *array, int index_first_not_sorted, is_sorted_t is_sorted)
{
	int last_sorted = index_first_not_sorted - 1;
	size_t counter = 0;
	while(!is_sorted(&array[last_sorted], &array[index_first_not_sorted]) && last_sorted >= 0)
	{
		++counter;
		--last_sorted;
	}
	return counter;
}

static size_t FindMin(int *arr, size_t start_from, is_sorted_t is_sorted, size_t num_of_elem)
{
	int minimum = arr[start_from];
	size_t minimum_index = start_from;
	++start_from;

	while(start_from <= num_of_elem)
	{
		if(is_sorted(&arr[start_from], &minimum))
		{
			minimum = arr[start_from];
			minimum_index = start_from;
		}
		++start_from;

	}
	return minimum_index;
}

static void AccumulateArray(int *arr, size_t arr_size)
{
	size_t sum_offset = 0;
	size_t current_value = 0;
	size_t i = 0;
	
	for(i = 0 ; i < arr_size ; ++i)
	{
		current_value = arr[i];
		arr[i] = sum_offset;
		sum_offset += current_value;
	}
}

void BubbleSort(
        void *arr,
        size_t elem_size,
        size_t num_of_elem,
        is_sorted_t is_sorted)
{
    char *current_element = arr;
    char *next_element = NEXT_EL(current_element);
    char *last_element = current_element + ((num_of_elem -1)* elem_size);/*minus - 1?*/
    char *first_element = current_element;
    int swap_flag = 1;
	void *temp = malloc(elem_size);
	/*how to test malloc?*/

    while(swap_flag)
    {
        swap_flag = 0;
        current_element = first_element;
        next_element = NEXT_EL(current_element);
        while(current_element < last_element)
        {
            if (!is_sorted(current_element, next_element))
            {
                SwapElements(current_element, next_element, temp ,elem_size);
                /*next is now before current*/
                next_element = NEXT_EL(current_element);
                swap_flag = 1;
            }
            else
            {
                current_element = next_element;
                next_element = NEXT_EL(next_element);
            }
        }
    }
    free(temp);
    /*flag for no swapping has occurred for a whole pass
     * loop while flag is 1. begining of loop makes it 0.
     * swapping makes flag 1.
     * for each index that is not the last, see if the element and the one after it is sorted.
     * if sorted, go to the next index
     * otherwise:
     * swap in place */
}

void InsertionSort(
	int *arr, 
	size_t num_of_elem,
	is_sorted_t is_sorted)
{
    size_t how_many_sorted = 0;
   	int num_taken_out = 0;
    int index_to_check = 0;
	size_t shift_count = 0;
	int index_first_not_sorted = 0;
    
    for(how_many_sorted = 0 ; how_many_sorted < (num_of_elem - 1) ; ++how_many_sorted)
    {
    	index_first_not_sorted = how_many_sorted + 1;
    	num_taken_out = arr[index_first_not_sorted];
    	index_to_check = how_many_sorted;
    	
    	if(!is_sorted(&arr[index_to_check], &num_taken_out))
    	{	
    		shift_count = HowManyToShift(arr, index_first_not_sorted, is_sorted);
    		ShiftElements(&arr[index_first_not_sorted - shift_count], shift_count);
			arr[index_first_not_sorted - shift_count] = num_taken_out; 
	 	}
	 }    
}

void SelectionSort(
	int *arr, 
	size_t num_of_elem,
	is_sorted_t is_sorted)
{
	/*finds minimum and brings to the start*/
	/*maintains two sub arrays - sorted and unsorted*/
	/*begins with nothing sorted, find minimum function searches all of the array*/
	/*when a new element is inserted at the begining, everything between that elemt 
	that is in the unsorted part of the array shifts to the right*/
	
	size_t start_from = 0;
	size_t minimum_index = 0;
	int num_taken_out = 0;
	
	for(start_from = 0 ; start_from < num_of_elem ; ++start_from)
	{
		minimum_index = FindMin(arr, start_from, is_sorted, num_of_elem);
		num_taken_out = arr[minimum_index];
		ShiftElements(&arr[start_from], minimum_index - start_from);
		arr[start_from] = num_taken_out;
	}
}


int CountingSort(
	const void *src, 
	size_t elem_size,
	size_t arr_size, 
	void *dest,	
	int range_min, 
	int range_max,
	int (*get_val)(const void *val, void *param),
	void *param
	)
{
	/*create histogram array, size of max-min*/
	size_t i = 0, j = 0;
	size_t histo_size = range_max - range_min + 1;
	int array_value = 0;
	int array_value_norm = 0;
	int histo_value = 0;
	

	int *histo_array = calloc(histo_size, sizeof(int));
	if(histo_array == NULL)
	{
		return 1;
	}
	
	/*go over the original array , for every element in the array, increment that index in the histogram*/
	for(i = 0 ; i < arr_size ; ++i)
	{
		array_value = get_val((void*)((char*)src + (elem_size * i)), param);
		array_value_norm = array_value - range_min;
		++histo_array[array_value_norm];/*the number in the array[i] minus the minimum value is the correct place in the histogram array*/
	}
	
	/*collect offsets*/

	AccumulateArray(histo_array, histo_size);

	/*return to original array and put the elements in the sorted array based on their value in the index in the histogram. after each one, we increment the value in the histogram array*/

	for(i = 0 ; i < arr_size ; ++i)
	{
		array_value = get_val((void*)((char*)src + (elem_size * i)), param);
		array_value_norm = array_value - range_min;
		histo_value = histo_array[array_value_norm];
		for(j = 0 ; j < elem_size ; ++j)
		{
			*((char*)dest + (histo_value * elem_size) + j) = 
			*((char*)src + (elem_size * i) + j);
		}
		++histo_array[array_value_norm];
	}
		
	free(histo_array);
	return 0;
}

/* returns 0 on success or 1 on failure */
/* RedixSort excepts an array of uint only! */
int RadixSort(
	unsigned int *arr, 
	size_t arr_size, 
	unsigned int *sorted_arr,
	size_t sort_base_bits)
{
	/*determine histogram size to send as min max to countingsort? - the number of possible numbers in that many bytes!! 2^sort_base_bits*/
	size_t num_shifts = 0;
	size_t uint_bits = sizeof(uint) * CHAR_BIT;
	radix_t params = {0};
	uint mask = 0;
	unsigned int *arr_copy = arr;  
	unsigned int *sorted_arr_copy = sorted_arr;
	size_t histo_size = 1 << sort_base_bits;
	size_t how_many_times_loop = uint_bits + (sort_base_bits - 1) / sort_base_bits; 
	
	/*create mask: pow(2,sort_base_bits) -1*/ 
	mask = histo_size - 1;
	 
	/*create a struct, in which to put the mask, and the shift number, 
	it will be sent to get val as params*/
	params.mask = mask;
	params.shift = 0;
	
	/*go over original array:
	for each member, use mask to and shift to get the index which will be returnd, 
	that value is the index in the histogram.
	that will happen using the counting sort function, and the get val function
	min is 0, max is pow(2, bits) -1 */
	/*printf("mask %lu \n", mask);*/
	for(num_shifts = 0 ; num_shifts < uint_bits ; num_shifts += sort_base_bits)
	{
		params.shift = num_shifts;
		printf("shift: %lu \n",num_shifts);
		if (CountingSort(arr_copy, sizeof(int), arr_size, 
			sorted_arr_copy, 0, mask, GetValRadix, &params) == 1)
		{
			return 1;
		}
		SwitchPointers(&arr_copy, &sorted_arr_copy);
		/*sorted arr is returned, switch between sorted and original arrays and
		loop again - sending the sorted original array to counting sort, 
		and increasing the shift by another base bits*/ 
		/*number of times loop will run will be as many as the shifting, meaning:
		uint size is 32 bits, divided by sort_base_bits, 
		is the number of times. if the result of the divide is not whole, 
		loop one more time.*/
	} 
	/*check if arr and sorted arr switched ( based on number of of iterations and memcpy if yes*/	
	if(IS_EVEN(how_many_times_loop))
	{
		memcpy(sorted_arr, arr, arr_size * sizeof(int));
	}
	

	return 0;
}

static void ActualMerge(int *array, int *cpy_array, size_t left_size, size_t right_size) 
{
	int *left_half = cpy_array;
	int *right_half = cpy_array + left_size;
	int *array_end = array+left_size+right_size;
	while(array != array_end)
	{
		if(left_size == 0)
		{
			*array = *right_half;
			--right_size;
			++array;
			++right_half;
		}
		else if(right_size == 0)
		{
			*array = *left_half;
			--left_size;
			++array;
			++left_half;
		}
		else
		{	
			if(*right_half <= *left_half /*&& right_size > 0*/)
			{
				*array = *right_half;
				--right_size;
				++array;
				++right_half;
			}
			else if(*left_half < *right_half/* && left_size > 0*/)
			{
				*array = *left_half;
				--left_size;
				++array;
				++left_half;
			}
		}
	}

}


int MergeSort(int *array, size_t array_size)
{
	int *left_half = NULL;
	int *right_half = NULL;
	int *cpy_array = NULL;
	size_t right_size = 0;
	size_t left_size = 0;

	if (1 == array_size)
	{
		return 0;
	}
	
	cpy_array = (int *)malloc(array_size * sizeof(int));
	if(NULL == cpy_array)
	{	
		return 1;
	}
	
	memcpy(cpy_array, array, array_size * sizeof(int));
	
	left_size = array_size / 2;
	right_size = array_size - left_size;
	
	left_half = cpy_array;
	right_half = cpy_array + left_size;

	if(1 == MergeSort(left_half, left_size))
	{
		free(cpy_array);
		return 1;
	}
	if(1 == MergeSort(right_half, right_size))
	{
		free(cpy_array);
		return 1;
	}

	ActualMerge(array, cpy_array, left_size, right_size);
	free(cpy_array);
	return 0;	
}

void Swap(int *num1, int *num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

void QuickSort(int *array, size_t array_size)
{
	int pivot_point = array_size-1;
	int wall = 0;
	int current_element = 0;
	if(array_size <= 1 )
	{
		return;
	}
	/*go from the wall up to the one before pivot.
	for each element see if its smaller than the pivot. if its is, replace it with the wall index.*/
	
	for (current_element = wall ; current_element < pivot_point ; ++current_element)
	{
		if(array[current_element] < array[pivot_point])
		{
			Swap(array+wall, array+current_element);
			++wall;
		}
	}
	
	if(array[wall] >= array[pivot_point])
	{
		Swap(array+wall, array+pivot_point);
	}
	QuickSort(array, wall);
	QuickSort(array + wall + 1 , array_size - wall - 1);
}

static void *SwapVoids(char *data1, char *data2, size_t elem_size)
{
	char *temp = malloc(elem_size);
	if(NULL == temp)
	{
		puts("temp is null");
		return NULL;
	}
	memcpy(temp, data1, elem_size);
	memcpy(data1, data2 , elem_size);
	memcpy(data2, temp, elem_size);
	free(temp);
	return data1;
}

void *HeapSort(
        void *arr,
        size_t elem_size,
        size_t num_of_elem,
        int (*is_before)(const void *data1, const void *data2, void *param))
{
	size_t i=0;
	char *array = (char*)arr;
	char *current_element = array;
	char *last_element = array + (num_of_elem - 1) * elem_size;
	char *first_element = array;
	/*heapify the array: go from second element to the last and heapify up everytime*/
	for(i = 1; i < num_of_elem ; ++i)
	{
		HeapifyUp(array, i+1 , elem_size, is_before, NULL);
	}
	
	/*create pointer to last element, replace last with first, 
	heapify down, decrement last pointer, repeat until the last is equal to 
	first*/
	for(i = 1; i < num_of_elem ; ++i)
	{
		if(SwapVoids(first_element , last_element, elem_size) == NULL)
		{
			return NULL;
		}
		HeapifyDown (first_element, num_of_elem-i, elem_size,0, is_before, NULL);
		last_element = last_element - elem_size;
	}
	
	return arr;
}

















