#include "vsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void unitestinit(void);
void unitestalloc(void);
void unitestfree(void);
void unitestcountfree(void);
void integrationtest(void);

int main()
{
	unitestinit();
	unitestalloc();
	unitestfree();
	unitestcountfree();/*
	integrationtest();*/
	
	return EXIT_SUCCESS;
}

void unitestinit(void)
{
	void *memory = malloc(1000);
	void *memory2 = malloc(100);
	vsa_t *new_vsa = VsaInit(memory, 1000);
	vsa_t *new_vsa2 = VsaInit(memory2, 100);
	
	assert(new_vsa);
	assert(new_vsa2);
	
	free(memory);
	free(memory2);
	puts("---passed init---");
}

void unitestalloc(void)
{
	void *memory = malloc(3000);
	
	vsa_t *new_vsa = VsaInit(memory, 3000);
	void *allocated_memory2 =NULL;
	void *allocated_memory4 = NULL;
	void *allocated_memory3 = NULL;
	void *allocated_memory = VsaAlloc(new_vsa, 200);
	puts("---passed 1 alloc---");
	
	allocated_memory2 = VsaAlloc(new_vsa, 700);

	allocated_memory3 = VsaAlloc(new_vsa, 1000);
	puts("---alloc too big---");
	allocated_memory4 = VsaAlloc(new_vsa, 1500);
	
	assert(new_vsa);
	assert(allocated_memory);
	assert(allocated_memory2);
	assert(allocated_memory3);
	assert(allocated_memory4 == NULL);

	free(memory);
	
	puts("---passed allocs no merging---");
}

void unitestfree(void)
{
	void *memory = malloc(1000);
	void *allocated_memory_all = NULL;
	void *allocated_memory = NULL;
	void *allocated_memory2 = NULL;
	void *allocated_memory3 = NULL;
	
	vsa_t *new_vsa = VsaInit(memory, 1000);
	
	assert(new_vsa);
	
	allocated_memory = VsaAlloc(new_vsa, 200);
	assert(allocated_memory);
	puts("---1---");
		
	allocated_memory2 = VsaAlloc(new_vsa, 700);
	assert(allocated_memory2);
	puts("---2---");
	
	VsaFree(allocated_memory2);

	allocated_memory3 = VsaAlloc(new_vsa, 200);
	assert(allocated_memory3);
	puts("---3---");
	
	VsaFree(allocated_memory);
	VsaFree(allocated_memory3);
	
	allocated_memory_all = VsaAlloc(new_vsa, 500);
	assert(allocated_memory_all);
	puts("---4---");

	free(memory);
	
	puts("passed free");

}

void unitestcountfree(void)
{
	void *memory = malloc(1000);

	void *allocated_memory = NULL;
	void *allocated_memory2 = NULL;
	void *allocated_memory3 = NULL;
	
	vsa_t *new_vsa = VsaInit(memory, 1000);
	
	assert(new_vsa);
	
	allocated_memory = VsaAlloc(new_vsa, 200);
	assert(allocated_memory);
				puts("---1---");
	printf("first alloc free count:%lu \n",VsaCountFree(new_vsa));
		
		
	allocated_memory2 = VsaAlloc(new_vsa, 700);
	assert(allocated_memory2);
			puts("---2---");
	printf("second alloc free count:%lu \n",VsaCountFree(new_vsa));
	VsaFree(allocated_memory2);

	allocated_memory3 = VsaAlloc(new_vsa, 200);
	assert(allocated_memory3);
				puts("---3---");
	printf("third alloc (freed 2 and alloc'd 3) free count:%lu \n",VsaCountFree(new_vsa));
	VsaFree(allocated_memory);
	VsaFree(allocated_memory2);
	
	VsaFree(allocated_memory3);

	free(memory);
	
	puts("passed count free");

}

void integrationtest(void)
{


}




