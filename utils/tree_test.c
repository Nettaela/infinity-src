#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

tree_t *UnitestInsert(int *array, size_t array_size);/*returns full tree*/
tree_iter_t UnitestFind(tree_t *tree, size_t tree_size);
void UnitestForEach(tree_t *tree, int *array, size_t array_size);
void UnitestHeight(tree_t *tree, size_t tree_size);
void UnitestRemove(tree_t *tree, tree_iter_t iter, size_t array_size);
int ActionDiv(void *data, void *param);
int ActionMult(void *data, void *param);
int CompareInt(const void *data, const void *data_to_compare, void *params);
int IsSorted(int num1, int num2);

int main()
{
	static int unsorted_array[] = {3, 6, 2, 45, 9, 61, -5, 4, -1, -435};
	static int sorted_array[] = {-435, -5, -1, 2, 3, 4, 6, 9, 45, 61};
	size_t unsorted_array_size = sizeof(unsorted_array)/sizeof(unsorted_array[0]);
	tree_t *tree = UnitestInsert(unsorted_array,unsorted_array_size );
	
	UnitestRemove(tree, UnitestFind(tree, unsorted_array_size),unsorted_array_size );
	UnitestForEach(tree, sorted_array,unsorted_array_size);
	UnitestHeight(tree, 0);

	
	TreeDestroy(tree);
	return EXIT_SUCCESS;
}

tree_t *UnitestInsert(int *array, size_t array_size)
{
	tree_t *my_tree = TreeCreate(CompareInt, NULL);
	tree_iter_t my_iter;
	tree_iter_t start_iter;
	tree_iter_t end_iter;
	tree_iter_t next_iter;
	tree_iter_t prev_iter;
	size_t index = 0;
	
	assert(TreeIsEmpty(my_tree));
	assert(TreeSize(my_tree) == 0);

	for (index = 0; index < array_size ; ++index)
	{
		my_iter = TreeInsert(my_tree, &array[index]);
	}
	
	assert(array[index-1] == *(int*)TreeGetData(my_iter));
	
	start_iter = TreeBegin(my_tree);
	end_iter = TreeEnd(my_tree);
	next_iter = start_iter;
		
	while (!TreeIsSameIter(next_iter, end_iter))
	{
		assert(IsSorted(*(int*)TreeGetData(next_iter), *(int*)TreeGetData(TreeNextIter(next_iter))));
		next_iter = TreeNextIter(next_iter);
	}
	
	next_iter = end_iter;
	
	while (!TreeIsSameIter(next_iter, start_iter))
	{
		assert(!IsSorted(*(int*)TreeGetData(next_iter), *(int*)TreeGetData(TreePrevIter(next_iter))));
		next_iter = TreePrevIter(next_iter);
	}

	assert(TreeSize(my_tree) == array_size);
	assert(!TreeIsEmpty(my_tree));
	puts("insert test passed");
	return my_tree;
}
tree_iter_t UnitestFind(tree_t *tree, size_t tree_size)
{
	int data_to_find = 45;
	int data_to_find2 = -435;
	int data_to_find3 = 61;
	
	int data_not_there = 30;
	int data_not_there2 = 70;
	int data_not_there3 = -500;
	
	tree_iter_t not_found;
	tree_iter_t found_iter;
	
	
	found_iter = TreeFind(tree, &data_to_find3);
	assert(*(int*)TreeGetData(found_iter) == data_to_find3);
	
	not_found = TreeFind(tree, &data_not_there);
	assert(TreeIsSameIter(not_found, TreeEnd(tree)));

	not_found = TreeFind(tree, &data_not_there2);
	assert(TreeIsSameIter(not_found, TreeEnd(tree)));
	
	found_iter = TreeFind(tree, &data_to_find2);
	assert(TreeIsSameIter(not_found, TreeEnd(tree)));
	
	not_found = TreeFind(tree, &data_not_there3);
	assert(TreeIsSameIter(not_found, TreeEnd(tree)));
	
	found_iter = TreeFind(tree, &data_to_find);
	assert(*(int*)TreeGetData(found_iter) == data_to_find);
	
	puts("find test passed");
	return found_iter;
}

void UnitestForEach(tree_t *tree, int *array, size_t array_size)
{
	int param = 24;
	size_t index = 0;
	int result = 0;
	tree_iter_t iter = TreeBegin(tree);
 
 	result = TreeForEach(TreeBegin(tree), TreeEnd(tree), ActionMult, &param);
	assert(result == 0);
	
	for(index = 0; index < array_size; ++index)
	{
		assert((array[index] * param) == *(int*)TreeGetData(iter));
		iter = TreeNextIter(iter);
	}
		
	result = TreeForEach(TreeBegin(tree), TreeEnd(tree), ActionDiv, &param);
	
	iter = TreeBegin(tree);
	
	for(index = 0; index < array_size; ++index)
	{
		assert((array[index]) == *(int*)TreeGetData(iter));
		iter = TreeNextIter(iter);
	}
	assert(result == 0);
	puts("for each test passed");
	
}

void UnitestHeight(tree_t *tree, size_t tree_size)
{

	assert(GetTreeHeight(tree) == 4);
	puts("height test passed");

}

void UnitestRemove(tree_t *tree, tree_iter_t iter, size_t array_size)
{
	void *data = NULL;
	void *data_from_iter = TreeGetData(iter);
	tree_iter_t start_iter = TreeBegin(tree);
	tree_iter_t end_iter = TreeEnd(tree);
	tree_iter_t next_iter = start_iter;
	
	assert(array_size == TreeSize(tree));

	data = TreeRemove(iter);
	
		
	while (!TreeIsSameIter(next_iter, end_iter))
	{
		assert(IsSorted(*(int*)TreeGetData(next_iter), *(int*)TreeGetData(TreeNextIter(next_iter))));
		next_iter = TreeNextIter(next_iter);
	}
	
	assert(data == data_from_iter);
	assert(array_size-1 == TreeSize(tree));
	
	TreeInsert(tree, data);
	
	assert(array_size == TreeSize(tree));
	
	puts("remove test passed");
	
}

int CompareInt(const void *data1, const void *data2, void *params)
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
	*(int*)data *= (*(int*)param);
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
