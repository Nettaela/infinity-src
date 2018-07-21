#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "uid.h"
#include "task.h"
#include "p_queue.h"


typedef struct sch sch_t;


typedef enum sch_status {SUCCESS = 0, SCH_FAIL = 1, EMPTY_QUEUE = 2,
												 SCH_BAD_UID = 3} sch_status_t;

/* Returns scheduler */
sch_t *SchCreate(void);

/* Destroys scheduler */
void SchDestroy(sch_t *sch);

/* Adds function as task to scheduler. Returns generated uid */
guid_t SchAdd(sch_t *sch, task_func_t task_func, void *params, time_t period, 
														time_t next_time);
/*fail if queue is empty, fail if task not exist, fail when recieving bad uid*/
/* Receives task uid and removes it from scheduler,  */
sch_status_t SchRemove(sch_t *sch, guid_t uid);

/* Starts sheduler, returns how many task ran. Recurring tasks will run imidiatly at the next run (each with its the priority) */
size_t SchRun(sch_t *sch);

/* Stops scheduler */
void SchStop(sch_t *sch);

/* Returns number of loaded tasks in scheduler */
size_t SchSize(sch_t *sch);

/* Returns 1 if scheduler is empty, 0 otherwise */

int SchIsEmpty(sch_t *sch);


#endif
