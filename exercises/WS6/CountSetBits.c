#include <stdio.h>  /*for printing*/
#include <stdlib.h> /*for exit success*/

typedef unsigned int uint_t;

void UniTest(void);
uint_t CountSetBits(uint_t num);

int main()
{
	UniTest();
	return EXIT_SUCCESS;
}

void UniTest(void)
{
	uint_t num1 = 587204; /* 1000 1111 0101 1100 0100 */
	printf("number: %u, set bits: %u\n", num1, CountSetBits(num1));
}	
	
uint_t CountSetBits(uint_t num)
{
	uint_t count = 0, i = 0;
	for (i = 0 ; i < (sizeof(uint) * 8) ; ++i)
	{
		(((num >> i) & 1) == 1)? ++count: 0;
	} 
	return count;
}
