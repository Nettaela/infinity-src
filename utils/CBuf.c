#include <stdlib.h> /*for malloc and free*/
#include <string.h> /*for memcpy*/
#include <assert.h> /*for assert*/
#include "CBuf.h"

#define MIN(a,b) (a > b)? b : a

typedef unsigned char byte_t;

CBuf_err_t Cbuf_errno_g;

struct cbuf
{
	size_t read_from;	/*index of read*/
	size_t written;		/*counter of written bytes*/
	size_t capacity;	/*maximum cap of buffer*/
	char buf_start[1];	/*buffer starts here*/
};

cbuf_t *CBufCreate(size_t buf_cap)
{
	cbuf_t *cbuf = NULL;

	
	assert(0 < buf_cap);
	
	cbuf = (cbuf_t*)malloc(sizeof(cbuf_t) + buf_cap);
	
	if(NULL == cbuf)
	{	
		Cbuf_errno_g = CBuf_OVERFLOW;
		return NULL;
	}
	
	cbuf->read_from = 0;
	cbuf->written = 0;
	cbuf->capacity = buf_cap;
	
	Cbuf_errno_g = CBuf_OK;
	return cbuf;
}

void CBufDestroy(cbuf_t *cbuf)
{
	assert(NULL != cbuf);
	free(cbuf);
}

size_t CBufFreeSpace(const cbuf_t *cbuf)
{
	assert(NULL != cbuf);
	return cbuf->capacity - cbuf->written;
	
}

size_t CBufCapacity(const cbuf_t *cbuf)
{
	assert(NULL != cbuf);
	return cbuf->capacity;
}

int CBufIsEmpty(const cbuf_t *cbuf)
{
	assert(NULL != cbuf);
	return (CBufFreeSpace(cbuf) == cbuf->capacity);
}

size_t CBufRead(cbuf_t *cbuf, char *data, size_t bytes_to_read)
{
	size_t till_the_end = cbuf->capacity - cbuf->read_from;
	size_t minimum = 0;
	
	assert(NULL != cbuf);
	assert(NULL != data);
	
	Cbuf_errno_g = CBuf_OK;
	
	if (bytes_to_read > cbuf->written)
	{
		bytes_to_read = cbuf->written;
		Cbuf_errno_g = CBuf_NODATA;
	}
	/*define the amount of bytes for the first memcpy by choosing between num of bytes or space till the end*/ 
	minimum = MIN(bytes_to_read, till_the_end);
	/*copy first part*/
	memcpy(data, cbuf->buf_start + cbuf->read_from, minimum);
	/*copy whats left after the first copy, starting at 0 */
	if(0 != (bytes_to_read - minimum))
	{
		memcpy(data + minimum, cbuf->buf_start, bytes_to_read - minimum);
	}
	/*update number of written bytes and read index*/
	cbuf->written -= bytes_to_read;
	
	cbuf->read_from = (cbuf->read_from + bytes_to_read) % cbuf->capacity;
	
	return bytes_to_read;
}

size_t CBufWrite(cbuf_t *cbuf, const char *data, size_t bytes_to_write)
{
	/*get the index for writing using read index and written bytes - go in a circle using mod*/
	size_t write_index = (cbuf->read_from + cbuf->written) % cbuf->capacity;
	size_t free_space = CBufFreeSpace(cbuf);	
	size_t till_the_end = cbuf->capacity - write_index;
	size_t minimum = 0;
	
	assert(NULL != cbuf);
	assert(NULL != data);
	
	Cbuf_errno_g = CBuf_OK;	
	
	if(bytes_to_write > free_space)
	{
		bytes_to_write = free_space;
		Cbuf_errno_g = CBuf_OVERFLOW;
	}
	/*define the amount of bytes for the first memcpy by choosing between num of bytes or space till the end*/ 
	minimum = MIN(till_the_end, bytes_to_write);
	
	/*copy first part*/
	memcpy(cbuf->buf_start + write_index, data, minimum);
	/*copy whats left after the first copy, starting at 0 */
	if(0 != (bytes_to_write - minimum))
	{ 
		memcpy(cbuf->buf_start, data + minimum, bytes_to_write - minimum);
	}
	/*update number of written bytes (read offset)*/
	cbuf->written += bytes_to_write;
		
	return bytes_to_write;
}




