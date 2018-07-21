#ifndef AVL_H
#define AVL_H

#include <stddef.h>

typedef struct avl avl_t;

typedef int (*cmp_func_t)(const void *data1, const void *data2);
typedef int (*action_func_t)(void *data, void *params);

avl_t *AVLCreate(cmp_func_t cmp_func);

void AVLDestroy(avl_t *tree); 

int AVLInsert(avl_t *tree, void *data); /*no duplicates allowed */

void *AVLRemove(avl_t *tree, const void *key);

void *AVLFind(const avl_t *tree, const void *key);

size_t AVLSize(const avl_t *tree); /*O(n)*/

int AVLIs_Empty(const avl_t *tree);

int AVLForEach(avl_t *tree, action_func_t action_func, void *params);

size_t AVLGetHeight(const avl_t *tree);

#endif
