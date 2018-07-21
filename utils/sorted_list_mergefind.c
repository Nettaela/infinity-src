
#include "sorted_list.h"
#include <stdio.h>
#include <stdlib.h>/*for size_t*/
#include <assert.h>/*for asserts */




struct sorted_list 
{
	dlist_t *dlist;
	sorted_list_is_sorted_func_t is_sorted;
};

struct is_sorted_wrap
{
	sorted_list_is_sorted_func_t is_sorted;
};

int FindWhereToInsert(const void *data, void *params, const void *data_to_match); 


sorted_list_t *SortedListCreate(sorted_list_is_sorted_func_t sorting_func)
{
	dlist_t *new_dlist = NULL;
	
	sorted_list_t *new_list = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	if(new_list == NULL)
	{
		return NULL;
	}
	new_dlist = DListCreate();
	
	if(new_dlist == NULL)
	{	
		free(new_list);
		return NULL;
	}
	new_list->dlist = new_dlist;
	new_list->is_sorted = sorting_func;
	
	return new_list;
}

size_t SortedListSize(const sorted_list_t *sorted_list)
{	
	assert(sorted_list != NULL);
	
	return DListSize(sorted_list->dlist);
}

int SortedListIsEmpty(const sorted_list_t *sorted_list)
{
	assert(sorted_list != NULL);
	
	return DListIsEmpty(sorted_list->dlist);

}
void SortedListDestroy(sorted_list_t *sorted_list)
{
	assert(sorted_list != NULL);
	
	DListDestroy((sorted_list->dlist));
	free(sorted_list);
}

sorted_list_iter_t SortedListBegin(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t it = {0};
	
	assert(sorted_list != NULL);
	
	it.iterator = DListBegin(sorted_list->dlist);
	return it;
}

/* Returns sorted list iterator to the element after the end of Sorted List */
sorted_list_iter_t SortedListEnd(const sorted_list_t *sorted_list)
{	
	sorted_list_iter_t it = {0};
	
	assert(sorted_list != NULL);
		
	it.iterator = DListEnd(sorted_list->dlist);
	return it;

}

/* Returns iterator to the next element in Sorted List
   SDListNext on End is undefined */
sorted_list_iter_t SortedListNext(const sorted_list_iter_t iter)
{
	dlist_iter_t dlistiter = iter.iterator;
	sorted_list_iter_t sortediter = {0};
	sortediter.iterator = DListNext(dlistiter);
	return sortediter;
	
}

/* Returns sorted list iterator to the previous element in Sorted List
   SortedListPrev on Begin is undefined
   SortedListPrev on End returns the last element in the list */
sorted_list_iter_t SortedListPrev(const sorted_list_iter_t iter)
{
	dlist_iter_t dlistiter = iter.iterator;
	sorted_list_iter_t sortediter = {0};
	sortediter.iterator = DListPrev(dlistiter);
	return sortediter;
}

/* Returns 1 on same; Otherwise returns 0 */
int SortedListIsSameIterator(const sorted_list_iter_t iter1, const sorted_list_iter_t iter2)
{
	return (iter1.iterator == iter2.iterator);  
}

/* Returns data pointer of the dlist_iter_t element */
void *SortedListGetData(const sorted_list_iter_t iter)
{	
	return DListGetData(iter.iterator);
}

int FindWhereToInsert(const void *data, void *params, const void *data_to_match)
{
	sorted_list_is_sorted_func_t is_sorted = ((struct is_sorted_wrap *)params)->is_sorted;
	return (is_sorted((void*)data_to_match, ((void*)data))); /* is new data before existing data*/
}

/* Returns iterator of the inserted element. On failure returns End */
sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data)
{
	dlist_iter_t inserted = NULL;
	dlist_iter_t iterbegin = NULL;
	dlist_iter_t iterend = NULL;
	sorted_list_iter_t it = {0};
	dlist_iter_t insert_before = NULL;
	struct is_sorted_wrap sorting_func = {NULL};
	
	assert(data != NULL);
	assert(sorted_list != NULL);	
	
	sorting_func.is_sorted = sorted_list->is_sorted;
	it.iterator = inserted;
	iterbegin = DListBegin(sorted_list->dlist);
	iterend = DListEnd(sorted_list->dlist);
	/*if the list is not empty , go over the list one by one, if the new data 
	should be before the current data, insert before the current iterator*/
	
	insert_before = DListFind(iterbegin, iterend, FindWhereToInsert,
								&sorting_func, data);
								
	inserted = DListInsert(sorted_list->dlist, insert_before, data);
	
	/*if(!SortedListIsEmpty(sorted_list))
	{		
		for(iterbegin = DListBegin(sorted_list->dlist) ; 
			!DListIsSameIterator(DListEnd(sorted_list->dlist),iterbegin) ; 
			iterbegin = DListNext(iterbegin))
		{
			if((sorted_list->is_sorted)(data, DListGetData(iterbegin))) 
			{				
				inserted = DListInsert(sorted_list->dlist, iterbegin, data);
				it.iterator = inserted;
				return it;
			}
		}
	}*/
	/*if the list is empty, insert at the begining (before the tail stub) or 
	if the  the new data didnt fit to any of the above, it should be inserted 
	at the end, before the tail stub*/
	
	/*inserted = DListInsert((sorted_list->dlist), DListEnd(sorted_list->dlist), data);*/
	
	it.iterator = inserted;
	return it; /*DListInsert returns end if it failed*/
	
}

/* Removes the element and returns the next sortedlist_iter_t */
sorted_list_iter_t SortedListErase(sorted_list_iter_t iter)
{
	sorted_list_iter_t it = iter;
	dlist_iter_t after_erased = DListErase(it.iterator);
	it.iterator = after_erased;
	return it;
}


/* Pop element from start of DList. Return data to user
   Pop on an empty list is undefined */
void *SortedListPopFront(sorted_list_t *sorted_list)
{
	assert(sorted_list != NULL);	
	return DListPopFront(sorted_list->dlist);
}

/* Pop element from end of DList. Return data to user
   Pop on an empty list is undefined */
void *SortedListPopBack(sorted_list_t *sorted_list)
{
	assert(sorted_list != NULL);	
	return DListPopBack(sorted_list->dlist);
}


/* Execute function for every element in "from..to" range in order ("to" element is excluded)
   On success: return 0 ; otherwise stop iteration and return status of first failed function */
int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to, sorted_list_action_func_t action, void *params)
{
	return DListForEach(from.iterator, to.iterator, action, params);
}


/* Returns dlist_iter_t that matches element in range. Returns End otherwsie */
sorted_list_iter_t SortedListFind(sorted_list_iter_t from, sorted_list_iter_t to, sorted_list_is_match_func_t is_match, void *params, const void *data_to_match)
{
	sorted_list_iter_t sorted_iterator = {0};
	
	dlist_iter_t dlist_iterator = DListFind(from.iterator, to.iterator,
											is_match, params, data_to_match);
											
	sorted_iterator.iterator = dlist_iterator;
	
	return sorted_iterator;
}
/* Gets two lists and merges them together. returns list1 and list 2 is empty.*/
sorted_list_t *SortedListMerge(sorted_list_t *sorted_list1, sorted_list_t *sorted_list2)
{

	/*  - compare each iterator of list1 with list 2.

		- if list2 iterator (from) shouldnt be inserted before (where),
		list 1 iterator is incremented.
		- otherwise, we "run" over list 2 until the condition is not met or we
		reach the end of the list.
		- then the current iterator is set as to and we  splice it before "where".
		- if the end of list 1 is reached and list 2 is not empty, all the
		 remaining items in list 2 are spliced to before end of 1*/

	dlist_iter_t to = NULL;
	dlist_iter_t from = NULL;
	dlist_iter_t where = NULL;
	dlist_iter_t end_list1 = NULL;
	dlist_iter_t end_list2 = NULL;

	struct is_sorted_wrap sorting_func = {NULL};
	
	assert(sorted_list1 != NULL);
	assert(sorted_list2 != NULL);

	sorting_func.is_sorted = sorted_list1->is_sorted;
	to = DListEnd(sorted_list2->dlist);
	from = DListBegin(sorted_list2->dlist);
	where = DListBegin(sorted_list1->dlist);
	end_list1 = DListEnd(sorted_list1->dlist);
	end_list2 = DListEnd(sorted_list2->dlist);


	while(!DListIsSameIterator(where,end_list1) && !DListIsSameIterator(from,end_list2))
	{
		/*find where to insert - compare from with the other list,
		 * find returns the node in which from is smaller than where */
		where = DListFind(where, end_list1, FindWhereToInsert,
								  &sorting_func, DListGetData(from));
								  
		if(DListIsSameIterator(where,end_list1))
		{
			break;
		}
		/*find the place in list 2 that should be the end of th ebatch to be spliced into list 1*/
		to =  DListFind(from, end_list2, FindWhereToInsert,
                                      &sorting_func, DListGetData(where));
                                      
        DListSpliceBefore(where, from, to);

        from = DListBegin(sorted_list2->dlist);

	}
	
	DListSpliceBefore(where, from, end_list2);
	return sorted_list1;

}


/*DIFFERENT VERSION OF MERGE< NOT USING FIND
sorted_list_t *SortedListMerge(sorted_list_t *sorted_list1, sorted_list_t *sorted_list2)
{*/

	/*  - compare each iterator of list1 with list 2. 
	
		- if list2 iterator (from) shouldnt be inserted before (where), 
		list 1 iterator is incremented. 
		- otherwise, we "run" over list 2 until the condition is not met or we 
		reach the end of the list. 
		- then the current iterator is set as to and we  splice it before "where". 
		- if the end of list 1 is reached and list 2 is not empty, all the
		 remaining items in list 2 are spliced to before end of 1*/	
/*	
	dlist_iter_t to = NULL;
	dlist_iter_t from = NULL;
	dlist_iter_t where = NULL;
	dlist_iter_t end_list1 = NULL;
	dlist_iter_t end_list2 = NULL;
	sorted_list_is_sorted_func_t IsSorted = NULL;
	
	assert(sorted_list1 != NULL);
	assert(sorted_list2 != NULL);		
	
	to = DListBegin(sorted_list2->dlist);
	from = DListBegin(sorted_list2->dlist);
	where = DListBegin(sorted_list1->dlist);
	end_list1 = DListEnd(sorted_list1->dlist);
	end_list2 = DListEnd(sorted_list2->dlist);
	IsSorted = sorted_list1->is_sorted;
	
	while(!DListIsSameIterator(where,end_list1) && !DListIsSameIterator(from,end_list2)) 
	{
		if(IsSorted(DListGetData(from), DListGetData(where)))
		{
			while(!DListIsSameIterator(to, end_list2) &&
				IsSorted(DListGetData(to), DListGetData(where)))
			{
				to = DListNext(to);
			}
			DListSpliceBefore(where, from, to);
			from = to;				
		}
		where = DListNext(where);
		
		if(DListIsSameIterator(where,end_list1)) 
		{	
			if(!SortedListIsEmpty(sorted_list2))
			{	
				DListSpliceBefore(where, from, end_list2);
			}
			return sorted_list1;
			
		}			
			
	}  
	return sorted_list1;
	

}*/










