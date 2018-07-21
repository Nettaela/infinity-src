#include <stdio.h> 	/*for printing*/
#include <stdlib.h> /*for exit*/

void UniTest(void);
void PrintA(void);
void PrintT(void);
void Escape(void);
void Nothing(void);

int main()
{
	UniTest();
	return EXIT_SUCCESS;
}

void UniTest(void)
{
	static void (*func_pointer[256])(void);
	unsigned int i = 0;
	char user_input = 0;
	for (i = 0 ; i < (sizeof(func_pointer) / sizeof(func_pointer[0])) ; i++)
	{
		func_pointer[i] = Nothing;
	}

	func_pointer[65] = PrintA;
	func_pointer[97] = PrintA;
	func_pointer[84] = PrintT;
	func_pointer[116] = PrintT;
	func_pointer[27] = Escape;
	
	system("stty -icanon -echo");
	
	do 
	{
		user_input = getchar();
		(func_pointer[(unsigned int)user_input])();
		
	}while (1);
	
}

void PrintA(void)
{
	puts("A pressed");
}

void PrintT(void)
{
	puts("T pressed");
}

void Escape(void)
{
	system("stty icanon echo");
	exit(0);
}
void Nothing(void)
{
	;
}
