#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/* a function takes 2 strings with numbers (assert this!) and returns
a string of addition. the max size of result string is 1 laeger than the two 
previous.numbers must be added from the end of each string. and we have to 
carry the one when addition result is larger than 9, and pass it to the next
 string. USES MALLOC< USER MUST FREE*/
 
 
 
 /*try it with check the first two chars of the numbers and adding them - if result is more than 1 we know that the string will be 1 char longer?*/
 
 
 
char * StringAddition(char *BigNum1, char *BigNum2);
int CharAdder(char num1, char num2,char carry);
void StrFlipper(char *str);
void UniTest(void);

int main()
{
	UniTest();
	
	return 0;
}

char * StringAddition(char *BigNum1, char *BigNum2)
{
		int ChaResult = 0;
		char carry = '0';
		size_t bignum1_len = strlen(BigNum1);
		size_t bignum2_len = strlen(BigNum2);
		int result_len = bignum1_len+bignum2_len + 1;
		char *result;
		char *bignum1_end = BigNum1+bignum1_len-1;/*maybe initialize them after the flip?*/
		char *bignum2_end = BigNum2+bignum2_len-1;
		char *longer;
		char *longer_end;
		unsigned int i = 0;
		
		assert(BigNum1 && BigNum2);
		
		result=calloc(result_len, sizeof(result));
		assert(result);
				
		StrFlipper(BigNum1);  /*flipped the numbers! now we can add them!! */
		StrFlipper(BigNum2);
		
		(bignum2_len >= bignum1_len) ? (longer_end = bignum2_end) : (longer_end = bignum1_end);
		(bignum2_len >= bignum1_len) ? (longer = BigNum2) : (longer = BigNum1);
		
				
		while ((longer_end-longer) >= 0)
		{
	
			
			
			ChaResult = CharAdder(*BigNum1, *BigNum2, carry);
			carry = '0';
			 
			if (ChaResult > 9)
			{
				ChaResult = ChaResult%10;
				carry = '1';
				result[i] = (char)('0'+ChaResult); 
			}
			else
			{
				result[i] = (char)('0'+ChaResult); 			
			}
			
			--longer_end;
			++BigNum1;
			++BigNum2;
			++i;
			
			if (*BigNum1 == '\0')
			{
				--BigNum1;
				*BigNum1 = '0';
			}
			if (*BigNum2 == '\0')
			{
				--BigNum2;
				*BigNum2 = '0';
			}
			
			
		}
		
		if (carry=='1')
		{
			result[i]='1';
			++i;
		}
		
		result[i]='\0';
		StrFlipper(result);
		
		return result;
		/*if carry = 1, add it to the last place of result and then flip result*/
		
}

int CharAdder(char num1, char num2, char carry)
{
	
	int CharAddResult=0;
	
	assert(num1 && num2 && carry);
	
	CharAddResult = ((int)(num1 - '0') + (int)(num2 - '0') + (int)(carry - '0'));
	return CharAddResult;
}

void StrFlipper(char *str)
{
	int end_idx = strlen(str)-1;
	int start_idx = 0;
	char temp;
	
	assert(str);
	
	while (start_idx <= end_idx)
	{
		temp = str[start_idx];
		str[start_idx] = str[end_idx];
		str[end_idx] = temp;
		++start_idx;
		--end_idx;
	}

}

void UniTest(void)
{
	char bignum1[] = "9";
	char bignum2[] = "999";
	char *result = StringAddition(bignum1,bignum2);
	printf("\"%s\"\n",result);
	free(result);
	

}
