#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
typedef enum state{EXP_NUM, EXP_OP, ERROR}state_t;
double calculator(char *str);

void SimpleTest()
{

	char *str = "3+2";
	char *str2 = "3-2";
	char *str_negative = "3-4";
	char *str_minus = "10-4-2-6";
	char *str_plus = "1+3+4+5+7+2+7";
	char *str_mult = "2*5";
	char *str_dev = "10/2";
	char *str_all = "2+3/3+5";
	char *str_space = "1+2 +3+ 4";
	char *str_error = "1**2";
	
	/*space*/
	
	
	double result = calculator(str);
	assert (result == 5);
	
	result = calculator(str2);
	assert (result == 1);
	
	result = calculator(str_negative);
	assert (result == -1);
	
	result = calculator(str_minus);
	assert (result == -2);
	
	result = calculator(str_plus);
	assert (result == 29);
	
	result = calculator(str_mult);
	assert (result == 10);
	
	result = calculator(str_dev);
	assert (result == 5);
	
	result = calculator(str_all);
	assert (result == 8);
	
	result = calculator(str_space);
	assert (result == 10);
	
	result = calculator(str_error);
	assert (result == 2);
	
	puts("-------Simple Test- Pass---------");

}

void ParTest()
{
	char *str_minus = "10-(4-2)-6";
	char *str_plus = "1+3+(4+5+7)+2+7";
	char *str_mult = "2*(5+2)";
	char *str_dev = "10/(2-1)";
	char *str_all = "(2+3)/2.5+5";
	char *str_space = "1+2 *(3+ 4)";
	char *str_error = "(1*)*3";
	char *str_no_num = "()";

	double result = calculator(str_minus);
	assert (result == 2);
	
	result = calculator(str_plus);
	assert (result == 29);
	
	result = calculator(str_mult);
	assert (result == 14);
	
	result = calculator(str_dev);
	assert (result == 10);
	
	result = calculator(str_all);
	assert (result == 7);
	
	result = calculator(str_space);
	assert (result == 15);
	
	result = calculator(str_error);
	assert (result == 2);
	
/*	printf("2: %f\n", result);*/
	
	result = calculator(str_no_num);
	assert (result == 2);
	
	puts("-------Par Test- pass------");



}


void PowTest()
{
	char *str_simple = "2^2";
	char *str_plus = "1+3^2-5";
	char *str_mult = "2*(5^2+2)";
	char *str_par = "2*(2+2)^2";
	char *str_pow_pow = "1+2^2^3/4";
	char *str_crazy_pow = "1+2^(1+1)^3";
	/*char *str_error = "(1*)*3";
	*/

	double result = calculator(str_simple);
	assert (result == 4);

	result = calculator(str_plus);
	assert (result == 5);

	result = calculator(str_mult);
	assert (result == 54);
	
	result = calculator(str_par);
	assert (result == 32);

	result = calculator(str_pow_pow);
	assert (result == 65);

	result = calculator(str_crazy_pow);
	assert (result == 257);
	puts("-----Pow Test Pass---------");

}


void UnaryTest()
{
	
	char *str_simple = "3+(-2+1)";
	char *test = "3+-3^2";
	char *str_one = "-(-2)";
	char *str_mult = "1---+-(5^2+2)";
	char *str_same = "1--+-(5^2+2)";
	char *str_pow = "1--(-2)^2";
	char *str_negative_pow = "3+2^(-3)";
	char *str__ = "-2^2 +3";
	
	double result = calculator(str_simple);
	puts("-----------------------");
	printf("2: %f\n", result);
	
	result = calculator(test);
	printf("-6: %f\n", result);
	
	
	result = calculator(str_one);
	printf("2: %f\n", result);
	
	result = calculator(str_mult);
	printf("28: %f\n", result);
	
	result = calculator(str_pow);
	printf("5: %f\n", result);
	
	result = calculator(str_same);
	printf("-26: %f\n", result);
	
	result = calculator(str_negative_pow);
	printf("3.125: %f\n", result);
	
	result = calculator(str__);
	printf("-1: %f\n", result);
}



int main()
{
	/*char *test = "(32";
	double result = strtod(test, &test);
	printf("result %f\n\n", result);
*/

	SimpleTest();	
	ParTest();	
	PowTest();
	UnaryTest();
	
	
	
	
	return EXIT_SUCCESS;

}


/*

disp *str
disp current_state
disp char_index

disp 








*/








