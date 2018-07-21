#include <stdio.h> 
#include <stdlib.h>

#define SIZEOF(x) ((size_t)((&x) + 1)) - ((size_t)(&x))
#define TYPESIZE(x) (((x*)0)+1)

int main()
{
	char f = 3;
	printf("%lu\n", SIZEOF(f));
	return 0;
}
