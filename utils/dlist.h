

#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>		/* For size_t	*/

typedef int (*DListIsMatch_func_t)(const void *data, void *params, const void *data_to_match);
typedef int (*DListAction_func_t)(void *data, void *params);

typedef void *dlist_iter_t;

/* Controller struct */
typedef struct dlist dlist_t;

/* Create DList. */
dlist_t *DListCreate(void);

/* Destroy the DList */
void DListDestroy(dlist_t *dlist);

/* Return number of elements in DList */
size_t DListSize(const dlist_t *dlist);

/* returns 1 on empty DList ; otherwise returns 0 */
int DListIsEmpty(const dlist_t *dlist);

/* Returns dlist iterator to the begining of DList */
dlist_iter_t DListBegin(const dlist_t *dlist);

/* Returns dlist iterator to the element after the end of DList */
dlist_iter_t DListEnd(const dlist_t *dlist);

/* Returns iterator to the next element in DList
   DListNext on End is undefined */
dlist_iter_t DListNext(const dlist_iter_t iter);

/* Returns dlist iterator to the previous element in DList
   DListPrev on Begin is undefined
   DListPrev on End returns the last element in the list */
dlist_iter_t DListPrev(const dlist_iter_t iter);

/* Returns 1 on same; Otherwise returns 0 */
int DListIsSameIterator(const dlist_iter_t iter1, const dlist_iter_t iter2);

/* Returns data pointer of the dlist_iter_t element */
void *DListGetData(const dlist_iter_t iter);

/* Returns iterator of the inserted element. On failure returns End */
dlist_iter_t DListInsertAfter(dlist_t *dlist, dlist_iter_t iter, void *data);

/* Returns iterator of the inserted element. On failure returns End */
dlist_iter_t DListInsert(dlist_t *dlist, dlist_iter_t iter, void *data);

/* Removes the element and returns the next dlist_iter_t */
dlist_iter_t DListErase(dlist_iter_t iter);

/* Push element to start of DList. 
On success: return iterator to pushed element
On failure: return iterator to end]  			*/
dlist_iter_t DListPushFront(dlist_t *dlist, void *data); 

/* Pop element from start of DList. Return data to user
   Pop on an empty list is undefined */
void *DListPopFront(dlist_t *dlist);

/* Push element to end of DList. 
On success: return iterator to pushed element
On failure: return iterator to end]  			*/
dlist_iter_t DListPushBack(dlist_t *dlist, void *data);

/* Pop element from end of DList. Return data to user
   Pop on an empty list is undefined */
void *DListPopBack(dlist_t *dlist); 

/* Execute function for every element in "from..to" range in order ("to" element is excluded)
   On success: return 0 ; otherwise stop iteration and return status of first failed function */
int DListForEach(dlist_iter_t from, dlist_iter_t to, DListAction_func_t action, void *params);

/* Returns dlist_iter_t that matches element in range. Returns End otherwsie */
dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, DListIsMatch_func_t is_match, void *params, const void *data_to_match);

/* Move elements in "from..to" range ("to" element is excluded) before "where" 
   (spliced elements start at "where"). Returns "where" iterator */
dlist_iter_t DListSpliceBefore(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to);


#endif

