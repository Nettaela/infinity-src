#include <stdio.h>	/*for printf*/
#include <stdlib.h> /*for exit success*/
#include <limits.h> /*for INT_MAX */
typedef unsigned int uint;

void UniTest(void);
int IsPower2(uint n);

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
	printf("is %d a power of 2? %d\n",INT_MAX, IsPower2(INT_MAX));

}	

int IsPower2(uint n)
{
	uint i = 0;
	uint checker = 1; /*a mask that changes with every iteration of the loop*/

	
	while ((checker << i) <= INT_MAX)
	{
		if ((checker << i) == n)
		{
			return 1;
		}
		else
		{
			++i;
		}
	}
	return 0;

}
