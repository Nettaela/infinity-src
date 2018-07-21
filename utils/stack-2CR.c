#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

struct stack
{
	size_t element_size;
	char * stack_ptr;
	char ch[1];
};

stack_t *StackCreate(size_t element_size, size_t element_num)
{
	/*1 malloc for both the meta data stack, and the stack itself*/
	stack_t *new_stack = (stack_t *)malloc(sizeof(stack_t) + (element_size * element_num));
	
	if(new_stack == NULL)
	{
		perror("memory allocation in StackCreate");
	}
	
/*better performance*/
	new_stack->stack_ptr = new_stack->ch - element_size;


	new_stack->element_size = element_size;	

	return new_stack;
}


void StackDestroy(stack_t *stack)
{
	free(stack);
	stack = NULL;
}

void StackPush(stack_t *stack, const void *data)
{
	memcpy(stack->stack_ptr, data , stack->element_size);
	stack->stack_ptr += stack->element_size;
}

void *StackPeek(const stack_t *stack)
{
	return stack->stack_ptr - stack->element_size ;
}

void StackPop(stack_t *stack)
{
	stack->stack_ptr -= stack->element_size;
}

size_t StackSize(const stack_t *stack)
{
	size_t stacksize = (stack->stack_ptr - stack->ch) / stack->element_size;
	return stacksize;
}




