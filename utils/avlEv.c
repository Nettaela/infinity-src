#include "avl.h"
#include <stdlib.h> /*malloc, free */
#include <assert.h>
#include "MyDefs.h"

enum {LEFT, RIGHT, NUM_SONS};

typedef struct node node_t;

struct node
{
	void *data;
	size_t height;/* CR change to int*/
	node_t *sons[NUM_SONS];
};

struct avl
{
	cmp_func_t cmp_func;
	node_t *root;
};

avl_t *AVLCreate(cmp_func_t cmp_func)
{
	avl_t *new_tree = (avl_t*)malloc(sizeof(*new_tree));
	
	if (NULL == new_tree)
	{
		return NULL;
	}
	
	new_tree->cmp_func = cmp_func;
	new_tree->root = NULL;
	return new_tree;
}
static void AVLDestroyImpl(node_t *node)
{
	if (NULL == node)
	{
		return;
	}
	AVLDestroyImpl(node->sons[LEFT]);
	AVLDestroyImpl(node->sons[RIGHT]);
	free(node);
}

 /*post order*/
void AVLDestroy(avl_t *tree)
{
	assert(tree);

	AVLDestroyImpl(tree->root);
	tree->root = NULL;
	free(tree);
	tree=NULL;

}

static node_t *InitNode(node_t *node, void* data, size_t height, node_t *l_son, node_t *r_son) 
{
	assert(node);
	assert(data);

	node->data = data;
	node->height = height;
	node->sons[LEFT] = l_son;
	node->sons[RIGHT] = r_son;

	return node;
}

static int GetNodeHeight(node_t *node)
{
	if (NULL == node)
	{
		return -1;
	}
	return (int)node->height;/*CR - if you change to int remove this cast*/
}

static void UpdateHeight(node_t *node)
{
	int l_height = 0;
	int r_height = 0;
	
	assert(NULL != node);
	
	l_height = GetNodeHeight(node->sons[LEFT]);
	r_height = GetNodeHeight(node->sons[RIGHT]);
	node->height = MAX(l_height, r_height) + 1;
}

static node_t *AVLSingleRotate(node_t *root, int dir)
{
	node_t *new_root = NULL;
	
	assert (NULL != root);
	assert (NULL != root->sons[!dir]);
	
	new_root = root->sons[!dir];
	root->sons[!dir] = new_root->sons[dir];
	new_root->sons[dir] = root;
	
	return new_root;
}

static node_t *AVLRotate(node_t *root, int dir)
{
	int double_rot = 0;
	node_t *new_root = NULL;
	
	assert (NULL != root);
	assert (NULL != root->sons[!dir]);
	
	new_root = root->sons[!dir];
	double_rot = (GetNodeHeight(new_root->sons[!dir]) < 
						GetNodeHeight(new_root->sons[dir]) ? 1 : 0);
						
	if (!double_rot)
	{
		new_root = AVLSingleRotate(root, dir);
	}
	else
	{
		root->sons[!dir] = AVLSingleRotate(root->sons[!dir], !dir);
		new_root = AVLSingleRotate(root, dir);
		UpdateHeight(new_root->sons[!dir]);
	}
	UpdateHeight(root);
	UpdateHeight(new_root);
	return new_root;
}

static node_t *BalNode(node_t *node)
{
	int h_diff = 0;
	
	assert(NULL != node);
	
	h_diff = GetNodeHeight(node->sons[LEFT]) - GetNodeHeight(node->sons[RIGHT]);
	if(h_diff <= 1 && h_diff >= -1)
	{
		return node;
	}
	if (h_diff > 1)
	{
		return AVLRotate(node, RIGHT);
	}
	return AVLRotate(node, LEFT);
}

node_t *AVLInsertImpl(node_t *root, node_t *new_node, cmp_func_t cmp_func)
{
	if (NULL == root)
	{
		root = new_node;
		return root;
	}
	if (cmp_func(root->data, new_node->data) < 0)
	{
		root->sons[RIGHT] = AVLInsertImpl(root->sons[RIGHT], new_node, cmp_func);
	}
	else /*CR - you allow duplicates, i think you should add another condition of cmp_func result, i know its supposed to be the users responsibility but if its not allowed (as documentations states), then dont ALLOW it*/  
	{
		root->sons[LEFT] = AVLInsertImpl(root->sons[LEFT], new_node, cmp_func);
	}
	++root->height;
	root = BalNode(root);
	UpdateHeight(root);
	return root;
}

int AVLInsert(avl_t *tree, void *data)
{
	node_t *new_node = (node_t*)malloc(sizeof(*new_node));
	if (NULL == new_node)
	{
		return 1;
	}
	new_node = InitNode(new_node, data, 0, NULL, NULL); 
	tree->root = AVLInsertImpl(tree->root, new_node, tree->cmp_func);
	return 0;

} /*no duplicates allowed */

static node_t *AVLFindNode(node_t *node, cmp_func_t cmp_func, const void *data2find)
{
	void *node2ret = NULL;
	
	assert (NULL != cmp_func);
	
	if (NULL == node)
	{
		return NULL;
	}
	if (cmp_func(node->data, data2find) == 0) /* CR - you call cmp func twice, how about saving the reult in a variable?*/
	{
		 node2ret = node;
	}
	else if (cmp_func(node->data, data2find) < 0)
	{
		node2ret = AVLFindNode(node->sons[RIGHT], cmp_func, data2find);
	}
	else
	{
		node2ret = AVLFindNode(node->sons[LEFT], cmp_func, data2find);
	}
	return node2ret;
}

static node_t *RemoveLeaf(node_t *node, cmp_func_t cmp_func, node_t *node2rem)
{
	void *data2ret = NULL;

	assert(NULL != node);
	
	data2ret = node2rem->data;/*cr - the name is a bit wrong, its called data to rturn but you dont return it, u just use it in cmp_func*/
	if (node2rem == node)
	{
		free(node2rem);
		node2rem = NULL;
		return node2rem;
	}
	if (cmp_func(node->data, data2ret) < 0)
	{
		node->sons[RIGHT] = RemoveLeaf(node->sons[RIGHT], cmp_func, node2rem);
	}
	else
	{
		node->sons[LEFT] = RemoveLeaf(node->sons[LEFT], cmp_func, node2rem);
	}
	node = BalNode(node);
	UpdateHeight(node);
	return node;
}

static node_t *RemoveParentOfOnlyChild(node_t *node, cmp_func_t cmp_func, node_t *node2rem, int what_child)
{
	void *data2ret = NULL;

	assert(NULL != node);
	
	data2ret = node2rem->data; /* CR the same*/
	if (node2rem == node)
	{
		node2rem = node2rem->sons[what_child];
		InitNode(node, 
				node->sons[what_child]->data, 
				node->sons[what_child]->height, 
				node->sons[what_child]->sons[LEFT], 
				node->sons[what_child]->sons[RIGHT]); 
		free(node2rem);
		node2rem = NULL;
		return node;
	}
	if (cmp_func(node->data, data2ret) < 0)
	{/*CR - the same exact code as in remove leaf function, could u have minimized it to one function or called it from here*/
		node->sons[RIGHT] = RemoveParentOfOnlyChild(node->sons[RIGHT], cmp_func, node2rem, what_child);
	}
	else
	{
		node->sons[LEFT] = RemoveParentOfOnlyChild(node->sons[LEFT], cmp_func, node2rem, what_child);
	}
	node = BalNode(node);
	UpdateHeight(node);
	return node;
}

static node_t *AVLFindNext(node_t *node)/* CR - bad name, it wont find the next of any node, it will only find the next of the right son, and what it actually does is go left (this is the same comment i got in my review...)*/
{
	assert(NULL != node);
	
	if (NULL == node->sons[LEFT])
	{
		return node;
	}
	return AVLFindNext(node->sons[LEFT]);
}
void *AVLRemove(avl_t *tree, const void *data)
{
	node_t *node2swap = NULL;
	node_t *node2rem = NULL;
	int what_child = 0;
	void *data2ret = NULL;
	void *data2swap = NULL;
	
	assert(tree);
	assert(tree->cmp_func);

	node2rem = AVLFindNode(tree->root, tree->cmp_func, data);
	data2ret = node2rem->data;
	if (NULL == node2rem)
	{
		return NULL;
	}
	if (NULL == node2rem->sons[LEFT] && NULL == node2rem->sons[RIGHT])
	{
		tree->root = RemoveLeaf(tree->root, tree->cmp_func, node2rem);
		return data2ret;
	}
	if (NULL == node2rem->sons[LEFT] || NULL == node2rem->sons[RIGHT])
	{
		what_child = (NULL == node2rem->sons[LEFT] ? RIGHT : LEFT);
		tree->root = RemoveParentOfOnlyChild(tree->root, tree->cmp_func, node2rem, what_child);
		return data2ret;
	}
	node2swap = node2rem;
	node2rem = AVLFindNext(node2swap->sons[RIGHT]);
	data2swap = node2rem->data;
	if (NULL == node2rem->sons[LEFT] && NULL == node2rem->sons[RIGHT])
	{
		tree->root = RemoveLeaf(tree->root, tree->cmp_func, node2rem);
	}
	else /*this node can have one child only */
	{
		assert(NULL == node2rem->sons[LEFT] || NULL != node2rem->sons[RIGHT]);
		tree->root = RemoveParentOfOnlyChild(tree->root, tree->cmp_func, node2rem, RIGHT);
	}
	node2swap->data = data2swap;
	return data2ret;
}

void *AVLFind(const avl_t *tree, const void *data)
{
	node_t *node_found = NULL;

	node_found = AVLFindNode(tree->root, tree->cmp_func, data);
	if (NULL == node_found) 
	{
		return NULL;
	}
	return node_found->data;	
}

static size_t AVLSizeImpl(node_t *root)
{
	if (NULL == root)
	{
		return 0;
	}
	return (1 + AVLSizeImpl(root->sons[LEFT]) + AVLSizeImpl(root->sons[RIGHT])); 
}

/*pre order */
size_t AVLSize(const avl_t *tree)
{	/*CR - assert tree*/
	return AVLSizeImpl(tree->root);
} 

int AVLIs_Empty(const avl_t *tree)
{/*CR - assert tree*/
	return (NULL == tree->root);
}

static int AVLForEachImpl(node_t *node, action_func_t action_func, void *params)
{
	int status = 0;

	if (NULL == node)
	{
		return status;
	}
	status = AVLForEachImpl(node->sons[LEFT], action_func, params);
	if (0 != status)
	{
		return status;
	}
	status = action_func(node->data, params);
	if (0 != status)
	{
		return status;
	}
	status = AVLForEachImpl(node->sons[RIGHT], action_func, params);
	return status;
}

int AVLForEach(avl_t *tree, action_func_t action_func, void *params)
{/*CR - assert tree*/
	return AVLForEachImpl(tree->root, action_func, params);

} /*in order*/

size_t AVLGetHeight(const avl_t *tree)
{/*CR - assert tree*/
	if (AVLIs_Empty(tree))
	{
		return 0;
	}
	return tree->root->height;
}

