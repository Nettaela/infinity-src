#ifndef TREE_H
#define TREE_H
#include <stddef.h>
/*enum TreeSons {LEFT, RIGHT, NUM_SONS};*/

/*
struct tree_node_t
{
	tree_node_t *parent;
	tree_node_t *sons[NUM_SONS];
	void *data;
};

*/
typedef struct tree tree_t;
typedef struct tree_iter 
{
	void *iterator;
}tree_iter_t;

typedef int (*compare_func_t)(const void *data, const void *data_to_compare, void *params);
typedef int (*action_func_t)(void *data, void *param);

tree_t *TreeCreate(compare_func_t func, void *params);

void TreeDestroy(tree_t *to_destroy);

size_t GetTreeHeight(tree_t *tree);

tree_iter_t TreeInsert(tree_t *tree, void *data);

void *TreeRemove(/*tree_t *remove_from,*/ tree_iter_t to_remove); /*Try to implement without the tree*/

tree_iter_t TreeFind(tree_t *tree, const void *data);

int TreeForEach(tree_iter_t from, tree_iter_t to, action_func_t action, void *param); /*Traverse in-order*/

void *TreeGetData(tree_iter_t iter);

int TreeIsEmpty(tree_t *tree);

size_t TreeSize(tree_t *tree);

tree_iter_t TreeNextIter(tree_iter_t iter);

tree_iter_t TreePrevIter(tree_iter_t iter);

tree_iter_t TreeBegin(tree_t *tree);

tree_iter_t TreeEnd(tree_t *tree);

int TreeIsSameIter(const tree_iter_t iter1, const tree_iter_t iter2);

#endif
