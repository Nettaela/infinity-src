#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dlist.h"

void UnitestBasic(void);
void UnitestIter(void);
void UnitestForEach(void);
void UnitestFind(void);
void UnitestSplice(void);
int TimesTwo(void *data, void *params);
int FindIsMatch(const void *data, void *params, const void *data_to_match);

int main()
{
	UnitestBasic();
	UnitestIter();
	UnitestForEach();
	UnitestFind();
	UnitestSplice();
	return EXIT_SUCCESS;
}

void UnitestBasic(void)
{
	/*create*/
	dlist_t *my_dlist = DListCreate();
	assert(0 == DListSize(my_dlist));
	assert(1 == DListIsEmpty(my_dlist));
	
	DListDestroy(my_dlist);
	
	puts("basic test completed");

}

void UnitestIter(void)
{
	int data[4] = {10, 20, 30, 40};
	int index = 0;
	
	dlist_iter_t iter = NULL;
	dlist_iter_t iter1 = NULL;
	
	dlist_t *my_dlist = DListCreate();

	assert(0 == DListSize(my_dlist));
	assert(1 == DListIsEmpty(my_dlist));
	/*insert (before) to empty list - must use end iterator*/
	iter1 = DListInsert(my_dlist, DListEnd(my_dlist), &data[1]);/*iter 1 is the inserted node*/
	/*insert after the previously inserted node*/
	assert(1 == DListSize(my_dlist));
	DListInsertAfter(my_dlist, iter1, &data[2]); 
	/*list should look like: 20, 30*/
	assert(2 == DListSize(my_dlist));
	/*iterate*/
	for(iter = DListBegin(my_dlist) ; !DListIsSameIterator(DListEnd(my_dlist),iter) ; 
		iter = DListNext(iter), ++index)
	{
		assert(*(data + index+1) == *(int *)(DListGetData(iter)));
	}
	
	
	/*push stuff*/
	DListPushFront(my_dlist, &data[0]);
	assert(3 == DListSize(my_dlist));
	/*10 20 30*/ 
	
	DListPushBack(my_dlist, &data[3]);
	/*10 20 30 40*/ 
	assert(4 == DListSize(my_dlist));
	
	/*iterate*/
	index = 0;
	for(iter = DListBegin(my_dlist) ; !DListIsSameIterator(DListEnd(my_dlist),iter) ; 
		iter = DListNext(iter), ++index)
	{
		/*printf("%d\n",*(int *)(DListGetData(iter)));*/
		assert(*(data + index) == *(int *)(DListGetData(iter)));
	}
	
	
	/*pop*/
	assert(*(int*)DListPopFront(my_dlist) == data[0]); 
	assert(*(int*)DListPopBack(my_dlist) == data[3]);

	
	/*erase*/
	/*assert(*(int*)DListErase(DListPrev(DListEnd(my_dlist))) == data[2]);*/
	
	DListErase(DListPrev(DListEnd(my_dlist)));
	
	assert(data[1] == *(int *)(DListGetData(DListBegin(my_dlist))));
	assert(1 == DListSize(my_dlist));
	
	
	
	DListDestroy(my_dlist);
	puts("passed iterations push and pop tests");

}

void UnitestForEach(void)
{

	int data[4] = {10, 20, 30, 40};
	int index = 0;
	int result = 0;
	dlist_iter_t iter = NULL;
	dlist_iter_t iter1 = NULL;
	
	dlist_t *my_dlist = DListCreate();

	assert(0 == DListSize(my_dlist));
	assert(1 == DListIsEmpty(my_dlist));
	/*insert (before) to empty list - must use end iterator*/
	iter1 = DListInsert(my_dlist, DListEnd(my_dlist), &data[1]);/*iter 1 is the inserted node*/
	/*insert after the previously inserted node*/
	assert(1 == DListSize(my_dlist));
	DListInsertAfter(my_dlist, iter1, &data[2]); 
	/*list should look like: 20, 30*/
	assert(2 == DListSize(my_dlist));
	/*iterate*/
	DListPushFront(my_dlist, &data[0]);
	assert(3 == DListSize(my_dlist));
	/*10 20 30*/ 
	
	DListPushBack(my_dlist, &data[3]);
	/*10 20 30 40*/ 
	assert(4 == DListSize(my_dlist));
	
	result = DListForEach(DListBegin(my_dlist), DListEnd(my_dlist), TimesTwo, &data);
	
	for(iter = DListBegin(my_dlist) ; !DListIsSameIterator(DListEnd(my_dlist),iter) ; 
		iter = DListNext(iter), ++index)
	{
		
		assert((*(data + index)) == *(int *)(DListGetData(iter)));
	}
	
	DListDestroy(my_dlist);
	puts("passed for each tests");

}

void UnitestFind(void)
{
	int data[4] = {10, 20, 30, 40};
	int index = 0;
	int tofind = 23;
	dlist_iter_t result = 0;
	dlist_iter_t result2 = 0;
	dlist_iter_t iter = NULL;
	dlist_iter_t iter1 = NULL;
	
	dlist_t *my_dlist = DListCreate();

	assert(0 == DListSize(my_dlist));
	assert(1 == DListIsEmpty(my_dlist));
	/*insert (before) to empty list - must use end iterator*/
	iter1 = DListInsert(my_dlist, DListEnd(my_dlist), &data[1]);/*iter 1 is the inserted node*/
	/*insert after the previously inserted node*/
	assert(1 == DListSize(my_dlist));
	DListInsertAfter(my_dlist, iter1, &data[2]); 
	/*list should look like: 20, 30*/
	assert(2 == DListSize(my_dlist));
	/*iterate*/
	DListPushFront(my_dlist, &data[0]);
	assert(3 == DListSize(my_dlist));
	/*10 20 30*/ 
	
	DListPushBack(my_dlist, &data[3]);
	/*10 20 30 40*/ 
	assert(4 == DListSize(my_dlist));
	/*something to find*/
	result = DListFind(DListBegin(my_dlist), DListEnd(my_dlist), FindIsMatch, &data, &data[2]);
	assert(*(int *)(DListGetData(result)) == data[2]);
	
	/*no thing to find*/
	result2 = DListFind(DListBegin(my_dlist), DListEnd(my_dlist), FindIsMatch, &data, &tofind);
	/*assert((DListGetData(result2)) == NULL);*/
	
	DListDestroy(my_dlist);
	puts("passed find tests");

}

void UnitestSplice(void)
{
	int data[4] = {10, 20, 30, 40};
	int splicedata[3] = {100,200,300};
	int index = 0;
	int tofind = 23;
	dlist_iter_t result = 0;
	dlist_iter_t where = 0;
	dlist_iter_t iter = NULL;
	dlist_iter_t iter1 = NULL;
	dlist_iter_t to = NULL;
	dlist_iter_t from = NULL;
	
	dlist_t *my_dlist = DListCreate();
	dlist_t *splice_dlist = DListCreate();
	
	assert(0 == DListSize(my_dlist));
	assert(1 == DListIsEmpty(my_dlist));
	/*insert (before) to empty list - must use end iterator*/
	iter1 = DListInsert(my_dlist, DListEnd(my_dlist), &data[1]);/*iter 1 is the inserted node*/
	/*insert after the previously inserted node*/
	assert(1 == DListSize(my_dlist));
	DListInsertAfter(my_dlist, iter1, &data[2]); 
	/*list should look like: 20, 30*/
	assert(2 == DListSize(my_dlist));
	/*iterate*/
	DListPushFront(my_dlist, &data[0]);
	assert(3 == DListSize(my_dlist));
	/*10 20 30*/ 
	DListPushBack(my_dlist, &data[3]);
	/*10 20 30 40*/ 
	assert(4 == DListSize(my_dlist));
	
	/*fill splice list fast*/
	DListPushFront(splice_dlist, &splicedata[2]);
	DListPushFront(splice_dlist, &splicedata[1]);	
	DListPushFront(splice_dlist, &splicedata[0]);

	/*splice from begining of splice list to the end. put in my list after the second node*/
	where = DListNext(DListNext(DListBegin(my_dlist)));
	result = DListSpliceBefore(where, DListBegin(splice_dlist), DListEnd(splice_dlist));
	assert(where == result);
	/*now print*/
	
	index = 0;
	for(iter = DListBegin(my_dlist) ; !DListIsSameIterator(DListEnd(my_dlist),iter) ; 
		iter = DListNext(iter), ++index)
	{
		printf("%d\n",*(int *)(DListGetData(iter)));
		/*assert(*(data + index) == *(int *)(DListGetData(iter)));*/
	}
	
	/*test when splicing from the same list*/
	
	/*from = */
	
	
	
	
	
	
	
	
	
		
	DListDestroy(my_dlist);
	DListDestroy(splice_dlist);
	puts("passed splice tests");
	


}





int TimesTwo(void *data, void *params)
{
	(void)params;	
	*(int*)data = *(int*)(data)*2;
	return 0;
}


int FindIsMatch(const void *data, void *params, const void *data_to_match)
{
	(void)params;	
	return (*(int*)data == *(int*)data_to_match);
}











