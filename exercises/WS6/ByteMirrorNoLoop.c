#include <stdio.h>	/*for printf*/
#include <stdlib.h> /*for exit success*/


typedef unsigned char uchar_t;

void UniTest(void);
uchar_t ByteMirror(uchar_t num);

int main()
{

	UniTest();
	return EXIT_SUCCESS;
}


void UniTest(void)
{
	uchar_t num = 129; /*the mirror is 129*/
	uchar_t num2 = 1;  /*the mirror is 128*/
	
	printf("%u\n",ByteMirror(num));
	printf("%u\n",ByteMirror(num2));
}
	

uchar_t ByteMirror(uchar_t num)
{
	uchar_t new_num = num;

	new_num = ((new_num << 4) | (new_num >> 4));	
	new_num = ((0xcc & (new_num << 2)) | ((new_num >> 2) & 0x33));
	new_num = ((0xaa & (new_num << 1)) | ((new_num >> 1) & 0x55));

	return new_num;


}
