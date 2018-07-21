#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void PointerSwapper(int **ptrptr1, int ** ptrptr2);
void UniTest(void);

int main()
{
	UniTest();
	return EXIT_SUCCESS;
}

void PointerSwapper(int **ptrptr1, int ** ptrptr2)
{
	
	int *temp = NULL;
	
	assert(ptrptr1 && ptrptr2);
	
	temp = *ptrptr1;
	*ptrptr1 = *ptrptr2;
	*ptrptr2 = temp;

}

void UniTest(void)
{
	
	int num1=20;
	int num2=30;
	int *num1_ptr=&num1;
	int *num2_ptr=&num2;
	printf("%p = %d , %p = %d\n", (void *)num1_ptr,num1,(void *)num2_ptr,num2);
	PointerSwapper(&num1_ptr,&num2_ptr);
	printf("%p = %d , %p = %d\n", (void *)num1_ptr,num1,(void *)num2_ptr,num2);

	

}
