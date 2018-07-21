#include "sorted_list.h"  	/*declarations*/
#include <stdio.h>
#include <stdlib.h>  		/*CR: for using malloc*/
#include <assert.h> 		/*CR: for using assetrt*/

dlist_iter_t InjectBefore(dlist_iter_t iter1, dlist_iter_t iter2);


struct sorted_list 
{
	dlist_t *dlist;
	sorted_list_is_sorted_func_t is_sorted;
};

sorted_list_t *SortedListCreate(sorted_list_is_sorted_func_t sorting_func)
{
	dlist_t *new_dlist = NULL; /*CR: I've added few spaces between the lines here*/
	
	sorted_list_t *new_list = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	if(new_list == NULL)
	{
		return NULL;
	}
	new_dlist = DListCreate();
	
	if(new_dlist == NULL)
	{
		return NULL;
	}
	new_list->dlist = new_dlist;
	new_list->is_sorted = sorting_func;
	
	return new_list;
}

size_t SortedListSize(const sorted_list_t *sorted_list)
{	
	return DListSize(sorted_list->dlist);
}

int SortedListIsEmpty(const sorted_list_t *sorted_list)
{
	return DListIsEmpty(sorted_list->dlist);

}
void SortedListDestroy(sorted_list_t *sorted_list)
{
	DListDestroy((sorted_list->dlist));
	free(sorted_list);  /*CR: more of a question, don't you need to set the 'is_sorted' pounter to 'NULL' before 'free'*/
}

sorted_list_iter_t SortedListBegin(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t it = {0};
	it.iterator = DListBegin(sorted_list->dlist);
	return it;
}

/* Returns sorted list iterator to the element after the end of Sorted List */
sorted_list_iter_t SortedListEnd(const sorted_list_t *sorted_list)
{	
	sorted_list_iter_t it = {0};
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

/* Returns iterator of the inserted element. On failure returns End */
sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data)
{
	dlist_iter_t inserted = NULL;
	dlist_iter_t iterbegin = NULL;
	sorted_list_iter_t it = {0};
	it.iterator = inserted;
	/*if the list is not empty , go over the list one by one, if the new data 
	should be before the current data, insert before the current iterator*/
	if(!SortedListIsEmpty(sorted_list))
	{
		
		for(iterbegin = DListBegin(sorted_list->dlist) ; 
			!DListIsSameIterator(DListEnd(sorted_list->dlist), iterbegin); /*CR: fixed some spaces*/
			iterbegin = DListNext(iterbegin))
		{
			if((sorted_list->is_sorted)(data, DListGetData(iterbegin))) 
			{				
				inserted = DListInsert(sorted_list->dlist, iterbegin, data);
				it.iterator = inserted;
				return it;
			}
		}
	}
	/*if the list is empty, insert at the begining (before the tail stub) or 
	if the  the new data didnt fit to any of the above, it should be inserted 
	at the end, before the tail stub*/
	
	inserted = DListInsert((sorted_list->dlist), DListEnd(sorted_list->dlist), data);
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
	return DListPopFront(sorted_list->dlist);
}

/* Pop element from end of DList. Return data to user
   Pop on an empty list is undefined */
void *SortedListPopBack(sorted_list_t *sorted_list)
{
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
	
	dlist_iter_t dlist_iterator = DListFind(from.iterator, to.iterator, is_match, params, data_to_match); /*CR: fixed some spaces*/
	sorted_iterator.iterator = dlist_iterator;
	return sorted_iterator;
}
/* Gets two lists and merges them together. returns list1 and list 2 is empty.*/
/*
sorted_list_t *SortedListMerge(sorted_list_t *sorted_list1, sorted_list_t *sorted_list2)
{
	dlist_iter_t begin_iter1 = NULL;
	dlist_iter_t begin_iter2 = NULL;	

	for(begin_iter1 = DListBegin(sorted_list1->dlist) ;
	 !DListIsSameIterator(DListEnd(sorted_list1->dlist), begin_iter1) ; 
	 begin_iter1 = DListNext(begin_iter1))
	{
		 for(begin_iter2 = DListBegin(sorted_list2->dlist) ;
		 !DListIsSameIterator(DListEnd(sorted_list2->dlist), begin_iter2) ;
		 begin_iter2 = DListNext(begin_iter2))
		{
			if((sorted_list1->is_sorted)(DListGetData(begin_iter2), DListGetData(begin_iter1)))
			{
				DListSpliceBefore(begin_iter1, begin_iter2, DListNext(begin_iter2));
				break;
			}
			break;		
		}
	

	}
	if((sorted_list1->is_sorted)(DListGetData(DListPrev(DListEnd 
		(sorted_list1->dlist))),
		 DListGetData(DListPrev(DListEnd(sorted_list2->dlist)))))
	{
		DListSpliceBefore(DListEnd(sorted_list1->dlist), 
		DListPrev(DListEnd(sorted_list2->dlist)), DListEnd(sorted_list2->dlist));
	}
	
	return sorted_list1;

}*/

sorted_list_t *SortedListMerge(sorted_list_t *sorted_list1, sorted_list_t *sorted_list2)
{
	dlist_iter_t iter2 = DListBegin(sorted_list2->dlist);
	dlist_iter_t to = NULL;
	dlist_iter_t from = iter2;
	dlist_iter_t where = DListBegin(sorted_list1->dlist);
	dlist_iter_t end_list1 = DListEnd(sorted_list1->dlist);
	dlist_iter_t end_list2 = DListEnd(sorted_list2->dlist);
	
	while(!DListIsSameIterator(where,end_list1) && !DListIsSameIterator(from,end_list2)) /*next(where)!= null?   where is not same iterator as end?*/
	{
		if((sorted_list1->is_sorted)(DListGetData(from), DListGetData(where)))
		{
			from = iter2;
			while((DListNext(iter2) != NULL) &&
				(sorted_list1->is_sorted)(DListGetData(iter2), DListGetData(where)))
			{
				iter2 = DListNext(iter2);
			}
			to = iter2;
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
	

}


