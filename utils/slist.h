#ifndef SLIST_H
#define SLIST_H

typedef struct sl_node sl_node_t;
typedef int (*IsMatch_func_t)(const void *data, const void *params);
typedef int (*Action_func_t)(void *data, void *params);

struct sl_node 
{
	void *data;
	sl_node_t *next;
};

sl_node_t *SListCreateNode(sl_node_t *next, void *data);

void SListFreeAll(sl_node_t *head);

size_t SListCount(const sl_node_t *head);

sl_node_t *SListInsertAfter(sl_node_t *after, sl_node_t *new_node); /* returns next node */

sl_node_t *SListInsert(sl_node_t *before, sl_node_t *new_node);

sl_node_t *SListRemoveAfter(sl_node_t *after);

/* shouldn't be used to remove last item. checked with assertion only */
sl_node_t *SListRemove(sl_node_t *to_remove); 

/*will stop on first failure, return status of last action */
int SListForEach(sl_node_t *head, Action_func_t action, void* params);   

sl_node_t *SListFind(sl_node_t *head, IsMatch_func_t IsMatch, const void* params);

sl_node_t *SListFlip(sl_node_t *head);

int SListHasLoop(const sl_node_t *head);

sl_node_t *SListFindIntersection(const sl_node_t *head1, const sl_node_t *head2);

#endif

