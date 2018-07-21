#include <stdio.h>

/*
a function that get an array of ints and array size, and prints corresponding chars.
*/

/*function declaration*/
void array_to_char(char array[]); 

int main()
{
    char helloOfHex[]={0x48, 0x65, 0x6c, 0x6c,0x6f, 0x20, /*hex numbers representation of "hello world"*/ 
				      0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x0a,0}; 
	
	/*int size=sizeof(helloOfHex)/sizeof(helloOfHex[0]);calculates array size*/

	array_to_char(helloOfHex);/*calls function*/
    
	return 0;
}


void array_to_char(char array[])
{
	
    
        puts(array); /*prints char for every hex number*/
    
}
