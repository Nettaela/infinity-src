#include "vsa.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h> /* puts*/
#include <string.h> /* memcpy*/
#define MAGIC_NUM 528772727
#define ABS(a) ( (a) < 0 ? -(a) : a )
#define IS_ALLOCATED(a) ( (a->seg_size) < 0 ? 1 : 0 )
#define IS_FREE(a)  ( (a->seg_size) > 0 ? 1 : 0 )

typedef struct segment
{
	long seg_size;
	#ifndef NDEBUG
	long magic_num;
	#endif
}segment_t;

struct vsa
{
	size_t total_size;
	segment_t *last_segment;
};

#define SIZEOF_SEG_T sizeof(segment_t)
#define SIZEOF_VSA_T sizeof(vsa_t)
#define NEXT_SEG(a) (a + (ABS(a->seg_size) / SIZEOF_SEG_T))


static void *Allocate(size_t num_bytes, size_t current_seg_size, segment_t *where);
static void *FindFreeSpace(vsa_t *vsa, segment_t *current_segment);
static segment_t *FindAndMerge(vsa_t *vsa, size_t requested_size);
static void MergeFreeSegments(segment_t *current_segment, segment_t *next_segment);
static segment_t *InitSegment(segment_t *seg, size_t seg_size);

/* initiation of an allocator */
/*if successful, returns vsa_t* , otherwise returns NULL */ 
/*O(?)*/ 
vsa_t *VsaInit(void *buffer, size_t buf_size)
{
	size_t buf_size_round_down = buf_size - (buf_size % SIZEOF_SEG_T) - SIZEOF_VSA_T;
	size_t buf_size_minus_init_structs = buf_size_round_down - (2 * SIZEOF_SEG_T);
	segment_t *new_segment = NULL;
	segment_t *last_segment = NULL;
	
	vsa_t *new_vsa = (vsa_t*)buffer;
	segment_t *seg_size_buffer_runner = (segment_t*) buffer;
	
	assert(buf_size_round_down > SIZEOF_VSA_T + SIZEOF_SEG_T);
	
	new_segment = seg_size_buffer_runner + 1;
	last_segment = seg_size_buffer_runner + (buf_size_minus_init_structs / SIZEOF_SEG_T);
	
	last_segment = InitSegment(last_segment, 0);
	new_segment = InitSegment(new_segment, buf_size_minus_init_structs);
	
	new_vsa->total_size = buf_size_minus_init_structs;
	new_vsa->last_segment = last_segment;
	
	return new_vsa;
}

static segment_t *InitSegment(segment_t *seg, size_t seg_size)
{
	seg->seg_size = seg_size;
	#ifndef NDEBUG
	seg->magic_num = MAGIC_NUM;
	#endif
	return seg;
}

/* allocation of one segment */
/*if successful, returns a pointer */
/* the returned pointer must be aligned based on the max possible size alignment */
/*otherwise returns NULL*/
/*O(1)*/
void *VsaAlloc(vsa_t *vsa, size_t num_bytes)
{	
	size_t total_buf_size = vsa->total_size;
	size_t current_seg_size = 0; 
	size_t num_bytes_pad_struct = num_bytes + (num_bytes % SIZEOF_SEG_T) + SIZEOF_SEG_T;
	segment_t *first_segment = (segment_t*)vsa + 1; 
	segment_t *current_segment = NULL;
	
	assert(NULL != vsa);

	/*make sure there is enough space*/
	if(total_buf_size < num_bytes_pad_struct)
	{
		puts("cant allocate, num bytes requested larger than buffer");
		return NULL;
	}
	
	/*find a free space (where seg size is positive*/
	current_segment = FindAndMerge(vsa, num_bytes_pad_struct);

	if(current_segment != NULL)
	{	
		current_seg_size = current_segment->seg_size;
		return Allocate(num_bytes_pad_struct, current_seg_size, current_segment);
	}
	
	puts("cant allocate, out of space");
	return NULL;

}

static segment_t *FindAndMerge(vsa_t *vsa, size_t requested_size)
{
	segment_t *next_segment = {NULL};
	segment_t *current_segment = {NULL};
	segment_t *last_segment = vsa->last_segment;
	segment_t *first_segment = (segment_t*)vsa + 1;
	long current_size = 0;
	long next_size = 0;
	current_segment = first_segment;
	next_segment = first_segment;

	
	/*find a free space*/
	/*if its large enough - allocate and return it*/
	/*otherwise: try to merge:
	here is the only loop!!
	see if the next segment is also free*/
	/*while the next one is free - mergem*/
	/*if the next is not free , try to find a new free space after the current*/
	/*if there is, return to the begining*/
	/*otherwise: return null*/
		
	
	current_segment = FindFreeSpace(vsa, first_segment);
	if(current_segment == NULL)
	{
		return NULL;
	}
	
	current_size = current_segment->seg_size;

	if(requested_size <= current_size)
	{
		return current_segment;
	}
	

	while(requested_size > current_size && current_segment != NULL)
	{
			
		next_segment = NEXT_SEG(current_segment);
		while(IS_FREE(next_segment) && next_segment < last_segment)
		{			
			MergeFreeSegments(current_segment, next_segment);
			next_segment = NEXT_SEG(current_segment);

		}
		current_size = current_segment->seg_size;
		if(requested_size <= current_size)
		{
			return current_segment;
		}
				
		current_segment = FindFreeSpace(vsa, next_segment);
		if(current_segment == NULL)
		{
			return NULL;
		}	
	}
	
	current_size = current_segment->seg_size;	
	if (current_size >= requested_size)
	{
		return current_segment;
	}
	return NULL;
}

static void *FindFreeSpace(vsa_t *vsa, segment_t *current_segment)
{
	segment_t *last_segment = vsa->last_segment;
	
	long current_size = 0;
		
	while(current_segment < last_segment) 
	{
		current_size = current_segment->seg_size;
		if(IS_ALLOCATED(current_segment))
		{
			/*current_segment += ((ABS(current_size)/SIZEOF_SEG_T));*/
			current_segment = NEXT_SEG(current_segment);
		}
		else
		{
			return current_segment;
		}
	}
	return NULL;
}

static void *Allocate(size_t num_bytes, size_t current_seg_size, segment_t *where)
{
	long seg_size_to_allocate = num_bytes - SIZEOF_SEG_T;
	long remaining_buf = current_seg_size - seg_size_to_allocate;
	segment_t *next_segment = NULL;
	
	next_segment = where + (seg_size_to_allocate / SIZEOF_SEG_T);
	next_segment = InitSegment(next_segment,remaining_buf);
	where->seg_size = -seg_size_to_allocate;
	
	return ++where;
}

static void MergeFreeSegments(segment_t *current_segment, segment_t *next_segment)
{
	long current_size = 0;
	long next_size = 0;

	if(IS_FREE(next_segment) && IS_FREE(current_segment))
	{
		current_size = current_segment->seg_size;
		next_size = next_segment->seg_size;
		current_segment->seg_size = current_size + next_size;
	}
}
/* free allocation of one segment */
/*O(1)*/
void VsaFree(void *to_free)
{
	/*change size from minus to plus (minus is occupied)*/
	segment_t *segment_to_free = to_free;
	long seg_size = 0;
	
	--segment_to_free;
		
	if(IS_FREE(segment_to_free))
	{
		return;
	}
	seg_size = segment_to_free->seg_size;
	segment_to_free->seg_size =	(-seg_size);
}


/* return the number of bytes that can still be allocated*/
/*O(n)*/
size_t VsaCountFree(const vsa_t *vsa)
{
	/*while not at the end of the buffer
	go over the sizes , count the ones that are more than 0*/
	segment_t *current_segment = {NULL};
	segment_t *last_segment = vsa->last_segment;
	long current_size = 0;
	size_t free_space = 0;

	++vsa;
	current_segment = (segment_t*)vsa;
	
	while(current_segment < last_segment) 
	{
		if(IS_FREE(current_segment))
		{
			current_size = current_segment->seg_size;
			free_space += current_size;
		}
		current_segment = NEXT_SEG(current_segment);
	}
	return free_space;
}
	



