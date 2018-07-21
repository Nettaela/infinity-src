#include <stdlib.h> /* for malloc() */
#include <assert.h> 
#include <time.h> /* for time() */

#include "task.h" /*CR - these (our libraries) should come before the others*/
#include "uid.h"

struct task
{
	guid_t task_id;
	task_func_t task_f;
	void* params;
	time_t task_period;
	time_t task_next_time;
};

task_t *TaskCreate(task_func_t task_func, void *params, time_t period, 
														time_t next_time)
{
	task_t* task = NULL;
	
	assert(NULL != task_func);
	
	task = malloc(sizeof(task_t));
	if (NULL == task)
	{
		return NULL; 
	} 
	
	task->task_f = task_func;
	task->task_id = UIDCreate();
	task->params = params;
	task->task_period = period;
	task->task_next_time = next_time;

	return task; 
}
/*Removes a task*/
void TaskDestroy(task_t *task)
{
	assert(NULL != task);

	free(task);
}

/*Gets pointer to a task and returns its uid*/
guid_t TaskGetUid(task_t *task)
{
	assert(NULL != task);

	return task->task_id;
}

/*The sch uses this function to run the task, returns success or the relevant fail*/
task_status_t TaskRunTask(task_t *task)
{
	if (NULL == task)
	{
		return TASK_NOT_EXISTS; /* CR - u can also test if uid is bad*/
	}

	if (0 != (task->task_f(task->params)))
	{
		return TASK_FUNC_FAIL;
	}
	return TASK_SUCCESS;
	
}

/*Checks if the tasks are the same and returns success or the relevant fail*/
int TaskIsSame(task_t *task1, task_t *task2, void *params)
{
	(void)params;
	
	assert(NULL != task1);
	assert(NULL != task2);

	if (UIDIsSame(task1->task_id, task2->task_id))
	{
		return 1;
	}
	return 0;	
}

/*Returns the next time of the task*/
time_t TaskGetNextTime(task_t *task)
{
	assert(NULL != task);
	
	return task->task_next_time;
}

/*Returns the period of the task*/
time_t TaskGetPeriod(task_t *task)
{
	assert(NULL != task);

	return task->task_period;
}
/*Reschedule the next time in recurring tasks*/
task_t* TaskUpdateNextTime(task_t *task)
{
	assert(NULL != task);
	
	task->task_next_time = TaskGetPeriod(task) + time(NULL);
  
	return task;
}
