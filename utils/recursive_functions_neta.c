#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#define NEXT_EL(a) (char*)a+elem_size
/*cr atlist a line space here */
size_t RecFibonacci(size_t num) /*return the num index of fibonacci series*/
/*cr num is not such a good name i think. to generic and doesn't help to 
	 understand it's meaning */
{
/*cr no space here */
	if(num == 0 || num == 1)
	{
		return num;
	}

	return RecFibonacci(num-1) + RecFibonacci(num-2);
}

int IterativeFibonacci(int n) /*cr n is a bad name */
{
	int num1 = 0;
	int num2 = 1;
	int result = num1 + num2; 

	if(n == 0)
	{
		return 0;
	}

	for(n; n > 2 ; --n) 
	{
		num1 = num2;
		num2 = result;
		result = num1 + num2;
	}
	
	return result;
}

size_t RecStrlen(const char *str)
{
	if ('\0' == *str ) /* trivial case*/ 
	{
		return 0;
	}
	return RecStrlen(str+1) + 1;
}

int RecStrcmp(const char *str1, const char *str2)
{
	int result = 0; /*cr difference is more accurate name */
	if((*str1 == '\0') || (*str2 == '\0') )
	{
		return *str1 - *str2;
	}
	result = *str1 - *str2; /*cr if result == 0 so there is no reason to send
it. if not that's an ending point. you don't need to run until the end of 
the string if the first letters are different*/
	return result + RecStrcmp(str1+1, str2+1);
}

char * RecStrcpy (char *dest, const char *src) /*returns pointer to dest */
{
	if(*src == '\0')
	{
		*dest = *src;
		return dest;
	}
	RecStrcpy(dest+1, src+1);
	*dest = *src;
	return dest;
}

char * RecStrncpy(char *dest, const char *src, size_t n) /*returns pointer to dest */
{
/*cr if n > sizeof(src) so it needs special care. n chars should be written*/
	if(n == 0 || *src == '\0') 

	{
		*dest = '\0';
		return dest;
	}

	RecStrncpy(dest+1, src+1, n-1);
	*dest = *src;
	return dest;
}

int RecStrcasecmp(const char *str1, const char *str2)
{
	char tmp_ch1 = *str1;
	char tmp_ch2 = *str2;
	int result = 0;
	assert(str1 && str2);
	
	tmp_ch1 = tolower(tmp_ch1); /*makes everything lower case*/
	tmp_ch2 = tolower(tmp_ch2);
	
	if (tmp_ch1 == '\0' || tmp_ch2 == '\0' || tmp_ch1 != tmp_ch2)
	{
		return (tmp_ch1 - tmp_ch2);
	}
		
	/*result = (tmp_ch1 - tmp_ch2);*/

	return /*result +*/ RecStrcasecmp(str1+1, str2+1);

}

char *RecStrchr(const char *str, int character) 
{
	if(*str == '\0')
	{
		return NULL;
	}
	
	if(*str == character)
	{
		return (char*)str;
	}
	
	return RecStrchr(str+1, character);

}

char *RecStrcat(char *dest, const char *src)
{
	size_t len = strlen(dest);
	char *dest_end = dest+len; 
	
	if(*src == '\0')
	{
		dest_end = '\0';
		return dest;
	}

	RecStrcat(dest_end+1, src+1);
	*dest_end = *src;
	return dest;

}

char *RecStrncat(char *dest, const char *src, size_t n)
{
	size_t len = strlen(dest);
	char *dest_end = dest+len;
	if(n == 0 || *src == '\0')
	{
		dest_end = '\0';
		return dest;
	}

	RecStrncat(dest_end+1, src+1, n-1);
	*dest_end = *src;
	return dest;


}

char *RecStrstr(const char *haystack, const char *needle)
{
	size_t needle_len = strlen(needle);
	size_t haystack_len = strlen(haystack);
	
	if (*haystack == '\0' || haystack_len < needle_len )
	{
		return NULL;
	}
	if (*needle == *haystack /*&& haystack_len >= needle_len*/&&
	(strncmp(needle, haystack, needle_len) == 0))
	{
		/*if (strncmp(needle, haystack, needle_len) == 0)
		{*/
			return (char*)haystack;
		/*}*/
	}
	return RecStrstr(haystack+1, needle);
}

size_t RecStrspn(const char *s, const char *accept)
{
	size_t idx_of_accept_char = 0;
	char * result = RecStrchr(accept, *s);
	if(*s == '\0' || NULL == result)
	{
		return idx_of_accept_char;
	}
	if (NULL != result) 
	{
		++idx_of_accept_char;
	}
	idx_of_accept_char += RecStrspn(s+1, accept);
	return idx_of_accept_char;
}

int FindMin(int *arr, size_t arr_size)
{
	int new_min = 0;
	int min_index = 0;
	if(arr_size == 1)
	{
		return new_min;
	}
	new_min = FindMin(arr+1, arr_size-1);
	if(arr[min_index] > arr[new_min+1])
	{
		return new_min+1;
	}
	else
	{
		return min_index;
	}
}

void RecSelectionSort(int *arr, size_t arr_size)
{
	int min_index = 0;
	int min = 0;
	if(arr_size == 1)
	{
		return;
	}
	
	min_index = FindMin(arr, arr_size);
	min = arr[min_index];
	memmove(&arr[1], &arr[0], min_index*sizeof(int));
	arr[0] = min;
	RecSelectionSort(arr+1,arr_size-1);
}

int IsSortSuccess(int *array, size_t arr_size)
{
	size_t i = 0;
	for(i = 0 ; i < arr_size - 1 ; ++i)
	{
		if(array[i] > array[i + 1])
		{
			return 0;
		}
	}
	return 1;
}

void unitestsort(void)
{
   int array[] = {2,435,435,-342,54,0,-239};

    RecSelectionSort(array, 7);

    assert(IsSortSuccess(array, 7));
	
    puts("recursive selection sort success");
}


void uniteststrspn(void)
{
	/*char *s="trings";
	char *accept = "s";
	size_t size = RecStrspn(s,accept);
	
	char *s1="ftftftrinfgis";
	char *accept1 = "ftr";
	size_t size1 = RecStrspn(s1,accept1);

	assert(size == 0);
	assert(size1 == 7);
	puts("recursive strspn successfull");*/
	/*char *s="trings";
	char *accept = "s";
	size_t size = RecStrspn(s,accept);
	
	char *s1="fffrinfgs";
	char *accept1 = "ft";
	size_t size1 = RecStrspn(s1,accept1);

	assert(size == 0);
	assert(size1 == 3);
	puts("recursive strspn successfull");*/
	
	const char *str1 ="abcsigttt";
	const char *str2 = "nlmabcsitcsiggggggt"; 
	const char *str3 ="abcpsicgttt";
	const char *str4 = "bcsitcsiggggggt";

	int lenght;

	lenght = RecStrspn(str1, str2);
	assert(9 == lenght);
	
	lenght = RecStrspn(str3, str2);
	assert(3 == lenght);

	lenght = RecStrspn(str3, str4);
	assert(0 == lenght);
}

void uniteststrstr(void)
{
	char *needle = "r";
	char *haystack = "abbcccdddd";	
	
	char *needle2 = "ccd";
	char *haystack2 = "abbcccdddd";
	
	char *needle3 = "r";
	char *haystack3 = "r";
	
	char *needle4 = "r";
	char *haystack4 = "a";

	char *needle5 = "a";
	char *haystack5 = "r";
	
	char *needle6 = "r";
	char *haystack6 = "";
	
	char *needle7 = "";
	char *haystack7 = "r";
	
	char *needle8 = "";
	char *haystack8 = "";
	
	char *needle9 = "aaa";
	char *haystack9 = "aaaa";
	
	assert(NULL == 	RecStrstr(haystack,needle));
	assert(strcmp(haystack2+4, RecStrstr(haystack2,needle2)) == 0);

	assert(strcmp(haystack3 , RecStrstr(haystack3,needle3)) == 0);
	assert(NULL == 	RecStrstr(haystack4,needle4));
	assert(NULL == 	RecStrstr(haystack5,needle5));

	assert(NULL == 	RecStrstr(haystack6,needle6));
	assert(NULL == 	RecStrstr(haystack7,needle7));
	assert(NULL == 	RecStrstr(haystack8,needle8));

	assert(strcmp(haystack9 , RecStrstr(haystack9,needle9)) == 0);
	puts("recursive strstr successfull");
}

void uniteststrncat(void)
{
	char *s2="whatchuwant";	
	char s1[70]="tell me ";
	char *expected = "tell me whatch";
	assert(*expected == *RecStrncat(s1,s2,6));
	puts("recursive strncat successfull");
}

void uniteststrcat(void)
{
	char *s2=" is";	
	char s1[70]="this";
	char *expected = "this is";
	assert(*expected == *RecStrcat(s1,s2));
	puts("recursive strcat successfull");
}
void uniteststrchr(void)
{
	char c='s';
	char s[]="iamsotired";
	char *result=RecStrchr(s, c);
	assert(*result == s[3]);
	puts("recursive strchr successfull");
}

void uniteststrcasecmp(void)
{
	assert(0 == RecStrcasecmp("sS","Ss"));
	assert(0 != RecStrcasecmp("sS","fs"));
	assert(0 == RecStrcasecmp("sSrR","ssRr"));
	puts("recursive strcasecmp successfull");
}

void uniteststrcpy(void)
{
	char src[]="this string ends with k";
	char dest[100];
	RecStrcpy(dest, src);
	assert(strcmp( src, dest) == 0);
	puts("recursive strcpy successfull");
}

void uniteststrncpy(void)
{
	char src[]="this string ends with k";
	char dest[100];
	RecStrncpy(dest, src, 11);
	assert(strncmp(src, dest ,11) == 0);
	puts("recursive strncpy successfull");
}

void uniteststrlen(void)
{
	assert(1== RecStrlen("x"));
	assert(1== RecStrlen(" "));
	assert(6== RecStrlen("123456"));
	assert(7== RecStrlen("123 456"));
	assert(0==RecStrlen("\0"));
	puts("recursive strlen successfull");
}

void uniteststrcmp(void)
{
	char s1[] = "lala";
	char s2[] = "lola";
	assert(0 != RecStrcmp(s1, s2));
	assert(0 != RecStrcmp("l", "dola"));
	assert(0 != RecStrcmp("zzzz", "zzz"));
	assert(0 == RecStrcmp("zzz", "zzz"));
	puts("recursive strcmp successfull");
}

void unitestfibo(void)
{
	time_t now = time(NULL);
	time_t after = 0;
	size_t result = IterativeFibonacci(26);
	after = time(NULL);
	printf("%lu \n", result);
	printf("took me %f sec\n", difftime(after,now));
}

int main()
{
	uniteststrlen();
	uniteststrcmp();
	uniteststrcpy();
	uniteststrncpy();
	uniteststrcasecmp();
	uniteststrchr();
	uniteststrcat();
	uniteststrncat();
	uniteststrstr();
	uniteststrspn();
	unitestsort();
	return 0;
}








