#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char *Strchr(const char *str, int c);
void SevenBoom (int from, int to);
void UniTest(void);

int main()
{
	UniTest();
	return EXIT_SUCCESS;
}

void SevenBoom (int from, int to)
{
	int number = from;
	char str[20];
	char *chr;
	
	if(from > to)
	{
		printf("Illogical! I don't go backwards!\n");
		return;
	}
	
	while (number<=to)
	{
		
		
	sprintf(str,"%d",number); /*converts number to string*/
	chr = Strchr(str,'7'); 	  /*finds seven in the string*/
	
		if (number%7 == 0)
		{
			printf("BOOM!\n");
		}
		else if (*chr == '7')
		{
			printf("BOOM!\n");
		}
		else
		{
			printf("%d\n",number);
		}
		++number;	
	 }
}

void UniTest(void)
{
	
	SevenBoom (1, 45);

}


char *Strchr(const char *str, int c) 
{
	
	assert(str);
	
	while (*str != c && *str != '\0')
	{
		++str;
	}
	
	if (*str == c)
	{
		return (char *)str;
	}

	return (char *)str;
	

}
