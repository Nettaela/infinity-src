#include <stdio.h>	/*for printf*/
#include <stdlib.h> /*for exit success*/
#include <limits.h> /*for INT_MAX */

#define BIT(i) (1 << i)

typedef unsigned int uint_t;

void UniTest(void);
void Print3on(uint_t *array_of_num, size_t array_size);

int main()
{

	UniTest();
	return EXIT_SUCCESS;
}


void UniTest(void)
{
	uint_t array_of_num[] = {2, 3 , 7, 11, 12, 13, 56 ,652 ,851968}; 
	/*only 7 ,11, 13, 56 and 851968 has 3 bits on */
	size_t array_size = sizeof(array_of_num) / sizeof(array_of_num[0]) ;
	Print3on(array_of_num, array_size);
}
	

void Print3on(uint_t *array_of_num, size_t array_size)
{
	uint_t i = 0, j = 1;
	uint_t counter = 0;
	uint_t size_of_uint = sizeof(uint_t) * 8;
	
	for(i = 0 ; i < array_size ; ++i)
	{	
		j = 1;
		while (j <=	size_of_uint)
		{	
			if (array_of_num[i]	& BIT(j)) /*goes bit by bit and counts the number of 1's*/
			{
				++counter;
			}
			++j;
		}
		if (counter == 3)
		{
			printf("%u\n",array_of_num[i]);
		}
		counter = 0;

	}


}
