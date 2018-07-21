#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "stack.h"

struct demo_t
{
    int i;
    long li;
    char chars[2];
};

int StructCmp (const struct demo_t *struct1, const struct demo_t *struct2);

void Test1()
{
    static int num_arr[5] = {0, 1, 2, 3, 4};
    
    stack_t *stk = StackCreate(sizeof(int), 10);
    assert(StackSize(stk) == 0);
    StackPush(stk, (void *)&num_arr[1]);
    assert(*(int *)StackPeek(stk) == 1);
    assert(StackSize(stk) == 1);
    StackPush(stk, (void *)&num_arr[3]);
    StackPush(stk, (void *)&num_arr[4]);
    assert(*(int *)StackPeek(stk) == 4);
    assert(StackSize(stk) == 3);
    StackPop(stk);
    assert(*(int *)StackPeek(stk) == 3);
    assert(StackSize(stk) == 2);
    StackPop(stk);
    StackPop(stk);
    assert(StackSize(stk) == 0);
    StackDestroy(stk);
    stk = NULL;
    
    puts("Test 1 >> success!");
}

void Test2()
{
    static struct demo_t strct_arr[5] = {{1, 1000, {'a', 'b'}}, 
                                        {2, 2000, {'c', 'd'}}, 
                                        {3, 3000, {'e', 'f'}}, 
                                        {4, 4000, {'g', 'h'}}, 
                                        {5, 5000, {'i', 'j'}}};
    
    stack_t *stk = StackCreate(sizeof(struct demo_t), 5);
    assert(StackSize(stk) == 0);
    StackPush(stk, &strct_arr[1]);
    assert(StructCmp((struct demo_t *)StackPeek(stk), &strct_arr[1]));
    assert(StackSize(stk) == 1);
    StackPush(stk, &strct_arr[3]);
    StackPush(stk, &strct_arr[4]);
    assert(StructCmp((struct demo_t *)StackPeek(stk), &strct_arr[4]));
    assert(StackSize(stk) == 3);
    StackPop(stk);
    assert(StructCmp((struct demo_t *)StackPeek(stk), &strct_arr[3]));
    assert(StackSize(stk) == 2);
    StackPop(stk);
    StackPop(stk);
    assert(StackSize(stk) == 0);
    StackDestroy(stk);
    stk = NULL;
                
	puts("Test 2 >> success!");                        
}

void TestSrt()
{
    static char str1[] = "sssssstttttttr1";
    char *str2 = (char*)malloc(5);
    stack_t *stk = StackCreate(sizeof(char*), 3);
    
    strcpy(str2, "str2");
    StackPush(stk, &str1);
    StackPush(stk, &str2);
    StackPush(stk, &str1);
    assert(StackSize(stk) == 3);
    assert(strcmp(((char*))StackPeek(stk), str1) == 0);
    StackPop(stk);
    StackPop(stk);
    assert(strcmp(((char*))StackPeek(stk), str1) == 0);
    free(str2);
    StackDestroy(stk);
    stk = NULL;
    
    puts("Test strings >> success!");
}

int StructCmp(const struct demo_t *struct1, const struct demo_t *struct2)
{
	if (struct1->i == struct2->i 
		&& struct1->li == struct2->li
		&& struct1->chars[0] == struct2->chars[0] 
		&& struct1->chars[1] == struct2->chars[1])
	{
		return 1;
	} 
	return 0;
		
}
int main()
{
    Test1();
	Test2();
	TestSrt();
    return EXIT_SUCCESS;
}
