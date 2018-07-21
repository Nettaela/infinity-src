#ifndef UID_H
#define UID_H


#include <sys/time.h>  /*for using timeval structure*/
#include <sys/types.h>/*for using pid_t*/



typedef struct uid
{
	struct timeval time;
	size_t counter;
	pid_t pid;
} guid_t;


extern guid_t g_bad_uid;


/* Create uid */  
guid_t UIDCreate(void);


/* Returns 1 if the same; Otherwise returns 0 */
int UIDIsSame(const guid_t uid1, const guid_t uid2);


/* Returns 1 if bad ID; Otherwise returns 0 */
int UIDIsBad(const guid_t uid);


#endif


