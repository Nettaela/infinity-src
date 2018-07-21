#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#define CONT_NUM 11
void SimpleUnitest(void);
void ComplexUnitest(void);
void StackofStructsUnitest(void);

int main()
{
	SimpleUnitest();
	ComplexUnitest();
	StackofStructsUnitest();
	return EXIT_SUCCESS;
}

void SimpleUnitest(void)
{
	size_t element_size = sizeof(int);
	size_t element_num = 2;
	int element1 = 3;
	int element2 = 43;
	stack_t *simple_int_stack = StackCreate(element_size, element_num);
	
	puts("---------simple test-------------");
	/*pointer to stack should be with & ? */
	
	if (StackSize(simple_int_stack) != 0)
	{
		puts("StackSize failed");
	}
	
	StackPush(simple_int_stack, &element1); /*needs cast to void?*/
	/*printf("%d\n", *(int*)StackPeek(simple_int_stack));*/
	/*printf("%lu\n", StackSize(simple_int_stack));*/
	
	
	if (StackSize(simple_int_stack) != 1 || *(int*)StackPeek(simple_int_stack) != element1)
	{
		puts("StackPush # 1 or StackPeek of element 1 failed");
	}
	
	StackPush(simple_int_stack, &element2);
	printf("%d\n", *(int*)StackPeek(simple_int_stack));
	printf("%lu\n", StackSize(simple_int_stack));
	if (StackSize(simple_int_stack) != 2 || *(int*)StackPeek(simple_int_stack) != element2)
	{
		puts("StackPush # 2 or StackPeek of element 2 failed");
	}
	
	StackPop(simple_int_stack);
	
	if (StackSize(simple_int_stack) != 1 || *(int*)StackPeek(simple_int_stack) != element1)
	{
		puts("StackPop # 1 failed");
	}
	
	StackDestroy(simple_int_stack);
}

void ComplexUnitest(void)
{
	size_t element_size_int = sizeof(int);
	size_t element_num_int = 2;
	int element1_int = 3;
	int element2_int = 43;
	size_t element_size_char = sizeof(char);
	size_t element_num_char = 3;
	int element1_char = 'g';
	int element2_char = 'a';
	
	float flt_array1[3] = {1.2,5.3,10.4};
	size_t element_size_flt_ar = sizeof(flt_array1);
	
	char *str = "you figuratively dont know what literally means";
	char *str2= "kjdhgfiwqagfa";
	size_t str_len = sizeof(str);

		
	stack_t *simple_int_stack = StackCreate(element_size_int, element_num_int);
	stack_t *simple_char_stack = StackCreate(element_size_char, element_num_char);
	
	stack_t *complex_flt_stack = StackCreate(element_size_flt_ar, element_num_char);
	
	stack_t *complex_str_stack = StackCreate(str_len , element_num_char);
	
	puts("---------complex test------------");
	/*if (StackSize(simple_int_stack) != 0)
	{
		puts("StackSize of int stack failed");
	}*/
	StackPush(complex_flt_stack, flt_array1);
	StackPush(simple_char_stack, &element1_char);
	StackPush(simple_char_stack, &element2_char);
	
	StackPush(complex_str_stack, &str);
	/*printf("first str in stack: %p, %p\n", *(char**)StackPeek(complex_str_stack), str);*/
	printf("first str in stack: %s\n", *(char**)StackPeek(complex_str_stack));
	StackPush(complex_str_stack, &str2);
	printf("first str in stack after 2nd push: %s\n", *(char**)StackPeek(complex_str_stack));
	/*printf("first str in stack: %p, %p\n", *(char**)StackPeek(complex_str_stack), str2);*/
	StackPush(complex_str_stack, &str);	
	
	printf("first str in stack after 3nd push: %s\n", *(char**)StackPeek(complex_str_stack));
	if (StackSize(complex_str_stack) != 3)
	{
		puts("StackPush of complex str stack failed");
	}
	
	/*printf("peeking into char stack should be 'a': %c\n", *(char*)StackPeek(simple_char_stack));*/
	if (StackSize(simple_char_stack) != 2)
	{
		puts("StackPush of char stack failed");
	}
	if (StackSize(simple_char_stack) != 2 || *(char*)StackPeek(simple_char_stack) != element2_char)
	{
		puts("StackPush # 2 or StackPeek of element 2 (char) failed");
	}
	
	StackPush(complex_flt_stack, flt_array1);
	
	
	printf("second float in array, second element: %.2f\n", *(((float*)StackPeek(complex_flt_stack))+1));
	
	if (StackSize(complex_flt_stack) != 2 || *(float*)StackPeek(complex_flt_stack) != flt_array1[0])
	{
		puts("float array second push failed");
	}
	
	StackPop(simple_char_stack);
	
	/*printf("peeking into char stack should be 'g': %c\n", *(char*)StackPeek(simple_char_stack));*/
	
	/*printf("int stack size should be 0: %lu\n", StackSize(simple_int_stack));*/
	
	if (StackSize(simple_char_stack) != 1 || *(char*)StackPeek(simple_char_stack) != element1_char)
	{
		puts("StackPush # 2 or StackPeek of element 2 (char) failed");
	}
	
	StackPush(simple_char_stack, &element1_char);
	
	/*printf("peeking into char stack should be 'g': %c\n", *(char*)StackPeek(simple_char_stack));*/
	if (StackSize(simple_char_stack) != 2 || *(char*)StackPeek(simple_char_stack) != element1_char)
	{
		puts("StackPush # 2 or StackPeek of element 1 (char) failed");
	}
	
	StackPush(simple_int_stack, &element1_int);
	if (StackSize(simple_int_stack) != 1 || *(int*)StackPeek(simple_int_stack) != element1_int)
	{
		puts("StackPush # 1 or StackPeek of element 1 failed");
	}
	
	StackPop(simple_int_stack);
	
	if (StackSize(simple_int_stack) != 0)
	{
		puts("StackPop # 1 of int element 1 failed");
	}
	StackPush(simple_int_stack, &element2_int);
		
	StackDestroy(simple_int_stack);
	StackDestroy(simple_char_stack);
	StackDestroy(complex_flt_stack);
	StackDestroy(complex_str_stack);
}

void StackofStructsUnitest(void)
{
	struct DateOfBirth
	{
		size_t day;
		size_t month;
		size_t year;
	};

	struct DateOfBirth date_struct = {05,12,1988};

	stack_t *complex_struct_stack = StackCreate(sizeof(struct DateOfBirth), 2);
	
	puts("---------struct test------------");
	
	StackPush(complex_struct_stack, &date_struct);
	
	printf("%lu\n", *(size_t*)StackPeek(complex_struct_stack));
	
	if (StackSize(complex_struct_stack) != 1 ||  *(size_t*)StackPeek(complex_struct_stack) != date_struct.day)
	{
		puts("StackPush # 1 or StackPeek of struct stack 1 failed");
	}
	
	StackPush(complex_struct_stack, &date_struct);
	
	if (StackSize(complex_struct_stack) != 2 ||  *(size_t*)StackPeek(complex_struct_stack) != date_struct.day)
	{
		puts("StackPush # 2 or StackPeek of struct stack failed");
	}
		
	StackPop(complex_struct_stack);
	if (StackSize(complex_struct_stack) != 1 ||  *(size_t*)StackPeek(complex_struct_stack) != date_struct.day)
	{
		puts("StackPush # 1 or StackPeek of struct stack 1 failed");
	}
	
	StackDestroy(complex_struct_stack);
}














