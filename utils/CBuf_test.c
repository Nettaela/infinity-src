#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "CBuf.h"



void SimpleTest(void);
void ComplexTest(void);

int main()
{
	SimpleTest();
	ComplexTest();
	return EXIT_SUCCESS;
}


void SimpleTest(void)
{
	char * dest = (char*)malloc(100);
	char * src = (char*)malloc(100);
	char * src_data = src;
	char * dest_data = dest;
	size_t strlendata = 0;
	size_t capacity = 25;
	size_t bytes_read = 0;
	size_t bytes_written = 0;
	cbuf_t * buffer = CBufCreate(capacity);
	strcpy(src_data, "123456789a123456789a123456789a123456789a123456789a");
	strlendata = strlen(src_data);
	
	printf("buffer created, is empty? %d \n", CBufIsEmpty(buffer));
	assert(1 == CBufIsEmpty(buffer));
	
	printf("buffer created, free space: %lu \n", CBufFreeSpace(buffer));
	assert(capacity ==  CBufFreeSpace(buffer));
	
	printf("buffer created, capacity: %lu \n", CBufCapacity(buffer));
	assert(capacity == CBufCapacity(buffer));
	
	printf("str len: %lu \n", strlendata);
	
	
	bytes_written = CBufWrite(buffer, src_data, 15);
	assert(bytes_written == 15);
	assert(Cbuf_errno_g == 0);
	/*printf("bytes_written: %lu \n", bytes_written);
	printf("errno says: %d \n", Cbuf_errno_g);*/
	src_data+=15;
	
	
	bytes_read = CBufRead(buffer, dest_data, 10);
	assert(bytes_read == 10);
	assert(Cbuf_errno_g == 0);
	/*printf("bytes_read: %lu \n", bytes_read);
	printf("errno says: %d \n", Cbuf_errno_g);*/
	dest_data+=10;
	
	bytes_written = CBufWrite(buffer, src_data, 15);
	assert(bytes_written == 15);
	assert(Cbuf_errno_g == 0);
	/*printf("bytes_written: %lu \n", bytes_written);
	printf("errno says: %d \n", Cbuf_errno_g);*/
	src_data+=15;
		
		
	bytes_read = CBufRead(buffer, dest_data, 10);
	assert(bytes_read == 10);
	assert(Cbuf_errno_g == 0);	
	/*printf("bytes_read: %lu \n", bytes_read);
	printf("errno says: %d \n", Cbuf_errno_g);*/
	dest_data+=10;
	
	/*printf("is empty? %d \n", CBufIsEmpty(buffer));*/
	/*assert(1 == CBufIsEmpty(buffer));*/
	
	/*printf("free space: %lu \n", CBufFreeSpace(buffer));*/
	/*assert(capacity ==  CBufFreeSpace(buffer));*/
	
	/*printf("capacity: %lu \n", CBufCapacity(buffer));*/
	/*assert(capacity == CBufCapacity(buffer));*/
	
	bytes_read = CBufRead(buffer, dest_data, 10);
	assert(bytes_read == 10);
	assert(Cbuf_errno_g == 0);	
	/*printf("bytes_read: %lu \n", bytes_read);
	printf("errno says: %d \n", Cbuf_errno_g);*/
	dest_data+=10;
	/*bytes_written = CBufWrite(buffer, src_data, 10);
	printf("bytes_written: %lu \n", bytes_written);
	printf("errno says: %d \n", Cbuf_errno_g);
	*/
	assert(0 == strncmp(dest, src, dest_data-dest));
	puts("-----------------------------");
	puts("made it this far with no errors? well done! now make a complex test.");
	free(dest);
	free(src);
	CBufDestroy(buffer);
	
}

void ComplexTest(void)	
{
	char * dest = (char*)malloc(250);
	char * src = (char*)malloc(250);
	char * src_data = src;
	char * dest_data = dest;
	size_t strlendata = 0;
	size_t capacity = 50;
	size_t bytes_read = 0;
	size_t bytes_written = 0;
	cbuf_t * buffer = CBufCreate(capacity);
	strcpy(src_data, "helloivewaitedhereforyoueverlongtonightillthrowmyselfintooutoftheredoutofherheadshesangandiwonderifanythingcouldeverbethisrealforeverifanythingcouldeverbethisgoodagaintheonlythingilleveraskofyouyougottapromisenottostopwhenisaywhen");
	
	
	strlendata = strlen(src_data);
	printf("str len: %lu \n", strlendata);
	
	printf("buffer created, is empty? %d \n", CBufIsEmpty(buffer));
	assert(1 == CBufIsEmpty(buffer));
	
	printf("buffer created, free space: %lu \n", CBufFreeSpace(buffer));
	assert(capacity ==  CBufFreeSpace(buffer));
	
	printf("buffer created, capacity: %lu \n", CBufCapacity(buffer));
	assert(capacity == CBufCapacity(buffer));
	
	
	bytes_written = CBufWrite(buffer, src_data,20);
	assert(bytes_written == 20);
	assert(Cbuf_errno_g == 0);
	/*printf("bytes_written: %lu \n", bytes_written);
	printf("errno says: %d \n", Cbuf_errno_g);*/
	src_data+=20;
	
	
	bytes_written = CBufWrite(buffer, src_data,20);
	assert(bytes_written == 20);
	assert(Cbuf_errno_g == 0);
	/*printf("bytes_written: %lu \n", bytes_written);
	printf("errno says: %d \n", Cbuf_errno_g);*/
	src_data+=20;
	
	bytes_read = CBufRead(buffer, dest_data, 15);
	assert(bytes_read == 15);
	assert(Cbuf_errno_g == 0);
	/*printf("bytes_read: %lu \n", bytes_read);
	printf("errno says: %d \n", Cbuf_errno_g);*/
	dest_data+=15;
	
	bytes_read = CBufRead(buffer, dest_data, 15);
	assert(bytes_read == 15);
	assert(Cbuf_errno_g == 0);
	/*printf("bytes_read: %lu \n", bytes_read);
	printf("errno says: %d \n", Cbuf_errno_g);*/
	dest_data+=15;
	
	/*first 30 places of dest and src should be equal*/
	assert(0 == strncmp(dest, src, 30));
	
	
	bytes_written = CBufWrite(buffer, src_data, 25);
	assert(bytes_written == 25);
	assert(Cbuf_errno_g == 0);
	/*printf("bytes_written: %lu \n", bytes_written);
	printf("errno says: %d \n", Cbuf_errno_g);*/
	src_data+=25;
	
	bytes_written = CBufWrite(buffer, src_data, 25);
	assert(bytes_written != 25);
	assert(Cbuf_errno_g == 2);
	/*printf("bytes_written: %lu \n", bytes_written);
	printf("errno says: %d \n", Cbuf_errno_g);*/
	src_data+=bytes_written;	
	
	bytes_read = CBufRead(buffer, dest_data, 30);
	assert(bytes_read == 30);
	assert(Cbuf_errno_g == 0);
	/*printf("bytes_read: %lu \n", bytes_read);
	printf("errno says: %d \n", Cbuf_errno_g);*/
	dest_data+=bytes_read;
	
	bytes_read = CBufRead(buffer, dest_data, 30);
	assert(bytes_read != 30);
	assert(Cbuf_errno_g == 1);
	/*printf("bytes_read: %lu \n", bytes_read);
	printf("errno says: %d \n", Cbuf_errno_g);*/
	dest_data+=bytes_read;
	
	assert(0 == strncmp(dest, src, dest_data-dest));
	
	
	
	puts("-----------------------------");
	puts("made it this far with no errors? well done! now make a complex test.");
	free(dest);
	free(src);
	CBufDestroy(buffer);

}
