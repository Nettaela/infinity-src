#ifndef TASK_H
#define TASK_H

#include "uid.h"

typedef struct task task_t;	
typedef enum task_status {TASK_SUCCESS = 0, TASK_FUNC_FAIL = 1,
					 TASK_NOT_EXISTS = 2, TASK_BAD_UID = 3} task_status_t;
					 
/*returns EXIT_SUCCESS or EXIT_FAILURE*/										
typedef int (*task_func_t)(void *params);


task_t *TaskCreate(task_func_t task_func, void *params, time_t period, 
														time_t next_time);
/*Removes a task*/
void TaskDestroy(task_t *task);

/*Gets pointer to a task and returns its uid*/
guid_t TaskGetUid(task_t *task);

/*The sch uses this function to run the task, returns success or the relevant fail*/
task_status_t TaskRunTask(task_t *task);

/*Checks if the tasks are the same and returns 1 for same or 0 for not*/
int TaskIsSame(task_t *task1, task_t *task2, void *params);

/*Returns the next time of the task*/
time_t TaskGetNextTime(task_t *task);

/*Reschedule the next time in recurring tasks*/
task_t *TaskUpdateNextTime(task_t *task);

/*Returns the period of the task*/
time_t TaskGetPeriod(task_t *task);

#endif

