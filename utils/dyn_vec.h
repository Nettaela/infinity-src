#ifndef DYN_VEC_H
#define DYN_VEC_H

typedef struct vector dyn_vec_t;


dyn_vec_t *DynVecCreate(size_t element_size, size_t capacity);

void DynVecDestroy(dyn_vec_t *vector);

size_t DynVecSize(const dyn_vec_t *vector);

size_t DynCapacity(const dyn_vec_t *vector);

int DynVecReserve(dyn_vec_t *vector, size_t capacity);

int DynVecPushBack(dyn_vec_t *vector, const void *data);

void DynVecPopBack(dyn_vec_t *vector);

void *DynVecGetItemAddress(const dyn_vec_t *vector, size_t index);



#endif


