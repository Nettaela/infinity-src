#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "slist.h"

void Unitest(void);
void Unitestloop(void);
void Unitestintersection(void);
void ListPrinter(sl_node_t *head);
int TimesTwo(void *data, void *params);
int FindIsMatch(const void *data, const void *params);

int main()
{
	Unitest();
	Unitestloop();
	Unitestintersection();
	return EXIT_SUCCESS;
}

void Unitest(void)
{
	int data1 = 2;
	int data2 = 43;
	int data3 = 565;
	int data4 = 1423;
	int newdata = 55465;
	int newdata2 = 5543425;
	size_t nodes_count = 4;
	void *params = &newdata;
	int data3times2 = data3 * 2;
	void *params_match = &data3times2;
	sl_node_t *head = NULL;
	sl_node_t *last = SListCreateNode(NULL, &data4);
	sl_node_t *node1 = SListCreateNode(last,&data3);
	sl_node_t *node2 = SListCreateNode(node1,&data2);
	sl_node_t *node3 = SListCreateNode(node2,&data1);
	sl_node_t *new_node = SListCreateNode(NULL,&newdata);
	sl_node_t *new_node2 = SListCreateNode(NULL,&newdata2);

	sl_node_t *removed_node = NULL;

	head = node3;

	assert(last != NULL);
	assert(node1 != NULL);
	assert(node2 != NULL);
	assert(node3 != NULL);
	assert(new_node != NULL);
	assert(new_node2 != NULL);
	
	assert(SListCount(head) == 4);
	
	ListPrinter(head);
	
	/*printf("inserted after node 2: %d\n", *(int*)(SListInsertAfter(node2,new_node)->data)); */
	assert(55465 == *(int*)(SListInsertAfter(node2,new_node)->data));
	assert(SListCount(head) == 5);
	/*ListPrinter(head);*/
	
	/*printf("inserted at node 3: %d\n", *(int*)(SListInsert(new_node,new_node2)->data)); */
	assert(5543425 == *(int*)(SListInsert(new_node,new_node2)->data));
	assert(SListCount(head) == 6);
	/*ListPrinter(head);*/
	
	removed_node = SListRemoveAfter(node2);
	
	/*printf("remove after node 2: %d\n", *(int*)removed_node->data);*/
	assert(5543425 == *(int*)removed_node->data);
	/*ListPrinter(head);*/
	assert(SListCount(head) == 5);
	free(removed_node);
	
	removed_node = SListRemove(new_node2);
	
	/*printf("remove at node 3: %d\n", *(int*)removed_node->data);*/
	assert(55465 == *(int*)removed_node->data);
	assert(SListCount(head) == 4);
	/*ListPrinter(head);*/
	free(removed_node);
	
	assert(0 == SListForEach(head, TimesTwo, params));/* multiples every item in the list by 2*/
	puts("should be multiplied by 2");
	ListPrinter(head);
	
	/*printf("params is %d, revcieved pointer pointes to: %d\n", *(int*)params_match,
			 				*(int*)(SListFind(head, FindIsMatch, params_match))->data);*/
	assert(*(int*)params_match == *(int*)(SListFind(head, FindIsMatch, params_match))->data);
	head = SListFlip(head);
	puts("should be flipped");
	ListPrinter(head);


	
	
	SListFreeAll(head);
	puts("no errors? you can go to the beach!");

}

void Unitestloop(void)
{
	int data1 = 2;
	int data2 = 43;
	int data3 = 565;
	int data4 = 1423;
	/*create list*/
	sl_node_t *head = NULL;
	sl_node_t *last = SListCreateNode(NULL, &data4);
	sl_node_t *node1 = SListCreateNode(last,&data3);
	sl_node_t *node2 = SListCreateNode(node1,&data2);
	sl_node_t *node3 = SListCreateNode(node2,&data1);

	head = node3;
	/*test that there is no loop*/
	assert(SListHasLoop(head) == 0);

	/*free list so it can be reused*/
	SListFreeAll(head);
	
	head = NULL;
	
	
	/*make a loop*/
	last = SListCreateNode(NULL, &data4);
	node1 = SListCreateNode(NULL,&data3);
	node2 = SListCreateNode(NULL,&data2);
	node3 = SListCreateNode(NULL,&data1);

	last->next = node1;
	node1->next = last;
	node2->next = node1;
	node3->next = node2;

	head = node3;
	assert(SListHasLoop(head) == 1);
	
	/*make it stop being a loop*/	
	last->next = NULL;
	
	assert(SListHasLoop(head) == 0);
	
	/*free it*/

	SListFreeAll(head);
	
	puts("no errors in has loop? you can go to the beach!");



}
void Unitestintersection(void)
{
	int data1 = 2;
	int data2 = 43;
	int data3 = 565;
	int data4 = 1423;
	/*create 2 lists*/
	sl_node_t *head = NULL;
	sl_node_t *head2 = NULL;
	sl_node_t *nodeintersectionlast = SListCreateNode(NULL, &data4);
	sl_node_t *nodeintersection1 = SListCreateNode(nodeintersectionlast,&data3);
	sl_node_t *nodeintersection2 = SListCreateNode(nodeintersection1,&data3);
	sl_node_t *last = SListCreateNode(NULL, &data4);
	sl_node_t *node1 = SListCreateNode(last,&data3);
	sl_node_t *node2 = SListCreateNode(node1,&data2);
	sl_node_t *node3 = SListCreateNode(node2,&data1);
	/*check that there is no intersection*/
	head = node3;
	head2 = nodeintersection2;
	assert(NULL == SListFindIntersection(head, head2));

	/*another head that points to somewhere in the list*/
		
	head2->next->next = head->next->next->next;
	/*printf("%d\n",*(int *)(SListFindIntersection(head, head2)->data));*/
	assert(data4 == *(int *)(SListFindIntersection(head, head2)->data));
   	
   	

	free(head2->next->next);
	head2->next->next = NULL;
	/*free(head2->next);*/
	
	SListFreeAll(head);
	SListFreeAll(head2);
	
	puts("no errors in find intersection? you can go to the beach!");

}


void ListPrinter(sl_node_t *head)
{
	sl_node_t *next_ptr = head;
	int i = 1;
	while(next_ptr != NULL)
	{
		printf("node %d = %d\n",i, *(int*)next_ptr->data);
		next_ptr = next_ptr->next;
		++i;		
	}
	puts("------------------");
}
int TimesTwo(void *data, void *params)
{
	(void)params;	
	*(int*)data = *(int*)(data)*2;
	return 0;
}


int FindIsMatch(const void *data, const void *params)
{
	return (*(int*)data == *(int*)params);
}
















