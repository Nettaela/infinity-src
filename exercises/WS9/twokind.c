#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOLOWER(c) (((c > 'A') && (c < 'Z'))? (c + 32) : (c)) 

void TwoOfKind(char* str1, char *str2, char *str3);
void UniTest(void);

int main()
{

	UniTest();
	return EXIT_SUCCESS;
}


void TwoOfKind(char* str1, char *str2, char *str3)
{
	char letters[26] = {0};
	int i = 0;
	char ch = '\0';
	
	/*create an array of alphabet chars*/
	for(i = 0 ; i < 26 ; ++i)
	{
		letters[i] = i + 'a';
	}
	
	while (*str1 != '\0' || *str2 != '\0')
	{
	
		if(TOLOWER(*str1) == TOLOWER(*str2))
		{
			if(TOLOWER(*str3) != TOLOWER(*str1))
			{
				ch = *str1;
				printf("%c",letters[TOLOWER(ch) - 'a']);
				letters[TOLOWER(ch) - 'a'] = '\0';/*put a null term after printing that char*/
				
			}
		}
		++str1;
		++str2;
		++str3;
	}
	putchar(10);
	
}
	

void UniTest(void)
{
	char str1[] = "sxafDaf";
	char str2[] = "sxdfdsasav";
	char str3[] = "gXeferfs";
	
	
	TwoOfKind(str1,str2, str3);
	
	
}	
