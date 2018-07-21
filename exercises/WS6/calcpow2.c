#include <stdio.h>	/*for printf*/
#include <stdlib.h> /*for exit success*/

typedef unsigned int uint_t;

void UniTest(void);
double Pow2(uint_t x, int y);

int main()
{

	UniTest();
	return EXIT_SUCCESS;
}


void UniTest(void)
{
	printf("%.2f\n",Pow2(2,-2));
	printf("%.2f\n",Pow2(20,-2));
	printf("%.2f\n",Pow2(70,5));
	printf("%.2f\n",Pow2(70,0));
	
}

double Pow2(uint_t x, int y)
{
	double result = 0;
	if (y < 0)
	{
		result = (x >> ((-1)*y));
	}
	else 
	{
		result = x << y; /*shifting left is multiplying by powers of 2*/
	}
	return result;
}
