
typedef struct fsa fsa_t;

fsa_t * FSAInit(size_t size_of_block, void *mallocd_mem);
void *FSAAlloc(fsa_t *allocator);/*returns pointer to block*/
void FSAFree(void *block);
size_t FSASuggestedSize(size_t num_of_block, size_t size_of_block);
size_t FSACountFree(fsa_t *allocator);



