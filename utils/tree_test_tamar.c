#include <assert.h>		/*assert*/
#include <stdlib.h>		/*EXIT_SUCCESS*/
#include <stdio.h>		/*printf*/

#include "tree.h"		/*func declarations*/

enum TreeSons {LEFT, RIGHT, NUM_SONS, EQUAL}; /*maybe cant be in the test*/

#define ARR_SIZE(x) (sizeof(x) / sizeof(int))



static int cmp_func(const void *data, const void *node_data, void *params)
{
	
/*	
	if (*(int*)data < *(int*)node_data)
	{
		return LEFT;
	}
	if(*(int*)data > *(int*)node_data)
	{
		return RIGHT;	
	}
*/	
	int data_int = *(int*)data;
	int node_data_int = *(int*)node_data;
	(void)params;
	
	return (data_int - node_data_int);	
}


void CreateInsertTest()
{

	tree_t *tree = TreeCreate(&cmp_func, NULL);
	tree_iter_t iter = {NULL};
	int data10 = 10;
	int data20 = 20;
	int data6 = 6;
	int data4 = 4;
	int data30 = 30;
	assert (1 == TreeIsEmpty(tree));
	
/*	puts("---------insert 10---------");*/
	iter = TreeInsert(tree, &data10);
	assert (0 == TreeIsEmpty(tree));
	assert (*(int*)TreeGetData(iter) == 10);
/*	printf("insert 1: %d\n", *(int*)TreeGetData(iter));*/

	/*puts("---------insert 20---------");*/
	iter = TreeInsert(tree, &data20);
	assert (*(int*)TreeGetData(iter) == 20);
	
	iter = TreeBegin(tree);
	assert (*(int*)TreeGetData(iter) == 10);

	/*puts("---------insert 6---------");*/
	iter = TreeInsert(tree, &data6);
	assert (*(int*)TreeGetData(iter) == 6);
	
	iter = TreeBegin(tree);
	
	printf("%d\n", *(int*)TreeGetData(iter));
	assert (*(int*)TreeGetData(iter) == 6);
	
	/*puts("---------insert 4---------");*/
	iter = TreeInsert(tree, &data4);
	assert (*(int*)TreeGetData(iter) == 4);
	iter = TreeBegin(tree);
	assert (*(int*)TreeGetData(iter) == 4);
	
	
	iter = TreeEnd(tree);
	/*assert ((int)TreeGetData(iter) == 0xdeadbeef);*/
	
	
	/*puts("---------insert 30---------");*/
	iter = TreeInsert(tree, &data30);
	assert (*(int*)TreeGetData(iter) == 30);
	
	
	TreeDestroy(tree);
	puts("Simple test- pass");
}


void NextPrevTest()
{
	tree_t *tree = TreeCreate(&cmp_func, NULL);
	tree_iter_t iter = {NULL};
	
	int data[] = {10, 20, 8, 30, 7, 25, 5};
	size_t i = 0;
	
	/*-----------insert elements-----------*/
	for (i = 0; i < ARR_SIZE(data); ++i)
	{
		TreeInsert(tree, &data[i]);
	}

	/*---------------test next------------*/
	iter = TreeBegin(tree);
	
	for (i = 0; i < ARR_SIZE(data) - 1; ++i)
	{
		assert (*(int*)TreeGetData(iter) < *(int*)TreeGetData(TreeNextIter(iter)));
		iter = TreeNextIter(iter);
	}

	iter = TreeNextIter(iter);
	assert (TreeIsSameIter(iter, TreeEnd(tree)));
	
	/*---------------test prev------------*/
	iter = TreeEnd(tree);
	iter = TreePrevIter(iter);
	
	for (i = 0; i < ARR_SIZE(data) - 1; ++i)
	{
		assert (*(int*)TreeGetData(iter) > *(int*)TreeGetData(TreePrevIter(iter)));
		iter = TreePrevIter(iter);
	}
	
	TreeDestroy(tree);

	puts("Next and Prev test- pass");
	
}


static int PrintAction (void *data, void *param)
{
	
	int data_int = *(int*)data;
	(void)param;
	printf("%d\n", data_int);
	
	return EXIT_SUCCESS;
}


void ForEachTest()
{
	tree_t *tree = TreeCreate(&cmp_func, NULL);
	
	
	int data[] = {10, 20, 8, 30, 7, 25, 5};
	size_t i = 0;
	
	
	
	/*-----------insert elements-----------*/
	for (i = 0; i < ARR_SIZE(data); ++i)
	{
		TreeInsert(tree, &data[i]);
	}

	puts("-------ForEach print element-------");
	TreeForEach(TreeBegin(tree), TreeEnd(tree), &PrintAction, NULL);
	
	TreeDestroy(tree);
	/*add a test when action fails*/
}


void SizeTest()
{
	
	tree_t *tree7 = TreeCreate(&cmp_func, NULL);
	tree_t *tree1 = TreeCreate(&cmp_func, NULL);
	tree_t *big_tree = TreeCreate(&cmp_func, NULL);
	
	
	int data[] = {10, 20, 8, 30, 7, 25, 5};
	int one_element[] = {3};
	int big_arr[1000]= {0};
	size_t i = 0;
	
	/*-----------insert elements-----------*/
	for (i = 0; i < ARR_SIZE(data); ++i)
	{
		TreeInsert(tree7, &data[i]);
	}
	
	assert(TreeSize(tree7) == ARR_SIZE(data));
	
	TreeInsert(tree1, &one_element);
	assert (TreeSize(tree1) == ARR_SIZE(one_element));
	
	for (i = 0; i < ARR_SIZE(big_arr); ++i)
	{
		big_arr[i] = i;
	}
	
	for (i = 0; i < ARR_SIZE(big_arr); ++i)
	{
		TreeInsert(big_tree, &big_arr[i]);
	}
	
	assert (TreeSize(big_tree) == ARR_SIZE(big_arr));
	
	TreeDestroy(tree7);
	TreeDestroy(tree1);
	TreeDestroy(big_tree);
	
	puts("Size test- pass");
}



void RemoveTest()
{
	tree_t *tree7 = TreeCreate(&cmp_func, NULL);
/*	tree_t *tree1 = TreeCreate(&cmp_func, NULL);*/
	/*tree_t *big_tree = TreeCreate(&cmp_func, NULL);*/
	tree_iter_t iter1 = {NULL};
	
	int data[] = {20, 15, 8, 12, 16, 30, 42, 25, 5, 41, 40, 39};
	/*int one_element[] = {3};*/
	/*int big_arr[1000]= {0};*/
	size_t i = 0;
	void *data_removed = NULL;
	
	/*-----------insert elements-----------*/
	for (i = 0; i < ARR_SIZE(data); ++i)
	{
		TreeInsert(tree7, &data[i]);
	}
	
	iter1 = TreeBegin(tree7);
	iter1 = TreeNextIter(iter1);
	iter1 = TreeNextIter(iter1);
	iter1 = TreeNextIter(iter1);
	assert (*(int*)TreeGetData(iter1) == 15);

	data_removed = TreeRemove(iter1);
	assert (*(int*)data_removed == 15);

	iter1 = TreeBegin(tree7);
	iter1 = TreeNextIter(iter1);
	iter1 = TreeNextIter(iter1);
	iter1 = TreeNextIter(iter1);
	
/*	printf("%d\n", *(int*)TreeGetData(iter1));*/
	assert (*(int*)TreeGetData(iter1) == 16);

	iter1 = TreePrevIter(iter1);
	assert (*(int*)TreeGetData(iter1) == 12);
	
	data_removed = TreeRemove(iter1);
	assert (*(int*)data_removed == 12);
	
	iter1 = TreeEnd(tree7);
	for (i = 0; i < 5; ++i)
	{
		iter1 = TreePrevIter(iter1);
	}
	
	assert (*(int*)TreeGetData(iter1) == 30);
	
	TreeRemove(iter1);
	
	iter1 = TreeEnd(tree7);
	for (i = 0; i < 5; ++i)
	{
		iter1 = TreePrevIter(iter1);
	}
	
	assert (*(int*)TreeGetData(iter1) == 25);
	assert (TreeSize(tree7) == 9);
	

	iter1 = TreeBegin(tree7);
	for (i = 0; i < 8; ++i)
	{	
		iter1 = TreeBegin(tree7);
		TreeRemove(iter1);
	}
	
	
	
	TreeDestroy(tree7);
	puts("Remove test- pass");
}

	
int main ()
{
	CreateInsertTest();
	NextPrevTest();
	ForEachTest();
	SizeTest();
	RemoveTest();
	
	
	return EXIT_SUCCESS;

}








