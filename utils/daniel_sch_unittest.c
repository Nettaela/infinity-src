/*
		Scheduler Unit tests, by Daniel Gomon, RD-47, 2018 (c)

		HOW TO USE THIS TEST:
		--------------------
		
		Create an empty file "stop.txt" -outside- of parent directory.
		Run scheduler.
		Before scheduler ends (before timer reaches 30), move "stop.txt" to parent directory.
		Scheduler should stop.
		Remove "stop.txt" from parent directory to resume scheduler.
		
		NOTE:
		----
		Thie test does not use asserts.
*/
#include "scheduler.h"
#include "p_queue.h"
#include "uid.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>			/* sleep()	*/

enum {TRUE = 1, FALSE = 0};

int UserTask(void *uid_ptr)
{
	guid_t taskid = *(guid_t*)uid_ptr;
	printf("Executing task: %ld", taskid.time.tv_sec);
	printf("%ld", taskid.time.tv_usec);
	printf("%ld", taskid.counter);
	printf("%d\n", taskid.pid);
	return SUCCESS;
}

/* ------------------------------------------------------ */
int UserStop(void *sch_ptr)
{
	sch_t *sch = (sch_t*)sch_ptr;
	SchStop(sch);
	
	return SUCCESS;
}
/* ------------------------------------------------------ */
int UserListenStop(void *sch_ptr)
{
	sch_t *sch = (sch_t*)sch_ptr;
	FILE *stop = fopen("stop.txt", "r");
	puts ("...Listeninig to stop.txt");
	
	if (NULL != stop)
	{
		SchStop(sch);
		fclose(stop);
	}
	return SUCCESS;
}

/* ------------------------------------------------------ */
void SchedulerTests()
{
	time_t rawtime;
	struct tm *timeinfo;
	sch_t *mysch = SchCreate();	
	int tasks_counter = 0;
	guid_t listener_task;
	guid_t task1;
	guid_t task2;
	guid_t task3;
	guid_t stop_task1;
	guid_t stop_task2;
	
	time_t listener_time = time(NULL);
	time_t time1 = time(NULL)+3;
	time_t time2 = time(NULL)+6;
	time_t time3 = time(NULL)+10;
	time_t stop_time1 = time(NULL)+15;
	time_t stop_time2 = time(NULL)+30;
	
	
	listener_task = SchAdd(mysch, &UserListenStop, mysch, 2, listener_time);
	task1 = SchAdd(mysch, &UserTask, &task1, 0, time1);
	task2 = SchAdd(mysch, &UserTask, &task2, 7, time2);
	task3 = SchAdd(mysch, &UserTask, &task3, 0, time3);
	stop_task1 = SchAdd(mysch, &UserStop, mysch, 0, stop_time1);
	stop_task2 = SchAdd(mysch, &UserStop, mysch, 0, stop_time2);
	
	puts("\nStarting scheduler\nCreate file \"stop.txt\" in parent directory to pause.");
	puts("-----------------------------------------------------");
	tasks_counter = SchRun(mysch);

	printf("Counted %d tasks, including SchStop\n", tasks_counter);
	puts  ("-----------------------------------");
	puts("Second run...");
	
	while(1)
	{
		FILE *stop = fopen("stop.txt", "r");

		if (NULL == stop)
		{
			break;
		}
		sleep(1);
	}

	puts("Continuing scheduler \n");
	tasks_counter = SchRun(mysch);
	printf("Counted %d tasks, including SchStop", tasks_counter);
	puts  ("-----------------------------------");
	
	(void)time1;
	(void)time2;
	(void)time3;
	(void)stop_time1;
	(void)stop_time2;
	
	(void)task1;
	(void)task2;
	(void)task3;
	(void)stop_task1;
	(void)stop_task2;
	(void)listener_task;
	
	rawtime = time(NULL);
	timeinfo = localtime(&rawtime);
	printf("\nScheduler stopped at: %s\n",asctime(timeinfo));
	
	SchDestroy(mysch);
}



/* ------------------------------------------------------ */
int main()
{
	SchedulerTests();	
	
	
	return EXIT_SUCCESS;	
}
