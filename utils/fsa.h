#ifndef FSA_H
#define FSA_H
#include <stdlib.h>

typedef struct fsa fsa_t;

/* initiation of an allocator */
/*if successful, returns fsa_t* , otherwise returns NULL */ 
/*O(?)*/ 
fsa_t *FsaInit(void *buffer, size_t total_size, size_t block_size);

/* allocation of one block */
/*if successful, returns a pointer */
/* the returned pointer must be aligned based on the max possible size alignment */
/*otherwise returns NULL*/
/*O(1)*/
void *FsaAlloc(fsa_t *fsa);

/* free allocation of one block */
/*O(1)*/
void FsaFree(void *block);

/* return suggested fsa size based on block sizes and the number of blocks*/
/*if Failed the function returns 0*/
/*max possible size alignment must be adressed*/
/*also note that every block will needs an allocated segment for managment */
/*O(1)*/
size_t FsaSuggestSize(size_t num_of_blocks, size_t block_size);

/* return the number of blocks that can still be allocated*/
/*O(n)*/
size_t FsaCountFree(const fsa_t *fsa);

#endif

