#include <stdio.h>	/*for printf*/
#include <stdlib.h> /*for exit success*/

typedef unsigned int uint_t;

void UniTest(void);
int IsPower2(uint_t n);

int main()
{

	UniTest();
	return EXIT_SUCCESS;
}


void UniTest(void)
{
	printf("is 1 a power of 2? %d\n",IsPower2(1));
	printf("is 2 a power of 2? %d\n",IsPower2(2));
	printf("is 5 a power of 2? %d\n",IsPower2(5));
	printf("is 8 a power of 2? %d\n",IsPower2(8));
	printf("is 64 a power of 2? %d\n",IsPower2(64));
	printf("is 65 a power of 2? %d\n",IsPower2(65));
}	

int IsPower2(uint_t n)
{
	return (0 == num) ? 0 : (0 == (n & (n-1))); 
}
