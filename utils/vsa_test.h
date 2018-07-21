#include "vsa.h"
#include <stdio.h>
#include <stdlib.h>


void unitestinit(void);
void unitestalloc(void);
void unitestfree(void);
void unitestcountfree(void);
void integrationtest(void);

int main()
{
	unitestinit();
	/*unitestalloc();
	unitestfree();
	unitestcountfree();
	integrationtest();*/
	
	return EXIT_SUCCESS;
}

void unitestinit(void)
{
	void *memory = malloc(1000);
	void *memory2 = malloc(100);
	vsa_t *new_vsa = VsaInit(&memory, 1000);
	vsa_t *new_vsa2 = VsaInit(&memory2, 100);
	
	assert(&new_vsa == &memory);
	
	assert(&new_vsa2 == &memory2);
	
	free(memory);
	free(memory2);
	puts("passed init");
}

void unitestalloc(void)
{
	void *memory = malloc(1000);
	
	vsa_t *new_vsa = VsaInit(&memory, 1000);
	
	assert(&new_vsa == &memory);
	
	void *allocated_memory = VsaAlloc(&new_vsa, 200);
	
	void *allocated_memory2 = VsaAlloc(&new_vsa, 700);
	
	void *allocated_memory3 = VsaAlloc(&new_vsa, 200);
	
	assert(&allocated_memory == &memory+16+16); /*vsa struct is, segment struct is 16*/
	
	assert(&allocated_memory2 == &memory+16+16+200); 
	
	assert(&allocated_memory3 == NULL); /*wasnt supposed to work*/
	
	free(memory);
	
	puts("passed alloc");
}

void unitestfree(void)
{
	void *memory = malloc(1000);
	void *allocated_memory_all = NULL;
	void *allocated_memory = NULL;
	void *allocated_memory2 = NULL;
	void *allocated_memory3 = NULL;
	
	vsa_t *new_vsa = VsaInit(&memory, 1000);
	
	assert(&new_vsa == &memory);
	
	allocated_memory = VsaAlloc(&new_vsa, 200);
	
	allocated_memory2 = VsaAlloc(&new_vsa, 700);
	
	allocated_memory3 = VsaAlloc(&new_vsa, 200);
	
	assert(&allocated_memory == &memory+16+16); /*vsa struct is, segment struct is 16*/
	
	assert(&allocated_memory2 == &memory+16+16+200); 
	
	assert(&allocated_memory3 == NULL); /*wasnt supposed to work*/
	
	VsaFree(&allocated_memory2);
	
	allocated_memory3 = VsaAlloc(&new_vsa, 200);
	
	assert(&allocated_memory3 == &memory+16+16+200); 
	
	VsaFree(&allocated_memory);
	VsaFree(&allocated_memory3);
	
	allocated_memory_all = VsaAlloc(&new_vsa, 1000);
	assert(&allocated_memory_all == &memory+16+16); /*vsa struct is, segment struct is 16*/
	
	free(memory);
	
	puts("passed free");

}

void unitestcountfree(void)
{


}

void integrationtest(void)
{


}




