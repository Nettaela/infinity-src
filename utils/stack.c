#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"

struct stack
{
	size_t element_size;
	size_t num_of_elements;
	char * stack_ptr;
	char ch[1];
};

stack_t *StackCreate(size_t element_size, size_t num_of_elements)
{
	/*1 malloc for both the meta data stack, and the stack itself*/
	stack_t *new_stack = NULL;
	assert(0 < num_of_elements);
	assert(0 < element_size);
	
	new_stack = (stack_t *)malloc(sizeof(stack_t) + (element_size * num_of_elements));
	if(new_stack == NULL)
	{
		return (NULL);
	} 
	new_stack->num_of_elements = num_of_elements;
	new_stack->stack_ptr = new_stack->ch;
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
	assert(NULL != stack);
	assert(stack->stack_ptr != (stack->ch + (stack->num_of_elements * stack->element_size)));
	assert(NULL != data);
	memcpy(stack->stack_ptr, data , stack->element_size);
	stack->stack_ptr += stack->element_size;

}

void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	assert(stack->stack_ptr != stack->ch);
	return (void*)(stack->stack_ptr - stack->element_size);
}

void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	assert(stack->stack_ptr != stack->ch);
	stack->stack_ptr -= stack->element_size;

}

size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);/*kills test, maybe it should be stack->stack_ptr?*/
	return (stack->stack_ptr - stack->ch) / stack->element_size;
}




