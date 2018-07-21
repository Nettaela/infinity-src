#include "heap.h"       /*heap API*/
#include "my_decs.h"    /*macros and more funcs*/

#include <stdio.h>      /*printf*/
#include <string.h>     /*memcpy*/
#include <stdlib.h>     /*malloc*/



static int SwapCheck(int (*is_before_heap)(const void *data1, const void *data2, void *param), const void *child, const void *parent, void *user_func)
{
    if (is_before_heap(parent, child, user_func) == 1)
    {
        return 1;
    }
    return 0;
}



int IsBeforHeap(const void *data1, const void *data2, void *param)
{
	int (*fptr)(const void *data1, const void *data2);
	*(void**)(&fptr) = param;
	
	return fptr(*(void**)data1, *(void**)data2);
}



/*take last element and loop through its parent, call is_before to see if parent*/
/*is smaller, if so- swap them*/
void HeapifyUp(void *arr, size_t nmemb, size_t elem_size, 
   int (*is_before_heap)(const void *data1, const void *data2, void *param), void *user_func)
{
    int index = (((nmemb - 1) - 1) / 2);
    char *heapify_elem = (char *)arr + (nmemb - 1) * elem_size;
    char *parent = (char *)arr + index * elem_size; 

    while (is_before_heap(parent, heapify_elem, user_func) == 1 && (heapify_elem != parent)) 
    {
        heapify_elem = SwapVoid(heapify_elem, parent, elem_size);
        index = (index - 1) / 2;
        parent = (char *)arr + index * elem_size;   
    }
}


static int GetMaxSonIndex(void *arr, size_t nmemb, size_t elem_size, size_t idx,
  int (*is_before_heap)(const void* data1, const void* data2, void *param), void *user_func)
{
	int left_index = 2 * idx + 1;
    int right_index = 2 * idx + 2;      

    if ((right_index > (int)(nmemb - 1)) ||
    (is_before_heap((char*)arr + right_index * elem_size,
    	(char*)arr + left_index * elem_size, user_func) == 1)) 
    {
     	return (left_index);
    } 
    
    return (right_index);  
 }


/*check which son is bigger and swap the heap_elem with it- heap_elem is a parent!!*/

void HeapifyDown (void *arr, size_t nmemb, size_t elem_size, size_t idx,
  int (*is_before_heap)(const void* data1, const void* data2, void *param), void *user_func)
{
    char *heapify_elem = (char*)arr + idx * elem_size;
	int max_son_idx = GetMaxSonIndex(arr, nmemb, elem_size, idx, is_before_heap, user_func);
	char *max_son = (char*)arr + max_son_idx * elem_size;

    while ((max_son_idx <= (int)(nmemb - 1)) && 
    		(SwapCheck(is_before_heap, max_son, heapify_elem, user_func) == 1))
    {
         heapify_elem = SwapVoid(heapify_elem, max_son, elem_size);
         idx = max_son_idx;
         max_son_idx = GetMaxSonIndex(arr, nmemb, elem_size, idx,
         								 is_before_heap, user_func);
         max_son = (char*)arr + max_son_idx * elem_size;
    }
}









