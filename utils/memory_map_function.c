#include <stdio.h>
#include <stdlib.h>

void FunctionFromOtherFile(void)
{
	int init_automatic_in_function_in_other_file = 2;
	int uninit_automatic_in_function_in_other_file;
	static init_static_in_function_in_other_file = 56;
	static uninit_static_in_function_in_other_file;
	puts("\n----=====  FunctionFromOtherFile  =====----");
	printf("init_automatic_in_function_in_other_file :    %p\n",&init_automatic_in_function_in_other_file);

	printf("uninit_automatic_in_function_in_other_file :  %p\n",&uninit_automatic_in_function_in_other_file);	
	printf("init_static_in_function_in_other_file :       %p\n",&init_static_in_function_in_other_file);

	printf("uninit_static_in_function_in_other_file :     %p\n",&uninit_static_in_function_in_other_file);	
}
