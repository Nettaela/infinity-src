#include "sorted_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void UnitestBasic(void);
void UnitestInsert(void);
void UnitestErase(void);
void UnitestPops(void);
void UnitestForeach(void);
void UnitestFind(void);
void UnitestMerge(void);
void SortedListMergeUritest(void);
void UltimateMergeTest(void);


int IsSortedInt(void *a, void *b);
int IntimLowtoHigh(void *data1, void *data2); /*sorting function*/
int TimesTwo(void *data, void *params);		  /*for use in for each*/
int FindIsMatch(const void *data, void *params, const void *data_to_match); /*find*/


int main()
{
	UnitestBasic();
	UnitestInsert();
	UnitestErase();
	UnitestPops();
	UnitestForeach();
	UnitestFind();
	UnitestMerge();
	UltimateMergeTest();
	SortedListMergeUritest();
	return EXIT_SUCCESS;
}

void UnitestBasic(void)
{
	
	/*testing create, size and is empty*/
	sorted_list_t *my_list = NULL;
	
	printf("basic test...");
	my_list = SortedListCreate(IntimLowtoHigh);
	assert(SortedListSize(my_list) == 0);
	assert(SortedListIsEmpty(my_list) == 1);
	
	/*test destroy*/
	SortedListDestroy(my_list);
	puts("passed");

}
void UnitestInsert(void)
{
	/*create*/
	sorted_list_t *my_list = NULL;
	sorted_list_iter_t iter1 = {0};
	int data1 = 1;
	int data2 = 2;
	int data5 = 5;
	int data3 = 3;
	printf("insert test...");
	my_list = SortedListCreate(IntimLowtoHigh);
	assert(SortedListSize(my_list) == 0);
	assert(SortedListIsEmpty(my_list) == 1);
	
	/*insert*/
	iter1 = SortedListInsert(my_list, &data1);
	/*check size changed*/
	assert(SortedListSize(my_list) == 1);
	assert(SortedListIsEmpty(my_list) == 0);
	
	/*get data*/
	assert(*(int*)SortedListGetData(iter1) == data1);
	/*insert another after that*/
	iter1 = SortedListInsert(my_list, &data2);
	assert(SortedListSize(my_list) == 2);
	assert(SortedListIsEmpty(my_list) == 0);
	assert(*(int*)SortedListGetData(iter1) == data2);
	
	/*check that the order is correct and test iterators*/
	/*first one should be data1*/
	assert(*(int*)SortedListGetData(SortedListBegin(my_list)) == data1);
	/*next one should be data2*/
	assert(*(int*)SortedListGetData(SortedListNext(SortedListBegin(my_list))) == data2);
	
	/*insert a larger number*/
	iter1 = SortedListInsert(my_list, &data5);
	assert(SortedListSize(my_list) == 3);
	assert(SortedListIsEmpty(my_list) == 0);
	assert(*(int*)SortedListGetData(iter1) == data5);
	
	/*now see if its the last one*/
	
	assert(*(int*)SortedListGetData(SortedListPrev(SortedListEnd(my_list))) == data5);

	/*now insert a number that should be going in between*/
	iter1 = SortedListInsert(my_list, &data3);
	assert(SortedListSize(my_list) == 4);
	assert(SortedListIsEmpty(my_list) == 0);
	assert(*(int*)SortedListGetData(iter1) == data3);
	
	/*check that the order is correct: the last one is data 5 and the 
	prev should be data3*/
	assert(*(int*)SortedListGetData(SortedListPrev(SortedListEnd(my_list))) == data5);
	assert(*(int*)SortedListGetData(SortedListPrev(SortedListPrev(SortedListEnd(my_list)))) == data3);
	
	/*insert a number that is already inside*/
	iter1 = SortedListInsert(my_list, &data3);
	assert(SortedListSize(my_list) == 5);
	assert(SortedListIsEmpty(my_list) == 0);
	assert(*(int*)SortedListGetData(iter1) == data3);
	
	
	
	/*destroy*/
	SortedListDestroy(my_list);
	puts("passed");


}
void UnitestErase(void)
{
	/*create the same list as before*/
	sorted_list_t *my_list = NULL;
	sorted_list_iter_t iter1 = {0};
	int data1 = 1;
	int data2 = 2;
	int data5 = 5;
	int data3 = 3;
	printf("erase test...");
	my_list = SortedListCreate(IntimLowtoHigh);
	assert(SortedListSize(my_list) == 0);
	assert(SortedListIsEmpty(my_list) == 1);
	
	/*insert*/
	iter1 = SortedListInsert(my_list, &data1);
	/*check size changed*/
	assert(SortedListSize(my_list) == 1);
	assert(SortedListIsEmpty(my_list) == 0);
	
	/*get data*/
	assert(*(int*)SortedListGetData(iter1) == data1);
	/*insert another after that*/
	iter1 = SortedListInsert(my_list, &data2);
	assert(SortedListSize(my_list) == 2);
	assert(SortedListIsEmpty(my_list) == 0);
	assert(*(int*)SortedListGetData(iter1) == data2);
	
	/*check that the order is correct and test iterators*/
	/*first one should be data1*/
	assert(*(int*)SortedListGetData(SortedListBegin(my_list)) == data1);
	/*next one should be data2*/
	assert(*(int*)SortedListGetData(SortedListNext(SortedListBegin(my_list))) == data2);
	
	/*insert a larger number*/
	iter1 = SortedListInsert(my_list, &data5);
	assert(SortedListSize(my_list) == 3);
	assert(SortedListIsEmpty(my_list) == 0);
	assert(*(int*)SortedListGetData(iter1) == data5);
	
	/*now see if its the last one*/
	
	assert(*(int*)SortedListGetData(SortedListPrev(SortedListEnd(my_list))) == data5);

	/*now insert a number that should be going in between*/
	iter1 = SortedListInsert(my_list, &data3);
	assert(SortedListSize(my_list) == 4);
	assert(SortedListIsEmpty(my_list) == 0);
	assert(*(int*)SortedListGetData(iter1) == data3);
	
	/*check that the order is correct: the last one is data 5 and the 
	prev should be data3*/
	assert(*(int*)SortedListGetData(SortedListPrev(SortedListEnd(my_list))) == data5);
	assert(*(int*)SortedListGetData(SortedListPrev(SortedListPrev(SortedListEnd(my_list)))) == data3);
	
	/*erase head*/
	iter1 = SortedListErase(SortedListBegin(my_list));
	assert(*(int*)SortedListGetData(iter1) == *(int*)SortedListGetData(SortedListBegin(my_list)));
	assert(data2 == *(int*)SortedListGetData(SortedListBegin(my_list)));
	
	/*erase before tail*/
	iter1 = SortedListErase(SortedListPrev(SortedListEnd(my_list)));
	assert(data3 == *(int*)SortedListGetData(SortedListPrev(SortedListEnd(my_list))));
	assert(SortedListGetData(iter1) == SortedListGetData(SortedListEnd(my_list)));
	assert(*(int*)SortedListGetData(SortedListPrev(iter1)) == 
	*(int*)SortedListGetData(SortedListPrev(SortedListEnd(my_list))));
	
	
	
	/*destroy*/
	SortedListDestroy(my_list);
	puts("passed");



}

void UnitestPops(void)
{

	/*create the same list as before*/
	sorted_list_t *my_list = NULL;
	sorted_list_iter_t iter1 = {0};
	int data1 = 1;
	int data2 = 2;
	int data5 = 5;
	int data3 = 3;
	void *voidata = 0;
	printf("pop test...");
	my_list = SortedListCreate(IntimLowtoHigh);
	assert(SortedListSize(my_list) == 0);
	assert(SortedListIsEmpty(my_list) == 1);
	
	/*insert*/
	iter1 = SortedListInsert(my_list, &data1);
	/*check size changed*/
	assert(SortedListSize(my_list) == 1);
	assert(SortedListIsEmpty(my_list) == 0);
	
	/*get data*/
	assert(*(int*)SortedListGetData(iter1) == data1);
	/*insert another after that*/
	iter1 = SortedListInsert(my_list, &data2);
	assert(SortedListSize(my_list) == 2);
	assert(SortedListIsEmpty(my_list) == 0);
	assert(*(int*)SortedListGetData(iter1) == data2);
	
	/*check that the order is correct and test iterators*/
	/*first one should be data1*/
	assert(*(int*)SortedListGetData(SortedListBegin(my_list)) == data1);
	/*next one should be data2*/
	assert(*(int*)SortedListGetData(SortedListNext(SortedListBegin(my_list))) == data2);
	
	/*insert a larger number*/
	iter1 = SortedListInsert(my_list, &data5);
	assert(SortedListSize(my_list) == 3);
	assert(SortedListIsEmpty(my_list) == 0);
	assert(*(int*)SortedListGetData(iter1) == data5);
	
	/*now see if its the last one*/
	
	assert(*(int*)SortedListGetData(SortedListPrev(SortedListEnd(my_list))) == data5);

	/*now insert a number that should be going in between*/
	iter1 = SortedListInsert(my_list, &data3);
	assert(SortedListSize(my_list) == 4);
	assert(SortedListIsEmpty(my_list) == 0);
	assert(*(int*)SortedListGetData(iter1) == data3);
	
	/*check that the order is correct: the last one is data 5 and the 
	prev should be data3*/
	assert(*(int*)SortedListGetData(SortedListPrev(SortedListEnd(my_list))) == data5);
	assert(*(int*)SortedListGetData(SortedListPrev(SortedListPrev(SortedListEnd(my_list)))) == data3);

	/*pop back*/
	voidata = SortedListPopBack(my_list);
	assert(*(int *)voidata == data5);
	assert(SortedListSize(my_list) == 3);
	assert(*(int*)SortedListGetData(SortedListPrev(SortedListEnd(my_list))) == data3);
	
	/*pop front*/
	voidata = SortedListPopFront(my_list);
	assert(*(int *)voidata == data1);
	assert(SortedListSize(my_list) == 2);
	assert(*(int*)SortedListGetData(SortedListBegin(my_list)) == data2);



	/*destroy*/
	SortedListDestroy(my_list);
	puts("passed");
}


void UnitestForeach(void)
{
	/*create the same list*/
	sorted_list_t *my_list = NULL;
	sorted_list_iter_t iter1 = {0};
	int datatomatch[] = {1,2,3,5};
	int data1 = 1;
	int data2 = 2;
	int data5 = 5;
	int data3 = 3;
	int result = 0;
	int index = 0;
	printf("for each test...");
	my_list = SortedListCreate(IntimLowtoHigh);
	assert(SortedListSize(my_list) == 0);
	assert(SortedListIsEmpty(my_list) == 1);
	
	/*insert*/
	iter1 = SortedListInsert(my_list, &data1);
	/*check size changed*/
	assert(SortedListSize(my_list) == 1);
	assert(SortedListIsEmpty(my_list) == 0);
	
	/*get data*/
	assert(*(int*)SortedListGetData(iter1) == data1);
	/*insert another after that*/
	iter1 = SortedListInsert(my_list, &data2);
	assert(SortedListSize(my_list) == 2);
	assert(SortedListIsEmpty(my_list) == 0);
	assert(*(int*)SortedListGetData(iter1) == data2);
	
	/*check that the order is correct and test iterators*/
	/*first one should be data1*/
	assert(*(int*)SortedListGetData(SortedListBegin(my_list)) == data1);
	/*next one should be data2*/
	assert(*(int*)SortedListGetData(SortedListNext(SortedListBegin(my_list))) == data2);
	
	/*insert a larger number*/
	iter1 = SortedListInsert(my_list, &data5);
	assert(SortedListSize(my_list) == 3);
	assert(SortedListIsEmpty(my_list) == 0);
	assert(*(int*)SortedListGetData(iter1) == data5);
	
	/*now see if its the last one*/
	
	assert(*(int*)SortedListGetData(SortedListPrev(SortedListEnd(my_list))) == data5);

	/*now insert a number that should be going in between*/
	iter1 = SortedListInsert(my_list, &data3);
	assert(SortedListSize(my_list) == 4);
	assert(SortedListIsEmpty(my_list) == 0);
	assert(*(int*)SortedListGetData(iter1) == data3);
	
	/*check that the order is correct: the last one is data 5 and the 
	prev should be data3*/
	assert(*(int*)SortedListGetData(SortedListPrev(SortedListEnd(my_list))) == data5);
	assert(*(int*)SortedListGetData(SortedListPrev(SortedListPrev(SortedListEnd(my_list)))) == data3);

	/*use for each to multiply by two*/
	
	result = SortedListForEach(SortedListBegin(my_list), SortedListEnd(my_list), 
								TimesTwo, &data1);	/*data 1 is not really used*/
	/*check no errors*/
	assert(result == 0);
	
	/*check if data changed*/
	for(iter1 = SortedListBegin(my_list) ; !SortedListIsSameIterator(iter1,SortedListEnd(my_list));  iter1 = SortedListNext(iter1), ++index)
	{
		assert((datatomatch[index] * 2) == *(int*)SortedListGetData(iter1));
	}
	
	/*destroy*/
	SortedListDestroy(my_list);
	puts("passed");
}

void UnitestFind(void)
{
	/*create the same list*/
	sorted_list_t *my_list = NULL;
	sorted_list_iter_t iter1 = {0};
	int data1 = 1;
	int data2 = 2;
	int data5 = 5;
	int data3 = 3;
	int datadontexist = 60;
	void *voidata = 0;
	printf("find test...");
	my_list = SortedListCreate(IntimLowtoHigh);
	assert(SortedListSize(my_list) == 0);
	assert(SortedListIsEmpty(my_list) == 1);
	
	/*insert*/
	iter1 = SortedListInsert(my_list, &data1);
	/*check size changed*/
	assert(SortedListSize(my_list) == 1);
	assert(SortedListIsEmpty(my_list) == 0);
	
	/*get data*/
	assert(*(int*)SortedListGetData(iter1) == data1);
	/*insert another after that*/
	iter1 = SortedListInsert(my_list, &data2);
	assert(SortedListSize(my_list) == 2);
	assert(SortedListIsEmpty(my_list) == 0);
	assert(*(int*)SortedListGetData(iter1) == data2);
	
	/*check that the order is correct and test iterators*/
	/*first one should be data1*/
	assert(*(int*)SortedListGetData(SortedListBegin(my_list)) == data1);
	/*next one should be data2*/
	assert(*(int*)SortedListGetData(SortedListNext(SortedListBegin(my_list))) == data2);
	
	/*insert a larger number*/
	iter1 = SortedListInsert(my_list, &data5);
	assert(SortedListSize(my_list) == 3);
	assert(SortedListIsEmpty(my_list) == 0);
	assert(*(int*)SortedListGetData(iter1) == data5);
	
	/*now see if its the last one*/
	
	assert(*(int*)SortedListGetData(SortedListPrev(SortedListEnd(my_list))) == data5);

	/*now insert a number that should be going in between*/
	iter1 = SortedListInsert(my_list, &data3);
	assert(SortedListSize(my_list) == 4);
	assert(SortedListIsEmpty(my_list) == 0);
	assert(*(int*)SortedListGetData(iter1) == data3);
	
	/*check that the order is correct: the last one is data 5 and the 
	prev should be data3*/
	assert(*(int*)SortedListGetData(SortedListPrev(SortedListEnd(my_list))) == data5);
	assert(*(int*)SortedListGetData(SortedListPrev(SortedListPrev(SortedListEnd(my_list)))) == data3);

	/*find data that exists*/
	
	iter1 = SortedListFind(SortedListBegin(my_list), SortedListEnd(my_list),
							FindIsMatch, &voidata, &data2);
							
	assert(*(int*)SortedListGetData(iter1) == data2);
	assert(*(int*)SortedListGetData(SortedListPrev(iter1)) == data1);
	
	/*find data that doesnt exist*/
	iter1 = SortedListFind(SortedListBegin(my_list), SortedListEnd(my_list),
							FindIsMatch, &voidata, &datadontexist);
							
	assert(SortedListGetData(iter1) == SortedListGetData(SortedListEnd(my_list)));
	assert(*(int*)SortedListGetData(SortedListPrev(iter1)) == *(int*)SortedListGetData(SortedListPrev(SortedListEnd(my_list))));
	
		
	/*destroy*/
	SortedListDestroy(my_list);
	puts("passed");


}

void UnitestMerge(void)
{
	/*create two lists*/
	sorted_list_t *my_list = NULL;
	sorted_list_t *my_list2 = NULL;
	sorted_list_iter_t iter1 = {0};
	int data1 = 1;
	int data2 = 3;
	int data3 = 5;
	int data4 = 7;
	int data11 = 2;
	int data22 = 4;
	int data33 = 6;
	int data44 = 8;
	int datatomatch[] = {1,2,3,4,5,6,7,8};	
	int index = 0;
	printf("merge test...");
	my_list = SortedListCreate(IntimLowtoHigh);
	my_list2 = SortedListCreate(IntimLowtoHigh);
	assert(SortedListSize(my_list) == 0);
	assert(SortedListIsEmpty(my_list) == 1);
	assert(SortedListSize(my_list2) == 0);
	assert(SortedListIsEmpty(my_list2) == 1);
	/*insert*/
	iter1 = SortedListInsert(my_list, &data1);
	
	iter1 = SortedListInsert(my_list, &data2);
	
	iter1 = SortedListInsert(my_list, &data4);
	
	iter1 = SortedListInsert(my_list, &data3);

	/*check size changed*/
	assert(SortedListSize(my_list) == 4);
	assert(SortedListIsEmpty(my_list) == 0);
	/*insert to list2*/
	
	iter1 = SortedListInsert(my_list2, &data11);
	
	iter1 = SortedListInsert(my_list2, &data22);
	
	iter1 = SortedListInsert(my_list2, &data44);
	
	iter1 = SortedListInsert(my_list2, &data33);
	
	assert(SortedListSize(my_list2) == 4);
	assert(SortedListIsEmpty(my_list2) == 0);
	
	/*merge it*/
	
	SortedListMerge(my_list, my_list2);
	
	/*check that it merged*/
	for(iter1 = SortedListBegin(my_list) ; !SortedListIsSameIterator(iter1,SortedListEnd(my_list));  iter1 = SortedListNext(iter1), ++index)
	{
		assert(datatomatch[index] == *(int*)SortedListGetData(iter1));
	}
		
	/*destroy*/
	SortedListDestroy(my_list);
	SortedListDestroy(my_list2);
	puts("passed");

	
	

}


void UltimateMergeTest(void)
{
	/*create two lists*/
	sorted_list_t *my_list12 = NULL;
	sorted_list_t *my_list13 = NULL;
	sorted_list_t *my_list14 = NULL;
	sorted_list_t *my_list23 = NULL;
	sorted_list_t *my_list24 = NULL;
	sorted_list_t *my_list34 = NULL;
	sorted_list_t *my_list1313 = NULL;
	sorted_list_iter_t iter1 = {0};
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;

	int datatomatch[] = {1,2,3,4};
	int datatomatch2[] = {1,1,3,3};		
	int index = 0;
	printf("ULTIMATE merge test...");
	
	/*merge'm 12 - 34*/
	my_list12 = SortedListCreate(IntimLowtoHigh);
	my_list34 = SortedListCreate(IntimLowtoHigh);		
	
	SortedListInsert(my_list12, &data1);
	SortedListInsert(my_list12, &data2);
	
	SortedListInsert(my_list34, &data3);
	SortedListInsert(my_list34, &data4);
	

	SortedListMerge(my_list12, my_list34);
	for(iter1 = SortedListBegin(my_list12) ; !SortedListIsSameIterator(iter1,SortedListEnd(my_list12));  iter1 = SortedListNext(iter1), ++index)
	{
		assert(datatomatch[index] == *(int*)SortedListGetData(iter1));
	}
	index = 0;
	SortedListDestroy(my_list12);
	SortedListDestroy(my_list34);
	
	
	/*merge 14 -23*/
	my_list14 = SortedListCreate(IntimLowtoHigh);
	my_list23 = SortedListCreate(IntimLowtoHigh);
	
	SortedListInsert(my_list14, &data1);
	SortedListInsert(my_list14, &data4);	
	SortedListInsert(my_list23, &data2);
	SortedListInsert(my_list23, &data3);
	
	SortedListMerge(my_list14, my_list23);
	for(iter1 = SortedListBegin(my_list14) ; !SortedListIsSameIterator(iter1,SortedListEnd(my_list14));  iter1 = SortedListNext(iter1), ++index)
	{
		assert(datatomatch[index] == *(int*)SortedListGetData(iter1));
	}
	index = 0;
	
	assert(SortedListSize(my_list14) == 4);
	assert(SortedListSize(my_list23) == 0);
	assert(SortedListIsEmpty(my_list23) == 1);
	SortedListDestroy(my_list14);
	SortedListDestroy(my_list23);
	
	/* merge 34 - 12*/
	
	my_list34 = SortedListCreate(IntimLowtoHigh);
	my_list12 = SortedListCreate(IntimLowtoHigh);		
	
	SortedListInsert(my_list34, &data3);
	SortedListInsert(my_list34, &data4);	
	SortedListInsert(my_list12, &data2);
	SortedListInsert(my_list12, &data1);
	
	SortedListMerge(my_list34, my_list12);
	for(iter1 = SortedListBegin(my_list34) ; !SortedListIsSameIterator(iter1,SortedListEnd(my_list34));  iter1 = SortedListNext(iter1), ++index)
	{
		assert(datatomatch[index] == *(int*)SortedListGetData(iter1));
	}
	index = 0;
	SortedListDestroy(my_list12);
	SortedListDestroy(my_list34);
	
	/*merge 23 - 14 */
	
	my_list23 = SortedListCreate(IntimLowtoHigh);
	my_list14 = SortedListCreate(IntimLowtoHigh);		
	
	SortedListInsert(my_list23, &data2);
	SortedListInsert(my_list23, &data3);

	SortedListInsert(my_list14, &data1);
	SortedListInsert(my_list14, &data4);	
	
	SortedListMerge(my_list23, my_list14);
	for(iter1 = SortedListBegin(my_list23) ; !SortedListIsSameIterator(iter1,SortedListEnd(my_list23));  iter1 = SortedListNext(iter1), ++index)
	{
		assert(datatomatch[index] == *(int*)SortedListGetData(iter1));
	}
	index = 0;
	SortedListDestroy(my_list14);
	SortedListDestroy(my_list23);

	/*merge 24 - 13 */
	
	my_list24 = SortedListCreate(IntimLowtoHigh);
	my_list13 = SortedListCreate(IntimLowtoHigh);		
	
	SortedListInsert(my_list24, &data2);
	SortedListInsert(my_list24, &data4);

	SortedListInsert(my_list13, &data1);
	SortedListInsert(my_list13, &data3);	
	
	SortedListMerge(my_list24, my_list13);
	for(iter1 = SortedListBegin(my_list24) ; !SortedListIsSameIterator(iter1,SortedListEnd(my_list24));  iter1 = SortedListNext(iter1), ++index)
	{
		assert(datatomatch[index] == *(int*)SortedListGetData(iter1));
	}
	index = 0;
	SortedListDestroy(my_list13);
	SortedListDestroy(my_list24);	
	
	/*merge 13 - 24 */
	
	my_list24 = SortedListCreate(IntimLowtoHigh);
	my_list13 = SortedListCreate(IntimLowtoHigh);		
	
	SortedListInsert(my_list24, &data2);
	SortedListInsert(my_list24, &data4);

	SortedListInsert(my_list13, &data1);
	SortedListInsert(my_list13, &data3);	
	
	SortedListMerge(my_list13, my_list24);
	
	for(iter1 = SortedListBegin(my_list13) ; !SortedListIsSameIterator(iter1,SortedListEnd(my_list13));  iter1 = SortedListNext(iter1), ++index)
	{
		assert(datatomatch[index] == *(int*)SortedListGetData(iter1));
	}
	index = 0;
	SortedListDestroy(my_list13);
	SortedListDestroy(my_list24);
	
		/*merge 13 - 13 */
	
	my_list1313 = SortedListCreate(IntimLowtoHigh);
	my_list13 = SortedListCreate(IntimLowtoHigh);		
	
	SortedListInsert(my_list1313, &data1);
	SortedListInsert(my_list1313, &data3);

	SortedListInsert(my_list13, &data1);
	SortedListInsert(my_list13, &data3);	
	
	SortedListMerge(my_list13, my_list1313);

	
	for(iter1 = SortedListBegin(my_list13) ; !SortedListIsSameIterator(iter1,SortedListEnd(my_list13));  iter1 = SortedListNext(iter1), ++index)
	{
		assert(datatomatch2[index] == *(int*)SortedListGetData(iter1));
	}
	index = 0;
	
	
	
	SortedListDestroy(my_list13);
	SortedListDestroy(my_list1313);	
	
	puts("PPPPPPPPPPAAAAAAAAAASSSSSSSSSSSSSSSSEEEEEEEEEEEDDDDDDDDDDDDDDDDDDDDDDDDD");
}

void SortedListMergeUritest(void)
{
	sorted_list_t *sorted_list1 = NULL;
	sorted_list_t *sorted_list2 = NULL;	

	int data1 = 10;
	int data2 = 20;	
	int data3 = 30;	
	int data4 = 40;	
	int data5 = 50;
	int data6 = 60;
	int data7 = 70;		
	int data8 = 80;
	int data9 = 90;	
	
	sorted_list1 = SortedListCreate(IsSortedInt);
	sorted_list2 = SortedListCreate(IsSortedInt);			

	SortedListInsert(sorted_list1, &data3);
	SortedListInsert(sorted_list1, &data8);
	SortedListInsert(sorted_list1, &data1);
	SortedListInsert(sorted_list1, &data4);
	SortedListInsert(sorted_list1, &data6);
	
	SortedListInsert(sorted_list2, &data7);
	SortedListInsert(sorted_list2, &data2);
	SortedListInsert(sorted_list2, &data5);
	SortedListInsert(sorted_list2, &data9);
	
	sorted_list1 = SortedListMerge(sorted_list1, sorted_list2);
	printf("%lu\n", SortedListSize(sorted_list1));/*9*/
	printf("%lu\n", SortedListSize(sorted_list2));/*0*/
	assert (0 == SortedListSize(sorted_list2));
	
	SortedListDestroy(sorted_list1);
	SortedListDestroy(sorted_list2);	
	puts("Merge URI... check!!!");
}


int IsSortedInt(void *a, void *b) 
{
	return (*(int*)a < *(int*)b);
}

int IntimLowtoHigh(void *data1,void *data2) 
{
	return (*(int*)data1 < *(int*)data2);
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


