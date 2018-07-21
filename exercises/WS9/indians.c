#include <stdio.h>
#include <stdlib.h>
#define ISLITTLE(i) (*(char*)&i)


int is_little(void);

int main()
{
	int i = 1;
	puts("is this computer a little indian?");
	printf("%d\n", is_little());
	printf("%d\n", ISLITTLE(i));
	return EXIT_SUCCESS;
}

int is_little(void)
{
	int i = 1;
	return (*(char*)&i);
	
}
