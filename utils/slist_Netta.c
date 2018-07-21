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
	sl_node_t *next_ptr = NULL; /* CR : its not so informative to call it next_ptr , because it holdes the adress of 
	the current node we are freeing + missing assert() */
	
	while(head != NULL)
	{
		next_ptr = head;
		head = head->next;
		free(next_ptr);
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
	/* CR : assert() */
	new_node->next = after->next;
	after->next = new_node;

	return new_node;

}

sl_node_t *SListInsert(sl_node_t *before, sl_node_t *new_node) /* returns inserted node */
{
	/* CR : assert() */
	void *temp = new_node->data;
	new_node->data = before->data;
	before->data = temp;
	/* CR : these lines do exactly what InsertAfter() does so we can use her */ 
	new_node->next = before->next;
	before->next = new_node;
	
	return before;/*before is the inserted node because we switched the data*/
}

sl_node_t *SListRemoveAfter(sl_node_t *after)/*returns removed pointer*/
{
	/* CR : assert(after != NULL); --------- if! next is null do nothing */
	sl_node_t *to_remove = after->next;
	after->next = after->next->next;
	to_remove->next = NULL;

	return to_remove;
}

sl_node_t *SListRemove(sl_node_t *to_remove)/*returns removed pointer*/
{

/* CR : again here with the use of Removeafter()
	missing assert() , and if we remove the last element we dont want our program to crash so no need for the assert onlu if..  -------------- assert*/


/* shouldn't be used to remove last item. checked with assertion only */
	sl_node_t *to_return = NULL;
	void *temp = NULL;
	
	assert(to_remove->next != NULL);
	assert(to_remove != NULL);
	
	
	/*define return as the one after to remove*/
	to_return = to_remove->next;
	/*switch data between to remove and to return*/
	temp = to_remove->data;
	to_remove->data = to_return->data;
	to_return->data = temp;
	/*disconnect to_return from the list on both ends - the node before it points to the one after it, and it points to NULL*/
	to_remove->next = to_return->next;
	to_return->next = NULL;
	
	return to_return;
}
/*will stop on first failure, return status of last action */
int SListForEach(sl_node_t *head, Action_func_t action, void* params)
{

/* CR : missing assert() it would be more efficient if you add to the while condition result != 0 so once one function fails it stops checkong */
	int result = 0;
	sl_node_t *next_ptr = NULL; 
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
	/* CR :  assert() */
	sl_node_t *curr_ptr = head; /* CR : curr shoud be head->next */
	sl_node_t *next_ptr = NULL;
	sl_node_t *prev_ptr = NULL; /* CR : prev should be head*/
 
	while(curr_ptr != NULL)
	{
		next_ptr = curr_ptr->next;
		curr_ptr->next = prev_ptr;
		prev_ptr = curr_ptr;
		curr_ptr = next_ptr;
	}
	
	return prev_ptr;
}

int SListHasLoop(const sl_node_t *head)
{
	/*2 pointers: 1 moves 1 step ahead at a time, the other moves 2 steps at a time. */

	/* CR : assert() */
	const sl_node_t *one_jumper = head;
	const sl_node_t *two_jumper = head;

	while (one_jumper != NULL && two_jumper != NULL) 
	{
		one_jumper = one_jumper->next;
		two_jumper = (one_jumper == NULL)? one_jumper : two_jumper->next->next; 
		 
		if(one_jumper == two_jumper)
		{
			return 1;
		}

	}
	return 0;

}

sl_node_t *SListFindIntersection(const sl_node_t *head1, const sl_node_t *head2)
{
/* CR : there is a shorter solution with less loops */
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



