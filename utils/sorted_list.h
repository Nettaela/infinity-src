
#ifndef SDLIST_H
#define SDLIST_H

#include "dlist.h"

typedef int (*sorted_list_is_match_func_t)(const void *data, void *params, const void *data_to_match);
typedef int (*sorted_list_action_func_t)(void *data, void *params);
typedef int (*sorted_list_is_sorted_func_t)(void *data1, void *data2);


typedef struct sorted_list_iter
{
	dlist_iter_t iterator;
	
}sorted_list_iter_t;


/* Controller struct */
typedef struct sorted_list sorted_list_t;

/* Create Sorted List. */
sorted_list_t *SortedListCreate(sorted_list_is_sorted_func_t sorting_func);

/* Destroy the Sorted List */
void SortedListDestroy(sorted_list_t *sorted_list);

/* Return number of elements in Sorted List */
size_t SortedListSize(const sorted_list_t *sorted_list);

/* returns 1 on empty Sorted List ; otherwise returns 0 */
int SortedListIsEmpty(const sorted_list_t *sorted_list);

/* Returns sorted list iterator to the begining of Sorted List */
sorted_list_iter_t SortedListBegin(const sorted_list_t *sorted_list);

/* Returns sorted list iterator to the element after the end of Sorted List */
sorted_list_iter_t SortedListEnd(const sorted_list_t *sorted_list);

/* Returns iterator to the next element in Sorted List
   SDListNext on End is undefined */
sorted_list_iter_t SortedListNext(const sorted_list_iter_t iter);

/* Returns sorted list iterator to the previous element in Sorted List
   SortedListPrev on Begin is undefined
   SortedListPrev on End returns the last element in the list */
sorted_list_iter_t SortedListPrev(const sorted_list_iter_t iter);

/* Returns 1 on same; Otherwise returns 0 */
int SortedListIsSameIterator(const sorted_list_iter_t iter1, const sorted_list_iter_t iter2);

/* Returns data pointer of the dlist_iter_t element */
void *SortedListGetData(const sorted_list_iter_t iter);

/* Returns iterator of the inserted element. On failure returns End */
sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data);

/* Removes the element and returns the next sortedlist_iter_t */
sorted_list_iter_t SortedListErase(sorted_list_iter_t iter);

/* Pop element from start of DList. Return data to user
   Pop on an empty list is undefined */
void *SortedListPopFront(sorted_list_t *sorted_list);


/* Pop element from end of DList. Return data to user
   Pop on an empty list is undefined */
void *SortedListPopBack(sorted_list_t *sorted_list); 

/* Execute function for every element in "from..to" range in order ("to" element is excluded)
   On success: return 0 ; otherwise stop iteration and return status of first failed function */
int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to, sorted_list_action_func_t action, void *params);


/* Returns sorted_list_iter_t that matches element in range. Returns to otherwsie */
sorted_list_iter_t SortedListFind(sorted_list_iter_t from, sorted_list_iter_t to, sorted_list_is_match_func_t is_match, void *params, const void *data_to_match);

/* Gets two lists and merges them together. returns list1 and list 2 is empty.*/

sorted_list_t *SortedListMerge(sorted_list_t *sorted_list1, sorted_list_t *sorted_list2);


#endif

