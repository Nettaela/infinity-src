#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int IsPalindrome(const char *str);
void UniTest(void);

int main()
{
	UniTest();
	return EXIT_SUCCESS;
}

int IsPalindrome(const char *str)
{
	int i, result = 1; /*1 means it is a palindrome*/
	int str_len = strlen(str);
	char *end_ptr = (char *)str+(str_len-1);
	
	assert(str);
	
	if (*str == '\0')
	{
		return 0;
	}
	
	for (i=0 ; i<(str_len/2) ; i++) /*try this with while (p1<=p2)*/
	{
		if (*str == *end_ptr)
		{
			++str;
			--end_ptr;
		}
		else
		{
			return 0;
		}	

	}

	return result;

}


void UniTest(void)
{

	char *palin1="bob";
	char *palin2="foof";
	char *palin3="fonf";
	char *palin4="";
	printf(" bob: %d\n", IsPalindrome(palin1));
	printf(" foof: %d\n", IsPalindrome(palin2));
	printf(" fonf: %d\n", IsPalindrome(palin3));
	printf("(empty): %d\n", IsPalindrome(palin4));

}
