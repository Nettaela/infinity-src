#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LOWTOUPPER(c) ((('a') < (c)) && ((c) < ('z')) ? (c)-=('a'-'A') : (c) )
/* string to int */

int Atoi10 (const char *nptr);
int Atoi (const char *nptr, int base);

void UniTest(void);
void UniTestbases(void);

int main()
{
	UniTest();
	UniTestbases();
	return EXIT_SUCCESS;
}

int Atoi10 (const char *nptr)
{
	size_t str_len = strlen(nptr) - 1;
	unsigned int i = 0; 
	char ch = 'a';
	int result = 0, var = 0;
	int base = 1;
	if (*nptr == '-')
	{
		++nptr;
		--str_len;
		base=-1;
	}

	for (i = 0 ; i <= str_len ; ++i)
	{
		ch = nptr[str_len - i];
		var = (int)ch - '0';
		var *= base;
		result = var + result;
		base *= 10;
	}
	
	
	return result;

}
int Atoi (const char *nptr, int base)
{
	size_t str_len = strlen(nptr) - 1 ;
	unsigned int i = 0; 
	char ch = 'a';
	int result = 0, var = 0;
	int exp = 1;
	
	for (i = 0 ; i <= str_len ; ++i)
	{
		ch = nptr[str_len - i];
		if (ch > '9')
		{
			ch = LOWTOUPPER(ch) - 7;
		}
		var = (int)ch - '0';
		var *= exp;
		result = var + result;
		exp *= base;
	}
	
	return result;

}

void UniTest(void)
{
	const char *nptr = "54668";
	const char *nptr_minus = "-54668";
 	puts("\n-------------base10---------------");
    printf("%d\n",Atoi10(nptr));
    printf("%d\n",Atoi10(nptr_minus));
	
}
void UniTestbases(void)
{

	const char *nptr = "1111";
	const char *nptr1 = " ";
 	puts("\n-------------any base---------------");
	printf("atoi base 2\n%d\n\n",Atoi(nptr,2));
	printf("atoi base 16\n%d\n\n",Atoi(nptr1,10));
}


















