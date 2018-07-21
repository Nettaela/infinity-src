#ifndef STACK_H
#define STACK_H

typedef struct stack stack_t;

stack_t *StackCreate(size_t element_size, size_t element_num);
void StackDestroy(stack_t *stack);
void StackPush(stack_t *stack, const void *data);
void *StackPeek(const stack_t *stack);
void StackPop(stack_t *stack);
size_t StackSize(const stack_t *stack);

#endif


