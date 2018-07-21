


typedef struct tree tree_t;
typedef struct node node_t;
typedef int (*cmp_func_t)(void *data1, void *data2);
typedef int (*action_func_t)(void *param);


tree_t *AVLTreeCreate(cmp_func_t func);

void AVLTreeDestroy(tree_t *tree);

size_t AVLTreeSize(tree_t *tree);

int AVLTreeIsEmpty(tree_t *tree);

node_t *AVLTreeInsert(tree_t *tree, void *data);

node_t *AVLTreeFind(tree_t *tree, void *data);

void AVLTreeRemove(tree_t *tree, void *data); /*seek and destroy*/

int AVLTreeForEach(tree_t *tree, action_func_t func, void *param);

size_t AVLTreeGetHeight(node_t *node);

 
