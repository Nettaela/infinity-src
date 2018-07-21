#include <stdio.h>
#include <stdlib.h>

int initialized_global_variable = 3;

int uninitialized_global_variable;

void PrintStackVariable(void);

static void Foo(void);

void PrintStaticInFunction(void);

extern uninitialized_global_variable_from_other_file;
extern initialized_global_variable_from_other_file;

const int const_global_read_only_init_int = 2;
const int const_global_read_only_uninit_int;

void FunctionFromOtherFile(void);

int main()
{
	static int initialized_static_variable = 5;
	static int uninitialized_static_variable;

	char read_write_string_in_main[] = "333";
	char *read_only_str_in_main = "2334";
	
	static char static_read_write_string_in_main[] = "333";
	static char *static_read_only_str_in_main = "2334";
	
	const int const_read_only_init_int_in_main = 2;
	const int const_read_only_uninit_int_in_main;
	
	char *uninitialized_allocated_memory = (char*)malloc(sizeof(char));
	
	PrintStackVariable();
	puts("\n----=====   MAIN    =====----");
	printf("initialized_static_variable:                  %p\n", &initialized_static_variable);
	printf("uninitialized_static_variable:                %p\n", &uninitialized_static_variable);
	printf("initialized_global_variable:                  %p\n", &initialized_global_variable);
	printf("uninitialized_global_variable:                %p\n", &uninitialized_global_variable);	
	printf("uninitialized_allocated_memory:               %p\n", uninitialized_allocated_memory);	
	
	printf("read_write_string_in_main:                    %p\n", &read_write_string_in_main[0]);	
	printf("read_only_str_in_main:                        %p\n", read_only_str_in_main);	
	printf("static_read_write_string_in_main:             %p\n", &static_read_write_string_in_main[0]);	
	printf("static_read_only_str_in_main:                 %p\n", static_read_only_str_in_main);
		
	printf("const_read_only_init_int_in_main:             %p\n", &const_read_only_init_int_in_main);	
	printf("const_read_only_uninit_int_in_main:           %p\n", &const_read_only_uninit_int_in_main);		
	
	printf("const_global_read_only_init_int:              %p\n", &const_global_read_only_init_int);	
	printf("const_global_read_only_uninit_int:            %p\n", &const_global_read_only_uninit_int);		
			
		
	
		
	printf("initialized_global_variable_from_other_file:  %p\n", &initialized_global_variable_from_other_file);	
	
	printf("uninitialized_global_variable_from_other_file:%p\n", &uninitialized_global_variable_from_other_file);	
	printf("function adress:                              %p\n", &PrintStackVariable);
	printf("static function adress:                       %p\n", &Foo);	
	printf("function adress from other file               %p\n", &FunctionFromOtherFile);
	
	FunctionFromOtherFile();
	PrintStaticInFunction();
	
	
	
	free(uninitialized_allocated_memory);
	return 0;
}

void PrintStackVariable(void)
{
	int automatic_variable = 8;
	puts("\n----===== PrintStackVariable =====----"); 
	printf("automatic variable adress:                    %p\n",&automatic_variable);
	
}

static void Foo(void)
{
	;
}
void PrintStaticInFunction(void)
{
	static int init_static_in_function = 6;
	static int uninit_static_in_function;
	puts("\n----===== PrintStaticInFunction =====----");
	printf("init_static_in_function:                      %p\n", &init_static_in_function);
	printf("uninit_static_in_function:                    %p\n", &uninit_static_in_function);
}
	
	
	

