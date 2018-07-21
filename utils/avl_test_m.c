#include <stdio.h>  /* printf */
#include <stdlib.h> /* srand */
#include <time.h>   /* time */
#include <assert.h> /* assert */

#include "avl.h"  
typedef struct node node_t;
enum {LEFT, RIGHT, NUM_SONS};

struct avl
{
	cmp_func_t cmp_func;
	node_t *root;
};

struct node
{
	void *data;
	size_t height;
	node_t *sons[NUM_SONS];
};

static int Sort(const void *data1, const void *data2)
{
	int ret = 0;

	if (*(int *)data1 < *(int *)data2)
	{
		ret = -1;
	}
	else if (*(int *)data1 > *(int *)data2)
	{
		ret = 1;
	}

	return (ret);
}

static int MinusOne(void *data, void *param)
{
	(void)param;
	--*(int *)data;

	return (0);
}

static avl_t *CreateRandomTree(avl_t *tree)
{
	int num_lut[21] = {0};
	static int arr[21] = {0};
	int n = 0;
	int i = 0;

	num_lut[0] = 1;

	for(i = 0; i < 21; ++i)
	{
		arr[i] = i;
	}

	srand(time(NULL));

	for(i = 0; i < 20; ++i)
	{
		while (1 == num_lut[n])
		{
			n = (rand() % 20) + 1;
		}

		num_lut[n] = 1;
	
/*		printf("%d\n", n);*/

		AVLInsert(tree, &arr[n]);
	}

	return (tree);
}

static void FillMatrixTree(node_t *node, int idx, int matrix_lut[][10])
{
	matrix_lut[*(int *)node->data][idx] = 1;

	printf("data: %d | height: %lu\n", *(int *)node->data, node->height);

	if (NULL != node->sons[RIGHT])
	{
		FillMatrixTree(node->sons[RIGHT], (idx + 1), matrix_lut);
	}

	if (NULL != node->sons[LEFT])
	{
		FillMatrixTree(node->sons[LEFT], (idx + 1), matrix_lut);
	}
}

static void PrintTree(avl_t *tree, node_t *node)
{
	int i,j,k;
	int h = AVLGetHeight(tree) + 1;
	int matrix_lut[1000][10] = {0};

	FillMatrixTree(node, 0, matrix_lut);

	printf("\n");

	for(j = 0; j < 10; ++j)
	{

		for(k = 0; k < h; ++k)
		{
			printf(" ");
		}

		for(i = 0; i < 1000; ++i)
		{

			if (0 != matrix_lut[i][j])
			{

				printf(" %d", i);
			}
		}

		--h;

		printf("\n");
	}

}

void test1()
{
	avl_t *tree = AVLCreate(Sort);
	assert(1 == AVLIs_Empty(tree));
	assert(0 == AVLSize(tree));

	CreateRandomTree(tree);
	assert(0 == AVLIs_Empty(tree));

	assert(0 == AVLForEach(tree, MinusOne, NULL));
	printf("\nTree height: %lu\n", AVLGetHeight(tree));
	printf("\nTree size: %lu\n", AVLSize(tree));
	PrintTree(tree, tree->root);

	{
		int a = 5;
		
		assert(a == *(int *)AVLFind(tree, &a));

		a = 90;

		assert(NULL == AVLFind(tree, &a));
	}

	{
		int a = 5;

		AVLRemove(tree, &a);
	}

	printf("\nTree height: %lu\n", AVLGetHeight(tree));
	printf("\nTree size: %lu\n", AVLSize(tree));
	PrintTree(tree, tree->root);

	AVLDestroy(tree);
}

void test2()
{
	int arr[11] = {100,99,101,98,102,97,103,96,104,95,105};
	int n = 0;


	avl_t *tree = AVLCreate(Sort);
	
	for (n = 0; n < 11; ++n)
	{
		AVLInsert(tree, &arr[n]);
	}

	printf("\nTree height: %lu\n", AVLGetHeight(tree));
	printf("\nTree size: %lu\n", AVLSize(tree));
	PrintTree(tree, tree->root);


	AVLDestroy(tree);
}
/*
void test3()
{

	int n = 0;


	avl_t *tree = AVLCreate(Sort);
	
	for (n = 0; n < 20; ++n)
	{
		AVLInsert(tree, &arr[n]);
	}

	printf("\nTree height: %lu\n", AVLGetHeight(tree));
	printf("\nTree size: %lu\n", AVLSize(tree));
	PrintTree(tree, tree->root);

	{
		int a = 5;

		AVLRemove(tree, &a);

	}

	printf("\nTree height: %lu\n", AVLGetHeight(tree));
	printf("\nTree size: %lu\n", AVLSize(tree));
	PrintTree(tree, tree->root);

	AVLDestroy(tree);
}*/

void test4()
{
	int arr[5] = {10,6,12,14,13};
	int n = 0;


	avl_t *tree = AVLCreate(Sort);
	
	for (n = 0; n < 4; ++n)
	{
		AVLInsert(tree, &arr[n]);
	}

	printf("\nTree height: %lu\n", AVLGetHeight(tree));
	printf("\nTree size: %lu\n", AVLSize(tree));
	PrintTree(tree, tree->root);

	AVLInsert(tree, &arr[4]);

	printf("\nTree height: %lu\n", AVLGetHeight(tree));
	printf("\nTree size: %lu\n", AVLSize(tree));
	PrintTree(tree, tree->root);

	AVLDestroy(tree);
}


int main()
{
test1();

	/*test2();*/

	/*test3();*/

/*	test4();
*/
	printf("Check Valgrind...\n");

	return 0;
}

