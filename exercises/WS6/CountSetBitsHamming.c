#include <stdio.h>  /*for printing*/
#include <stdlib.h>	/*for exit success*/

typedef unsigned int uint_t;
 
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
	uint_t num2 = 0xffffffff; /* 1111 1111 1111 1111 1111 */
	printf("number: %u, set bits: %u\n", num1, CountSetBits(num1));
	printf("number: %u, set bits: %u\n", num2, CountSetBits(num2));
}	
	
uint_t CountSetBits(uint_t num) /*an int is 0x12345678 long*/
{
   	uint_t new_num = 0;
    uint_t mask1 = 0x55555555;
    uint_t mask2 = 0x33333333;
    uint_t mask3 = 0x0f0f0f0f;
    uint_t mask4 = 0x00ff00ff;
    uint_t mask5 = 0x0000ffff;
    
    new_num = ((num) & mask1) + ((num >> 1) & mask1);
    new_num = ((new_num) & mask2) + ((new_num >> 2) & mask2);
    new_num = ((new_num) & mask3) + ((new_num >> 4) & mask3); 
    new_num = ((new_num) & mask4) + ((new_num >> 8) & mask4);
    new_num = ((new_num) & mask5) + ((new_num >> 16) & mask5);    
    
    return new_num;
}
