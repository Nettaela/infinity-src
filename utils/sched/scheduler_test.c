#include "scheduler.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <dlfcn.h>

int PrintSomething(void *params);
int PrintRecurring(void *params);
void UnitestCreateDestroy(void);
void UnitestAddRemove(void);
void UnitestRunStop(void);
int CallStop(void *params);

int main(int argc, char **argv)
{
	
	sch_t * new_sched = SchCreate();
	guid_t new_task;
	guid_t stop_task;
	time_t period = 2; /*5 sec */
	time_t next_time = time(NULL);
	task_func_t func_ptr = NULL;
	
	void *lib = dlopen(argv[1], RTLD_LAZY); /*"./print.so"*/
  	*(void **) (&func_ptr) = dlsym(lib, argv[2]);
  	
	new_task = SchAdd(new_sched, func_ptr, NULL, period, next_time);
	
	stop_task = SchAdd(new_sched,CallStop, new_sched, 0, next_time+10);
	
	SchRun(new_sched);
	
	(void)stop_task;
	(void)new_task;
	
	SchDestroy(new_sched);
	
	dlclose(lib);
	
	/*UnitestCreateDestroy();
	UnitestAddRemove();
	UnitestRunStop();*/
	return EXIT_SUCCESS;

}

void UnitestCreateDestroy(void)
{

	sch_t * new_sched = SchCreate();
	assert(SchSize(new_sched) == 0);
	assert(SchIsEmpty(new_sched));
	SchDestroy(new_sched);
	
	puts("create destroy done");	

}


void UnitestAddRemove(void)
{

	sch_t * new_sched = SchCreate();
	guid_t new_task;
	guid_t new_task2;
	
	time_t period = 5 ; /*5 sec */
	time_t next_time = time(NULL);
	
	 /*{ 12, 0, 0, 3, 5, 118 };*/ /*june 3rd 2018 (5 months after january, 118 years after 1900)*/ 

	
	new_task = SchAdd(new_sched, PrintRecurring, NULL, period, next_time+10);
	assert(SchSize(new_sched) == 1);
	

	new_task2 = SchAdd(new_sched, PrintSomething, NULL, 0, next_time+20);/*not recurring*/
	
	assert(SchSize(new_sched) == 2);
	
	SchRemove(new_sched, new_task2);
	
	assert(SchSize(new_sched) == 1);
	
	(void)new_task;
	
	SchDestroy(new_sched);
	
	puts("add remove done");

}
void UnitestRunStop(void)
{
	sch_t * new_sched = SchCreate();
	guid_t new_task;
	guid_t new_task2;
	guid_t stop_task;
	time_t period = 3 ; /*5 sec */
	time_t next_time = time(NULL);


	
	new_task = SchAdd(new_sched, PrintRecurring, NULL, period, next_time);
	assert(SchSize(new_sched) == 1);
	

	new_task2 = SchAdd(new_sched, PrintSomething, NULL, 0, next_time);/*not recurring*/
	
	stop_task = SchAdd(new_sched,CallStop, new_sched, 10, next_time);
	
	assert(SchSize(new_sched) == 3);
	
	SchRun(new_sched);
	
	(void)stop_task;
	(void)new_task;
	(void)new_task2;
	
	
	SchDestroy(new_sched);
	
	puts("run stop done");


}


int PrintSomething(void *params)
{
	(void)params;
	puts("i print");
	return 0;
}

int CallStop(void *params)
{
	SchStop((sch_t*)params);
	return 0;
}


int PrintRecurring(void *params)
{
	(void)params;
	puts("i print rec");
	return 0;
}
