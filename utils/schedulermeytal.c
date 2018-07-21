#include "scheduler.h"
#include <stdlib.h>
#include <assert.h> /*CR - reasons*/
#include <time.h>
#define TIME_TO_SLEEP 2 /* CR after headers */
#include <unistd.h>


static int IsMatchUID(const void *task, void *params, const void *uid_to_match)
{
	guid_t uid = g_bad_uid;
	
	assert(NULL != task);
	assert(NULL != uid_to_match);
	
	uid = TaskGetUid((task_t*)task); 
	(void)params;

	return UIDIsSame(uid, *(guid_t*)uid_to_match);
}

static int IsErlier(void* task1, void* task2)
{
	time_t time1 = 0;
	time_t time2 = 0;
	
	assert(NULL != task1);
	assert(NULL != task2);
	
	time1 = TaskGetNextTime((task_t*)task1);
	time2 = TaskGetNextTime((task_t*)task2);
	
	return (difftime(time1, time2) < 0);
}

struct sch
{
	pqueue_t *pq;
	int exit_flag;
};

/* Returns scheduler */
sch_t *SchCreate(void)
{
	sch_t* sch = malloc(sizeof(sch_t));
	
	if (NULL == sch)
	{
		return NULL;
	}
		
	sch->pq = PQueueCreate(IsErlier);/*CR - check is pq is successful, if not, free sch*/
	sch->exit_flag = 0;
	
	return sch;
}

/* Destroys scheduler */
void SchDestroy(sch_t *sch)
{
	task_t* curr_task = NULL;
	
	assert(NULL != sch);
	assert(NULL != sch->pq);

	while (SchIsEmpty(sch) != 1)
	{
		curr_task = PQueueDequeue(sch->pq);
		TaskDestroy(curr_task);
	}
	PQueueDestroy(sch->pq);
	free(sch);
}

/* Adds function as task to scheduler. Returns generated uid */
guid_t SchAdd(sch_t *sch, task_func_t task_func, void *params, time_t period, 
														time_t next_time)
{
	task_t* new_task = NULL;
	
	assert(NULL != sch);
	assert(NULL != sch->pq);
	assert(NULL != task_func);
	
	new_task = TaskCreate(task_func, params, period, next_time);
	if (new_task == NULL)
	{
		return g_bad_uid;
	}	

	if (SCH_FAIL == PQueueEnqueue(sch->pq, new_task)) /* CR - if it failed, free/destroy task?*/
	{
		return g_bad_uid;
	}
	
	return TaskGetUid(new_task);
	 
}
/*fail if queue is empty, fail if task not exist, fail when recieving bad uid*/
/* Receives task uid and removes it from scheduler,  */
sch_status_t SchRemove(sch_t *sch, guid_t uid)
{
	task_t *match_task = NULL;

	assert(1 != UIDIsBad(uid)); /* CR why assert and not if, we have an error code for it*/
	assert(NULL != sch);
	assert(NULL != sch->pq);
	
	if (SchIsEmpty(sch))
	{
		return EMPTY_QUEUE; 
	}
	match_task = (task_t*)PQueueEraseMatching(sch->pq, IsMatchUID, NULL, &uid);
	
	if (match_task == NULL)
	{
		return SCH_BAD_UID;
	}
	TaskDestroy(match_task);
	return SUCCESS;	
}

/* Starts sheduler, returns how many tasks ran */
size_t SchRun(sch_t *sch)
{
	size_t tasks_ran = 0;
	task_t* pq_peek = NULL;
	time_t time_to_next_task = 0;

	assert(NULL != sch);
	assert(NULL != sch->pq);
	
	sch->exit_flag = 0; 
	while ((SchIsEmpty(sch) == 0) && (sch->exit_flag == 0))
	{
		pq_peek = PQueuePeek(sch->pq);
		/* if next task is due in a long time we put on sleep mode */
		time_to_next_task = difftime(TaskGetNextTime(pq_peek), time(NULL));
		/* if next task is not due to come , prog. goes to sleep */
		if (time_to_next_task > 2)
		{
			sleep(time_to_next_task - 1);
		}

		if (0 >= time_to_next_task)
		{
			TaskRunTask(pq_peek);
			PQueueDequeue(sch->pq);
		
			if (TaskGetPeriod(pq_peek) > 0)
			{
				TaskUpdateNextTime(pq_peek);
				PQueueEnqueue(sch->pq, pq_peek);	
			}
			else
			{
				TaskDestroy(pq_peek);
			}
		}
		++tasks_ran;
	}
	
	return tasks_ran;
}

void SchStop(sch_t *sch)
{
	assert(NULL != sch);

	sch->exit_flag = 1;
}

/* Returns number of loaded tasks in scheduler */
size_t SchSize(sch_t *sch)
{
	assert(NULL != sch);
	assert(NULL != sch->pq);

	return PQueueSize(sch->pq);
}

/* Returns 1 if scheduler is empty, 0 otherwise */
int SchIsEmpty(sch_t *sch)
{
	assert(NULL != sch);
	assert(NULL != sch->pq);

	if (1 == PQueueIsEmpty(sch->pq))
	{
		return 1;
	}

	return 0; 	
}

