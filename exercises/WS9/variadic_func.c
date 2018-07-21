#include <stdio.h>
#include <stdarg.h>

int summing(int num, ...);

int main()
{
	printf("%d\n", summing(7,1,1,1,23,2,4,5));
	return 0;
}

int summing(int num, ...)
{
	int i=0, result = 0;
	va_list arguments;
	va_start(arguments, num);
	
	for (i=0 ; i<num; ++i)
	{
		result += va_arg(arguments,int);
	}
	va_end(arguments);
	return result;
}
