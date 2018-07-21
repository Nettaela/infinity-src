#ifndef DYN_VECTOR_H
#define DYN_VECTOR_H

typedef struct DynVec dynVec_t;

dynVec_t *DynVec_Create(size_t element_size, size_t element_num);
void DynVec_Destroy(dynVec_t *vector);
size_t DynVec_Size(const dynVec_t *vector);
size_t DynVec_Capacity(const dynVec_t *vector);                    
int  DynVec_Reserve(dynVec_t *vector, size_t amount);
int DynVec_PushBack(dynVec_t *vector, const void *data);
void DynVec_StackPopBack(dynVec_t *vector);
void * DynVec_GetItemAdress(dynVec_t *vector, size_t index);

#endif


