#include "scheduler.h"
#include "uid.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


int TestPrint1Min(void *params)
{
  
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  printf ( "Current local time and date: %s", asctime (timeinfo) );


 
    
    return 0;
}

int StopMe(void *params)
{
	if(access("exit_file", F_OK)!= -1)
		{
	   
		    SchStop((sch_t *)params);    
	  }
	  
	  return 0;
}

void SchedulerUnitTest(void)
{
    time_t current_time;
    guid_t tasks[10] = {0};
    sch_t *my_sched = SchCreate();

    assert (NULL != my_sched);
   assert (1 == SchIsEmpty(my_sched));
    assert (0 == SchSize(my_sched));
    time(&current_time);
    tasks[0] = SchAdd(my_sched, TestPrint1Min, NULL, 0, current_time+2);

     assert (1 == SchSize(my_sched));
    assert (0 == SchIsEmpty(my_sched));
   
    
  SchRemove(my_sched, tasks[0]);
    assert (1 == SchIsEmpty(my_sched));
    assert (0 == SchSize(my_sched));
    
    tasks[0] = g_bad_uid;
    
    tasks[0] = SchAdd(my_sched, TestPrint1Min, NULL, 0, current_time+10);
    
    tasks[1] = SchAdd(my_sched, TestPrint1Min, NULL, 3, current_time+3);
    
    tasks[2] = SchAdd(my_sched, StopMe, my_sched, 2, current_time+2);
    
    tasks[3] = SchAdd(my_sched, TestPrint1Min, NULL, 0, current_time+5);
    
    assert(SchSize(my_sched) == 4);
    
   SchRemove(my_sched, tasks[3]);
    
    assert(SchSize(my_sched) == 3);
    
    
    tasks[3] = SchAdd(my_sched, TestPrint1Min, NULL, 0, current_time+22);
    
    
    printf("sheduler ran %lu tasks \n",SchRun(my_sched));
    

    
    SchDestroy(my_sched);
    
}
int main()
{
    puts("!!!!important!!!!");
    puts("to stop the program, create a file named exit_file in the program's folder");
    SchedulerUnitTest();
    
    return EXIT_SUCCESS;
}


