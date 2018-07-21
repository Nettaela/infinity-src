#include <stdio.h>	/*for printf*/
#include <stdlib.h> /*for exit success*/
typedef unsigned int uint_t;

void UniTest(void);
uint_t add1(uint_t num);

int main()
{

	UniTest();
	return EXIT_SUCCESS;
}


void UniTest(void)
{
	printf("%u\n",add1(90));
	printf("%u\n",add1(1));
	
}

uint_t add1(uint_t num)
{
	return (-(~num));
}
