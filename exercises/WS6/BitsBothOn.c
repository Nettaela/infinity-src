#include <stdio.h>	/*for printf*/
#include <stdlib.h> /*for exit success*/

#define BIT(i) (1 << i)

typedef unsigned char uchar_t;


void UniTest(void);
int BitsBothOn(uchar_t num);

int main()
{

	UniTest();
	return EXIT_SUCCESS;
}


void UniTest(void)
{
	uchar_t num = 68; /*bits 2 and 6 are on*/
	uchar_t num2 = 1;  
	uchar_t num4 = 4;
	printf("%d\n",BitsBothOn(num));
	printf("%d\n",BitsBothOn(num2));
	printf("%d\n",BitsBothOn(num4));
}
	

int BitsBothOn(uchar_t num)
{
	return ((num & (BIT(6) | BIT(2))) == ((BIT(6) | BIT(2))));
}
