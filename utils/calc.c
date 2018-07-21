#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

#define MAX_EVENTS 256

typedef enum priority { PR_END, PR_C_PAR, PR_ADD, PR_SUB = PR_ADD, PR_MULT, PR_DIV = PR_MULT, PR_POW, PR_O_PAR} priority_t ;

typedef enum state {EXPECT_NUM, EXPECT_OP, ERROR, FINISH, MAX_STATES} state_t;

typedef char * (*func_t)(const char *str, void *param); /*int?*/
typedef double (*func_op_t)(double num1, double num2);
typedef struct
{
	func_t func;
	state_t next_state;
} event_t;

typedef struct
{
	func_op_t op;
	priority_t priority;
} op_t;

char *ErrorFunc(const char *str,  void *param);
char *OpHandle(const char *str, void *param);
char *DummyFunc(const char *str, void *param);
char *ParOpenHandle(const char *str, void *param);
char *ParClosedHandle(const char *str, void *param);
char *NumHandle(const char *str, void *param);
char *MinusHandle(const char *str, void *param);
char *SpaceHandle(const char *str, void *param);
char *NullHandle(const char *str, void *param);

op_t priority_table[MAX_EVENTS];
event_t lookup[MAX_STATES][MAX_EVENTS];
stack_t *op_stack;
stack_t *num_stack;

void InitStatesEvents(void)
{
	event_t error = {ErrorFunc, ERROR};
	event_t op_num = {OpHandle, EXPECT_NUM};
	event_t dummy_num = {DummyFunc, EXPECT_NUM};
	event_t par_op = {ParClosedHandle, EXPECT_OP};
	event_t par_num =  {ParOpenHandle, EXPECT_NUM};
	event_t num_op = {NumHandle, EXPECT_OP};
	event_t minus_num = {MinusHandle, EXPECT_NUM};
	event_t space_num = {SpaceHandle, EXPECT_NUM};
	event_t space_op = {SpaceHandle, EXPECT_OP};
	event_t null_op = {NullHandle, FINISH};
	int i = 0;
	int j = 0;

	for(j = 0 ; j < MAX_STATES; ++j)
	{
		for(i = 0 ; i < MAX_EVENTS; ++i)
		{
			lookup[j][i] = error;
		}
	}

	lookup[EXPECT_NUM][' '] = space_num;
	lookup[EXPECT_OP][' '] = space_op;	
		
	lookup[EXPECT_NUM]['('] = par_num;
	lookup[EXPECT_NUM]['-'] = minus_num;
	lookup[EXPECT_NUM]['+'] = dummy_num;
	
	lookup[EXPECT_OP]['\0'] = null_op;
	lookup[EXPECT_OP]['='] = null_op;
	lookup[EXPECT_OP][')'] = par_op;
	lookup[EXPECT_OP]['-'] = op_num;	
	lookup[EXPECT_OP]['+'] = op_num;
	lookup[EXPECT_OP]['*'] = op_num;	
	lookup[EXPECT_OP]['/'] = op_num;
		
	for(i = '0' ; i < '9'+1 ; ++i)
	{	
		lookup[EXPECT_NUM][i] = num_op;
	}
}

double Add(double num1, double num2)
{
	return num1 + num2;
}

double Mult(double num1, double num2)
{
	return num1 * num2;
}

double Div(double num1, double num2)
{
	return num2 / num1;
}

double Sub(double num1, double num2)
{
	return num2 - num1;
}

void InitPriorityTable(void)
{
	op_t minus = {Sub, PR_SUB};
	op_t plus = {Add, PR_ADD};
	op_t mult = {Mult, PR_MULT};
	op_t div = {Div, PR_DIV};
	op_t end = {NULL, PR_END};
	op_t par_o = {NULL, PR_O_PAR};
	op_t par_c = {NULL, PR_C_PAR};
	op_t pow = {NULL, PR_POW};
/*
typedef enum priority { PR_END, PR_C_PAR, PR_ADD, PR_SUB = PR_ADD, PR_MULT, PR_DIV = PR_MULT, PR_POW, PR_O_PAR} priority_t ;*/	
	priority_table['+'] = plus;
	priority_table['-'] = minus;
	priority_table['*'] = mult;
	priority_table['/'] = div;
	priority_table['\0'] = end;
	priority_table[')'] = par_c;
	priority_table['('] = par_o; /*?????????????? higher lower?*/
	priority_table['^'] = pow;
	priority_table['='] = end;
}


char *NumHandle (const char *str, void *param)
{

	char *newlocation = NULL;
	double number = strtod(str, &newlocation);
	StackPush(num_stack, &number);
	(void)param;
	/*printf("from inside num handle:\n num = %f stack = %f\n", number, *(double *)StackPeek(num_stack));*/

	
	return newlocation;
}

char *ErrorFunc(const char *str,  void *param)
{

	puts("invalid syntax");
	StackDestroy(op_stack);
	StackDestroy(num_stack);
	(void)param;
	(void)str;
	exit(EXIT_FAILURE);
}

char *OpHandle(const char *str, void *param)
{

	char operation = *str;
	char *strs = (char*)str;
	double num1 = 0;
	double num2 = 0;
	double result = 0;
	op_t prev_op = {0};
	op_t op = priority_table[(int)operation];
	char prev_operation = '\0';
		(void)param;
	if(StackSize(op_stack) > 0)
	{
		prev_operation = *(char *)StackPeek(op_stack);
	}
	prev_op = priority_table[(int)prev_operation];

	while(StackSize(op_stack) > 0 && op.priority <= prev_op.priority )
	{
			num1 = *(double *)StackPeek(num_stack);
			StackPop(num_stack);
			num2 = *(double *)StackPeek(num_stack);
			StackPop(num_stack);
			StackPop(op_stack);
			result =  prev_op.op(num1, num2);
			StackPush(num_stack,&result);
			prev_op = priority_table[(int)prev_operation];
			
			if(StackSize(op_stack) > 0)
			{
				prev_operation = *(char *)StackPeek(op_stack);
			}
			
	}
	StackPush(op_stack, &operation);
	++strs;
	return strs;

}



char *DummyFunc(const char *str, void *param)
{
	(void)param;
		
	return (char*)str;
}

char *ParOpenHandle(const char *str, void *param)
{
	char *strs = (char*)str;
	char par_open = *strs;
	StackPush(op_stack, &par_open);
	++strs;
	(void)param;
	return strs;
}

char *ParClosedHandle(const char *str, void *param)
{
	(void)str;
	(void)param;
	return 0;
}

char *NullHandle(const char *str, void *param)
{

	while (StackSize(op_stack) > 0 )
	{
		OpHandle(str, NULL);
		StackPop(op_stack);
	}
	(void)param;
	return (char*)str;
}
char *MinusHandle(const char *str, void *param)
{
	double number = 1;
	double neg_number = -1;
	char *strs = (char*)str;
	char mult = '*';
		/*size_t minus_count = 0;
		char *newlocation = NULL;*/
	
	while(*strs == '-' || *strs == '+')
	{
		if(*strs == '-')
		{
			StackPush(num_stack, &neg_number);
			StackPush(op_stack, &mult);
		}
		else if (*strs == '+')
		{
			StackPush(num_stack, &number);
			StackPush(op_stack, &mult);
		}
		++strs;
	}
	
	/*
	if((minus_count & 1) == 1) 
	{
		number = -1;
	} 
	
	if(*strs == '(' )
	{
		ParHandle(strs, NULL);
	}
	else if(isdigit(*strs))
	{
		number *= strtod(strs, &newlocation);
		StackPush(num_stack, &number);	
		return newlocation;
	}*/	
	
	(void)param;
	return strs;

}
char *SpaceHandle(const char *str, void *param)
{
	char *strs = (char*)str;
	++strs;
	(void)param;
	return strs;
}


int main()
{
	const char *str = "5+85*2-9/5=" /* "2 +3/3*5-20.8- 60.2 ="*/;	
	char *strs = (char*)str;
	char *curr_strs = strs;
	state_t current_state = EXPECT_NUM;
	op_stack = StackCreate(sizeof(char), 100);
	num_stack = StackCreate(sizeof(double), 100);
	InitStatesEvents();
	InitPriorityTable();
	
	printf("%s\n", str);
	
	while(current_state != FINISH)
	{
		strs = lookup[current_state][(int)*curr_strs].func(strs,NULL);
		current_state = lookup[current_state][(int)*curr_strs].next_state;
		curr_strs = strs;
	}

	printf("%f\n", *(double *)StackPeek(num_stack));

	StackDestroy(op_stack);
	StackDestroy(num_stack);
	return 0;
}
	
	


