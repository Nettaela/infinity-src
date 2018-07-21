#include "scheduler.h"
#include <assert.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h> /* for using sleep */


static void PrintColorMsg(char* msg, int color);


void TestCreate(void)
{
    sch_t *sch = SchCreate();
    
    PrintColorMsg("create test started..", 6);
    assert(sch);
    assert(SchIsEmpty(sch));
    assert(SchSize(sch) == 0);
    
    SchDestroy(sch);
    sch = NULL;
}

static int PrintString(void* str)
{
    puts(str);
    
    return 0;
}

static int PrintCountDown(void* seconds)
{
    int sec_left = 0;
    
    sec_left = *(int*)seconds;
    putchar(sec_left + 48);
    putchar('\n');
    *(int*)seconds = sec_left - 1;
    return 0;
}

static int StopShd(void* sch)
{
	SchStop(sch);
	
	return 0;
}

void TestAdd(void) 
{
    struct timeval time2print = {0};
    guid_t uid1 = g_bad_uid;
    guid_t uid2 = g_bad_uid;
    sch_t *sch = SchCreate();
    
    PrintColorMsg("add test started..", 6);
    
    gettimeofday(&time2print, NULL);   
    uid1 = SchAdd(sch, &PrintString, NULL, 5, time2print.tv_sec + 10);
    assert(!SchIsEmpty(sch));
    assert(SchSize(sch) == 1);
    
    uid2 = SchAdd(sch, &PrintString, NULL, 15, time2print.tv_sec + 15);
    assert(!SchIsEmpty(sch));
    assert(SchSize(sch) == 2);
    
    assert(!UIDIsBad(uid1));
    assert(!UIDIsBad(uid2));
    assert(!UIDIsSame(uid1, uid2));

    SchDestroy(sch);
    sch = NULL;  
}

void TestRemove(void)
{
	struct timeval time2print = {0};
    guid_t uid1 = g_bad_uid;
    guid_t uid2 = g_bad_uid;
    sch_t *sch = SchCreate();
    
    PrintColorMsg("remove test started..", 6);
    gettimeofday(&time2print, NULL);   
    uid1 = SchAdd(sch, &PrintString, NULL, 5, time2print.tv_sec + 10);    
    uid2 = SchAdd(sch, &PrintString, NULL, 15, time2print.tv_sec + 15);
	
	assert(SchRemove(sch, uid1) == SUCCESS);
	assert(!SchIsEmpty(sch));
	assert(SchSize(sch) == 1);
	
	assert(SchRemove(sch, uid1) == SCH_BAD_UID); /* PQueueEraseMatching should return data to free or null for not found */
	assert(!SchIsEmpty(sch));
	assert(SchSize(sch) == 1);

	assert(SchRemove(sch, uid2) == SUCCESS);
	assert(SchIsEmpty(sch));
	assert(SchSize(sch) == 0);

	assert(SchRemove(sch, uid2) == EMPTY_QUEUE);
	assert(SchIsEmpty(sch));
	assert(SchSize(sch) == 0);

    SchDestroy(sch);
    sch = NULL;  

}


void TestRun(void)
{
	struct timeval time2print = {0};
    guid_t uid1 = g_bad_uid;
    guid_t uid2 = g_bad_uid;
    guid_t uid3 = g_bad_uid;
    sch_t *sch = SchCreate();
    int count_down = 5;
    
    PrintColorMsg("run test started..", 6);
    
    gettimeofday(&time2print, NULL);   
    uid1 = SchAdd(sch, &PrintString, "this should print after 1 sec", 0, time2print.tv_sec + 1);    
    uid2 = SchAdd(sch, &PrintString, "this should print after 2 sec", 0, time2print.tv_sec + 2);
    assert(SchSize(sch) == 2);
    
	SchRun(sch);
	assert(SchSize(sch) == 0);
	
	gettimeofday(&time2print, NULL);   
	uid1 = SchAdd(sch, &PrintString, "count down will start now..", 0, time2print.tv_sec + 1);
	uid2 = SchAdd(sch, &PrintCountDown, &count_down, 1, time2print.tv_sec + 2);
	uid3 = SchAdd(sch, &StopShd, sch, 0, time2print.tv_sec + 5);
	
    assert(!UIDIsBad(uid1));
    assert(!UIDIsBad(uid2));
    assert(!UIDIsBad(uid3));
	
	assert(SchSize(sch) == 3);
	
	SchRun(sch);

	assert(SchSize(sch) == 1);
	
	gettimeofday(&time2print, NULL);
	uid3 = SchAdd(sch, &StopShd, sch, 0, time2print.tv_sec + 5);
	PrintColorMsg("stoped!", 1);
	PrintColorMsg("should continue from the same place in 3 seconds..", 6);
	sleep(3);
	SchRun(sch);
	
    SchDestroy(sch);
    sch = NULL;  
}


static void PrintColorMsg(char* msg, int color)
{
    char color_str[] = "echo \"$(tput setaf 3)\"";
    
    system("echo \"$(tput bold)\"");
    color_str[19] = color + 48;
    system(color_str);
    puts(msg);
    system("echo \"$(tput sgr0)\"");
}

int main()
{
    /*TestCreate();
    TestAdd(); 
	TestRemove();*/
    TestRun();
    
    PrintColorMsg("YESSSSSSS!!!! Thats a hell of a schduler you got there!", 3);

    
    return EXIT_SUCCESS;
}
