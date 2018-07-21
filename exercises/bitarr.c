#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bitarr.h"

#define BIT(i) ((word_t)1 << i)

/*SET COUNT LUT:*/
#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define COUNT_BITS B6(0), B6(1), B6(1), B6(2)									

/*MIRROR LUT:*/
#define R2(n)                 n,     n + 2*64,     n + 1*64,     n + 3*64
#define R4(n)                 R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#define R6(n)                 R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )

typedef unsigned char byte_t;

static byte_t  MirrorLUT(byte_t bayit); /*gets a byte from BA_MirrorLUT and returns the mirrored byte*/
static byte_t SetCntLUT(byte_t bayit);	/*gets a byte from BA_SetCntLUT and returns the number of set bits*/


bool BA_IsSet (word_t b_arr, int b_num)
{	
	assert(b_num >= 0);
	
	if ((b_arr & BIT(b_num)) == BIT(b_num))
	{
		return TRUE;
	}
	return FALSE;
}

bool BA_IsClear (word_t b_arr, int b_num)
{
	assert(b_num >= 0);
	
	if ((b_arr & BIT(b_num)) == 0)
	{
		return TRUE;
	}
	return FALSE;
}

size_t BA_SetCnt (word_t b_arr)
{
	size_t count = 0;
	
	while(b_arr)
	{
		b_arr &= (b_arr - 1);
		++count;
	}
	return count;
}

size_t BA_ClearCnt (word_t b_arr) /*we can do the same as with set count for NOT b_arr, or we can call set count and subtract it from 64*/
{
	/*size_t count = 0;
	b_arr = (~b_arr);
	while(b_arr)
	{
		b_arr &= (b_arr - 1);
		++count;
	}
	return count;*/
	
	return (64 - BA_SetCnt(b_arr));
}

word_t BA_ModBit (word_t b_arr, int b_num, int val)
{		
	assert((b_num >= 0) && (b_num <= 64));
	assert((val == 0) || (val == 1));
	
	if(val)
	{
		return (b_arr | BIT(b_num));
	}
	return (b_arr & ~BIT(b_num));
}

word_t BA_SetBit (word_t b_arr, int b_num)
{
	assert((b_num >= 0) && (b_num <= 64));
	
	return (b_arr | BIT(b_num));
}

word_t BA_ClearBit (word_t b_arr, int b_num)
{	
	assert((b_num >= 0) && (b_num <= 64));
	
	return (b_arr & ~BIT(b_num));
}

word_t BA_SetAll (void)
{
	return 0xffffffffffffffff;
}

word_t BA_ClearAll (void)
{
	return 0x0000000000000000;
}

word_t BA_FlipBit (word_t b_arr, int b_num)
{
	assert((b_num >= 0) && (b_num <= 64));
	
	return (b_arr ^= BIT(b_num));
}

word_t BA_Mirror (word_t b_arr)
{
		
	b_arr = ((b_arr << 32) | (b_arr >> 32));
	b_arr = ((0xffff0000ffff0000 & (b_arr << 16)) | ((b_arr >> 16) & 0x0000ffff0000ffff));
	b_arr = ((0xff00ff00ff00ff00 & (b_arr << 8))  | ((b_arr >> 8)  & 0x00ff00ff00ff00ff));	
	b_arr = ((0xf0f0f0f0f0f0f0f0 & (b_arr << 4))  | ((b_arr >> 4)  & 0x0f0f0f0f0f0f0f0f));			
	b_arr = ((0xcccccccccccccccc & (b_arr << 2))  | ((b_arr >> 2)  & 0x3333333333333333));
	b_arr = ((0xaaaaaaaaaaaaaaaa & (b_arr << 1))  | ((b_arr >> 1)  & 0x5555555555555555));
	return b_arr;
}

char* BA_ToStr (word_t b_arr, char* dest)
{
	int i = 0;
	char * dest_start = dest;
	word_t mask = 0x8000000000000000;
	
	assert(dest != NULL);

	while(i < (64))
	{

		if((i%8 == 0) && (i != 0))
		{
			*dest = '|';
			++dest;
		}
		*dest = (char)(((mask & b_arr) != 0) + '0'); 
		mask >>= 1;
		++dest;
		++i;
	}
	*dest = '\0';
	return dest_start;
}

word_t BA_RotR (word_t b_arr, int n_bits)
{
	assert((n_bits >= 0) && (n_bits <= 64));
	
	return ((b_arr << ((sizeof(word_t)*8)-n_bits)) | (b_arr >> n_bits));
}

word_t BA_RotL (word_t b_arr, int n_bits)
{
	assert((n_bits >= 0) && (n_bits <= 64));
	
	return ((b_arr >> ((sizeof(word_t)*8)-n_bits)) | (b_arr << n_bits));
}

static byte_t MirrorLUT(byte_t bayit)/*value of bayit doesnt need to be asseted because its unsigned char*/
{
	static unsigned char lookup_mirror[256] = { R6(0), R6(2), R6(1), R6(3) };
	 
	return (byte_t)lookup_mirror[bayit];
}

word_t BA_MirrorLUT (word_t b_arr)
{	/* take the right byte, mirror it, and put in the right side of the new word. shift new word left and take the next byte from b_arr */

	word_t byte_mask_right = 0xff;
	byte_t right_byte = 0;
	word_t new_b_arr = 0;
	unsigned int i = 0;
			
	for (i = 0 ; i < 7; ++i)
	{

		right_byte = b_arr & byte_mask_right;
		right_byte = MirrorLUT((byte_t)right_byte);
		new_b_arr |= right_byte;
		new_b_arr <<= 8;
		b_arr >>=8;
	}
	right_byte = b_arr & byte_mask_right;
	right_byte = MirrorLUT((byte_t)right_byte);
	new_b_arr |= right_byte;
	
	return new_b_arr;
}

static byte_t SetCntLUT(byte_t bayit)
{
	static size_t lookup_count[256] = {COUNT_BITS};

	return lookup_count[bayit] ;
}

size_t BA_SetCntLUT (word_t b_arr)
{
	size_t result = 0;
	byte_t mask = 0xff;
	byte_t right_byte = 0;
	int i = 0;
		
	for(i = 0; i < 8 ; ++i)
	{
		right_byte = (b_arr >> (i*8)) & mask;
		result += SetCntLUT(right_byte);
	}
	return result;	
}


















