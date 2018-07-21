#include <stdlib.h>
#include <stdio.h>

int main()
{
	const char *str = "32+2";	
	char *str_increment = NULL;
	printf("%f\n",strtod(str, &str_incremen));
	printf("%c\n", *str_increment);
	printf("%f\n",strtod(str_increment, NULL));
	
	return 0;
}
	
