#ifndef HEAP_H_
#define HEAP_H_

#include <stddef.h>

void HeapifyUp(void *arr, size_t nmemb, size_t elem_size, 
				int (*is_before)(const void *data1, const void *data2, 
				void *param), void *param);

/*index is for removing from the middle.*/
void HeapifyDown (void *arr, size_t nmemb, size_t elem_size, size_t idx, 
		int (*is_before)(const void* data1, const void* data2, void *param), 
		void *param);


#endif /* HEAP_H_ */

