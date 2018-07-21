#ifndef CBUF_H
#define CBUF_H

typedef enum {CBuf_OK , CBuf_NODATA, CBuf_OVERFLOW} CBuf_err_t;
typedef struct cbuf cbuf_t;

extern CBuf_err_t Cbuf_errno_g;

cbuf_t *CBufCreate(size_t buf_cap);
void CBufDestroy(cbuf_t *cbuf);
size_t CBufFreeSpace(const cbuf_t *cbuf);
size_t CBufCapacity(const cbuf_t *cbuf);
int CBufIsEmpty(const cbuf_t *cbuf);

size_t CBufRead(cbuf_t *cbuf, char *data, size_t bytes_to_read);
size_t CBufWrite(cbuf_t *cbuf, const char *data, size_t bytes_to_write);


#endif
