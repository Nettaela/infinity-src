#include "tree.h"
#include <stdio.h>
#include <stdlib.h> /*for malloc*/
#include <assert.h> /*for assert*/
#include <string.h>

/*in order*/
typedef struct node node_t;
enum TreeSides {LEFT, RIGHT, NUM_SONS};

#define RIGHT_SON(a) a->sons[RIGHT]
#define LEFT_SON(a) a->sons[LEFT]
#define PARENT(a) a->parent

#define IS_A_LEFT_SON(a) (a->parent->sons[LEFT] == a)
#define IS_A_RIGHT_SON(a) (a->parent->sons[RIGHT] == a)

#define ROOT(tree) tree->end_stub->sons[LEFT]

#define MAGIC_NUM 528772727

static int magic = MAGIC_NUM;

struct tree
{
	compare_func_t func;
	void *params;
	node_t *end_stub;
};

struct node
{
	node_t *parent;
	node_t *sons[NUM_SONS];
	void *data;
};

static void InitNode(node_t *node, node_t *parent, void *data) 
{
	assert(NULL != node);
		
	node->parent = parent;
	node->sons[LEFT] = NULL;
	node->sons[RIGHT] = NULL;
	node->data = data;
}

static node_t *CreateNode(node_t *parent, void *data)
{
	node_t *new_node = (node_t*)malloc(sizeof(*new_node));
	if(NULL == new_node)
	{
		return NULL;
	}
	
	InitNode(new_node, parent, data);

	return new_node;
}
	
static void InitTree(tree_t *tree, compare_func_t func, void *params, node_t *end)
{
	assert(NULL != tree);
	
	tree->func = func;
	tree->params = params;
	tree->end_stub = end;
}

tree_t *TreeCreate(compare_func_t func, void *params)
{
	node_t *new_stub = NULL;
	tree_t *new_tree = (tree_t*)malloc(sizeof(*new_tree));
	
	if(NULL == new_tree)
	{
		return NULL;
	}

	new_stub = CreateNode(NULL, &magic);

	if(NULL == new_stub)
	{
		return NULL;
	}

	
	InitTree(new_tree, func, params, new_stub);

	return new_tree;
}

int TreeIsEmpty(tree_t *tree)
{
	assert(NULL != tree);
	
	return (ROOT(tree) == NULL);
}

size_t TreeSize(tree_t *tree)
{
	size_t counter = 0;
	tree_iter_t start_iter = {0};
	tree_iter_t end_stub = {0};

	assert(NULL != tree);
		
	start_iter = TreeBegin(tree);
	end_stub = TreeEnd(tree);
	
	/*when tree is empty, both start and end are end*/
	while (!TreeIsSameIter(start_iter, end_stub))
	{
		start_iter = TreeNextIter(start_iter);
		++counter;
	}
	
	return counter;
}
int TreeIsSameIter(const tree_iter_t iter1, const tree_iter_t iter2)
{
	return (iter1.iterator == iter2.iterator);
}
tree_iter_t TreeInsert(tree_t *tree, void *data)
{
	node_t *current_node = NULL;
	node_t *next_node = NULL;
	compare_func_t cmp_data = NULL;
	tree_iter_t return_iter = {0}; 
	int result = 0;
	
	assert(NULL != tree);
	
	current_node = ROOT(tree);
	next_node = current_node;
	cmp_data = tree->func;
	return_iter = TreeEnd(tree);

	
	if(TreeIsEmpty(tree))
	{
		current_node = CreateNode(tree->end_stub , data);
		ROOT(tree) = current_node;
		return_iter.iterator = current_node;
		return return_iter;
	}
	
	while(next_node != NULL)
	{
		current_node = next_node;
		result = cmp_data(current_node->data, data, NULL);
		if(result > 0)
		{
			next_node = LEFT_SON(current_node);
		}
		else if (result < 0)
		{
			next_node = RIGHT_SON(current_node);
		}
		else
		{
			return return_iter; /*no duplicates allowed!*/
		}
	}
	
	next_node = CreateNode(current_node, data);
	/*use result to tell if its a right or left son*/
	if(result > 0)
	{
		LEFT_SON(current_node) = next_node;
	}
	else if(result < 0)
	{
		RIGHT_SON(current_node) = next_node;
	}
	
	return_iter.iterator = next_node;

	return return_iter;
}

tree_iter_t TreeNextIter(tree_iter_t iter)
{
	node_t *current_node = iter.iterator;
	tree_iter_t return_iter = {0};

	if(RIGHT_SON(current_node) != NULL)
	{
		current_node = RIGHT_SON(current_node);
		
		while (LEFT_SON(current_node) != NULL)
		{
			current_node = LEFT_SON(current_node);
		}
		return_iter.iterator = current_node;
		return return_iter;
	}
	else 
	{
		while (IS_A_RIGHT_SON(current_node))
		{
			current_node = PARENT(current_node);
		}
	}
	/*if current is a right son it needs to go up one more time, this time 
	also handles the case when current is a left son*/
		current_node = PARENT(current_node);
		return_iter.iterator = current_node;
		return return_iter;
}

tree_iter_t TreePrevIter(tree_iter_t iter)
{/*if iter is begin, behaviour undefined*/
	node_t *current_node = iter.iterator;
	tree_iter_t return_iter = {0};

	if(LEFT_SON(current_node) != NULL)
	{
		current_node = LEFT_SON(current_node);
		
		while (RIGHT_SON(current_node) != NULL)
		{
			current_node = RIGHT_SON(current_node);
		}
		return_iter.iterator = current_node;
		return return_iter;
	}
	else 
	{
		while (IS_A_LEFT_SON(current_node))
		{
			current_node = PARENT(current_node);
		}
	}
	current_node = PARENT(current_node);
	return_iter.iterator = current_node;
	return return_iter;
}

tree_iter_t TreeBegin(tree_t *tree)
{
	tree_iter_t return_iter = {0};
	node_t *current_node = NULL;
	
	assert(NULL != tree);
	
	current_node = ROOT(tree);
	
	if (TreeIsEmpty(tree))
	{
		return TreeEnd(tree);
	}
	
	while(LEFT_SON(current_node) != NULL)
	{
		current_node = LEFT_SON(current_node);
	}
	return_iter.iterator = current_node;
	return return_iter;
}

tree_iter_t TreeEnd(tree_t *tree)
{
	node_t *end_node = NULL;
	tree_iter_t return_iter = {0};
	
	assert(NULL != tree);
	end_node = tree->end_stub;
	
	return_iter.iterator = end_node;	
	return return_iter;
}

void *TreeGetData(tree_iter_t iter)
{
	node_t *node = iter.iterator;
	return (node->data);
}

int TreeForEach(tree_iter_t from, tree_iter_t to, action_func_t action, void *param)
{
	int result = 0;
	
	while (!TreeIsSameIter(from, to))
	{
		result = action(TreeGetData(from), param);
		from = TreeNextIter(from);
	}
	return result;
}

tree_iter_t TreeFind(tree_t *tree, const void *data)
{	
	int result = 0;
	tree_iter_t return_iter = {0};
	compare_func_t cmp_data = NULL;
	node_t *current_node = NULL;
	node_t *next_node = NULL;
	
	assert(NULL != tree);
	
	cmp_data = tree->func;
	current_node = ROOT(tree);
	next_node = current_node;

	return_iter.iterator = tree->end_stub;
	
	while(next_node != NULL && next_node != tree->end_stub)
	{
	/*use compare function to compare root data with data*/
		current_node = next_node;
		
		result = cmp_data(current_node->data, data, NULL);
		if(result > 0)
		{
			next_node = LEFT_SON(current_node);
		}
		else if(result < 0)
		{
			next_node = RIGHT_SON(current_node);
		}
		else
		{	
			return_iter.iterator = next_node;
			return return_iter; 
		}
	}

	return return_iter;
}
static node_t *FindLeaf(node_t *current)
{
	assert(NULL != current);
	
	if(RIGHT_SON(current) != NULL)
	{
		current = RIGHT_SON(current);
	}
	while(!(LEFT_SON(current) == NULL && RIGHT_SON(current) == NULL))
	{
		if(LEFT_SON(current) != NULL)
		{
			current = LEFT_SON(current);
		}
		else if(RIGHT_SON(current) != NULL)
		{
			current = RIGHT_SON(current);
		}
	}
	return current;
}

static void FreeLeaf(node_t *leaf)
{
	node_t *parent = NULL;
	
	assert(NULL != leaf);
	
	parent = leaf->parent;
	
	assert(LEFT_SON(leaf) == NULL && RIGHT_SON(leaf) == NULL);
	
	if(IS_A_LEFT_SON(leaf))
	{
		LEFT_SON(parent) = NULL;
	}
	else if(IS_A_RIGHT_SON(leaf))
	{
		RIGHT_SON(parent) = NULL;
	}
	free(leaf);
	leaf = NULL;
}

void TreeDestroy(tree_t *to_destroy)
{
	node_t *root = NULL;
	node_t *current = NULL;
	node_t *leaf = NULL;
	
	assert(NULL != to_destroy);
	
	root = ROOT(to_destroy);
	current = TreeBegin(to_destroy).iterator;

	if(TreeIsEmpty(to_destroy))
	{
		free(to_destroy->end_stub->sons[LEFT]);
		free(to_destroy->end_stub);
		free(to_destroy);
		return;
	}
	
	/*free left side*/
	while(current != root)
	{
		leaf = FindLeaf(current);
		current = leaf->parent;
		FreeLeaf(leaf);
	}
	/*free right side*/
	current = TreePrevIter(TreeEnd(to_destroy)).iterator;
	
	while(current != root)
	{
		leaf = FindLeaf(current);
		current = leaf->parent;
		FreeLeaf(leaf);
	}
	
	/*free root*/
	free(root);
	
	/*free end stub*/
	
	free(to_destroy->end_stub);
	
	/*free tree*/
	free(to_destroy);
}

static int IsLeaf(node_t *node)
{
	return (LEFT_SON(node) == NULL && RIGHT_SON(node) == NULL);
}

size_t GetTreeHeight(tree_t *tree)
{
	tree_iter_t start = {0};
	tree_iter_t end = {0};
	node_t *root = NULL;
	node_t *leaf = NULL;
	size_t counter = 0;
	size_t max = 0;
	
	assert(NULL != tree);
	
	start = TreeBegin(tree);
	end = TreeEnd(tree);
	root = ROOT(tree); 
			
	while(!TreeIsSameIter(start, end))
	{
		if(IsLeaf(start.iterator))
		{
			leaf = start.iterator;
			while(leaf != root)
			{
				leaf = PARENT(leaf);
				++counter;
			}
			if (counter > max)
			{
				max = counter;
			}
			counter = 0;
		}
		start = TreeNextIter(start);
	}
	return max;		 /*edges*/
}

static void ReplaceSonAndParent(node_t *parent_node, node_t *son_node)
{
	PARENT(son_node) = PARENT(parent_node);
		 
	if(IS_A_LEFT_SON(parent_node))
	{
		LEFT_SON(PARENT(parent_node)) = son_node;
	}
	else
	{
		RIGHT_SON(PARENT(parent_node)) = son_node;
	}
}

void *TreeRemove(/*tree_t *remove_from,*/ tree_iter_t to_remove) /*Try to implement without the tree*/
{
	node_t *remove_node = to_remove.iterator;
	node_t *son_node = NULL;
	void *data_to_return = NULL;
	
	/*first make sure it not the end*/
	assert(TreeGetData(to_remove) != &magic);
	
	data_to_return = TreeGetData(to_remove);
	
	/*if to remove is a leaf*/
	if(LEFT_SON(remove_node) == NULL && RIGHT_SON(remove_node) == NULL)
	{
		FreeLeaf(remove_node);
		remove_node = NULL;
		return data_to_return;
	}
	
	if(LEFT_SON(remove_node) != NULL && RIGHT_SON(remove_node) != NULL)
	{
		if(IS_A_LEFT_SON(remove_node))
		{
			/*go to right side and then left until null*/
			son_node = RIGHT_SON(remove_node);
			while(LEFT_SON(son_node) != NULL)
			{
				son_node = LEFT_SON(son_node);
			} 
			LEFT_SON(son_node) = LEFT_SON(remove_node);
			
			PARENT(LEFT_SON(remove_node)) = son_node;
			LEFT_SON(remove_node) = NULL;
			
			ReplaceSonAndParent(remove_node, RIGHT_SON(remove_node));
		}
		else
		{
			son_node = LEFT_SON(remove_node);
			while(RIGHT_SON(son_node) != NULL)
			{
				son_node = RIGHT_SON(son_node);
			} 
			RIGHT_SON(son_node) = RIGHT_SON(remove_node);
			
			PARENT(RIGHT_SON(remove_node)) = son_node;
			RIGHT_SON(remove_node) = NULL;

			ReplaceSonAndParent(remove_node, LEFT_SON(remove_node));
		}
		free(remove_node);
		remove_node = NULL;
		return data_to_return;
	}
	
	if(LEFT_SON(remove_node) != NULL || RIGHT_SON(remove_node) != NULL)
	{
		/*just replace the child with the node*/
		if(LEFT_SON(remove_node) != NULL)
		{
			son_node = LEFT_SON(remove_node);
		}
		else
		{
			son_node = RIGHT_SON(remove_node);
		} 
		ReplaceSonAndParent(remove_node, son_node);
	 
		free(remove_node);
		remove_node = NULL;
		return data_to_return;
	}
	return data_to_return;
}

