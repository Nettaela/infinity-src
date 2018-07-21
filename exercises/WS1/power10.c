#include <stdio.h>
/*
a function that calculates 10 by the power of an int
*/

/*function declarations*/
float power10(int number);
void unitest(void);

int main()
{
	unitest();				/*use unitest function to test*/
	return 0;
}

float power10(int number)			/*power10 recieves number and returns 10^number*/
{
	float result = 1;				
	int i;	
	int count = number;
	if (number < 0)
	{
		count = number * -1;	/*if the number is negative */
	}
	
	if (number!=0)	/*if the exponent is 0, while doesnt happen and result is 1*/
	{
		for (i = 0 ; i < count ; i++)
		{
			result *= 10;	/*multiply result by 10*/
		}
	}
	
	if (number < 0)
	{
		result = 1 / result;	/*if the number is negative */
	}
	
	return result;
}
					

void unitest(void)					/*print results*/
{
	int x;
	x=2;
	printf("x=2, power10(2)=%f\n",power10(x));
	x=0;
	printf("x=0, power10(0)=%f\n",power10(x));
	x=-2;
	printf("x=-2, power10(-2)=%f\n",power10(x));
}








