#include <stdio.h>
#include <stdlib.h>

/* int to string */

char * itoa10 (int value, char *str);
char * itoa (int value, char *str, int base);

void UniTest(void);
void UniTestbases(void);

int main()
{
	
	UniTest();
	UniTestbases();
	return EXIT_SUCCESS;
}

char * itoa10 (int value, char *str)
{
	char * str_start = str;
	int i = 0;
	int last_digit = 0;
	int nums[20] = {0};
	if(value < 0)
	{
		 value *= -1;
		 *str = '-';
		 ++str;
	}
	while(value % (10) > 0)
	{
		last_digit = value % 10;
		nums[i] = last_digit;
		++i;
		value /= 10;

	}
	for(i-=1 ; i >= 0 ; --i)
	{
		*str = ('0' + nums[i]);
		++str;
	}
	return str_start;


}
char * itoa (int value, char *str, int base)
{
	char * str_start = str;
	int i = 0;
	int last_digit = 0;
	int nums[20] = {0};
	
	/*if(value < 0)
	{
		 value = -value;
		 *str = '-';
		 ++str;
	}*/
	
	while(value > 0)
	{
		last_digit = value % base;
		nums[i] = last_digit;
		++i;
		value /= base;

	}
	
	for(i-=1 ; i >= 0 ; --i)
	{
		
		if (nums[i] > 9)
		{	
			*str = ('7' + nums[i]);
			++str;
		}
		else
		{
			*str = ('0' + nums[i]);
			++str;
		}
	}
	
	return str_start;


}

void UniTest(void)
{
	char this[20] = {0};
	char this2[20] = {0};
	int integer = 5468;
	int integer_minus = -5468;
 	puts("\n-------------base10---------------");
    printf("%s\n",itoa10(integer,this));
    printf("%s\n",itoa10(integer_minus,this2));
}

void UniTestbases(void)
{
	char this[20] = {0};
	char this2[20] = {0};
	int integer = 5468;
    puts("\n------------anybase---------------");
    printf("%s\n",itoa(integer,this,2));
	printf("%s\n",itoa(integer,this2,16));
}
