#include <stdio.h>
/*
a function that flips integer
*/

/*function declarations*/
int flipper(int num2flip);
void unitest(void);

int main()
{
	unitest();			/*use unitest function to test*/

	return 0;
}

int flipper(int num2flip)		/*flipper flips an integer*/
{	
	
	int last_digit=0;
	
	while (num2flip != 0)
	{	
		last_digit = last_digit * 10;			/*multiply by 10*/
		last_digit = last_digit + (num2flip % 10);      /*get the last digit*/	
		num2flip   = num2flip / 10;			/*divide original number by 10 to get the 									next to last digit*/
	}
	
	return last_digit;					/*divied result by 10*/
}
		
void unitest(void)							/* test flipper function in here */
{
	int x;
	x=12343;
	printf("x=%d, flipper(x)=%d\n",x,flipper(x));		/*print x and the result of flipper(x)*/
	
	x=-12340;
	printf("x=%d, flipper(x)=%d\n",x,flipper(x));

	x=4;
	printf("x=%d, flipper(x)=%d\n",x,flipper(x));

}
