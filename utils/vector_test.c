#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dyn_vec.h"


void SimpleUnitest(void);
void ComplexUnitest(void);
void OPTest(void);



int main()
{

	SimpleUnitest();
	ComplexUnitest();
	OPTest();
	return EXIT_SUCCESS;

}



void SimpleUnitest(void)
{
	int element = 2;
	int element2 = 4;
	int element3 = 8;
	size_t capacity = 2;
	dyn_vec_t * testvec = DynVecCreate(sizeof(int), capacity); /*immidiatly after, size should be the same as capacity*/
	
	/*if size if the same as capacity, how are we to know how many of the elements have been initialized?*/
	
	puts("---------simple test-------------");
	
	if(DynCapacity(testvec) != 2)
	{
		puts("capacity failed");
	}
	
	DynVecPushBack(testvec, &element);/*first one should doublt the capacity*/
	if(DynCapacity(testvec) != 4)
	{
		puts("capacity after push + reserve failed");
	}
	
	if(*(int*)(DynVecGetItemAddress(testvec, 2)) != element) /*element was pushed into the third place of the vector*/
	{
		puts("1 push failed (or get adress failed)");
	}
		
	if(DynVecSize(testvec) != 3)
	{
		puts("push or size failed");
	}
	
	DynVecPushBack(testvec, &element2);
	
	if(DynVecSize(testvec) != 4)
	{
		puts("push or size failed");
	}
	
	if(*(int*)(DynVecGetItemAddress(testvec, 3)) != element2) /*element was pushed into the third place of the vector*/
	{
		puts("2 push failed (or get adress failed)");
	}
	*(int*)(DynVecGetItemAddress(testvec, 0)) = element3;
	if(*(int*)(DynVecGetItemAddress(testvec, 0)) != element3) /*element was pushed into the third place of the vector*/
	{
		puts("value change using get adress failed)");
	}
	
	DynVecPopBack(testvec);
	
	if(DynVecSize(testvec) != 3)
	{
		puts("pop or size failed");
	}

	
	DynVecDestroy(testvec);
}
void ComplexUnitest(void)
{
	struct DateOfBirth
	{
		size_t day;
		size_t month;
		size_t year;
	};
	
	struct InFlt
	{
		int inti;
		float floati; 
	};
	
	/*initializing 5 structs of each kind*/
	struct InFlt inflt_struct1 = {146, 19.88};
	/*struct InFlt inflt_struct2 = {246, 123.88};
	struct InFlt inflt_struct3 = {316, 156.88};
	struct InFlt inflt_struct4 = {446, 132.88};
	struct InFlt inflt_struct5 = {556, 123.88};*/

	struct DateOfBirth date_struct1 = {85,35,178};	
	/*struct DateOfBirth date_struct2 = {65, 82,1988};	
	struct DateOfBirth date_struct3 = {3,4,1978};	
	struct DateOfBirth date_struct4 = {45,2,1948};	
	struct DateOfBirth date_struct5 = {98,15,1958};*/
		
	size_t capacity = 5;
	
	dyn_vec_t * testvec_date = DynVecCreate(sizeof(struct DateOfBirth), capacity);
	dyn_vec_t * testvec_inflt = DynVecCreate(sizeof(struct InFlt), capacity);
	/*cpacity and size are == 5*/
	puts("---------complex test------------");
	if(DynVecSize(testvec_date) != DynCapacity(testvec_date))
	{
		puts("cap and size are not equal following create of date struct");
	}
	if(DynVecSize(testvec_inflt) != DynCapacity(testvec_inflt))
	{
		puts("cap and size are not equal following create of_inflt struct");
	}
	
	/* pushback will now call reserve */
	DynVecPushBack(testvec_date, &date_struct1);
	DynVecPushBack(testvec_inflt, &inflt_struct1);
	
	if(capacity * 2 != DynCapacity(testvec_date))
	{
		puts("cap increase of first push in date struct failed ");
	}
	if(capacity * 2 != DynCapacity(testvec_inflt))
	{
		puts("cap increase of first push in inflt struct failed ");
	}
	/*push put structs in the 6 th place of the vector (index 5)*/
		
	/*printf("%lu \n", *((size_t*)(DynVecGetItemAddress(testvec_date, 5))));*/
	
	if (*((size_t*)(DynVecGetItemAddress(testvec_date, 5))) != 85)
	{
		puts("get adress in date struct index 5 failed");
	}
	
	/*printf("%lu \n", *((size_t*)(DynVecGetItemAddress(testvec_date, 5))+1));*/
	
	if ((*((size_t*)(DynVecGetItemAddress(testvec_date, 5))+1)) != 35)
	{
		puts("get adress in date struct index 5 (2 item in struct) failed");
	}
	
	*(size_t*)(DynVecGetItemAddress(testvec_date, 5)) = 65;
	/*printf("%lu \n", *((size_t*)(DynVecGetItemAddress(testvec_date, 5))));*/
	if (*((size_t*)(DynVecGetItemAddress(testvec_date, 5))) != 65)
	{
		puts("changing value using get adress in date struct index 5 failed");
	}
	
	/*printf("%d \n", *((int*)(DynVecGetItemAddress(testvec_inflt, 5))));*/
	if (*((int*)(DynVecGetItemAddress(testvec_inflt, 5))) != 146)
	{
		puts("get adress in inflt struct index 5 failed");
	}
	
	
	/*printf("%.2f \n", *((float*)(DynVecGetItemAddress(testvec_inflt, 5))+1));*/
	if (*((float*)(DynVecGetItemAddress(testvec_inflt, 5))+1) != (float)19.88)
	{
		puts("get adress in inflt struct index 5 (2nd item in struct) failed");
	}
	
	
	*(int*)(DynVecGetItemAddress(testvec_inflt, 5)) = 12;
	/*printf("%d \n", *((int*)(DynVecGetItemAddress(testvec_inflt, 5))));*/
	if (*((int*)(DynVecGetItemAddress(testvec_inflt, 5))) != 12)
	{
		puts("changing value using get adress in inflt struct index 5 failed");
	}
	
	DynVecDestroy(testvec_inflt);
	DynVecDestroy(testvec_date);
	


}


void OPTest(void)
{
	struct DateOfBirth
	{
		size_t day;
		size_t month;
		size_t year;
	};

	struct DateOfBirth date_struct1 = {85,35,178};	
	struct DateOfBirth date_struct2 = {65, 82,1988};	
	struct DateOfBirth date_struct3 = {3,4,1978};	
	struct DateOfBirth date_struct4 = {45,2,1948};	
	struct DateOfBirth date_struct5 = {98,15,1958};
		
	size_t capacity = 0;
	
	dyn_vec_t * testvec_date = DynVecCreate(sizeof(struct DateOfBirth), capacity);
	dyn_vec_t * testvec_date2 = DynVecCreate(sizeof(struct DateOfBirth), capacity);
	puts("-------initializing with cap 0-----------");
	
	/*reserving cap of 5, size is 0*/
	
	DynVecReserve(testvec_date, 5);
	
	if (DynVecSize(testvec_date) != 0)
	{
		puts("size is not 0 after initializing with 0 and reserving cap");
	}
	if (DynCapacity(testvec_date) != 5)
	{
		puts("cap is not 5 after initializing with 0 and reserving cap 5");
	}
	
	
	*(struct DateOfBirth*)(DynVecGetItemAddress(testvec_date, 0)) = date_struct1;
	
	/*printf("if u see 85,35,178 -> initializing using get adress is successful\n%lu, %lu, %lu\n", (*((size_t*)(DynVecGetItemAddress(testvec_date, 0)))),(*((size_t*)(DynVecGetItemAddress(testvec_date, 0))+1)), (*((size_t*)(DynVecGetItemAddress(testvec_date, 0))+2)));*/
	assert(85 == (*((size_t*)(DynVecGetItemAddress(testvec_date, 0)))));
	assert(35 == (*((size_t*)(DynVecGetItemAddress(testvec_date, 0))+1)));
	assert(178 == (*((size_t*)(DynVecGetItemAddress(testvec_date, 0))+2)));
	
	if (*((size_t*)(DynVecGetItemAddress(testvec_date, 0))) != 85)
	{
		puts("changing value using get adress in date struct index 0 failed");
	}
	
	/*pushing when cap is 0*/
	
	DynVecPushBack(testvec_date2, &date_struct1);
	assert(1 == DynVecSize(testvec_date2));
	assert(2 == DynCapacity(testvec_date2));
	/*printf("after creating with cap = 0 and pushing an element:\nsize: %lu cap: %lu \n", DynVecSize(testvec_date2), DynCapacity(testvec_date2));*/
	
	DynVecPushBack(testvec_date2, &date_struct2);
	/*printf("after creating with cap = 0 and pushing 2 an element:\nsize: %lu cap: %lu \n", DynVecSize(testvec_date2), DynCapacity(testvec_date2));*/
	assert(2 == DynVecSize(testvec_date2));
	assert(2 == DynCapacity(testvec_date2));
	DynVecPushBack(testvec_date2, &date_struct3);
	/*printf("after creating with cap = 0 and pushing 3 an element:\nsize: %lu cap: %lu \n", DynVecSize(testvec_date2), DynCapacity(testvec_date2));*/
	assert(3 == DynVecSize(testvec_date2));
	assert(4 == DynCapacity(testvec_date2));
	/*pushing in reserved vector*/
	/*printf("after creating with cap = 0 reserving 5:\nsize: %lu cap: %lu \n", DynVecSize(testvec_date), DynCapacity(testvec_date));*/
	assert(0 == DynVecSize(testvec_date));
	assert(5 == DynCapacity(testvec_date));
	DynVecPushBack(testvec_date, &date_struct1);
	DynVecPushBack(testvec_date, &date_struct2);
	DynVecPushBack(testvec_date, &date_struct3);
	DynVecPushBack(testvec_date, &date_struct4);
	DynVecPushBack(testvec_date, &date_struct5);
	
	assert(85 == (*((size_t*)(DynVecGetItemAddress(testvec_date2, 0)))));
	assert(35 == (*((size_t*)(DynVecGetItemAddress(testvec_date2, 0))+1)));
	assert(178 == (*((size_t*)(DynVecGetItemAddress(testvec_date2, 0))+2)));
		
	/*printf("if u see 85,35,178 -> pushing is successful\n%lu, %lu, %lu\n", (*((size_t*)(DynVecGetItemAddress(testvec_date2, 0)))),(*((size_t*)(DynVecGetItemAddress(testvec_date2, 0))+1)), (*((size_t*)(DynVecGetItemAddress(testvec_date2, 0))+2)));*/
	
	assert(65 == (*((size_t*)(DynVecGetItemAddress(testvec_date2, 1)))));
	assert(82 == (*((size_t*)(DynVecGetItemAddress(testvec_date2, 1))+1)));
	assert(1988 == (*((size_t*)(DynVecGetItemAddress(testvec_date2, 1))+2)));
	/*printf("if u see 65, 82,1988 -> pushing is successful\n%lu, %lu, %lu\n", (*((size_t*)(DynVecGetItemAddress		(testvec_date2, 1)))),(*((size_t*)(DynVecGetItemAddress(testvec_date2, 1))+1)), (*((size_t*)(DynVecGetItemAddress(testvec_date2, 1))+2)));*/
	
	assert(5 == DynVecSize(testvec_date));
	assert(5 == DynCapacity(testvec_date));
	/*printf("after creating with cap = 0 reserving 5 and pushing 5:\nsize: %lu cap: %lu \n", DynVecSize(testvec_date), DynCapacity(testvec_date));	*/
	DynVecPushBack(testvec_date, &date_struct1);/*6th push*/
	assert(6 == DynVecSize(testvec_date));
	assert(10 == DynCapacity(testvec_date));
	/*printf("after creating with cap = 0 reserving 5 and pushing 6:\nsize: %lu cap: %lu \n", DynVecSize(testvec_date), DynCapacity(testvec_date));*/	
	DynVecPopBack(testvec_date);/*pop 1*/
	assert(5 == DynVecSize(testvec_date));
	assert(10 == DynCapacity(testvec_date));
	/*printf("after creating with cap = 0 reserving 5 and pushing 6 and popping 1:\nsize: %lu cap: %lu \n", DynVecSize(testvec_date), DynCapacity(testvec_date));*/
	puts("made it this far with no errors? way to go!\ndont forget to valgrind");
	DynVecDestroy(testvec_date2);
	DynVecDestroy(testvec_date);

}
