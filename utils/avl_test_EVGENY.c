#include "avl.h"
#include <stdlib.h> /*malloc, free */
#include <stdio.h>
#include <assert.h>

/* Test developed by Evgeny from CrushProg Inc. 2018 */

typedef struct person
{
	long id;
	int age;
}person_t;

static int Compare(const void *data, const void *data_to_compare)
{
	const person_t *person = (const person_t*)data;
	const person_t *person_to_compare = (const person_t*)data_to_compare;
	
	return person_to_compare->id - person->id ;
}

void UniTestCreate(void)
{
	avl_t *tree = AVLCreate(&Compare);
	
	assert(tree);
	assert(AVLIs_Empty(tree));
	
	AVLDestroy(tree);
	tree = NULL;
	
	puts("simple create test passed");
}

void UnitTestInsert(void) /*test also size, hight and is empty */
{
	avl_t *tree = AVLCreate(&Compare);
	person_t me = {309392, 29};
	person_t motty = {307647, 33};
	
	assert(AVLSize(tree) == 0);
	assert(AVLGetHeight(tree) == 0);
	assert(AVLInsert(tree, &me) == 0);
	assert(!AVLIs_Empty(tree));
	assert(AVLSize(tree) == 1);
	assert(AVLGetHeight(tree) == 0);
	assert(AVLInsert(tree, &motty) == 0);
	assert(AVLSize(tree) == 2);
	assert(AVLGetHeight(tree) == 1);
	
	AVLDestroy(tree);
	tree = NULL;
	
	puts("simple insert test passed");
}

static int ChangeAge(void* data, void *param)
{
	person_t *person = (person_t*)data;
	int age = *(int*)param;
	
	if (age < 0)
	{
		return 1;
	}
	person->age = age;
	return 0;
}

void UnitTestForEach(void) /*test also size, hight and is empty */
{
	avl_t *tree = AVLCreate(&Compare);
	person_t me = {309392, 29};
	person_t motty = {307647, 33};
	person_t gavriel = {316879, 27};
	person_t daniel = {309285, 32};
	int status = 0;
	int age = 0;
	
	assert(AVLInsert(tree, &me) == 0);
	assert(AVLInsert(tree, &motty) == 0);
	assert(AVLInsert(tree, &gavriel) == 0);
	assert(AVLInsert(tree, &daniel) == 0);
	
	age = 5;
	status = AVLForEach(tree, &ChangeAge, &age);
	assert(status == 0);
	assert(me.age == 5);
	assert(motty.age == 5);
	assert(gavriel.age == 5);
	assert(daniel.age == 5);
	
	age = -1;
	status = AVLForEach(tree, &ChangeAge, &age);
	assert(status == 1);
	
	AVLDestroy(tree);
	tree = NULL;
	
	puts("for each test passed");
}

void UnitTestFind(void) /*test also size, hight and is empty */
{
	avl_t *tree = AVLCreate(&Compare);
	person_t me = {309392, 29};
	person_t motty = {307647, 33};
	person_t gavriel = {316879, 27};
	person_t daniel = {309285, 32};
	
	person_t me2find = {309392, 29};
	person_t motty2find = {307647, 33};
	person_t gavriel2find = {316879, 27};
	person_t daniel2find = {309285, 32};
	person_t plony2find = {309999, 32};
	
	assert(AVLInsert(tree, &me) == 0);
	assert(AVLInsert(tree, &motty) == 0);
	assert(AVLInsert(tree, &gavriel) == 0);
	assert(AVLInsert(tree, &daniel) == 0);
	
	assert(AVLFind(tree, &me2find) == &me);
	assert(AVLFind(tree, &motty2find) == &motty);
	assert(AVLFind(tree, &gavriel2find) == &gavriel);
	assert(AVLFind(tree, &daniel2find) == &daniel);
	assert(AVLFind(tree, &plony2find) == NULL);
	
	AVLDestroy(tree);
	tree = NULL;
	
	puts("find test passed");
}

void BalanceTest(void)
{
	avl_t *tree = AVLCreate(&Compare);
	person_t me = {309392, 29};
	person_t motty = {307647, 33};
	person_t gavriel = {316879, 27};
	person_t daniel = {309285, 32};
	person_t old_man = {315000, 99};
	
	assert(AVLInsert(tree, &motty) == 0);
	assert(AVLSize(tree) == 1);
	assert(AVLGetHeight(tree) == 0);
	
	assert(AVLInsert(tree, &daniel) == 0);
	assert(AVLSize(tree) == 2);
	assert(AVLGetHeight(tree) == 1);
	
	assert(AVLInsert(tree, &me) == 0);
	assert(AVLSize(tree) == 3);
	assert(AVLGetHeight(tree) == 1);
	
	assert(AVLInsert(tree, &gavriel) == 0);
	assert(AVLSize(tree) == 4);
	assert(AVLGetHeight(tree) == 2);
	
	assert(AVLInsert(tree, &old_man) == 0);
	assert(AVLSize(tree) == 5);
	assert(AVLGetHeight(tree) == 2);
	
	AVLDestroy(tree);
	tree = NULL;
	
	puts("Balance test passed");
}

void RemoveTest(void)
{
	avl_t *tree = AVLCreate(&Compare);
	person_t me = {309392, 29};
	person_t motty = {307647, 33};
	person_t gavriel = {316879, 27};
	person_t daniel = {309285, 32};
	person_t old_man = {315000, 99};
	
	person_t me2find = {309392, 29};
	person_t motty2find = {307647, 33};
	person_t gavriel2find = {316879, 27};
	person_t daniel2find = {309285, 32};
	
	assert(AVLInsert(tree, &motty) == 0);
	assert(AVLInsert(tree, &daniel) == 0);
	assert(AVLInsert(tree, &me) == 0);
	assert(AVLInsert(tree, &gavriel) == 0);
	assert(AVLInsert(tree, &old_man) == 0);
	
	assert(AVLSize(tree) == 5);
	assert(AVLGetHeight(tree) == 2);
	
	assert(AVLRemove(tree, &old_man) == &old_man);
	assert(AVLSize(tree) == 4);
	assert(AVLFind(tree, &old_man) == NULL);
	assert(AVLFind(tree, &me2find) == &me);
	assert(AVLFind(tree, &motty2find) == &motty);
	assert(AVLFind(tree, &gavriel2find) == &gavriel);
	assert(AVLFind(tree, &daniel2find) == &daniel);
	
	assert(AVLInsert(tree, &old_man) == 0);
	assert(AVLSize(tree) == 5);
	assert(AVLGetHeight(tree) == 2);
	
	assert(AVLRemove(tree, &daniel) == &daniel);
	assert(AVLSize(tree) == 4);
	assert(AVLFind(tree, &me2find) == &me);
	assert(AVLFind(tree, &motty2find) == &motty);
	assert(AVLFind(tree, &gavriel2find) == &gavriel);
	assert(AVLFind(tree, &daniel2find) == NULL);
	
	assert(AVLRemove(tree, &motty) == &motty);
	assert(AVLSize(tree) == 3);
	assert(AVLGetHeight(tree) == 1);
	
	AVLDestroy(tree);
	tree = NULL;
	
	puts("remove test passed");
}

int main()
{
	UniTestCreate();
	UnitTestInsert();
	UnitTestForEach();
	UnitTestFind();
	BalanceTest();
	RemoveTest();
	
	puts("\nall tests passed");
	puts("\n(c) ALL RIGHTS RESERVED TO CRUSH_CORP INC (c)");
	
	return EXIT_SUCCESS;
}
