#include <stdlib.h>
#include <stdio.h>


void *MemSet(void *s, int c, size_t n);
void *MemCpy(void *dest, const void *src, size_t n);
void *MemMove(void *dest, const void *src, size_t n);

void UnitTestSet(void);
void UnitTestCpy(void);
void UnitTestMove(void);


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
	int i = 0;
	char* p_byte = NULL;
	unsigned long *word_p = NULL;
	unsigned long word = 0;
	c &= 0x000000ff;
	p_byte = (char *)&c;
	printf("%d\n", *p_byte);
	
	for (i = 0 ; i <= 8 ; ++i)
	{
		word = (word << (i * 8)) | *p_byte;
	}
	word_p = &word;
	
	/*word = 0x6161616161616161;

	word_p = &word;*/
	
	printf("%lu\n", word);
	
	/*print the adress of s to see if its aligned*/
	printf("%p\n", s);
	/*put chars byte by byte until aligned adress is reached - use helper pointer*/

	{
		while ((size_t)s % 8 != 0)
		{
			printf("%p\n", s);
			*(char *)s = *p_byte;
			s = ((char*)s) + 1;
		}
		*(unsigned long *)s = *word_p;
		s = ((unsigned long*)s) + 1;
		*(unsigned long *)s = *word_p;
		
	}	
		
	/*see the current adress of helper pointer*/
	
	/*put chars in word size chunks ??? "char ptr [64] = 'a'??? use long??*/
	
	/*int c - we take only the 1 byte in the right = c & 0x000000ff*/
	
	
	


}

void UnitTestSet(void)
{
	char *str = malloc(sizeof(char)*80);
	char *offset_ptr = str + 5;
	MemSet(offset_ptr, 'a', sizeof(char)*80);
	printf("%s\n", offset_ptr);
	free(str);
	str = NULL;
}

void *MemCpy(void *dest, const void *src, size_t n)
{



}

void UnitTestCpy(void)
{



}

void *MemMove(void *dest, const void *src, size_t n)
{



}

void UnitTestMove(void)
{




}




