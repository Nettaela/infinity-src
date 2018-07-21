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
	uchar_t num = 154;
	printf("%u\n",ByteMirror(num)); 
}
	

uchar_t ByteMirror(uchar num)
{
	uchar_t new_num = 0;
	uchar_t checker = 1;
	int i = 0, j = 7;
	for (i = 0 ; i < 8 ; ++i, --j)
	{
		if ((num >> i) & checker)
		{
			new_num |= (checker << j);
		}
	}
	return new_num;


}
