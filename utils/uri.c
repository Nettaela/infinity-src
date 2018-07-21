static int ImpleIsBefore(const void *data1, const void *data2, void *params)
{
    func_container_t *func_container = NULL;
    p_queue_is_before_t is_before = NULL;
    void **d1 = {NULL};
    void **d2 = {NULL};
   
    assert (NULL != data1);
    assert (NULL != data2);
    assert (NULL != params);       
   
    func_container = params;
    is_before = func_container->is_before;
    d1 = (void**)data1;
    d2 = (void**)data2;
   
    return is_before(*d1, *d2);
}

typedef struct func_container func_container_t;
struct func_container
{
    p_queue_is_before_t is_before;
};


/*int DynVecPushBack(dyn_vec_t *vector, const void *data);*/
int PQueueEnqueue(pqueue_t *pqueue, void *data)
{
    void *dyn_vec_data = NULL;
    size_t num_members = 0;
    size_t elem_size = 0;
    func_container_t func_container = {0};
   
    assert(NULL != pqueue);
    assert(NULL != pqueue->dyn_vec);
    assert(NULL != pqueue->is_before);       
   
    if(1 == DynVecPushBack(pqueue->dyn_vec, data)) {
        return 1;
    }
   
    func_container.is_before = pqueue->is_before;
    dyn_vec_data = DynVecGetItemAddress(pqueue->dyn_vec, 0);
    num_members = DynVecSize(pqueue->dyn_vec);
    elem_size = sizeof(void*);
   
    HeapifyUp(
        dyn_vec_data,
        num_members,
        elem_size,
        ImpleIsBefore,
        &func_container);
   
    return 0;
