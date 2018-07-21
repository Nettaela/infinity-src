#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void SimpleUnitest(void);
void ComplexUnitest(void);


int main()
{
	SimpleUnitest();
	ComplexUnitest();
	
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
	/*
	StackPush(simple_int_stack, &element2);
	printf("%d\n", *(int*)StackPeek(simple_int_stack));
	printf("%lu\n", StackSize(simple_int_stack));
	if (StackSize(simple_int_stack) != 2 || *(int*)StackPeek(simple_int_stack) != element2)
	{
		puts("StackPush # 2 or StackPeek of element 2 failed");
	}
	*/
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
	size_t element_num_char = 2;
	int element1_char = 'g';
	int element2_char = 'a';
	stack_t *simple_int_stack = StackCreate(element_size_int, element_num_int);
	stack_t *simple_char_stack = StackCreate(element_size_char, element_num_char);
	puts("---------complex test------------");
	if (StackSize(simple_int_stack) != 0)
	{
		puts("StackSize of int stack failed");
	}
	
	StackPush(simple_char_stack, &element1_char);
	StackPush(simple_char_stack, &element2_char);
	/*printf("peeking into char stack should be 'a': %c\n", *(char*)StackPeek(simple_char_stack));*/
	if (StackSize(simple_char_stack) != 2)
	{
		puts("StackPush of char stack failed");
	}
	if (StackSize(simple_char_stack) != 2 || *(char*)StackPeek(simple_char_stack) != element2_char)
	{
		puts("StackPush # 2 or StackPeek of element 2 (char) failed");
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
}
















