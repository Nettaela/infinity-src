#include <stdio.h>	/*for printing*/
#include <stdlib.h> /*for exit success*/

#define BIT(i) (1 << i)

typedef unsigned int uint_t;
void UniTest(void);
uint_t DividedBy16(uint_t num);

int main()
{
	UniTest();
	return EXIT_SUCCESS;
}

void UniTest(void)
{
	uint_t num1 = 16;
	uint_t num2 = 3824720;
	uint_t num3 = 33;
	uint_t num4 = 3824773;
	
	
	printf("%u\n", DividedBy16(num1));
	printf("%u\n", DividedBy16(num2));
	printf("%u\n", DividedBy16(num3));
	printf("%u\n", DividedBy16(num4));
}

uint_t DividedBy16(uint_t num)
{

	return (num & 0xFFFFFFF0);

}
