#include "tree.h"
#include <stdlib.h> /* for malloc and free */
#include <assert.h>

#define DEADBEEF ((void*)0xdeadbeef)

/*CR - great macros!!!!!!!!!!*/
#define RIGHT_SON(a) a->sons[RIGHT]
#define LEFT_SON(a) a->sons[LEFT]
#define PARENT(a) a->parent

#define IS_A_LEFT_SON(a) (a->parent->sons[LEFT] == a)
#define IS_A_RIGHT_SON(a) (a->parent->sons[RIGHT] == a)

#define ROOT(tree) tree->end_stub->sons[LEFT]


enum TreeSons {LEFT, RIGHT, NUM_SONS};

typedef struct tree_info tree_info_t;

typedef struct tree_node tree_node_t;
struct tree_node
{
	tree_node_t *parent;
	tree_node_t *sons[NUM_SONS];
	void *data;
};

struct tree
{
	tree_node_t *root;
	compare_func_t cmp_func;
	void *params;
};
/*cr - i know i said they are great macros, but there's no need to put them here twice...*/
#define RIGHT_SON(a) a->sons[RIGHT]
#define LEFT_SON(a) a->sons[LEFT]
#define PARENT(a) a->parent

#define IS_A_LEFT_SON(a) (a->parent->sons[LEFT] == a)
#define IS_A_RIGHT_SON(a) (a->parent->sons[RIGHT] == a)

#define ROOT(tree) tree->end_stub->sons[LEFT] /* cr - there is no end_stub in your tree struct*/

 
static int IsRightSon(tree_node_t *node)/*cr - u dont need this function if u have a macro do u?*/
{
	assert(NULL != node);
	assert(NULL != node->parent);
		
	return (node->parent->sons[RIGHT] == node);
}
	
static void InitTree(
	tree_t *tree, 
	tree_node_t* root, 
	compare_func_t compare_func,
	void *params)
{
	assert(NULL != tree);
	assert(NULL != root);
	assert(NULL != compare_func);	
	
	tree->root = root;
	tree->cmp_func = compare_func;
	tree->params = params; 
}

static void InitTreeNode(
	tree_node_t *node_to_init,
	tree_node_t *parent,
	tree_node_t *sons[NUM_SONS],
	void *data)
{	
	assert(NULL != node_to_init);
		
	node_to_init->parent = parent;
	node_to_init->sons[LEFT] = sons[LEFT];
	node_to_init->sons[RIGHT] = sons[RIGHT];
	node_to_init->data = data;
}
	
tree_t *TreeCreate(compare_func_t func, void *params)
{
	tree_t *tree = NULL;
	tree_node_t *dummy_biggest = NULL;
	tree_node_t *sons[NUM_SONS] = {DEADBEEF, DEADBEEF};
	
	assert(NULL != func);
	
	tree = (tree_t*)malloc(sizeof(*tree));
	if (NULL == tree) {
		return NULL;
	}
	
	dummy_biggest = (tree_node_t*)malloc(sizeof(*dummy_biggest));
	if (NULL == tree) {
		return NULL;
	}
	/*cr - u can have a create node function that calls initnode and save some lines. also, arent the sons always NULL/deadbeef when u create/init the node? dont really need to pass is as a parameter to the function...*/
	InitTreeNode(dummy_biggest, NULL, sons, "dummy");
	InitTree(tree, dummy_biggest, func, params);
	
	return tree;	
}

static void *PlaceFirstNode(tree_node_t *root, tree_node_t *node_to_insert)
{
	assert(NULL != root);
	assert(NULL != node_to_insert);
	
	root->sons[LEFT] = node_to_insert;
	node_to_insert->parent = root;
			
	return root->sons[LEFT];
}

static void *PlaceTreeNode(tree_t *tree, tree_node_t *node_to_insert)
{
	tree_node_t *root = NULL;
	tree_node_t *cur_node = NULL;
	tree_node_t *parent_to_be = NULL;
	int last_turn = 0;
	compare_func_t cmp_func = NULL;
	void *data_to_insert = NULL;
	void *cur_data = NULL;
			
	assert(NULL != tree);
	assert(NULL != tree->root);
	assert(NULL != tree->cmp_func);
	assert(NULL != node_to_insert);
	assert(NULL != node_to_insert->data);	

	root = tree->root;	
			
	if (1 == TreeIsEmpty(tree)) {/*cr - parenthesis*/
		return (PlaceFirstNode(root, node_to_insert));
	}
	
	cur_node = root;
	cmp_func = tree->cmp_func;
	data_to_insert = node_to_insert->data;
	
	while (DEADBEEF != cur_node)
	{
		cur_data = cur_node->data;
		parent_to_be = cur_node;

		if (0 < cmp_func(data_to_insert, cur_data, NULL))
		{
			cur_node = cur_node->sons[RIGHT];
			last_turn = RIGHT;
		}
		else
		{
			cur_node = cur_node->sons[LEFT];
			last_turn = LEFT;
		}
	}
	
	node_to_insert->parent = parent_to_be;
	parent_to_be->sons[last_turn] = node_to_insert;

	return node_to_insert;
}

tree_iter_t TreeInsert(tree_t *tree, void *data)
{
	tree_node_t *node_to_insert = NULL;
	tree_iter_t tree_iter = {NULL};
	tree_node_t *sons[NUM_SONS] = {DEADBEEF, DEADBEEF};/*cr - see? whenever u create a node u dont relly put any information about the sons because newly created nodes are leaves, so u dont really need to create this array in advance and send it to the function*/
	
	assert(NULL != tree);
	assert(NULL != tree->root);	
	assert(NULL != data);

	node_to_insert = (tree_node_t*)malloc(sizeof(tree_node_t));/*cr - change size of to *var*/
	if (NULL == node_to_insert) {/*cr - parenthesis*/
		return TreeEnd(tree);
	}
/*cr - like i said in create tree, this insert function is just creating a node, the same way as in treecreate (needless duplication) and all the insert code is actually in a different function. u can call this function create node and placetreenode insert*/ 
	InitTreeNode(node_to_insert, NULL, sons, data);
	tree_iter.iterator = PlaceTreeNode(tree, node_to_insert);	
	
	return tree_iter;	
}

int TreeIsEmpty(tree_t *tree)
{
	assert(NULL != tree);
	assert(NULL != tree->root);

	return (DEADBEEF == tree->root->sons[LEFT]);/*cr - u have a root macro dont u?*/
}

size_t TreeSize(tree_t *tree)
{
	size_t counter = 0;
	tree_iter_t counting_iter = {NULL};
	tree_iter_t end_iter = {NULL};
	
	assert(NULL != tree);
	assert(NULL != tree->root);
	
	end_iter = TreeEnd(tree);
	counting_iter = TreeBegin(tree);
		
	while (!TreeIsSameIter(counting_iter, end_iter))
	{
		counting_iter = TreeNextIter(counting_iter);
		++counter;
	}
	return counter;
}

void *TreeGetData(tree_iter_t iter)
{
	tree_node_t *node = NULL;					
	
	assert(NULL != iter.iterator);

	node = iter.iterator;
	return node->data;
}

tree_iter_t TreeBegin(tree_t *tree)
{
	tree_iter_t begin_iter = {NULL};
	tree_node_t *cur_node = NULL;

	assert(NULL != tree);
	assert(NULL != tree->root);

	cur_node = tree->root;
	while (DEADBEEF != cur_node->sons[LEFT]) {/*cr - left son macro...*//*cr - parenthesis*/
		cur_node = cur_node->sons[LEFT];
	}
	begin_iter.iterator = cur_node;

	return begin_iter;
}

tree_iter_t TreeEnd(tree_t *tree)
{
	tree_iter_t end_iter = {NULL};
	
	assert(NULL != tree);
	assert(NULL != tree->root);
	
	end_iter.iterator = tree->root;/*cr - is the root the end? if it isnt, maybe think about changing the name...*/

	return end_iter;
}

tree_iter_t TreeNextIter(tree_iter_t iter)
{
	tree_iter_t cur_iter = {NULL};
	tree_node_t *cur_node = NULL;

	assert(NULL != iter.iterator);

	cur_iter.iterator = iter.iterator;
	cur_node = cur_iter.iterator;

	if (DEADBEEF != cur_node->sons[RIGHT]) {/*cr - u put the macros twice but arent using them...*//*cr - parenthesis*/
		cur_node = cur_node->sons[RIGHT];
	 
		while (DEADBEEF != cur_node->sons[LEFT]) {/*cr - parenthesis*/
			cur_node = cur_node->sons[LEFT];
		}
		cur_iter.iterator = cur_node;
	}
	else {
		while (IsRightSon(cur_node)) {/*cr - parenthesis*/
			cur_node = cur_node->parent;
		}
		cur_iter.iterator = cur_node->parent;
	}
	
	return cur_iter;
}

tree_iter_t TreePrevIter(tree_iter_t iter)
{
	tree_iter_t cur_iter = {NULL};
	tree_node_t *cur_node = NULL;
	
	assert(NULL != iter.iterator);
	
	cur_iter.iterator = iter.iterator;
	cur_node = cur_iter.iterator;
	
	if (DEADBEEF != cur_node->sons[LEFT]) {/*cr - parenthesis*/
		cur_node = cur_node->sons[LEFT];
		
		while (DEADBEEF != cur_node->sons[RIGHT]) {/*cr - parenthesis*/
			cur_node = cur_node->sons[RIGHT];
		}
		cur_iter.iterator = cur_node;
	}
	else {/*cr - parenthesis*/
		while (!IsRightSon(cur_node)) {/*cr - parenthesis*/
			cur_node = cur_node->parent;
		}
		cur_iter.iterator = cur_node->parent;
	}
	return cur_iter;
	
}

int TreeIsSameIter(const tree_iter_t iter1, const tree_iter_t iter2)
{
	assert(NULL != iter1.iterator);
	assert(NULL != iter2.iterator);
	
	return (iter1.iterator == iter2.iterator);
}

static int IsLeaf(tree_node_t *node)
{
	assert(NULL != node);
	
	return (node->sons[RIGHT] == DEADBEEF && node->sons[LEFT] == DEADBEEF);
}

void LeafRemove(tree_node_t *node_to_remove)/*cr - static!*/
{
	assert(NULL != node_to_remove);
	
	if (IsRightSon(node_to_remove)) {/*cr - parenthesis*/
		node_to_remove->parent->sons[RIGHT] = DEADBEEF;
	}
	else {/*cr - parenthesis*/
		node_to_remove->parent->sons[LEFT] = DEADBEEF;
	}
}

static void HasOneSonRemove(tree_node_t *node_to_remove)
{
	tree_node_t *son_node = DEADBEEF;
	
	if (DEADBEEF != node_to_remove->sons[RIGHT]) {/*cr - parenthesis*/
		son_node = node_to_remove->sons[RIGHT];
	} 
	else {
		son_node = node_to_remove->sons[LEFT];
	}

	son_node->parent = node_to_remove->parent;
	
	if( IsRightSon(node_to_remove)) {/*cr - parenthesis*/
		node_to_remove->parent->sons[RIGHT] = son_node;
	}
	else {
		node_to_remove->parent->sons[LEFT] = son_node;
	}
}

static int IsHasOneSon(tree_node_t *node_to_remove)
{
	int num_sons = 0;
	if(DEADBEEF != node_to_remove->sons[RIGHT])	{
		++num_sons;
	}
	if(DEADBEEF != node_to_remove->sons[LEFT])	{
		++num_sons;
	}	
	return (num_sons == 1);
}

static void ReplaceNode(tree_node_t *to_remove, tree_node_t *replacement)
{
	if (IsRightSon(to_remove)) {
		to_remove->parent->sons[RIGHT] = replacement;
	}
	else {
		to_remove->parent->sons[LEFT] = replacement;
	}
	
	replacement->parent = to_remove->parent;
	if (replacement != to_remove->sons[RIGHT]) {
		replacement->sons[RIGHT] = to_remove->sons[RIGHT];
	}
	replacement->sons[LEFT] = to_remove->sons[LEFT];
}

void *TreeRemove(/*tree_t *remove_from,*/ tree_iter_t to_remove)
/*Try to implement without the tree*/
{
	tree_node_t *node_to_remove = DEADBEEF;
	tree_node_t *replacement_node = DEADBEEF;
	tree_node_t *replacement_right_son = DEADBEEF;
	void *removed_data = NULL;
	
	tree_iter_t replace_iter = {NULL};
	
	assert(NULL != to_remove.iterator);
	
	node_to_remove = to_remove.iterator;
	removed_data = node_to_remove->data;
	
	if (IsLeaf(node_to_remove)) {
		LeafRemove(node_to_remove);
	} 
	else if (IsHasOneSon(node_to_remove)) {
		HasOneSonRemove(node_to_remove);
	}
	else {
		replace_iter = TreeNextIter(to_remove);
		replacement_node = replace_iter.iterator;
		replacement_right_son = replacement_node->sons[RIGHT];

		if (DEADBEEF != replacement_right_son) {
			replacement_right_son->parent = replacement_node->parent;
			replacement_node->parent->sons[LEFT] = replacement_right_son;
		}	
		
		if (!IsRightSon(replacement_node)) {
			replacement_node->parent->sons[LEFT] = DEADBEEF;
		}
		node_to_remove->sons[LEFT]->parent = replacement_node;
		node_to_remove->sons[RIGHT]->parent = replacement_node;	
		
		ReplaceNode(node_to_remove, replacement_node);
	}
	
	free(node_to_remove);
	node_to_remove = NULL;
	
	return removed_data;
}
	
int IsLeftSonLeaf(tree_node_t *node)
{
	tree_node_t *left_son = NULL;
	
	assert(NULL != node);
	
	if (DEADBEEF == node->sons[LEFT]) {
		return 0;
	}
	left_son = node->sons[LEFT];
	
	
	return (IsLeaf(left_son));
}
	
int IsRightSonLeaf(tree_node_t *node) /*cr -  static*/
{
	tree_node_t *right_son = NULL;
	
	assert(NULL != node);
	
	if (DEADBEEF == node->sons[RIGHT]) {
		return 0;
	}
	right_son = node->sons[RIGHT];
	
	
	return (IsLeaf(right_son));
}		

void CutLeaves(tree_node_t *node) /* cr - static*/
{
	tree_iter_t iter_to_remove = {NULL};
	assert(NULL != node);
	
	if(IsLeftSonLeaf(node)) {
		iter_to_remove.iterator = node->sons[LEFT];
		TreeRemove(iter_to_remove);
	}
	if(IsRightSonLeaf(node)) {
		iter_to_remove.iterator = node->sons[RIGHT];
		TreeRemove(iter_to_remove);
	}
}

static void RemoveAllNodes(tree_t *to_destroy)
{
	tree_node_t *cur_node = NULL;
	
	assert(NULL != to_destroy);
	assert(NULL != to_destroy->root);
	
	cur_node = to_destroy->root;
	while(!TreeIsEmpty(to_destroy)) 
	{
		while (!IsLeftSonLeaf(cur_node) && DEADBEEF != cur_node->sons[LEFT]) {
			cur_node = cur_node->sons[LEFT];
		}
		CutLeaves(cur_node);
		
		if (DEADBEEF != cur_node->sons[RIGHT]) {
			cur_node = cur_node->sons[RIGHT];
		}
		else {
			cur_node = cur_node->parent;
		}
	}
}

void TreeDestroy(tree_t *to_destroy)
{
	assert(DEADBEEF != to_destroy);
	
	RemoveAllNodes(to_destroy);
	
	free(to_destroy->root);
	to_destroy->root = NULL;
	free(to_destroy);
	to_destroy = NULL;
}

tree_iter_t TreeFind(tree_t *tree, const void *data)
{
	int cmp_result = -1;
	compare_func_t cmp_func = NULL;
	tree_node_t *cur_node = NULL;
	void *cur_data = NULL;
	const void *data_to_find = NULL;
	tree_iter_t found_iter = {NULL};
	
	assert(NULL != tree);
	assert(NULL != tree->cmp_func);
	assert(NULL != tree->root);
	
	cmp_func = tree->cmp_func;
	data_to_find = data;
	cur_node = tree->root->sons[LEFT];
	
	while (1) {
		cur_data = cur_node->data;
		cmp_result = cmp_func(cur_data, data_to_find, NULL);
		
		if (0 == cmp_result) {
			found_iter.iterator = cur_node;
			return found_iter;
		}
		
		if (0 > cmp_result) {
			if (DEADBEEF == cur_node->sons[RIGHT]) {
				break;
			}
			cur_node = cur_node->sons[RIGHT];	
		}
			
		if (0 < cmp_result) {
			if (DEADBEEF == cur_node->sons[LEFT]) {
				break;
			}
			cur_node = cur_node->sons[LEFT];
		}
		
	}
	found_iter = TreeEnd(tree);
	return found_iter;	
}

static size_t CurrentNodeHeight(tree_t *tree, tree_node_t *node)
{
	size_t height = 0;
		
	assert(NULL != tree);
	assert(NULL != tree->root);
	
	while (node != tree->root->sons[LEFT]) {/* cr - wrong place for a parenthesis*/
		node = node->parent;
		++height;
	}
	return height;	
}	

size_t GetTreeHeight(tree_t *tree)
{
	tree_iter_t begin_iter = {NULL};
	tree_iter_t end_iter = {NULL};
	tree_iter_t cur_iter = {NULL};
	size_t max_height = 0;
	size_t cur_height = 0;	
	tree_node_t *cur_node = NULL;
	
	assert(NULL != tree);
	
	if (TreeIsEmpty(tree)) {
		return max_height;
	}
	
	begin_iter = TreeBegin(tree);
	end_iter = TreeEnd(tree);
		
	for(cur_iter = begin_iter
		; !TreeIsSameIter(cur_iter, end_iter)
		; cur_iter = TreeNextIter(cur_iter))
	{
		cur_node = cur_iter.iterator;
		if (IsLeaf(cur_node)) {
			cur_height = CurrentNodeHeight(tree, cur_node);
			if (cur_height > max_height) {
				max_height = cur_height;
			}
		}
	}
	return max_height;
}

int TreeForEach(
	tree_iter_t from_iter, 
	tree_iter_t to_iter, 
	action_func_t action, 
	void *param)
{
	tree_iter_t cur_iter = {NULL};
	tree_node_t *cur_node = NULL;
	void *cur_data = NULL;
	int action_status = 0;
	
	assert(NULL != from_iter.iterator);
	assert(NULL != to_iter.iterator);
	assert(NULL != action);
			
	for(cur_iter = from_iter
		; !TreeIsSameIter(cur_iter, to_iter)
		; cur_iter = TreeNextIter(cur_iter)) 
	{
		cur_node = cur_iter.iterator;
		cur_data = cur_node->data;
		action_status = action(cur_data, param);
		if (0 != action_status) {
			return action_status;
		}
	}	
	return action_status;
}


