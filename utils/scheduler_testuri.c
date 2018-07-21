#include "scheduler.h"
#include "p_queue.h" /* funcs declarations*/
#include "task.h"
#include <stdlib.h> 	 /* for malloc, free  */
#include <assert.h>		 /* for asserts 	  */
#include <time.h>		 /* for difftime	  */
#include <unistd.h>		 /* for sleep		  */
#include <stdio.h>


static int CallStop(void *params)
{
	SchStop(params);
	puts("in call stop");	

	return 0;
}

static int PrintBoomBoom(void *params)
{
	int i = 0;
	
	for(i = 0; i < *(int*)params; ++i)
	{
		puts("Boom Boom Medabrim PakaPaka :)");
	}
	return 0;
}

static int PrintTime(void* somthing)
{
	time_t rawtime;
	struct tm * timeinfo;
	
	(void)somthing;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	printf ( "Current local time and date: %s", asctime (timeinfo) );

	return 0;
}


/*sch_t *SchCreate(void)*/
void SchCreateAndDestroyUritest(void)
{
	sch_t *new_sch = NULL;

	new_sch = SchCreate();

	assert(NULL != new_sch);
	assert(1 == SchIsEmpty(new_sch));
	assert(0 == SchSize(new_sch));

	SchDestroy(new_sch);
	puts("CreateAndDestroy... check!");	
}

/* Adds function as task to scheduler. Returns generated uid /
guid_t SchAdd(  sch_t *sch, 
				task_func_t task_func, 	
				void *params, 
				time_t period, 
				time_t next_time)*/
void SchAddUritest(void)
{
	sch_t *new_sch = NULL;
	guid_t task_uid1 = g_bad_uid;
	guid_t task_uid2 = g_bad_uid;
	
new_sch = SchCreate();

	assert(NULL != new_sch);
	assert(1 == SchIsEmpty(new_sch));
	assert(0 == SchSize(new_sch));

	task_uid1 = SchAdd(new_sch, PrintTime, NULL, 0, time(NULL) +30);
	assert(1 != UIDIsBad(task_uid1));
	assert(0 == SchIsEmpty(new_sch));
	assert(1 == SchSize(new_sch));

	task_uid2 = SchAdd(new_sch, PrintTime, NULL, 0, time(NULL) +30);
	assert(1 != UIDIsBad(task_uid2));
	assert(1 != UIDIsSame(task_uid1, task_uid2));
	assert(0 == SchIsEmpty(new_sch));
	assert(2 == SchSize(new_sch));

	SchDestroy(new_sch);
	puts("Add... check!");	
}

/*fail if queue is empty, fail if task not exist, fail when recieving bad uid*/
/* Receives task uid and removes it from scheduler, 
sch_status_t SchRemove(sch_t *sch, guid_t uid)  */
void SchRemoveUritest(void)
{
	sch_t *new_sch = NULL;
	guid_t task_uid1 = g_bad_uid;
	guid_t task_uid2 = g_bad_uid;

	new_sch = SchCreate();

	task_uid1 = SchAdd(new_sch, PrintTime, NULL, 0, time(NULL) +30);
	task_uid2 = SchAdd(new_sch, PrintTime, NULL, 0, time(NULL) +60);

	assert(1 != UIDIsBad(task_uid2));
	assert(1 != UIDIsBad(task_uid2));
	assert(1 != UIDIsSame(task_uid1, task_uid2));
	assert(2 == SchSize(new_sch));

	assert(0 == SchRemove(new_sch, task_uid1));
	assert(1 == SchSize(new_sch));

	assert(3 == SchRemove(new_sch, g_bad_uid));
	assert(1 == SchSize(new_sch));

	assert(0 == SchRemove(new_sch, task_uid2));
	assert(0 == SchSize(new_sch));

	SchDestroy(new_sch);
	puts("Remove... check!");	
}

/* Starts sheduler, returns how many task ran /
size_t SchRun(sch_t *sch);*/
void SchRunNoRecurrentUritest(void)
{
	sch_t *new_sch = NULL;

	new_sch = SchCreate();
	
	SchAdd(new_sch, PrintTime, NULL, 0, time(NULL) +3);
	SchAdd(new_sch, PrintTime, NULL, 0, time(NULL) +5);
	SchAdd(new_sch, PrintTime, NULL, 0, time(NULL) +20);
	
	SchRun(new_sch);
	
	SchDestroy(new_sch);
	puts("RUN... FINISHED");	
}

void SchRunRecurrentAndStopUritest(void)
{
	sch_t *new_sch = NULL;
	int params = 1;
	
	new_sch = SchCreate();
	
	SchAdd(new_sch, PrintBoomBoom, &params, 2, time(NULL));
	SchAdd(new_sch, PrintTime, NULL, 0, time(NULL) +5);
	SchAdd(new_sch, PrintTime, NULL, 0, time(NULL) +10);
	SchAdd(new_sch, CallStop, new_sch, 0, time(NULL) +11);
	SchRun(new_sch);
	
	SchDestroy(new_sch);
	puts("RUN + RECURRENT... FINISHED");	
}
int main()
{
	SchCreateAndDestroyUritest();
	SchAddUritest();
	SchRemoveUritest();
	/*SchRunNoRecurrentUritest();*/
	SchRunRecurrentAndStopUritest();
	
	return EXIT_SUCCESS;
}
