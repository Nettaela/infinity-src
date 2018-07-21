#include "scheduler.h"
#include "p_queue.h"
#include "task.h"
#include <stdlib.h> /*for malloc*/
#include <stdio.h>  /*for null*/
#include <assert.h> /*for assert*/
#include <time.h>   /*for time*/
#include <unistd.h> /*for sleep*/

struct sch 
{
	pqueue_t * pq;
	int exit_flag;
};


int IsBefore(void *data1, void *data2);
int FindIsMatch(const void *data, void *params, const void *data_to_match);

sch_t *SchCreate(void)
{
	pqueue_t *new_pq = NULL;
	sch_t *new_scheduler = (sch_t *)malloc(sizeof(sch_t));
	if(new_scheduler == NULL)
	{
		return NULL;
	}
	puts("print inside create");
	new_pq = PQueueCreate(IsBefore);
	if(new_pq == NULL)
	{
		free(new_scheduler);
		return NULL;
	}
	
	new_scheduler->pq = new_pq;
	new_scheduler->exit_flag = 0;
	
	return new_scheduler;
}

void SchDestroy(sch_t *sch)
{
	task_t *data_to_remove = NULL;
	assert(sch != NULL);
	assert(sch->pq != NULL);
	
	while(!SchIsEmpty(sch))
	{
		data_to_remove = PQueueDequeue(sch->pq);
		TaskDestroy(data_to_remove);
	}	
	PQueueDestroy(sch->pq);
	free(sch);
	sch = NULL;
}

guid_t SchAdd(sch_t *sch, task_func_t task_func, void *params, time_t period, 
														time_t next_time)
{
	task_t *new_task = NULL;
	
	assert(sch != NULL);
	assert(sch->pq != NULL);
		
	new_task = TaskCreate(task_func,params,period,next_time);
	if(new_task == NULL)
	{
		return g_bad_uid;
	}
	
	if(PQueueEnqueue(sch->pq, new_task) != 0)
	{
		TaskDestroy(new_task);
		return g_bad_uid;
	}
		
	return TaskGetUid(new_task);
}

size_t SchSize(sch_t *sch)
{
	assert(sch != NULL);
	assert(sch->pq != NULL);
	
	return PQueueSize(sch->pq);
}

int SchIsEmpty(sch_t *sch)
{
	assert(sch != NULL);
	assert(sch->pq != NULL);
	
	return PQueueIsEmpty(sch->pq);
}

sch_status_t SchRemove(sch_t *sch, guid_t uid)
{	
	/*check uid is bad, check is empty, check uid not found - return bad uid*/
	void *data = NULL;

	assert(sch != NULL);

	if(SchIsEmpty(sch))
	{
		return EMPTY_QUEUE;
	}
	else if(UIDIsBad(uid))
	{
		return SCH_BAD_UID;
	}
	
	data = PQueueEraseMatching(sch->pq, FindIsMatch, NULL, &uid); 
	if(data == NULL)
	{
		return SCH_BAD_UID;
	}
	free(data);
	data = NULL;
	return SUCCESS;
}

size_t SchRun(sch_t *sch)
{
	size_t counter = 0;
	task_t* current_task = NULL;
	sch->exit_flag = 0;

	assert(sch->pq);
	assert(sch != NULL);
	
	while(!SchIsEmpty(sch) && sch->exit_flag == 0)
	{
		current_task = PQueuePeek(sch->pq);
		
		if(time(NULL) >= TaskGetNextTime(current_task))
		{
			TaskRunTask(current_task);
			++counter;
			current_task = PQueueDequeue(sch->pq);
			if(TaskGetPeriod(current_task) != 0)
			{
				PQueueEnqueue(sch->pq, TaskUpdateNextTime(current_task));			
			}
			else
			{
				TaskDestroy(current_task);
			}
		}
		else
		{
			sleep(TaskGetNextTime(current_task) - time(NULL));
		}
	}
	return counter;
}

void SchStop(sch_t *sch)
{
	assert(sch != NULL);
	sch->exit_flag = 1;

}

int FindIsMatch(const void *data, void *params, const void *data_to_match)
{
	(void)params;	
	return TaskIsSame((task_t*)data, (task_t*) data_to_match, NULL);
}

int IsBefore(void *task1, void *task2)
{
	double result = 0;
	time_t task1_next_time = TaskGetNextTime(task1);
	time_t task2_next_time = TaskGetNextTime(task2);
		
	result = difftime(task1_next_time, task2_next_time); /* if data1 is before data2, result is negative*/
	return (result < 0);
}
