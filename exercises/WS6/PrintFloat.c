#include <stdio.h>	/*for printing*/
#include <stdlib.h> /*for exit success*/
#define BIT(i) (1 << i)

typedef unsigned int uint_t;

void UniTest(void);
void PrintFloat(float num);

int main()
{
	UniTest();
	return EXIT_SUCCESS;
}

void UniTest(void)
{
	float num1 = 3.14; 
	PrintFloat(num1);
}	

void PrintFloat(float num) 
{
	int i = 0;
	uint_t *ptr = (uint_t*)(&num);
	
	for (i = ((sizeof(float) * 8)-1); i >= 0 ; --i)
	{
		printf("%u", (((*ptr >> i) & 1)));
	} 

	putchar(10);
	
}
