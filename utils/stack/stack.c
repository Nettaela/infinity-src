#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

struct stack
{
	size_t element_size;
	size_t offset;
	char * stack_start;
};

stack_t *StackCreate(size_t element_size, size_t element_num)
{
	/*1 malloc for both the meta data stack, and the stack itself*/
	stack_t *new_stack = (stack_t *)malloc(sizeof(stack_t) + (element_size * element_num));
	
	if(new_stack == NULL)
	{
		perror("memory allocation in StackCreate");
	}
	
	new_stack->stack_start = (char*)(new_stack + sizeof(stack_t));
	new_stack->element_size = element_size;	
	new_stack->offset = 0;
	return new_stack;
}


void StackDestroy(stack_t *stack)
{
	free(stack);
	stack = NULL;
}

void StackPush(stack_t *stack, const void *data)
{

	memcpy((stack->stack_start + ((stack->offset) * (stack->element_size))), data , stack->element_size);
	stack->offset = stack->offset + 1;
}

void *StackPeek(const stack_t *stack)
{
	return stack->stack_start + ((stack->offset) * (stack->element_size));
}

void StackPop(stack_t *stack)
{
	stack->offset = stack->offset - 1;
}

size_t StackSize(const stack_t *stack)
{
	size_t stacksize = stack->offset + 1;
	return stacksize;
}




