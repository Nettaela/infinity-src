#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

avl_t *UnitestInsert(int *array, size_t array_size);/*returns full tree*/
void UnitestFind( avl_t *tree, size_t tree_size);
void UnitestForEach( avl_t *tree, int *array, size_t array_size);
void UnitestRemove( avl_t *tree, size_t array_size);
int CompareInt(const void *data1, const void *data2);
int ActionDiv(void *data, void *param);
int ActionMult(void *data, void *param);
int IsSorted(int num1, int num2);
void UnitestBalance(int *array, size_t array_size);
int main()
{
	static int unsorted_array[] = {3, 6, 2, 45, 9, 61, -5, 4, -1, -435};
	static int sorted_array[] = {-435, -5, -1, 2, 3, 4, 6, 9, 45, 61};
	size_t unsorted_array_size = sizeof(unsorted_array)/sizeof(unsorted_array[0]);
	avl_t *tree = UnitestInsert(unsorted_array,unsorted_array_size );
	
	UnitestRemove(tree, unsorted_array_size );
	UnitestForEach(tree, sorted_array,unsorted_array_size);
	UnitestBalance(sorted_array, unsorted_array_size);
	
	AVLDestroy(tree);
	puts("check vlg to see if destroy worked");
	return EXIT_SUCCESS;
}

void UnitestBalance(int *array, size_t array_size)
{
	size_t index = 0;
	int more= -3;
	int and= -4;
	int even = -420;
	int alot = -425;
	int ofstuff = -428;
	avl_t *tree = AVLCreate(CompareInt);
	assert(tree);
	/*array is sorted*/
	assert(AVLIs_Empty(tree));
	assert(AVLSize(tree) == 0);
	assert(AVLGetHeight(tree) == 0);
	
	assert(0 == AVLInsert(tree, &array[0]));
	assert(AVLGetHeight(tree) == 0);
	
	assert(0 == AVLInsert(tree, &array[1]));
	assert(AVLGetHeight(tree) == 1);
	/*should rotate left*/
	assert(0 == AVLInsert(tree, &array[2]));
	assert(AVLGetHeight(tree) == 1);
	
	assert(0 == AVLInsert(tree, &array[3]));
	assert(AVLGetHeight(tree) == 2);
	/*should roatete left*/
	assert(0 == AVLInsert(tree, &array[4]));
	assert(AVLGetHeight(tree) == 2);
	/*should rotate rightleft*/
	assert(0 == AVLInsert(tree, &more));
	assert(AVLGetHeight(tree) == 2);

	assert(0 == AVLInsert(tree, &and));
	assert(AVLGetHeight(tree) == 3);
	
	puts("balance test passed");
}


avl_t *UnitestInsert(int *array, size_t array_size)/*returns full tree*/
{
	size_t index = 0;
	avl_t *tree = AVLCreate(CompareInt);
	assert(tree);
	
	assert(AVLIs_Empty(tree));
	assert(AVLSize(tree) == 0);
	assert(AVLGetHeight(tree) == 0);
	
	for (index = 0 ; index < array_size ; ++index)
	{
		assert(0 == AVLInsert(tree, &array[index]));
	}
	assert(!AVLIs_Empty(tree));
	assert(AVLSize(tree) == array_size);
	
	assert(AVLGetHeight(tree) == 3);
		
	assert(-435 == *(int*)AVLFind(tree, &array[array_size-1]));
	
	assert(-1 == *(int*)AVLFind(tree, &array[array_size-2]));
	
	assert(61 == *(int*)AVLFind(tree, &array[5]));
	
	puts("insert and find test passed");
	return tree;

}
void UnitestForEach( avl_t *tree, int *array, size_t array_size)
{
	int params = 2;
	assert(0 == AVLForEach(tree, ActionMult, &params)); 

}
void UnitestRemove( avl_t *tree, size_t array_size)
{
	int data_exist = 45;
	int data_exist_need_balance = 61;
	int data_root = 3;
	int data_not_exist = 20;
	
	/*remove something that exists: */
	assert(!AVLIs_Empty(tree));
	assert(AVLSize(tree) == array_size);

	assert(AVLGetHeight(tree) == 3);
	
	assert(data_exist == *(int*)AVLRemove(tree, &data_exist));
	assert(!AVLIs_Empty(tree));
	
	assert(AVLSize(tree) == array_size-1);
	assert(AVLGetHeight(tree) == 3);
	
	assert(data_exist_need_balance == *(int*)AVLRemove(tree, &data_exist_need_balance));
	assert(!AVLIs_Empty(tree));
	assert(AVLSize(tree) == array_size-2);
	assert(AVLGetHeight(tree) == 3);

	/*remove the root: */
	assert(data_root == *(int*)AVLRemove(tree, &data_root));
	assert(AVLSize(tree) == array_size-3);

	assert(AVLGetHeight(tree) == 3);

	/*remove something that doesnt exist: */

	assert(NULL == AVLRemove(tree, &data_not_exist));
	assert(!AVLIs_Empty(tree));
	assert(AVLSize(tree) == array_size-3);
	puts("remove test passed");
}

int CompareInt(const void *data1, const void *data2)
{
	/*
	data1 == data2 -> 0
	data1 < data2 -> negative
	data1 > data2 -> positive
	
	*/
	return (*(int*)data1 - *(int*)data2);
}

int ActionMult(void *data, void *param)
{
	printf("data before: %d\n", *(int*)data);
	*(int*)data *= (*(int*)param);
	printf("data after: %d\n", *(int*)data);
	return 0;
}


int ActionDiv(void *data, void *param)
{
	
	*(int*)data /= (*(int*)param);
	return 0;
}

int IsSorted(int num1, int num2)
{
	return (num1 < num2);
}
