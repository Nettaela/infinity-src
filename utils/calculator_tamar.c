
#include <stdlib.h>		/*strtod*/
#include <stdio.h>		/*printf*/
#include <assert.h>		/*assert*/
#include <math.h>		/*pow*/
#include <ctype.h>		/*isdigit*/
#include "stack.h"		/*stack func declarations*/
/* + - * / ( ) */
#define EVENTS (256)
#define STATES (3)
#define OPS (6)
typedef double (*calculate)(double num1, double num2);
typedef char* (*handler)(stack_t *operators, stack_t *numbers, char *str);
typedef struct transition transition_t;
typedef enum state{EXP_NUM, EXP_OP, ERROR}state_t;
typedef enum priority{ADD = 1, MINUS = 1, DEV = 2, MULT = 2, POWER = 3, 
													PAR = 0} priority_t;
struct transition
{
	state_t next_state;
	handler handler_func;
};

typedef struct cal
{
	priority_t priority;
	calculate cal_func;

}cal_t;


cal_t g_lut_ops[EVENTS];


char *NumHandler(stack_t *operators, stack_t *numbers, char *str)
{
	double num = 0;
	(void) operators;
	num = strtod(str, &str);
	StackPush(numbers, &num);
	
	return str; 
}

static char operate_once(stack_t *operators, stack_t *numbers)
{
	int top = *(char*)StackPeek(operators);
	double num1 = 0;
	double num2 = 0;
	double result = 0;
	
	num2 = *(double*)StackPeek(numbers);
	StackPop(numbers);
	num1 = *(double*)StackPeek(numbers);
	StackPop(numbers);
	result = g_lut_ops[top].cal_func(num1, num2);
	StackPush(numbers, &result);
	StackPop(operators);
	
	if (StackSize(operators) != 0)
	{
		return *(char*)StackPeek(operators);
	}
	
	return 0;
}

char *OpHandler(stack_t *operators, stack_t *numbers, char *str)
{
	cal_t current_op = g_lut_ops[(int)*str]; 
	char top = 0;
	char operator_ch = *str;
	
	if (StackSize(operators) != 0)
	{
		top = *(char*)StackPeek(operators);
		while ((current_op.priority <= g_lut_ops[(int)top].priority) && 
									(StackSize(operators) != 0))
		{
			top = operate_once(operators, numbers);	
		}
	}
	
	
	StackPush(operators, &operator_ch);
	++str;
	return str; 
}	
	
	
char *Endler(stack_t *operators, stack_t *numbers, char *str)
{
	size_t size = StackSize(operators);
	
	while (size > 0)
	{
		operate_once(operators, numbers);
		--size;
	}
	
	return str;
}

char *Space(stack_t *operators, stack_t *numbers, char *str)
{
	(void)operators;
	(void)numbers;
	++str;
	
	return str;
}

char *Error(stack_t *operators, stack_t *numbers, char *str)
{
	(void)operators;
	(void)numbers;
	(void)str;
	return str;
}


char *OpParHandler(stack_t *operators, stack_t *numbers, char *str)
{
	char operator = *str;
	
	if (operator == '(')
	{
		StackPush(operators, &operator);
	}
	else 
	{
		while (*(char*)StackPeek(operators) != '(')
		{
			operator = operate_once(operators, numbers);
		}
		StackPop(operators);
	}
	
	++str;
	return str;
}

char *PowHandler(stack_t *operators, stack_t *numbers, char *str)
{
	char operator_ch = *str;
	(void)numbers;
	StackPush(operators, &operator_ch);
		
	++str;
	
	return str; 
}
char *UnaryHandler(stack_t *operators, stack_t *numbers, char *str)
{
	int counter = 0;
	double num = 0;
	double negative = -1;
	char mult = '*';
	
	(void)operators;
	
	while (isdigit(*str) == 0 && *str != '(')
	{
		while(*str == '-')
		{
			++counter;
			++str;
		}
		while(*str == '+')
		{
			++str;
		}
	}
	
	if (counter % 2 != 0)
	{
		StackPush(numbers, &negative);
		StackPush(operators, &mult);
		return str;
	}
	else 
	{
		return str;
	}
	
	
	
	/*
	if (*str == '(')
		{
			if (counter % 2 != 0)
			{
				StackPush(numbers, &negative);
				StackPush(operators, &mult);
				return str;
			}
			else 
			{
				return str;
			}
		}
	
	*/
	
	
/*
	num = strtod(str, &str);
	if (counter % 2 != 0)
	{
		num = -num;
		
	}
	
	StackPush(numbers, &num);
*/	
	return str;
}

/*!!!!!!!!!!!dont push the num, push -/+1 and * and return!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!! change the  pow func so and change the next state of the unary to exp num*/





/*add to op lut [EXP_NUM]['-'] ADD unary handler that will loop through all the minuses and then call strtod and that will return a number, if the minus count is  e zugi than -num will be pushed to numbers add a func priority*/
/*----------------------------------------------------------------------------*/

double AddFunc(double num1, double num2)
{
	return (num1 + num2);
}

double MinusFunc(double num1, double num2)
{
	return (num1 - num2);
}

double MultFunc(double num1, double num2)
{
	return (num1 * num2);

}

double DevFunc(double num1, double num2)
{
	assert (num2 != 0);
	return (num1 / num2);
}


double ParFunc(double num1, double num2)
{
	(void)num1;
	(void)num2;
	return 0;
}

double PowFunc(double num1, double num2)
{
/*	if ((num1 < 0) && ((int)num2 % 2 == 0))
	{
		return (- pow(num1, num2));
	}
*/	
	return pow(num1, num2);
}


/*----------------------------------------------------------------------------*/
/*LUT for states and events*/

transition_t g_lut[STATES][EVENTS];

void CreateTransitionLUT()
{
	int i = 0;
	state_t states = EXP_NUM;
	
	transition_t error = {ERROR, Error};
	transition_t num = {EXP_OP, NumHandler};
	transition_t op = {EXP_NUM, OpHandler};
	transition_t open_par = {EXP_NUM, OpParHandler};
	transition_t close_par = {EXP_OP, OpParHandler};
	transition_t end_op = {EXP_NUM, Endler};
	transition_t space_op = {EXP_OP, Space};
	transition_t space_num = {EXP_NUM, Space};
	transition_t pow = {EXP_NUM, PowHandler};
	transition_t unary = {EXP_NUM, UnaryHandler};
	
	for (states = 0; states < STATES; ++states)
	{
		for (i = 0; i < EVENTS; ++i)
		{
			g_lut[states][i] = error;
		}
	}
	for (i = 0; i < 10; ++i)
	{
		g_lut[EXP_NUM][i + '0'] = num;
	}
	
	g_lut[EXP_OP]['+'] = op;
	g_lut[EXP_OP]['-'] = op;
	g_lut[EXP_OP]['*'] = op;
	g_lut[EXP_OP]['/'] = op;
	g_lut[EXP_NUM]['('] = open_par;	
	/*g_lut[EXP_OP]['('] = open_par;	*//*for unary minus. doesnt work well*/
	g_lut[EXP_OP][')'] = close_par;
	g_lut[EXP_OP]['\0'] = end_op;
	g_lut[EXP_OP][' '] = space_op;
	g_lut[EXP_NUM][' '] = space_num;
	g_lut[EXP_OP]['^'] = pow;
	g_lut[EXP_NUM]['-'] = unary;
}


void CreateLutOps()
{
	int i = 0;
	cal_t error_op = {10, NULL};
	cal_t add_op = {ADD, AddFunc};
	cal_t minus_op = {MINUS, MinusFunc};
	cal_t mult_op = {MULT, MultFunc};
	cal_t dev_op = {DEV, DevFunc};
	cal_t open_par = {PAR, ParFunc};
	cal_t power_op = {POWER, PowFunc};

	for (i = 0; i < EVENTS; ++i)
	{
		g_lut_ops[i] = error_op;
	}
	
	g_lut_ops['+'] = add_op; 
	g_lut_ops['-'] = minus_op;
	g_lut_ops['*'] = mult_op;
	g_lut_ops['/'] = dev_op;
	g_lut_ops['('] = open_par;
	g_lut_ops['^'] = power_op;
}


double calculator(char *str)
{
	stack_t *operators = StackCreate(sizeof(char), 2000);
	stack_t *numbers = StackCreate(sizeof(double), 2000);
	state_t current_state = EXP_NUM;
	double result = 0;
	int char_index = *str;
	
	CreateTransitionLUT();
	CreateLutOps();
	
	
	while (*str != '\0' && current_state != ERROR)
	{	
		str = g_lut[current_state][(char_index)].handler_func(operators, numbers, str);
		current_state = g_lut[current_state][char_index].next_state;
		char_index = *str;
	}
	
	if (current_state == ERROR)
	{
		return ERROR;
	}
	
	g_lut[current_state][char_index].handler_func(operators, numbers, str);
	result = *(double*)StackPeek(numbers);
	
	StackDestroy(numbers);
	numbers = NULL;
	
	StackDestroy(operators);
	operators = NULL;
	
	return result;
}


















