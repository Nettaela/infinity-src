#include "uid.h"

#include <unistd.h>

#define MAX_PID 4194304 /*in 64 bit systems. 32768 in 32 bit*/

static int IsEqualCounter(size_t counter1 , size_t counter2);
static int IsEqualTime(struct timeval time1,struct timeval time2);
static int IsEqualPid(pid_t pid1, pid_t pid2);


guid_t g_bad_uid = {{0,0},0, (MAX_PID+1)};
/*
g_bad_uid.time.tv_sec = 0;
g_bad_uid.time.tv_usec = 0;*/
/*g_bad_uid.pid = MAX_PID + 1;*/

/* Create uid */  
guid_t UIDCreate(void)
{
	guid_t new_uid = {0};
	static size_t counter = 0;
	
	struct timeval time = {0};
	if(0 != gettimeofday(&time, NULL))
	{
		return g_bad_uid;
	}	
	new_uid.time = time; 
	new_uid.counter = ++counter;
	new_uid.pid = getpid();
	
	return new_uid;
}
	

/* Returns 1 if the same; Otherwise returns 0 */
int UIDIsSame(const guid_t uid1, const guid_t uid2)
{
	if(IsEqualCounter(uid1.counter, uid2.counter))
	{
		if(IsEqualTime(uid1.time, uid2.time))
		{
			if(IsEqualPid(uid1.pid, uid2.pid))
			{	
				return 1;
			}
			return 0;
		}
		return 0;
	}
	return 0;
}


/* Returns 1 if bad ID; Otherwise returns 0 */
int UIDIsBad(const guid_t uid)
{
	return UIDIsSame(uid, g_bad_uid); 
}

static int IsEqualCounter(size_t counter1 , size_t counter2)
{
	return (counter1 == counter2);
}

static int IsEqualTime(struct timeval time1,struct timeval time2)
{
	return ((time1.tv_sec == time2.tv_sec) && (time1.tv_usec == time2.tv_usec));
}

static int IsEqualPid(pid_t pid1, pid_t pid2)
{
	return (pid1 == pid2);
}

























