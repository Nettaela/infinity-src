#include <stdio.h>	/*for printf*/
#include <stdlib.h> /*for exit success*/

#define BIT(i) (1 << i)

typedef unsigned char uchar_t;


void UniTest(void);
int EitherBitOn(uchar_t num);

int main()
{

	UniTest();
	return EXIT_SUCCESS;
}


void UniTest(void)
{
	uchar_t num = 68; /*bits 2 and 6 are on*/
	uchar_t num2 = 128; /*both off*/
	 
	
	printf("%d\n",EitherBitOn(num));
	printf("%d\n",EitherBitOn(num2));
}
	

int EitherBitOn(uchar_t num)
{
	return ((num & (BIT(6) | BIT(2))) != 0);
}
