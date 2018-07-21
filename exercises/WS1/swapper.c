#include <stdio.h>
#include <stdlib.h>
/*
a function that swaps between 2 int variables
*/

/*function declarations*/
void Swapper(int *p1, int *p2);
void UniTest(void);

int main()
{
	UniTest();		/*use unitest function to test*/
	return EXIT_SUCCESS;
}


void Swapper(int *p1, int *p2)  /*swapper recieves 2 variable pointers*/
{
	int temp = *p1;		/* saves value of first pointer in temporary var */
	*p1 = *p2;		/* put value of second var in pointer of first var */	
	*p2 = temp;		/* put temp(first pointer value) in second pointer */	
} 

void UniTest(void)			/* test swap function in here */
{
	int num1 = 2;		/* get 2 numbers */
	int num2 = 4;
	printf("before swap\n");	
				/*print values and adresses before swap */
	printf("num1 = %d, adress = %p\n", num1, (void *)&num1); 
	printf("num2 = %d, adress = %p\n", num2, (void *)&num2);

	Swapper(&num1, &num2);  /* swap dat */

	printf("after swap\n");	
				/*print values and adresses before swap */
	printf("num1 = %d, adress = %p\n", num1, (void *)&num1);
	printf("num2 = %d, adress = %p\n", num2, (void *)&num2);
	
}

