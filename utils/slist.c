#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "slist.h"

#define MAX(a,b) a > b ? a : b
#define MIN(a,b) a < b ? a : b 

/*
typedef struct sl_node sl_node_t;
typedef int (*IsMatch_func_t)(const void *data, const void *params);
typedef int (*Action_func_t)((void *data, void *params);

struct sl_node 
{
	void *data;
	sl_node_t *next;
};
*/
sl_node_t *SListCreateNode(sl_node_t *next, void *data)
{
	sl_node_t *node = (sl_node_t *)malloc(sizeof(sl_node_t));
	if(NULL == node)
	{
		return NULL;
	}
	node->data = data;
	node->next = next;
	
	return node;
}

void SListFreeAll(sl_node_t *head)
{
	sl_node_t *node_ptr = NULL;

	
	while(head != NULL)
	{
		node_ptr = head;
		head = head->next;
		free(node_ptr);
	}

}

size_t SListCount(const sl_node_t *head)
{
	size_t counter = 1;
	sl_node_t *next_ptr = NULL; 
	
	next_ptr = head->next;
	
	while (next_ptr != NULL)
	{
		++counter;
		next_ptr = next_ptr->next;
	}
	return counter;
}
	

sl_node_t *SListInsertAfter(sl_node_t *after, sl_node_t *new_node) /* returns inseerted node */
{
	assert(after != NULL);
	assert(new_node != NULL);
	
	new_node->next = after->next;
	after->next = new_node;

	return new_node;

}

sl_node_t *SListInsert(sl_node_t *before, sl_node_t *new_node) /* returns inserted node */
{
	void *temp = NULL;
	
	assert(before != NULL);
	assert(new_node != NULL);
	
	new_node = SListInsertAfter(before, new_node);
	
	temp = new_node->data;
	new_node->data = before->data;
	before->data = temp;
	

	/*before is the inserted node because we switched the data*/
	return before;

}

sl_node_t *SListRemoveAfter(sl_node_t *after)/*returns removed pointer*/
{
	sl_node_t *to_remove = NULL;
	
	assert(after != NULL);
	if(after->next == NULL)
	{
		return NULL;
	}
	
	to_remove = after->next;
	after->next = after->next->next;
	to_remove->next = NULL;

	return to_remove;
}

sl_node_t *SListRemove(sl_node_t *to_remove)/*returns removed pointer*/
{
/* shouldn't be used to remove last item. checked with assertion only */
	sl_node_t *next_node = NULL;
	void *temp = NULL;
	
	assert(to_remove != NULL);
	assert(to_remove->next != NULL);
		
	/*define return as the one after to remove*/
	next_node = to_remove->next;
	/*switch data between to remove and to return*/
	temp = to_remove->data;
	to_remove->data = next_node->data;
	next_node->data = temp;
	/*disconnect to_return from the list on both ends - the node before it points to the one after it, and it points to NULL*/
	
	return SListRemoveAfter(to_remove);
}
/*will stop on first failure, return status of last action */
int SListForEach(sl_node_t *head, Action_func_t action, void* params)
{
	int result = 0;
	sl_node_t *next_ptr = NULL; 
	
	assert(head != NULL);
	
	next_ptr = head;
	
	while (next_ptr != NULL)
	{
		result += action(next_ptr->data,params);
		if(result != 0)
		{
			return result;
		}
		next_ptr = next_ptr->next;
	}
	return result;

}

sl_node_t *SListFind(sl_node_t *head, IsMatch_func_t IsMatch, const void* params)
{
	sl_node_t *next_ptr = NULL; 
	
	next_ptr = head;
	
	while (next_ptr != NULL)
	{	
		
		if(IsMatch(next_ptr->data, params))
		{
			return next_ptr;
		}
		next_ptr = next_ptr->next;
	}
	return NULL;

}

sl_node_t *SListFlip(sl_node_t *head)
{
	/*sl_node_t *curr_ptr = NULL;
	sl_node_t *next_ptr = NULL;
	sl_node_t *prev_ptr = NULL;
	
	assert(head != NULL);
	
	curr_ptr = head;
			
	while(curr_ptr != NULL)
	{
		next_ptr = curr_ptr->next;
		curr_ptr->next = prev_ptr;
		prev_ptr = curr_ptr;
		curr_ptr = next_ptr;
	}
	
	return prev_ptr;*/
	/*recursive:*/
	sl_node_t *next_ptr = NULL;
	sl_node_t *sorted = NULL;
	
	if(head->next == NULL)
	{
		return head;
	}
	next_ptr = head->next;
	sorted = SListFlip(next_ptr);
	head->next->next = head;
	head->next = NULL;
	return sorted;
	
}

int SListHasLoop(const sl_node_t *head)
{
	/*2 pointers: 1 moves 1 step ahead at a time, the other moves 2 steps at a time. */
	const sl_node_t *one_jumper = NULL;
	const sl_node_t *two_jumper = NULL;

	assert(head != NULL);
	
	one_jumper = head;
	two_jumper = head;

	while (one_jumper != NULL && two_jumper->next != NULL && two_jumper->next->next != NULL)
	{
		one_jumper = one_jumper->next;
		two_jumper = two_jumper->next->next;
		 
		if(one_jumper == two_jumper)
		{
			return 1;
		}

	}
	return 0;


}

sl_node_t *SListFindIntersection(const sl_node_t *head1, const sl_node_t *head2)
{
	const sl_node_t *next_node1 = head1;
	const sl_node_t *next_node2 = head2;
	size_t count1 = 0;
	size_t count2 = 0;
	size_t difference = 0;
	size_t index = 0;
	
	/* run till the end on both lists, if the last one of both is the same - there is an intersection. otherwise return null.*/
	while(next_node1->next != NULL)
	{
		next_node1 = next_node1->next;
		++count1;
	}
	while(next_node2->next != NULL)
	{
		 next_node2 = next_node2->next;
		 ++count2;
	}
	
	if(next_node2 != next_node1)
	{
		return NULL;
	}
	
	next_node1 = head1;
	next_node2 = head2;
	
	if(count1 > count2)
	{
		difference = count1 - count2;
		
		for (index = 0 ; index < difference ; ++index)
		{	
			next_node1 = next_node1->next;
		}
	}
	else
	{
		difference = count2 - count1;

		for (index = 0 ; index < difference ; ++index)
		{	
			next_node2 = next_node2->next;
		}
	}
	
	/*run on both 1 by 1*/
	
	while (next_node1 != NULL)
	{
		if(next_node1 == next_node2)
		{
			return (sl_node_t *)next_node1;
		}
		next_node2 = next_node2->next;
		next_node1 = next_node1->next;
	}
	
	return NULL;


}



