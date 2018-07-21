#include <stdio.h>	/*for printing*/
#include <stdlib.h> /*for exit success*/

typedef unsigned int uint_t;

void UniTest(void);
void SwapInts(uint_t *num1, uint_t *num2);

int main()
{
	UniTest();
	return EXIT_SUCCESS;
}

void UniTest(void)
{
	uint_t num1 = 1;
	uint_t num2 = 2;
	printf("%u %u\n", num1, num2);
	SwapInts(&num1, &num2);
	printf("%u %u\n", num1, num2);
}	
	
void SwapInts(uint_t *num1, uint_t *num2)
{
	*num1 = (*num1 ^ *num2);
	*num2 = (*num2 ^ *num1);
	*num1 = (*num2 ^ *num1);
}
