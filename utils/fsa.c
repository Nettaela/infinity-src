#include "fsa.h"

static size_t max_padding = sizeof(struct padder pad{ long long number; char c[1]});

struct fsa 
{
	void *memory;
	size_t block_size;
	size_t total_size;
	void *allocated_ptr;
	void *next_free;
	void *locality;	
};

typedef struct block 	
{
	void *next_ptr;
}block_t;
/* initiation of an allocator */
/*if successful, returns fsa_t* , otherwise returns NULL */ 
/*O(?)*/ 
fsa_t *FsaInit(void *buffer, size_t total_size, size_t block_size)
{
	/*initialize fsa_t struct at the start of *(fsa_t)(buffer)*/
	/*calculate padding by max padding macro*/
	/*initialize struct fields:
	memory = buffer
	block size = block size + padding
	total_size = total_size
	allocated_ptr will be initialized to locality+1
	next free initialized to null*/
	
	/*return ptr to fsa_t*/
	
}

/* allocation of one block */
/*if successful, returns a pointer */
/* the returned pointer must be aligned based on the max possible size alignment */
/*otherwise returns NULL*/
/*O(1)*/
void *FsaAlloc(fsa_t *fsa)
{
	/*check that ((allocated_ptr - locality) / block size) is < less than num_of_blocks
	(there is still space available for allocation)*/
	
	/*the following can be a seperate static function: */ 
	/*initialize variable blocksize from fsa->block_size*/
	/*create new block_t struct*/

	/*initialize block struct at the point of allocated_ptr*/
	/* *(struct block)(fsa->allocated_ptr) = new_block; */
		
	/*check in fsa if next free == NULL*/
		/*initialize next_ptr in block to fsa*/
		/*increase allocated_ptr by block_size + sizeof pointer*/
		/*return that block_t + sizeof block_t*/
	
	/*otherwise:*/
		/*follow next_free pointer in fsa and save that block adress in a variable*/
			/*if next_ptr in that block is the fsa struct (adresses are the same)*/
				/*initialize next_free pointer in fsa to NULL*/
				/*return that block + sizeof block_t*/
				
			/*otherwise:*/
				/*initialize next_free pointer in fsa to the next_ptr in that block*/
				/*initialize next_ptr in the block to fsa*/
				/*return that block + sizeof block_t*/	
				
}

/* free allocation of one block */
/*O(1)*/
void FsaFree(void *block)
{
	/*block_t = block - sizeof(block_t)*/
	/*next_ptr in block points to fsa, save it in variable*/
	/*check in fsa if next free == NULL*/
		/*point next_free in fsa to the block*/
	
	/*otherwise:*/
		/*point next_ptr in the block to the same as the next_free in fsa*/ 
		/*point next_free in fsa to the block*/
}

/* return suggested fsa size based on block sizes and the number of blocks*/
/*if Failed the function returns 0*/
/*max possible size alignment must be adressed*/
/*also note that every block will needs an allocated segment for managment */
/*O(1)*/
size_t FsaSuggestSize(size_t num_of_blocks, size_t block_size)
{
	/*add sizeof void* pointer to block_size */ 
	/*return (num_of_blocks * block_size) + sizeof fsa_t */

}
/* return the number of blocks that can still be allocated*/
/*O(n)*/
size_t FsaCountFree(const fsa_t *fsa)
{
	/*define counter = 0*/
	/*save a a variable = allocated_ptr from fsa*/
	/*save variable = next free from fsa*/
	/*while next_free != NULL*/
		/*initialize next free from next ptr*/
		/*increment counter*/
		
	/*while allocated_ptr is not at the end (locality + total size +1)*/
		/*increase allocated_ptr by block size + sizeof pointer*/
		/*increment counter*/
	/*return counter*/
}
















