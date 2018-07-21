#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "CBuf.h"

typedef unsigned char byte_t;
/*typedef enum {CBuf_OK , CBuf_NODATA, CBuf_OVERFLOW} CBuf_err_t;*/
CBuf_err_t Cbuf_errno_g;

struct cbuf
{
	size_t read;
	size_t write;
	size_t capacity;
	char buf_start[1];
};

cbuf_t *CBufCreate(size_t buf_cap)
{
	cbuf_t *cbuf = (cbuf_t*)malloc(sizeof(cbuf_t) + buf_cap + 1);
	assert(cbuf);/*put an  actual if here*/
	cbuf->read = 0;
	cbuf->write = 0;
	cbuf->capacity = buf_cap;
	/*define full flag: 1=full, 0=empty*/
	*(cbuf->buf_start + cbuf->capacity + 1) = 0;
	return cbuf;
}

void CBufDestroy(cbuf_t *cbuf)
{
	free(cbuf);
}

size_t CBufFreeSpace(const cbuf_t *cbuf)
{
	size_t head = cbuf->read;
	size_t tail = cbuf->capacity - cbuf->write;
	if(*(cbuf->buf_start + cbuf->capacity + 1) == 0) /*flag 0 means read has passed through and freed some space. its 1 after write has been there and read hasnt*/
	{
		return head + tail;
	}
	return cbuf->read - cbuf->write;
}

size_t CBufCapacity(const cbuf_t *cbuf)
{
	return cbuf->capacity;
}

int CBufIsEmpty(const cbuf_t *cbuf)
{
	return (CBufFreeSpace(cbuf) == cbuf->capacity);
}

size_t CBufRead(cbuf_t *cbuf, char *data, size_t bytes_to_read)
{
	size_t index = 0;
	size_t bytes_read = 0;
/*cbuf->buf_start + cbuf->capacity + 1) == 0*/

	if(0 == CBufFreeSpace(cbuf))
	{
		Cbuf_errno_g = CBuf_NODATA;
		return bytes_read;
	}
	
	for(index = 0 ; index < bytes_to_read ; ++index)
	{	
		/*for(; cbuf->write < cbuf->capacity; (cbuf->write += 1) % cbuf->capacity)*/
		
		if(cbuf->read == cbuf->write && (*(cbuf->buf_start + cbuf->capacity + 1) == 1))
		{
			Cbuf_errno_g = CBuf_NODATA;
			return bytes_read;
		}
			
		data[index] = cbuf->buf_start[cbuf->read] ;
		++bytes_read;
		cbuf->read = (cbuf->read + 1) % cbuf->capacity;
		
		if(0 == cbuf->read)
		{
			*(cbuf->buf_start + cbuf->capacity + 1) = 0;
		}
		
	}
	
	Cbuf_errno_g = CBuf_OK;	
	return bytes_read;
}

size_t CBufWrite(cbuf_t *cbuf, const char *data, size_t bytes_to_write)
{
	size_t index = 0;
	size_t bytes_written = 0;
	size_t free_space = CBufFreeSpace(cbuf);	
	
	if(0 == free_space)
	{
		Cbuf_errno_g = CBuf_OVERFLOW;
		return bytes_written;
	}
	(bytes_to_write > free_space)? (bytes_to_write = free_space) : bytes_to_write;
	for(index = 0 ; index < bytes_to_write ; ++index)
	{	
		if(cbuf->read == cbuf->write && *(cbuf->buf_start + cbuf->capacity + 1) == 1)
		{
			Cbuf_errno_g = CBuf_OVERFLOW;
			return bytes_written;
		}
			
		cbuf->buf_start[cbuf->write] = data[index];
		++bytes_written;
		cbuf->write = (cbuf->write + 1)% cbuf->capacity;
		
		if(0 == cbuf->write)
		{
			*(cbuf->buf_start + cbuf->capacity + 1) = 1;
		}
		
	}
	Cbuf_errno_g = CBuf_OK;	
	return bytes_written;
}




