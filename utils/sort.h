#include <stddef.h>

typedef int (*is_sorted_t)(const void *data1, const void *data2);

/* BubbleSort excepts an arrey of elements of any size */
void BubbleSort(
	void *arr, 
	size_t elem_size, 
	size_t num_of_elem,
	is_sorted_t is_sorted);
	
/* InsertionSort excepts an arrey of int only! */
void InsertionSort(
	int *arr, 
	size_t num_of_elem,
	is_sorted_t is_sorted);
	
/* SelectionSort excepts an arrey of int only! */
void SelectionSort(
	int *arr, 
	size_t num_of_elem,
	is_sorted_t is_sorted);


/* returns 0 on success or 1 on failure */
/* CountingSort excepts an array of int only! */
int CountingSort(
	const void *src, 
	size_t elem_size,
	size_t arr_size, 
	void *dest,	
	int range_min, 
	int range_max,
	int (*get_val)(const void *val, void *param),
	void *param
	);
	
/* returns 0 on success or 1 on failure */
/* RedixSort excepts an array of int only! */
int RadixSort(
	unsigned int *arr, 
	size_t arr_size, 
	unsigned int *sorted_arr,
	size_t sort_base_bits
	);
	

int MergeSort(int *array, size_t array_size);

void QuickSort(int *array, size_t array_size);

void *HeapSort(
        void *arr,
        size_t elem_size,
        size_t num_of_elem,
        int (*is_before)(const void *data1, const void *data2, void *param));




