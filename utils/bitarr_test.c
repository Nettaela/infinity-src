#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "bitarr.h"

void UnitestIsSet(void);
void UnitestIsClear(void);
void UnitestSetCnt(void);
void UnitestClearCnt(void);
void UnitestModBit(void);
void UnitestSetBit(void);
void UnitestClearBit(void);
void UnitestSetAll(void);
void UnitestClearAll(void);
void UnitestFlipBit(void);
void UnitestMirror(void);
void UnitestToStr(void);
void UnitestRotR(void);
void UnitestRotL(void);
void UnitestMirrorLUT(void);
void UnitestSetCntLUT(void);

int main()
{
	UnitestIsSet();
	UnitestIsClear();
	UnitestSetCnt();
	UnitestClearCnt();
	UnitestModBit();
	UnitestSetBit();
	UnitestClearBit();
	UnitestSetAll();
	UnitestClearAll();
	UnitestFlipBit();
	UnitestMirror();
	UnitestToStr();
	UnitestRotR();
	UnitestRotL();
	UnitestMirrorLUT();
	UnitestSetCntLUT();
	
	return EXIT_SUCCESS;

}

void UnitestIsSet(void)
{
	word_t bitword = 7;
	puts("---------------------------------------------------------");
	puts("\nUnitestIsSet:\n");
	printf("%lu -> is bit 2 set?: %d\n",bitword, BA_IsSet(bitword, 2));
	printf("%lu -> is bit 11 set?: %d\n",bitword, BA_IsSet(bitword, 11));
}

void UnitestIsClear(void)
{
	word_t bitword = 7;
	puts("---------------------------------------------------------");
	puts("\nUnitestIsClear:\n");
	printf("%lu -> is bit 2 clear?: %d\n",bitword, BA_IsClear(bitword, 2));
	printf("%lu -> is bit 11 clear?: %d\n",bitword, BA_IsClear(bitword, 11));
}
void UnitestSetCnt(void)
{
	word_t bitword = 7;
	puts("---------------------------------------------------------");
	puts("\nUnitestSetCnt:\n");
	printf("how many bits set in %lu?: %lu\n",bitword, BA_SetCnt(bitword));

}
void UnitestClearCnt(void)
{
	word_t bitword = 7;
	puts("---------------------------------------------------------");
	puts("\nUnitestClearCnt:\n");
	printf("how many bits clear in %lu?: %lu\n",bitword, BA_ClearCnt(bitword));
	
}
void UnitestModBit(void)
{
	word_t bitword = 0xffffffffaaaaaaaa;
	puts("---------------------------------------------------------");
	puts("\nUnitestModBit:\n");
	printf("%lu -> change 63rd bit to 0: %lu\n", bitword, BA_ModBit(bitword, 63, 0)); /*should be f = 1111*/

}
void UnitestSetBit(void)
{
	word_t bitword = 7;
	puts("---------------------------------------------------------");
	puts("\nUnitestSetBit:\n");
	printf("%lu -> set 3rd bit: %lu\n",bitword, BA_SetBit(bitword, 3)); /*should be f = 1111*/
	
}
void UnitestClearBit(void)
{
	word_t bitword = 7;
	puts("---------------------------------------------------------");
	puts("\nUnitestClearBit:\n");
	printf("%lu -> clear 2nd bit: %lu\n",bitword, BA_ClearBit(bitword, 2)); /*should be 3 = 0011*/
	
}
void UnitestSetAll(void)
{
	puts("---------------------------------------------------------");
	puts("\nUnitestSetAll:\n");
	printf("set all: %lu\n",BA_SetAll()); 

}
void UnitestClearAll(void)
{
	puts("---------------------------------------------------------");
	puts("\nUnitestClearAll:\n");
	printf("clear all: %lu\n",BA_ClearAll()); 
	
}
void UnitestFlipBit(void)
{
	word_t bitword = 7;
	puts("---------------------------------------------------------");
	puts("\nUnitestFlipBit:\n");
	printf("%lu -> flip bit 2: %lu\n",bitword, BA_FlipBit(bitword, 2)); /*should be 3 = 0011*/

}
void UnitestMirror(void)
{
	word_t bitword = 1;  /*the mirror is 128*/
	puts("---------------------------------------------------------");
	puts("\nUnitestMirror:\n");
	printf("%lu -> mirror: %lu\n",bitword, BA_Mirror(bitword)); 
	bitword = 0xaaaaaaaaffffffff;/*the mirror is 0xffffffff555555555*/
	printf("%lu -> mirror: %lu\n",bitword, BA_Mirror(bitword)); 
	
}
void UnitestToStr(void)
{
	word_t bitword = 7;
	char buffer[80] = {0};
	puts("---------------------------------------------------------");
	puts("\nUnitestToStr:\n");
	printf("%lu in bits: %s\n",bitword, BA_ToStr(bitword, buffer));

}

void UnitestRotR(void)
{
	word_t bitword = 7;
	puts("---------------------------------------------------------");
	puts("\nUnitestRotR:\n");
	printf("%lu -> rotate right 1 time: %lu\n",bitword, BA_RotR(bitword, 1));
	
}

void UnitestRotL(void)
{
	word_t bitword = 7;
	puts("---------------------------------------------------------");	
	puts("\nUnitestRotL:\n");
	printf("%lu -> rotate left 1 time: %lu\n",bitword, BA_RotL(bitword, 1));
	
}


void UnitestMirrorLUT(void)
{
	word_t testword1 = 0xff00ff00ff00ff00;/*9223372036854775808*/
	word_t testword2 = 0x0000000000000000;/*0*/
	word_t testword3 = 0x0000000000000001;/*0x80000000000000000*/
	word_t testword4 = 0x0000000ff0000000;/*0x0000000ff0000000*/
	puts("---------------------------------------------------------");	
	puts("\nUnitestMirrorLUT:\n");
	printf("result %lu == %lu ?\n" ,BA_MirrorLUT(testword1),BA_Mirror(testword1));
	printf("result %lu == %lu ?\n" ,BA_MirrorLUT(testword2),BA_Mirror(testword2));
	printf("result %lu == %lu ?\n" ,BA_MirrorLUT(testword3),BA_Mirror(testword3));
	printf("result %lu == %lu ?\n" ,BA_MirrorLUT(testword4),BA_Mirror(testword4));

}

void UnitestSetCntLUT(void)
{
	word_t testword = 0xffff0000ffff0000; 
	puts("---------------------------------------------------------");	
	puts("\nUnitestSetCntLUT:\n");
	printf("%lu\n" ,BA_SetCntLUT(testword));

}























