
#include "task.h"
#include <stdlib.h>/*for malloc*/
#include <assert.h>/*for assert*/
#include <time.h>  /*for time*/
struct task 
{
	guid_t task_id;
	task_func_t task_func;
	void *params;
	time_t period; /*relative*/
	time_t next_time; /*absolute*/
};

int PrintTask(void *params);

task_t *TaskCreate(task_func_t task_func, void *params, time_t period, 
														time_t next_time)
{
	task_t *new_task = (task_t*)malloc(sizeof(task_t));
	if(new_task == NULL)	
	{
		return NULL;
	}
	
	new_task->task_id = UIDCreate();
	if(UIDIsBad(new_task->task_id))
	{
		free(new_task);
		return NULL;
	}
	
	new_task->task_func = task_func;
	new_task->params = params;
	new_task->period = period;
	new_task->next_time = next_time;
	
	return new_task;
	
}

void TaskDestroy(task_t *task)
{
	assert(task != NULL);
	free(task);
	task = NULL;
}

guid_t TaskGetUid(task_t *task)
{
	assert(task != NULL);
	
	return task->task_id;
}

task_status_t TaskRunTask(task_t *task)
{
	if(task == NULL)
	{
		return TASK_NOT_EXISTS;
	}
	else if(UIDIsBad(TaskGetUid(task)))
	{
		return TASK_BAD_UID;
	}
	
	if((task->task_func)(task->params))/*failed task returns 1 according to convention*/
	{
		return TASK_FUNC_FAIL;
	}
	
		
	return TASK_SUCCESS;
}

int TaskIsSame(task_t *task1, task_t *task2, void *params)
{
	assert(task1 != NULL);
	assert(task2 != NULL);
	(void)params;
	
	return UIDIsSame(task1->task_id ,task2->task_id);
}

time_t TaskGetNextTime(task_t *task)
{
	assert(task != NULL);
	return task->next_time;	
}

task_t *TaskUpdateNextTime(task_t *task)
{/*when rescheduling reccurring*/
	assert(task != NULL);

	task->next_time = time(NULL) + (task->period);
	
	return task;
}

time_t TaskGetPeriod(task_t *task)
{
	assert(task != NULL);
	return task->period;		
}















