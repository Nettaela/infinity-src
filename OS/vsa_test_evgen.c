#include "vsa.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> /* for strcpy, strcmp */

#define BUF_SZ 1000
#define SMALL_SEG_SZ 5 
#define BIG_SEG_SZ BUF_SZ + 1
#define ALIGNMENT sizeof(long double)

/* this is a black box test made by Evgeny */
/* magic numbers should be checked inside the program */

void UniTestCreate(void) /* depnends on CountFree */
{
	char *buff = (char*)malloc(BUF_SZ);
	vsa_t *vsa = VsaInit(buff, BUF_SZ);
	
	assert(vsa);
	
	printf("vsa created,\nbuffer size is: %d\navaileble space is: %lu\n------------------\n\n",
			 BUF_SZ, VsaCountFree(vsa));
	
	assert(VsaCountFree(vsa) > BUF_SZ/2); /* expecting half the space to be free */
	free(buff);
}

void UniTestAlloc(void)
{
	char *buff = (char*)malloc(BUF_SZ);
	vsa_t *vsa = VsaInit(buff, BUF_SZ);
	char *test_str1 = NULL;
	char *test_str2 = NULL;	

	test_str1 = VsaAlloc(vsa, SMALL_SEG_SZ);
	assert(test_str1);
	strcpy(test_str1, "1234");
	assert(strcmp("1234", test_str1) == 0);
	assert(((size_t)test_str1 % ALIGNMENT) == 0); /* check alighnment */
	printf("vsa created,\nallocated: %d\navailable space is: %lu\n------------------\n\n", SMALL_SEG_SZ, VsaCountFree(vsa));
	
	test_str2 = VsaAlloc(vsa, BIG_SEG_SZ - SMALL_SEG_SZ); /* should fail */
	assert(!test_str2);
	test_str2 = VsaAlloc(vsa, SMALL_SEG_SZ);
	strcpy(test_str2, "6789");
	assert(strcmp("6789", test_str2) == 0);
	strcpy(test_str1, "54321");
	assert(strcmp("54321", test_str1) == 0);
	assert(strcmp("6789", test_str2) == 0);
	assert(((size_t)test_str1 % ALIGNMENT) == 0); /* check alighnment */
	printf("vsa created,\nallocated: %d\navailable space is: %lu\n------------------\n\n", SMALL_SEG_SZ, VsaCountFree(vsa));
	
	
	free(buff);
}

void UniTestFree(void)
{
	char *buff = (char*)malloc(BUF_SZ);
	vsa_t *vsa = VsaInit(buff, BUF_SZ);
	char *test_str1 = NULL;
	char *test_str2 = NULL;	
	char *test_str3 = NULL;	
	char *test_str4= NULL;	
	char *alloced[100] = {NULL};
	size_t i = 0;	
	
	test_str1 = VsaAlloc(vsa, 200);
	printf("vsa created,\nallocated: %d\navaileble space is: %lu\n------------------\n\n", 200, VsaCountFree(vsa));
	test_str2 = VsaAlloc(vsa, 200);
	printf("allocated: %d\navaileble space is: %lu\n------------------\n\n", 200, VsaCountFree(vsa));
	strcpy(test_str1, "54321");
	strcpy(test_str2, "6789");
	
	test_str3 = VsaAlloc(vsa, 600); /* should fail */
	assert(!test_str3);
	
	VsaFree(test_str1);
	printf("freed: %d\navaileble space is: %lu\n------------------\n\n", 200, VsaCountFree(vsa));
	
	VsaFree(test_str2);
	printf("freed: %d\navaileble space is: %lu\n------------------\n\n", 200, VsaCountFree(vsa));	
	test_str3 = VsaAlloc(vsa, 600); /* should succeed */
	printf("allocated: %d\navaileble space is: %lu\n------------------\n\n", 600, VsaCountFree(vsa));
	assert(test_str3);
	
	while (NULL != (alloced[i] = VsaAlloc(vsa, 10)))
	{
		strcpy(alloced[i], "0123456789");
		printf("allocated: %d\navaileble space is: %lu\n------------------\n\n", 10, VsaCountFree(vsa));
		++i;
	}
	
	VsaFree(alloced[4]);
	printf("freed: %d\navaileble space is: %lu\n------------------\n\n", 10, VsaCountFree(vsa));
	alloced[4] = VsaAlloc(vsa, 10);
	printf("allocated: %d\navaileble space is: %lu\n------------------\n\n", 10, VsaCountFree(vsa));
	strcpy(alloced[4], "9876543210");
	assert(strcmp("9876543210", alloced[4]) == 0);
	VsaFree(alloced[7]);
	printf("freed (to test merging): %d\navaileble space is: %lu\n------------------\n\n", 10, VsaCountFree(vsa));
	VsaFree(alloced[8]);
	printf("freed near previous: %d\navaileble space is: %lu\n------------------\n\n", 10, VsaCountFree(vsa));
	VsaFree(alloced[9]);
	printf("freed near previous: %d\navaileble space is: %lu\n------------------\n\n", 10, VsaCountFree(vsa));
	test_str4 = VsaAlloc(vsa, 40);
	printf("allocated: %d\navaileble space is: %lu\n------------------\n\n", 40, VsaCountFree(vsa));

	strcpy(test_str4, "9876543210abcdefghijklmnopqrstuvwzyz");
	assert(strcmp("9876543210abcdefghijklmnopqrstuvwzyz", test_str4) == 0);
	free(buff);
}

int main()
{
	UniTestCreate();
	UniTestAlloc();
	UniTestFree();
	
	puts("KKKKKKKAAAAAAAAAAAAABBBBBBBBBBUUUUUUUUUUUUUMMMMMMMMMMMMMMMM\n");
	puts("now dont forget to visit our dear friend valgrind and look for the the magic (numbers)");
	return EXIT_SUCCESS;
}
