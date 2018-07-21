#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned long ul;

void *MemSet(void *s, int c, size_t n);
void *MemCpy(void *dest, const void *src, size_t n);
void *MemMove(void *dest, const void *src, size_t n);
void UnitTestMove(void);
void UnitTestCpy(void);
void UnitTestSet(void);


int main()
{
	UnitTestSet();
	UnitTestCpy();
	UnitTestMove();	
	
	
	return EXIT_SUCCESS;
}

void *MemSet(void *s, int c, size_t n)
{
	/*define word c*/
	void *s_start = s;
	char* p_byte = NULL;
	ul *word_p = NULL;
	ul  word = 0;
	c &= 0xff;
	p_byte = (char *)&c;
	
	word |= *p_byte;
	word |= ((word << 8) | *p_byte); 
	word |= ((word << 16) | *p_byte); 	
	word |= ((word << 32) | *p_byte); 
	printf("%lx\n", word);	

	word_p = &word;
	
	/*set head- put chars byte by byte until aligned adress is reached*/
	while (((size_t)s % 8 != 0) && (n > 0))
	{
		/*printf("%p\n", s);*/
		*(char *)s = *p_byte;
		s = ((char*)s) + 1;
		--n;

	}
	/*set word by word once adress is aligned*/
	while (((size_t)s % 8 == 0) && (n > 8))
	{
		*(ul *)s = *word_p;
		s = ((ul*)s) + 1;
		n -= 8;
	}
	/*set tail byte by byte*/
	while (n > 0)
	{
		/*printf("%p\n", s);*/
		*(char *)s = *p_byte;
		s = ((char*)s) + 1;
		--n;

	}
	return s_start;
	
}

void UnitTestSet(void)
{
	/*int i = 0;*/
	char *str = malloc(sizeof(char)*800);
	char *offset_ptr = str + 3;
	if (str==NULL)
	{
		perror("allocation for memset");
		return;
	}
	puts("\n--------------MEMSET TEST---------------");
	MemSet(offset_ptr, 'a', 80);
	printf("%s\n", offset_ptr);
	
	/*
	MemSet(offset_ptr, 34, 250);
	for(i = 0 ; i <250 ;++i)
	{	
		printf("%d", offset_ptr[i]);
	}
	*/
	free(str);
	str = NULL;
}

void *MemCpy(void *dest, const void *src, size_t n)
{	
	/*run on src ptr*/
	/*make acounter*/
	void *dest_start = dest;
	while (((size_t)dest % 8 != 0) && (n > 0))
	{
		*(char *)dest = *(char*)src;
		dest = ((char*)dest) + 1;
		src = ((char*)src) + 1;
		--n;	
	}
	/*set word by word once adress is aligned*/
	while (((size_t)src % 8 == 0) && (n > 8))
	{
		/*printf("%p\n", src);*/
		*(ul *)dest = *(ul *)src;
		src = ((ul*)src) + 1;
		dest = ((ul*)dest) + 1;
		n -= 8;
	}
	/*set tail byte by byte*/
	while (n > 0)
	{
		*(char *)dest = *(char*)src;
		dest = ((char*)dest) + 1;
		src = ((char*)src) + 1;
		--n;	
	}
	
	return dest_start;

}

void UnitTestCpy(void)
{
	int i=0;
	
	const char *src = malloc(sizeof(char)*800);
	char *dest = malloc(sizeof(char)*800);
	if (src == NULL)
	{
		perror("allocation 1 for memcpy");
		return;
	}
	if (dest == NULL)
	{
		perror("allocation 2 for memcpy");
		return;
	}
	/*strcpy((char*)src,"this is a string that is more than a word long, hopefully, i dont feel like counting it.");
	strcpy(dest,"Helloooo!!");
	puts("\n--------------MEMCPY TEST---------------");
	printf("Before memcpy dest = %s\n", dest);
	MemCpy(dest+1, src+1, strlen(src)+1);
	printf("After memcpy dest = %s\n", dest);
	*/
	puts("\n--------------MEMCPY TEST---------------");
	MemSet((char*)src, 5, 80);
	MemSet(dest, 6, 40);
	MemCpy(dest+20, src+20, 70);
	
	for(i=0;i<70;++i)
	{
		printf("%d",dest[i]);
	}
	
	free((char *)src);
	src = NULL;
	free(dest);
	dest = NULL;
}

void *MemMove(void *dest, const void *src, size_t n)
{
	/*find src end using strlen, make 2 pointers for src end and dest end.
	  begin with a loop for the tail - while the adress is not aligned, 
	  copy backwards byte by byte. when and aligned adress  is reached, 
	  if there are still more than 8 bytes left, we can copy in batches 
	  of 8 bytes copying must be done in way where we first make the pointers 
	  backward 8 bytes and then copy. we should reach an aligned adress.*/
	   
	void *dest_start = dest;
	void *dest_end = ((char*)dest) + n;
	void *src_end = ((char*)src) + n;
	size_t count = 0;
	
	if(src > dest) 					/*in this case there is no need to copy from end*/
	{
		dest_start = MemCpy(dest, src, n);	
		return dest_start;			/*return void pointer to copied str */
	}

	
	while (((size_t)src_end % 8 != 0) && count < n)
	{
		*(char *)dest_end = *(char*)src_end;
		dest_end = ((char*)dest_end) - 1;
		src_end = ((char*)src_end) - 1;
		++count;	
	}
	while (((size_t)src % 8 == 0) && count < n)
	{
		dest_end = ((char*)dest_end) - 8;
		src_end = ((char*)src_end) - 8;
		*(ul *)dest_end = *(ul*)src_end;
		count += 8;
	}
	
	return dest_start;

}

void UnitTestMove(void)
{
	const char *src = malloc(sizeof(char)*800);
	char *dest = (char*)src+8;
	if (src == NULL)
	{
		perror("allocation 1 for memmove");
		return;
	}
	strcpy((char*)src,"this is a string for the memmove function, hopefully, i dont feel like counting it.");
	
	puts("\n--------------MEMMOVE TEST---------------");
	/*
	printf("dest before move: %p %s\n", dest, dest);
	MemMove(dest, src, 20);
	printf("dest aftter move: %p %s\n", dest, dest);*/
	
	printf("dest before move: %p %s\n", dest, dest);
	printf(" src before move: %p %s\n", src, src);
	MemMove(dest, src,strlen(src)+1 );
	printf("\n dest after move: %p %s\n", dest, dest);

	
	free((char*)src);
	src = NULL;
	

}




