#include <stdio.h>	/*for printing*/
#include <stdlib.h> /*for exit success*/

#define BIT(i) (1<<i)

typedef unsigned char uchar_t;

void UniTest(void);
uchar_t SwapBits(uchar_t num);

int main()
{
	UniTest();
	return EXIT_SUCCESS;
}

void UniTest(void)
{
	uchar_t num = 51; /*swap result should be 27*/	
	uchar_t num2 = 0xFF; /*11111111 no change */
	printf("%u\n", SwapBits(num));
	printf("%u\n", SwapBits(num2));
}

uchar_t SwapBits(uchar_t num)
{
	uchar_t new_num = 0;
	uchar_t bit3 = ((BIT(3) & num) >> 3); /*isolate bits and 5*/
	uchar_t bit5 = ((BIT(5) & num) >> 5);
	uchar_t temp_bits = bit3 ^ bit5;	/*xor them and put back in 3 and 5 positions*/
	temp_bits = ((temp_bits << 3) | (temp_bits << 5));
	new_num = temp_bits ^ num;
	
	return new_num;

}
