#include <stdio.h>   /*for printing*/
#include <stdlib.h>	 /*for exit success*/

typedef unsigned int uint_t;

 /* Pseudocode of the lookup table 'uint_t bits_set[256]' */
 /*                    			  0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF */
static const uint_t bits_set[] = { 0,  1,  1,  2,  1,  2,  2,  3,  1,  2,  2,  3,  2,  3,  3,  4};	 


void UniTest(void);
uint_t CountSetBits(uint_t num);

int main()
{
	UniTest();
	return EXIT_SUCCESS;
}

void UniTest(void)
{
	uint_t num1 = 587204; /* 1000 1111 0101 1100 0100 */
	printf("number: %u, set bits: %u\n", num1, CountSetBits(num1));
}	
	
uint_t CountSetBits(uint_t num) /*an int is 0x12345678 long*/
{
    return bits_set[ num        & 15] +
    	   bits_set[(num >>  4) & 15] +
    	   bits_set[(num >>  8) & 15] + 
    	   bits_set[(num >> 12) & 15] +
    	   bits_set[(num >> 16) & 15] +
    	   bits_set[(num >> 20) & 15] + 
    	   bits_set[(num >> 24) & 15] +
    	   bits_set[(num >> 28) & 15];
}
