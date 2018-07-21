#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "p_queue.h"
#define UNUSED(x) (void)(x)  


static int IsSortedStr(void *str1, void *str2)
{
    return (strcmp(str1, str2) <= 0);
}

void TestCreate(void) /* basic is_empty create and size */
{
    pqueue_t *pq = PQueueCreate(IsSortedStr);
    
    assert(pq);
    assert(PQueueIsEmpty(pq));
    assert(PQueueSize(pq) == 0);
    
    PQueueDestroy(pq);
    pq = NULL;
    
    puts("Create test passed!");
}

void TestEnqueue(void) /* testing also is_empty, size, peek */
{
    pqueue_t *pq = PQueueCreate(IsSortedStr);
    
    char* name1 = "evgeny";
	char* name2 = "uri";
	char* name3 = "neta";
	char* name4 = "doron";
	char* name5 = "tamar";
	
    assert(PQueueEnqueue(pq, name1) == 0);
    assert(PQueuePeek(pq) == name1);
    assert(!PQueueIsEmpty(pq));
    assert(PQueueSize(pq) == 1);
    
    PQueueEnqueue(pq, name2);
    PQueueEnqueue(pq, name3);
    assert(PQueuePeek(pq) == name1);
    
    PQueueEnqueue(pq, name4);
    PQueueEnqueue(pq, name5);
    assert(!PQueueIsEmpty(pq));
    assert(PQueueSize(pq) == 5);
    
    
    PQueueDestroy(pq);
    pq = NULL;
    
    puts("Enqueue test passed!");
}

void TestDequeue(void) 
{
    pqueue_t *pq = PQueueCreate(IsSortedStr);
    
    char* name1 = "evgeny";
	char* name2 = "uri";
	char* name3 = "neta";
	char* name4 = "doron";
	char* name5 = "tamar";
	
    PQueueEnqueue(pq, name1);    
    PQueueEnqueue(pq, name2);
    PQueueEnqueue(pq, name3);
    PQueueEnqueue(pq, name4);
    PQueueEnqueue(pq, name5);
    
    assert(PQueueDequeue(pq) == name4);	/* doron */
    assert(PQueueDequeue(pq) == name1);	/* evgeny */
    assert(PQueueSize(pq) == 3);
    assert(PQueuePeek(pq) == name3);	/* neta */
    
    assert(PQueueDequeue(pq) == name3);	/* neta */
    assert(PQueueDequeue(pq) == name5);	/* tamar */
    assert(PQueuePeek(pq) == name2);	/* uri */
    
    assert(PQueueDequeue(pq) == name2);	/* uri */
    assert(PQueueIsEmpty(pq));
    assert(PQueueSize(pq) == 0);
    
    PQueueDestroy(pq);
    pq = NULL;
    
    puts("Dequeue test passed!");
}

void TestClear(void) 
{
    pqueue_t *pq = PQueueCreate(IsSortedStr);
    
    char* name1 = "evgeny";
	char* name2 = "uri";
	char* name3 = "neta";
	char* name4 = "doron";
	char* name5 = "tamar";
	
    PQueueEnqueue(pq, name1);    
    PQueueEnqueue(pq, name2);
    PQueueEnqueue(pq, name3);
    PQueueEnqueue(pq, name4);
    PQueueEnqueue(pq, name5);
    
    PQueueClear(pq);
    
    assert(pq);
    assert(PQueueIsEmpty(pq));
    assert(PQueueSize(pq) == 0);
    
    PQueueDestroy(pq);
    pq = NULL;
    
    puts("Clear test passed!");
}

static int IsMatch(const void *data, void *params, const void *data_to_match)
{
    UNUSED(params);
    return !strcmp(data, data_to_match);
}

void TestEraseMatching(void) 
{
    pqueue_t *pq = PQueueCreate(IsSortedStr);
    
    char* name1 = "evgeny";
	char* name2 = "uri";
	char* name3 = "neta";
	char* name4 = "doron";
	char* name5 = "tamar";
	char* name6 = "evgeny";
	
    PQueueEnqueue(pq, name1);    
    PQueueEnqueue(pq, name2);
    PQueueEnqueue(pq, name3);
    PQueueEnqueue(pq, name4);
    PQueueEnqueue(pq, name5);
    PQueueEnqueue(pq, name6);
    
	PQueueEraseMatching(pq, &IsMatch, NULL, "doron"); 
	assert(PQueueSize(pq) == 5);
    PQueueEraseMatching(pq, &IsMatch, NULL, "evgeny"); /* erase 2 instances */
	assert(PQueueSize(pq) == 3);
	PQueueEraseMatching(pq, &IsMatch, NULL, "doron"); /* no match */
	assert(PQueueSize(pq) == 3);
	PQueueEraseMatching(pq, &IsMatch, NULL, "tamar");
	PQueueEraseMatching(pq, &IsMatch, NULL, "uri");
	PQueueEraseMatching(pq, &IsMatch, NULL, "neta");

    assert(pq);
    assert(PQueueIsEmpty(pq));
    assert(PQueueSize(pq) == 0);
    
    PQueueDestroy(pq);
    pq = NULL;
    
    puts("EraseMatching test passed!");
}

int main()
{
    TestCreate();
    TestEnqueue();
    TestDequeue();
    TestClear();
	TestEraseMatching();
    
    puts("peace of cake");
    return EXIT_SUCCESS;
}

