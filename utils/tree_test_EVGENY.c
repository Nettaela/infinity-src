#include "tree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAGIC_NUM 0xcafacafa
#define UNUSED(x) (void)(x)

static void PrintRndColorMsg(char* msg);

typedef struct person
{
	long id;
	int age;
}person_t;

static int Compare(const void *data, const void *data_to_compare, void *params)
{
	const person_t *person = (const person_t*)data;
	const person_t *person_to_compare = (const person_t*)data_to_compare;
	
	UNUSED(params);
	return person->id - person_to_compare->id;
}

void UniTestCreate(void)
{
	tree_t *tree = TreeCreate(&Compare, NULL);
	
	assert(tree);
	assert(TreeIsEmpty(tree));
	
	TreeDestroy(tree);
	tree = NULL;
	
	puts("simple create test passed");
}

void UnitTestInsert(void) /* tests TreeBegin too */
{
	tree_t *tree = TreeCreate(&Compare, NULL);
	person_t me = {309392, 29};
	person_t motty = {307647, 33};
	tree_iter_t it = {0};
	
	it = TreeInsert(tree, &me);
	assert(!TreeIsEmpty(tree));
	assert(TreeGetData(it) == &me);
	assert(TreeGetData(TreeBegin(tree)) == &me);
	it = TreeInsert(tree, &motty);
	assert(TreeGetData(it) == &motty);
	assert(TreeGetData(TreeBegin(tree)) == &motty);
	TreeDestroy(tree);
	tree = NULL;
	
	puts("simple insert test passed");
}

void UnitTestNextPrev(void) /* tests TreeEnd and IsSameIter too */
{
	tree_t *tree = TreeCreate(&Compare, NULL);
	person_t me = {309392, 29};
	person_t motty = {307647, 33};
	person_t gavriel = {316879, 27};
	person_t daniel = {309285, 32};
	tree_iter_t it = {0};
	
	it = TreeInsert(tree, &me);
	it = TreeInsert(tree, &motty);
	it = TreeInsert(tree, &gavriel);
	it = TreeInsert(tree, &daniel);

	it = TreeBegin(tree);
	assert(TreeGetData(it) == &motty);
	it = TreeNextIter(it);
	assert(TreeGetData(it) == &daniel);
	it = TreeNextIter(it);
	assert(TreeGetData(it) == &me);
	it = TreeNextIter(it);
	assert(TreeGetData(it) == &gavriel);
	it = TreeNextIter(it);
	assert(TreeIsSameIter(it, TreeEnd(tree)));
	
	it = TreePrevIter(it);
	assert(TreeGetData(it) == &gavriel);
	it = TreePrevIter(it);
	assert(TreeGetData(it) == &me);
	it = TreePrevIter(it);
	assert(TreeGetData(it) == &daniel);
	it = TreePrevIter(it);
	assert(TreeGetData(it) == &motty);
	assert(TreeIsSameIter(it, TreeBegin(tree)));
	
	TreeDestroy(tree);
	tree = NULL;
	
	puts("Next&Prev test passed");

}

void UnitTestCount(void) /* tests TreeEnd too */
{
	tree_t *tree = TreeCreate(&Compare, NULL);
	person_t me = {309392, 29};
	person_t motty = {307647, 33};
	person_t gavriel = {316879, 27};
	person_t daniel = {309285, 32};
	
	assert(TreeSize(tree) == 0);	
	TreeInsert(tree, &me);
	assert(TreeSize(tree) == 1);
	TreeInsert(tree, &motty);
	assert(TreeSize(tree) == 2);
	TreeInsert(tree, &gavriel);
	assert(TreeSize(tree) == 3);
	TreeInsert(tree, &daniel);
	assert(TreeSize(tree) == 4);

	
	TreeDestroy(tree);
	tree = NULL;
	
	puts("Count test passed");

}

void UnitTestHeight(void) /* tests TreeEnd too */
{
	tree_t *tree = TreeCreate(&Compare, NULL);
	person_t me = {309392, 29};
	person_t motty = {307647, 33};
	person_t gavriel = {316879, 27};
	person_t daniel = {309285, 32};
	
	assert(GetTreeHeight(tree) == 0);	
	TreeInsert(tree, &me);
	assert(GetTreeHeight(tree) == 0);
	TreeInsert(tree, &motty);
	assert(GetTreeHeight(tree) == 1);
	TreeInsert(tree, &gavriel);
	assert(GetTreeHeight(tree) == 1);
	TreeInsert(tree, &daniel);
	assert(GetTreeHeight(tree) == 2);

	
	TreeDestroy(tree);
	tree = NULL;
	
	puts("Height test passed");

}

void UnitTestFind(void) /* tests TreeEnd too */
{
	tree_t *tree = TreeCreate(&Compare, NULL);
	person_t me = {309392, 29};
	person_t motty = {307647, 33};
	person_t gavriel = {316879, 27};
	person_t daniel = {309285, 32};
	person_t ghost = {777777, 0};
	tree_iter_t it = {0};
		
	TreeInsert(tree, &me);
	TreeInsert(tree, &motty);
	TreeInsert(tree, &gavriel);
	TreeInsert(tree, &daniel);

	it = TreeFind(tree, &me);
	assert(TreeGetData(it) == &me);
	it = TreeNextIter(it);
	assert(TreeGetData(it) == &gavriel);
	
	it = TreeFind(tree, &ghost); /* ghosts do not leave in trees! */
	assert(TreeIsSameIter(it, TreeEnd(tree)));  
	
	TreeDestroy(tree);
	tree = NULL;
	
	puts("Find test passed");

}

void UniTestRemove(void)
{
	tree_t *tree = TreeCreate(&Compare, NULL);
	tree_t *tree2 = TreeCreate(&Compare, NULL);
	person_t me = {309392, 29};
	person_t motty = {307647, 33};
	person_t gavriel = {316879, 27};
	person_t daniel = {309285, 32};
	void *data_removed = NULL;
	tree_iter_t it = {0};
	
	TreeInsert(tree, &me);
	TreeInsert(tree, &motty);
	TreeInsert(tree, &gavriel);
	it = TreeInsert(tree, &daniel);
	
	data_removed = TreeRemove(it);
	assert((person_t*)data_removed == &daniel);
	
	it = TreeFind(tree, &daniel);
	assert(TreeIsSameIter(it, TreeEnd(tree)));
	
	it = TreeInsert(tree2, &me);
	TreeInsert(tree2, &motty);
	TreeInsert(tree2, &gavriel);
	TreeInsert(tree2, &daniel);
	data_removed = TreeRemove(it);
	assert((person_t*)data_removed == &me);
	it = TreeFind(tree2, &me);
	assert(TreeIsSameIter(it, TreeEnd(tree2)));
	
	while (!TreeIsEmpty(tree2))
	{
		it = TreeBegin(tree2);
		TreeRemove(it);
	}
	
	TreeDestroy(tree);
	tree = NULL;
	TreeDestroy(tree2);
	tree2 = NULL;
	puts("Remove test passed");
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

void UniTestForEach(void)
{
	tree_t *tree = TreeCreate(&Compare, NULL);
	person_t me = {309392, 29};
	person_t motty = {307647, 33};
	person_t gavriel = {316879, 27};
	person_t daniel = {309285, 32};
	tree_iter_t from = {0};
	tree_iter_t to = {0};
	int status = 0;
	int age = 0;
	
	from = TreeInsert(tree, &me);
	TreeInsert(tree, &motty);
	TreeInsert(tree, &gavriel);
	TreeInsert(tree, &daniel);
	
	to = TreeEnd(tree);
	age = 5;
	status = TreeForEach(from, to, &ChangeAge, &age);
	assert(status == 0);
	assert(me.age == 5);
	assert(motty.age == 33);
	assert(gavriel.age == 5);
	assert(daniel.age == 32);
	
	age = -1;
	status = TreeForEach(from, to, &ChangeAge, &age);
	assert(status == 1);
	
	TreeDestroy(tree);
	tree = NULL;
	puts("ForEach test passed");
}

int main()
{
	UniTestCreate();
	UnitTestInsert();
	UnitTestNextPrev();
	UnitTestCount();
	UnitTestHeight();
	UnitTestFind();
	UniTestRemove();
	UniTestForEach();
	
	/*PrintRndColorMsg("YES YOU DID IT!!!!");*/
	
	return EXIT_SUCCESS;
}

static void PrintRndColorMsg(char* msg)
{
    char color_str[] = "echo \"$(tput setaf 3)\"";
    size_t idx = 0;
    int color = 0;
    
    for(idx = 0; idx < 10000; ++idx)
    {
    	color = rand() % 7;
		system("echo \"$(tput bold)\"");
		color_str[19] = color + 48;
		system(color_str);
		puts(msg);
		system("echo \"$(tput sgr0)\"");
    }
}
