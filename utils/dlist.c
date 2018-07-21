#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dlist.h"

typedef struct dl_node node_t;

struct dl_node 
{
	void *data;
	node_t *next;
	node_t *prev;
	
};

struct dlist 
{
	node_t *head;
	node_t *tail;
};

static node_t *CreateNode(node_t *prev, node_t *next, void *data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	
	if(NULL == new_node)
	{
		return NULL;
	}
	new_node->next = next;
	new_node->prev = prev;
	new_node->data = data;
	return new_node;  
}

dlist_t *DListCreate(void)
{
	node_t *headstub = NULL;
	node_t *tailstub = NULL;
	dlist_t *new_dlist = (dlist_t *)malloc(sizeof(dlist_t));
	if(NULL == new_dlist)
	{
		return NULL;
	}

	headstub = CreateNode(NULL, NULL, NULL);
	if(NULL == headstub)
	{
		free(new_dlist);
		return NULL;
	}

	tailstub = CreateNode(NULL, NULL, NULL);
	if(NULL == tailstub)
	{	
		free(headstub);
		free(new_dlist);
		return NULL;
	}

	tailstub->prev = headstub;
	headstub->next = tailstub;
	new_dlist->head = headstub;
	new_dlist->tail = tailstub;
	
	return new_dlist;
	
}

void DListDestroy(dlist_t *dlist)
{
	node_t *next_ptr = NULL;
	node_t *prev_ptr = NULL;
	
	assert(dlist != NULL);
	
	next_ptr = dlist->head;	
		
	while(next_ptr->next != NULL)	
	{	/*doesnt remove tail*/
		next_ptr = next_ptr->next;
		prev_ptr = next_ptr->prev;	
		free(prev_ptr);			
	}

	free(dlist->tail);
	dlist->tail = NULL;			
	free(dlist);
	dlist = NULL;
}

size_t DListSize(const dlist_t *dlist)
{
	dlist_iter_t start = NULL;
	dlist_iter_t end = NULL;
	size_t count = 0;
	
	assert(dlist != NULL);
	
	start = DListBegin(dlist);
	end = DListEnd(dlist);

	while(!DListIsSameIterator(start, end))
	{
		start = DListNext(start);
		++count;
	}
	
	return (count);
}

int DListIsEmpty(const dlist_t *dlist)
{
	assert(dlist != NULL);	
	return (DListIsSameIterator(DListBegin(dlist),DListEnd(dlist)));
}

/* Returns dlist iterator to the begining of DList */
dlist_iter_t DListBegin(const dlist_t *dlist)
{
	assert(dlist != NULL);
	return (dlist->head->next);
}

/* Returns dlist iterator to the element after the end of DList */
dlist_iter_t DListEnd(const dlist_t *dlist)
{
	assert(dlist != NULL);
	return (dlist->tail);
}

/* Returns iterator to the next element in DList
   DListNext on End is undefined */
dlist_iter_t DListNext(const dlist_iter_t iter)
{
	return (dlist_iter_t)(((node_t *)iter)->next);
}

/* Returns dlist iterator to the previous element in DList
   DListPrev on Begin is undefined
   DListPrev on End returns the last element in the list */
dlist_iter_t DListPrev(const dlist_iter_t iter)
{
	return (dlist_iter_t)(((node_t *)iter)->prev);
}

/* Returns 1 on same; Otherwise returns 0 */
int DListIsSameIterator(const dlist_iter_t iter1, const dlist_iter_t iter2)
{
	return (((node_t *)iter1) == ((node_t*)iter2));
}

/* Returns data pointer of the dlist_iter_t element */
void *DListGetData(const dlist_iter_t iter)
{	
	return (((node_t *)iter)->data);
}

/* Returns iterator of the inserted element. On failure returns End */
dlist_iter_t DListInsertAfter(dlist_t *dlist, dlist_iter_t iter, void *data)
{/*undefined behaviour on empty list*/
	node_t *new_node = NULL;
	assert(dlist != NULL);
	
	new_node = CreateNode(((node_t *)iter), (((node_t *)iter)->next), data);
	
	if(NULL == new_node)
	{
		return dlist->tail;	
	}
	
	(((node_t *)iter)->next)->prev = new_node;
	((node_t *)iter)->next = new_node;
	
	return new_node;
}

/* Returns iterator of the inserted element. On failure returns End */
dlist_iter_t DListInsert(dlist_t *dlist, dlist_iter_t iter, void *data)
{/*on empty list iter should be the end stub*/
	node_t *new_node = NULL;
	/*creates new node and sets it prev and next ptrs*/
	new_node = CreateNode((((node_t *)iter)->prev), ((node_t *)iter), data);
	if(NULL == new_node)
	{
		return dlist->tail;
	}
	/*next of prev ptr points to new node*/
	(((node_t *)iter)->prev)->next = new_node;
	/*prev of iter points to new node*/
	((node_t *)iter)->prev = new_node;
		
	return new_node;
}

/* Removes the element and returns the next dlist_iter_t */
dlist_iter_t DListErase(dlist_iter_t iter)
{	
	node_t *node_iter= iter;
	node_t *next_node = node_iter->next;
	node_t *prev_node = node_iter->prev;
	
	prev_node->next = next_node;
	next_node->prev = prev_node;
	
	free(node_iter);
	node_iter = NULL;
	
	return next_node;
}

/* Push element to start of DList. 
On success: return iterator to pushed element
On failure: return iterator to end]  			*/
dlist_iter_t DListPushFront(dlist_t *dlist, void *data)
{
	assert(dlist != NULL);
	return DListInsert(dlist, DListBegin(dlist), data);
}

/* Pop element from start of DList. Return data to user
   Pop on an empty list is undefined */
void *DListPopFront(dlist_t *dlist)
{
	node_t *to_remove = NULL;
	void* data_to_return = NULL;
		
	assert(dlist != NULL);
	
	to_remove = dlist->head->next;
	data_to_return = to_remove->data;
	
	DListErase(to_remove);
	
	return data_to_return;
}

/* Push element to end of DList. 
On success: return iterator to pushed element
On failure: return iterator to end]  			*/
dlist_iter_t DListPushBack(dlist_t *dlist, void *data)
{
	return DListInsert(dlist, DListEnd(dlist), data);
}

/* Pop element from end of DList. Return data to user
   Pop on an empty list is undefined */
void *DListPopBack(dlist_t *dlist)
{
	node_t *to_remove = NULL;
	void* data_to_return = NULL;
	
	to_remove = dlist->tail->prev;
	data_to_return = to_remove->data;
	DListErase(to_remove);

	return data_to_return;
}

int DListForEach(dlist_iter_t from, dlist_iter_t to, DListAction_func_t action, void *params)
{
	int index = 0, result = 0;
	dlist_iter_t it = 0;
	
	for(it = from ; !DListIsSameIterator(to,it) ; 
		it = DListNext(it), ++index)
	{
		result = action(((node_t *)it)->data, params);
		if(result)
		{
			return result;
		}
	}
	return result;
}

dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, DListIsMatch_func_t is_match, void *params, const void *data_to_match)
{
	int index = 0;
	dlist_iter_t it = 0;
	
	for(it = from ; !DListIsSameIterator(to,it) ; 
		it = DListNext(it), ++index)
	{
		if(is_match(((node_t *)it)->data, params, data_to_match))
		{
			return it;
		}
	}
	return to;
}

dlist_iter_t DListSpliceBefore(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to)
{
	/*everything is easier with automatic variables*/
	node_t *to_node = to;
	node_t *before_to_node = to_node->prev;
	node_t *from_node = from;
	node_t *before_from_node = from_node->prev;
	node_t *where_node = where;
	node_t *before_where_node = where_node->prev;
	
	if(DListIsSameIterator(from, to))
	{
		return where;
	}
	
	/*connect ends around to and from*/
	before_from_node->next = to_node;
	to_node->prev = before_from_node;
	
	/*connect before where with the start of from*/
	before_where_node->next = from_node;
	from_node->prev = before_where_node;
	
	/*connect where with the end of to*/
	where_node->prev = before_to_node;
	before_to_node->next = where_node;
	
	return where;
}
	
	
	
	

