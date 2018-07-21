#include <stdio.h>  /* printf */
#include <time.h>   /* time   */
#include <string.h> /* strcmp */
#include <stdlib.h> /* system */
#include <dlfcn.h>

#include "scheduler.h"
/*#include "one.h"
#include "two.h" */


void test();
void test1();
/*void test2();*/
/*void test3(char *argv[]);*/

int main(/*int argc, char *argv[]*/)
{
	test();
/*	test1();*/
/*	test2();*/
/*	test3(argv);*/

	return 0;
}

static int Barney(void *str)
{
	if (*(char *)str != 'x')
	{
		printf("%s\n", (char *)str);
	}
	else
	{
		printf("DARY!!!\n");
	}

	return (0);
}

static int File(void *param)
{	
	char str[1000];
	char stop[] = "stop";
	char *test;
	FILE *file = fopen(stop, "a+");

	while (fscanf(file, "%s", str) != EOF)
	{
		test = strstr(str, stop);

		if(test)
		{
			SchStop((sch_t *)param);
		}
	}

	return (0);
}

void test()
{
	sch_t *sch = SchCreate();
	char a[] = "L E G E N D";
	char b[] = "wait for it";
	char c[] = ".";
	char d[] = "x";
	time_t curr_time = time(NULL);


	SchAdd(sch, Barney, a, 0, curr_time + 1);
	SchAdd(sch, Barney, c, 0, curr_time + 2);
	SchAdd(sch, Barney, b, 0, curr_time + 3);
	SchAdd(sch, Barney, c, 0, curr_time + 4);
	SchAdd(sch, Barney, c, 0, curr_time + 5);
	SchAdd(sch, Barney, c, 0, curr_time + 6);
	SchAdd(sch, Barney, d, 0, curr_time + 8);

	SchRun(sch);

	SchDestroy(sch);
}

void test1()
{
	sch_t *sch = SchCreate();
	time_t curr_time = time(NULL);
	char a[] = ".";	

	SchAdd(sch, Barney, a, 2, curr_time + 1);
	SchAdd(sch, File, sch, 2, curr_time);

	SchRun(sch);

	SchDestroy(sch);
}

/*void test2()
{
	Hello();
	Me();
	Too();
}*/

void test3(char *argv[])
{
	void *handle;
    int (*func)();
	sch_t *sch = SchCreate();
	time_t curr_time = time(NULL);

	handle = dlopen(argv[1], RTLD_LAZY);

	*(void**)(&func) = dlsym(handle, argv[2]);
	
	SchAdd(sch, func, NULL, 5, curr_time + 1);

	SchRun(sch);

	SchDestroy(sch);


	dlclose(handle);
}






