#ifndef VSA_H
#define VSA_H
#include <stddef.h>


typedef struct vsa vsa_t;

/* initiation of an allocator */
/*if successful, returns vsa_t* , otherwise returns NULL */ 
vsa_t *VsaInit(void *buffer, size_t buf_size);

/* allocation of one segment */
/*if successful, returns a pointer */
/* the returned pointer must be aligned based on the max possible size alignment */
/*otherwise returns NULL*/
void *VsaAlloc(vsa_t *vsa, size_t num_bytes);

/* free allocation of one segment */
void VsaFree(void *to_free);

/* return the number of bytes that can still be allocated*/
size_t VsaCountFree(const vsa_t *vsa);

#endif


