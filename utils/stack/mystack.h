#ifdef STACK_H
#define STACK_H
typedef struct stack stack_t;
typedef enum {  OK , FAIL } status;

stack_t *StackCreate(size_t element_size, size_t element_num);
status StackDestroy(stack_t *stack);
size_t StackSize(stack_t *stack); /*number of elements*/
void StackPush(stack_t *stack_top);
void StackPop(stack_t *stack_top);
void* Peek(stack_t *stack_top);

#endif /*stack.h*/
