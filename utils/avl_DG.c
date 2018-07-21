#include "avl.h"
#include <assert.h>
#include <stdlib.h> /*malloc*/
typedef enum TreeSides {LEFT, RIGHT, NUM_SONS} sides_t;

#define RIGHT_SON(node) ((node)->sons[RIGHT])
#define LEFT_SON(node) ((node)->sons[LEFT])
typedef struct node node_t;

struct avl
{
	cmp_func_t cmp_func;
	node_t *root;
};

struct node
{
	void *data;
	int height;
	node_t *sons[NUM_SONS];
};

static int MaxHeight(int right, int left)
{
	if(right == -1 && left == -1)
	{
		return 0;
	}
	return (right > left ? right : left);	
}

static void FixHeight(node_t *subtree_root)
{
	int left_height = -1;
	int right_height = -1;
	if(subtree_root == NULL)
	{
		return;
	}
	if(LEFT_SON(subtree_root) != NULL)
	{
		left_height = LEFT_SON(subtree_root)->height + 1;	
	}
	if(RIGHT_SON(subtree_root) != NULL)
	{
		right_height = RIGHT_SON(subtree_root)->height + 1;
	}
	subtree_root->height = MaxHeight(right_height ,left_height);
}

static node_t *LeftLeftRot(node_t *node)
{
	/*make right son replace node and return it*/
	node_t *right_son = RIGHT_SON(node);
	RIGHT_SON(node) = LEFT_SON(right_son);
	LEFT_SON(right_son) = node;
	
	/* right son is now the root of the sub tree instead of node, 
	update heights accordingly:*/
	FixHeight(LEFT_SON(right_son));
	FixHeight(RIGHT_SON(right_son));
	FixHeight(right_son);
	return right_son;
}

static node_t *RightRightRot(node_t *node)
{
	/*make left son replace node and return it*/
	node_t *left_son = LEFT_SON(node);
	LEFT_SON(node) = RIGHT_SON(left_son);
	RIGHT_SON(left_son) = node;
	
	/* left son is now the root of the sub tree instead of node, 
	update heights accordingly:*/
	FixHeight(LEFT_SON(left_son));
	FixHeight(RIGHT_SON(left_son));
	FixHeight(left_son);
	return left_son;
}

static node_t *LeftRightRot(node_t *node)
{
	LEFT_SON(node) = LeftLeftRot(LEFT_SON(node));	
	return RightRightRot(node);
}

static node_t *RightLeftRot(node_t *node)
{
	RIGHT_SON(node) = RightRightRot(RIGHT_SON(node));
	return LeftLeftRot(node);
}

static int GetNodeHeight(const node_t *node)
{
	if(node == NULL)
	{
		return -1;
	}
	return node->height;
}

static int HeightDiff(node_t *left_son, node_t *right_son)
{
	return GetNodeHeight(left_son) - GetNodeHeight(right_son);
}

static node_t *Balance(node_t *node) /*diff is always left - right*/
{
	int heightdiff = 0; 
	int heightdiff_grandchildren = 0;
	
	if(node == NULL)
	{
		return node;
	}
	
	heightdiff = HeightDiff(LEFT_SON(node), RIGHT_SON(node));
		
	if(heightdiff >= 2) 
	{
		/*go left*/
		heightdiff_grandchildren = 
		HeightDiff(LEFT_SON(LEFT_SON(node)), RIGHT_SON(LEFT_SON(node)));
		if(heightdiff_grandchildren <= -1)
		{
			return LeftRightRot(node);
		}
		return RightRightRot(node);
	}
	if(heightdiff <= -2)
	{
		/*go right*/
		heightdiff_grandchildren = 
		HeightDiff(LEFT_SON(RIGHT_SON(node)), RIGHT_SON(RIGHT_SON(node)));
		if(heightdiff_grandchildren >= 1)
		{
			return RightLeftRot(node);
		}
		return LeftLeftRot(node);
	}
	return node; /* balanced*/
}

static void InitTree(avl_t *tree, node_t *root ,cmp_func_t cmp_func)
{
	assert(NULL != tree);
	
	tree->root = root;
	tree->cmp_func = cmp_func;
}

static void InitNode(node_t *node, void *data, int height)
{	
	node->data = data;
	node->height = height;
	node->sons[LEFT] = NULL;
	node->sons[RIGHT] = NULL;
}

static node_t *CreateNode(void *data, int height)
{
	node_t *new_node = (node_t*)malloc(sizeof(*new_node));
	if(NULL == new_node)
	{
		return NULL;
	}
	
	InitNode(new_node, data, height);

	return new_node;
}

avl_t *AVLCreate(cmp_func_t cmp_func)
{
	avl_t *new_tree = (avl_t*)malloc(sizeof(*new_tree));
	if(NULL == new_tree)
	{
		return NULL;
	}
	
	InitTree(new_tree, NULL , cmp_func);
	
	return new_tree;
}

static void ImplementDestroy(node_t *node)
{
	if(NULL == node)
	{
		return;
	}
	ImplementDestroy(LEFT_SON(node));
	ImplementDestroy(RIGHT_SON(node));
	free(node);
}

void AVLDestroy(avl_t *tree) /*post order*/
{
	assert(NULL != tree);
	
	if(!AVLIs_Empty(tree))
	{
		ImplementDestroy(tree->root);
	}
	free(tree);
}

static node_t *ImplementInsert(node_t *node,cmp_func_t cmp_func , void *data)
{
	int result = 0;
	
	if(NULL == node)
	{
		return CreateNode(data, 0);
	}
	/*
	data1 == data2 -> 0
	data1 < data2 -> negative
	data1 > data2 -> positive
	*/
	result = cmp_func(data, node->data);
	if(result < 0 ) /* is new data smaller than curr data?*/
	{
		LEFT_SON(node) = ImplementInsert(LEFT_SON(node), cmp_func, data);
		/*if(node->height == LEFT_SON(node)->height)
		{
			++node->height;
		}*/
	}
	else if(result > 0)
	{
		RIGHT_SON(node) = ImplementInsert(RIGHT_SON(node), cmp_func, data);
		/*if(node->height == RIGHT_SON(node)->height)
		{
			++node->height;
		}*/
	}
	else
	{
		assert(0 == "Duplicate values are no allowed");
	}
	FixHeight(node);
	return Balance(node);
}

int AVLInsert(avl_t *tree, void *data) /*no duplicates allowed */
{	
	assert(NULL != tree);

	if(AVLIs_Empty(tree))
	{
		tree->root = CreateNode(data, 0);
		return (NULL == tree->root);
	}
	
	tree->root = ImplementInsert(tree->root, tree->cmp_func, data);
	return 0;
}
static node_t *ImplementFind(node_t *node, cmp_func_t cmp_func, const void *key)
{
	int result = 0;
	if(NULL == node)
	{
		return NULL;
	}

	result = cmp_func(key, node->data);
	if(result < 0 ) 
	{
		return ImplementFind(LEFT_SON(node), cmp_func, key);
	}
	else if(result > 0)
	{
		return ImplementFind(RIGHT_SON(node), cmp_func, key);
	}
	else
	{
		return node; 
	}
}


void *AVLFind(const avl_t *tree, const void *key)
{
	node_t *found = NULL;
	
	assert(NULL != tree);
	
	if(!AVLIs_Empty(tree))
	{
		found = ImplementFind(tree->root, tree->cmp_func, key);
		if(NULL == found)
		{
			return NULL;
		}
	}
	return found->data;
	
}
static node_t *GetMostLeft(node_t *right_son)
{
	if(NULL == LEFT_SON(right_son)) 
	{
		return right_son;
	}
	return GetMostLeft(LEFT_SON(right_son));
}

static node_t *ImplementRemove(node_t *node, cmp_func_t cmp_func, const void *key)
{	
	int result = 0;
	node_t *new = NULL;
	
	if (NULL == node)
	{
		return NULL;
	}
	
	result = cmp_func(key, node->data);
	if (result < 0) 
	{
		LEFT_SON(node) = ImplementRemove(LEFT_SON(node), cmp_func, key);
		FixHeight(node);
		return Balance(node);
	}
	else if (result > 0)
	{
		RIGHT_SON(node) = ImplementRemove(RIGHT_SON(node), cmp_func, key);
		FixHeight(node);
		return Balance(node);
	}
	else
	{
		if (NULL == LEFT_SON(node) && NULL == RIGHT_SON(node))
		{
			free(node);
			return NULL;
		}
		if (NULL != LEFT_SON(node) && NULL != RIGHT_SON(node))
		{
			void *node_data = node->data;
			new = GetMostLeft(RIGHT_SON(node));
			node->data = new->data;/*swap*/
			new->data = node_data;
			RIGHT_SON(node) = ImplementRemove(RIGHT_SON(node), cmp_func, key);
			FixHeight(node);
			return node;
		}
		/*the other case is one child: */
							
		new = ((NULL == RIGHT_SON(node)) ? LEFT_SON(node) : RIGHT_SON(node)) ;
		free(node);
		FixHeight(new);
		return new;
	}	
	
}

void *AVLRemove(avl_t *tree, const void *key)
{
	void *data = NULL;
	
	assert(NULL != tree);
	data = AVLFind(tree, key);
	
	if(!AVLIs_Empty(tree) && data != NULL)
	{
		tree->root = ImplementRemove(tree->root, tree->cmp_func, key); 
	}	
	return data;
}


static size_t Size(node_t *node)
{
	if(NULL == node)
	{
		return 0;
	}
	return 1 + Size(LEFT_SON(node)) + Size(RIGHT_SON(node));
}
 
size_t AVLSize(const avl_t *tree) /*pre order */
{
	assert(NULL != tree);
	
	if(!AVLIs_Empty(tree))
	{
		return Size(tree->root);
	}
	return 0;
}

int AVLIs_Empty(const avl_t *tree)
{
	assert(NULL != tree);
	
	return (NULL == tree->root);
}

static int ImplementForEach(node_t *node, action_func_t action_func,  void *params)
{
	int result = 0;
	if(NULL == node)
	{
		return 0;
	}
	ImplementForEach(LEFT_SON(node), action_func,  params);
	result = action_func(node->data, params);
	ImplementForEach(RIGHT_SON(node), action_func,  params);
	return result;
}

int AVLForEach(avl_t *tree, action_func_t action_func, void *params) /*in order*/
{
	if(!AVLIs_Empty(tree))
	{
		return ImplementForEach(tree->root, action_func, params);
	}
	return 0;
}

size_t AVLGetHeight(const avl_t *tree)
{
	assert(NULL != tree);
	
	if(!AVLIs_Empty(tree))
	{
		return tree->root->height;
	}
	return 0;
}



