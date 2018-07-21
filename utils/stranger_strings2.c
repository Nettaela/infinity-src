
/* ------------------------------------------------------------------ 
	header files
 ------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <ctype.h>
#include <sys/time.h>

#define UNCONST_CHAR(x) (char *)(x)
#define LOWER_CASE(x) ((x) + ('a' - 'A'))
#define TO_LOWER(x) ((x)>='A' && (x)<='Z' ? LOWER_CASE(x) : (x))

/* ------------------------------------------------------------------ 
	function declerations
 ------------------------------------------------------------------ */

void unitest(void);

/* ------------------------------------------------------------------ 
	main
 ------------------------------------------------------------------ */

int main() 
{
    unitest();



    return EXIT_SUCCESS;
}

/* ------------------------------------------------------------------ 
	fibbo
 ------------------------------------------------------------------ */
int fibbo(int n)
{
	if (1 == n) 
	{
		return 0;
	}
	if (2 == n) 
	{
		return 1;
	}
	{
		return fibbo(n-1) + fibbo(n-2);
	}
	 
}

/* ------------------------------------------------------------------ 
	Strlen
 ------------------------------------------------------------------ */

size_t Strlen(const char *s)
{
	assert (NULL != s);

	if (*s == '\0') 
	{
		return 0;
	}
	{
		return strlen(s+1)+1;
	}
	 
}

/* ------------------------------------------------------------------ 
	Strcmp
 ------------------------------------------------------------------ */

int Strcmp(const char *s1, const char *s2)
{
	int diff = *s1 - *s2;
	assert(NULL != s1);
	assert(NULL != s2);
	
	if ( *s1 == '\0'|| *s2 == '\0') 
	{
		return 0;
	}
	if (diff != 0) 
	{
		return diff;
	}
		
	return Strcmp(++s1,++s2);
}

/* ------------------------------------------------------------------ 
	Strcpy
 ------------------------------------------------------------------ */

char *Strcpy(char *dest, const char *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	*dest = *src;
	if (*src != '\0')
	{
		return dest;
	}
	Strcpy(++dest,++src);
	return dest;
}

/* ------------------------------------------------------------------ 
	Strncpy
 ------------------------------------------------------------------ */


char *Strncpy(char *dest, const char *src, size_t n)
{
	assert(NULL != dest);
	assert(NULL != src);

	if (n > 0 && *src == '\0')
	{
		*dest = '\0';
		Strncpy(++dest, src,--n);
	}

	if (*src == '\0' || n == 0)
	{
		*dest = '\0';
		return dest;
	}
	*dest = *src;
	Strncpy(++dest,++src,--n);
	return dest;
}

/* ------------------------------------------------------------------ 
	Strcasecmp
 ------------------------------------------------------------------ */

int Strcasecmp(const char *s1, const char *s2)
{
	int c1 = 0;
	int c2 = 0;
	assert(NULL != s1);
	assert(NULL != s2);

	c1 = TO_LOWER(*s1);
	c2 = TO_LOWER(*s2);

	if ( *s1 == '\0' && *s2 == '\0') 
	{
		return 0;
	}

	if (c1 != c2) 
	{
		return c1 - c2;
	}
		
	return Strcasecmp(++s1,++s2);
}

/* ------------------------------------------------------------------ 
	Strchr
 ------------------------------------------------------------------ */

char *Strchr(const char *s, int c)
{
	assert(NULL != s);

	if (*s == '\0')
	{
		return NULL;
	}
	if (*s == c)
	{
		/* return strdup(s); */
		return UNCONST_CHAR(s);
	}
	return Strchr(++s,c);
}

/* ------------------------------------------------------------------ 
	Strcat
 ------------------------------------------------------------------ */

char *Strcat(char *dest, const char *src)
{
	assert(NULL != dest);
	assert(NULL != src);

	if (*dest != '\0') 
	{
		Strcat(++dest, src);
	}
	else if (*src != '\0')
	{
		*dest = *src;
		Strcat(++dest, ++src);
	}
	else if (*src == '\0')
	{
		*dest = *src;
	}
	return --dest;
}

/* ------------------------------------------------------------------ 
	Strncat
 ------------------------------------------------------------------ */

char *Strncat(char *dest, const char *src, size_t n)
{
	assert(NULL != dest);
	assert(NULL != src);

	if (*dest != '\0') 
	{
		Strncat(++dest, src, n);
	}
	else if (*src != '\0' && n > 0)
	{
		*dest = *src;
		Strncat(++dest, ++src, --n);
	}
	else if (*src == '\0')
	{
		*dest = *src;
	}
	return --dest;
}

/* ------------------------------------------------------------------ 
	Strstr
 ------------------------------------------------------------------ */

char *Strstr(const char *haystack, const char *needle)
{
	assert(NULL != haystack);
	assert(NULL != needle);
    if (haystack == '\0')
	{
        return 0;
	}

	if (strncmp(haystack, needle, strlen(needle)) == 0)
	{
        return UNCONST_CHAR(haystack);
	}
	/* cr - return null if not found?*/
    return(Strstr(haystack+1, needle));
}

/* ------------------------------------------------------------------ 
	Strspn
 ------------------------------------------------------------------ */

size_t Strspn(const char *str1, const char *str2) 
{
	assert(NULL != str1);
	assert(NULL != str2);
	if (*str1 == '\0' || *str2 == '\0')
	{
		return 0;
	}
	if (Strchr(str2, *str1) == NULL)
	{
		return 0;
	}

	return Strspn(++str1, ++str2) + 1;
}

/* ------------------------------------------------------------------ 
	selection sort
 ------------------------------------------------------------------ */
typedef int (*is_sorted_t)(const void *data1, const void *data2);

void swap(int *n1, int *n2)
{
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

int *FindMin(int *arr, size_t n, is_sorted_t is_sorted)
{
	int *return_ptr = NULL;
	assert(NULL != arr);

	if (arr == NULL || n == 0)
	{
		return return_ptr;
	}
	if (n == 1)
	{
		return arr;
	}
	return_ptr  = FindMin(arr + 1, n - 1, is_sorted);
	return is_sorted (arr, return_ptr)  ? arr : return_ptr;
}

void SelectionSort(
	int *arr, 
	size_t num_of_elem,
	is_sorted_t is_sorted)
{
	static size_t current_indx = 0;
	int *current_min = NULL;

	assert(NULL != arr);

	if (num_of_elem == 0)
	{
		return;
	}
	current_min = FindMin(arr, num_of_elem, is_sorted);
	
	swap(current_min, arr);

	SelectionSort(arr+1, num_of_elem -1, is_sorted);
}

static int IsIntSortedUp(const void *data1, const void *data2)
{
	int num1 = *(int*)data1;
	int num2 = *(int*)data2;

	return (num1 <= num2);
}

static int IsIntSortedDown(const void *data1, const void *data2)
{
	int num1 = *(int*)data1;
	int num2 = *(int*)data2;
	
	return (num1 >= num2);
}

void UnitestSelection(void)
{
	#define ARR_SIZE 20
	#define DEVIDE_BY 1

	/* TEST 1 */
    struct timeval before = {0};
	struct timeval after = {0};
	static int arr[ARR_SIZE] = {0};
	size_t idx = 0;
	puts("\nbefore:\n");
	for (idx = 0; idx < ARR_SIZE; ++idx)
	{
		arr[idx] = rand() / DEVIDE_BY;
		printf("%li\n", arr[idx]);
	}	
	gettimeofday(&before, NULL);
	SelectionSort(arr, ARR_SIZE, IsIntSortedUp); 
	gettimeofday(&after, NULL);
	puts("\nafter:\n");

	for (idx = 0; idx < ARR_SIZE - 1; ++idx)
	{
		printf("%li\n", arr[idx + 1]);
		assert(IsIntSortedUp(&arr[idx], &arr[idx + 1]) == 1); 
	}
	
	/* TEST 2 */
	puts("\nbefore:\n");
	for (idx = 0; idx < ARR_SIZE; ++idx)
	{
		arr[idx] = rand() / DEVIDE_BY;
		printf("%li\n", arr[idx]);
	}	
	SelectionSort(arr, ARR_SIZE, IsIntSortedDown); 
	puts("\nafter:\n");
	printf("%li\n", arr[0]);
	for (idx = 0; idx < ARR_SIZE - 1; ++idx)
	{
		printf("%li\n", arr[idx + 1]);
		assert(IsIntSortedDown(&arr[idx], &arr[idx + 1]) == 1); 
	}
	printf("after: %lu\n", after.tv_usec);
	printf("before: %lu\n", before.tv_usec);
	puts("Selection passed!");
	printf("duration in ms: %lu\n\n", after.tv_usec - before.tv_usec);
}

static void FindMinMax(int* min, int *max, int *arr, size_t arr_size)
{
	size_t idx = 0;
	
	*min = arr[0];
	*max = arr[0];
	for (idx = 1; idx < arr_size; ++idx)
	{
		if (arr[idx] < *min)
		{
			*min = arr[idx];
		}
		else if (arr[idx] > *max)
		{
			*max = arr[idx];
		}
	}
}

typedef struct digit
{
	size_t digit;
	size_t sort_base_bits;
}digit_t;

static int GetVal(const void *val, void *param)
{
	int int_val = *(int*)val;
	digit_t *digit_strct = (digit_t*)param;
	
	if (NULL == param)
	{
		return int_val;
	}
	int_val >>= digit_strct->digit * digit_strct->sort_base_bits;
	int_val &= (1 << digit_strct->sort_base_bits) - 1;
	
	return int_val;
}


/* ------------------------------------------------------------------ 

	unitest

 ------------------------------------------------------------------ */




void unitest(void)
{/*cr - testing would be easier with assertions because then i would know what was the expected outcome*/
    char str1[30] = "accd";
    char str2[30] = "acDd";
    char str3[30] = "34568";
    char str4[30] = "abba";
    char s1[30] = "hello";
    char s2[30] = "Bye";
    char s3[30] = "H";
	char for_dup[30] = "this is for dup";
	char for_cat[50] = "cat the ";
	char for_cat2[50] = "dog";
	char for_ncat[40] = "cat the ";
	char for_ncat2[40] = "dog";
	char for_strspn[40] = "aaaabbddssssss";
	char for_strspn2[40] = "abd";
    char stok[] =" - please,work, .. , , . please....";
	char * pch;
    char* news;


	UnitestSelection();

	printf("fibonacci of 5: %d \n", fibbo(5));

 	printf("%lu\n", strspn("abcccaacc","bab"));
	printf("%lu\n", Strspn("abcccaacc","bab"));

     printf("testing for Strlen function:\n");
     printf("%lu\n", Strlen(str1));
     printf("%lu\n", strlen(str1));
     printf("%lu\n", Strlen(str2));
     printf("%lu\n", strlen(str2));
     printf("%lu\n", Strlen(str3));
     printf("%lu\n", strlen(str3));
     


     printf("testing for Strcmp function:\n");
     printf("%d\n", Strcmp(str1,str2));
     printf("%d\n", strcmp(str1,str2));
     printf("%d\n", Strcmp(str2,str3));
     printf("%d\n", strcmp(str2,str3));
     printf("%d\n", Strcmp(str3,str1));
     printf("%d\n", strcmp(str3,str1));
     
     printf("testing for Strcpy function:\n");
     strcpy(s1,s2);
     printf("%s\n", s1);
     Strcpy(s2,s1);
     printf("%s\n", s1);
     strcpy(s1,s2);
     printf("%s\n", s1);
 
     
     printf("testing for Strncpy function:\n");
     Strncpy(s1,s2,3);
     printf("%s\n", s1);
     Strncpy(s1,s3,1);
     printf("%s\n", s1);

     
     printf("testing for Strcasecmp function:\n");
     printf("%d\n", Strcasecmp(str1,str2));
     printf("%d\n", strcasecmp(str1,str2));	 
     printf("%d\n", Strcasecmp(str1,s2));
     printf("%d\n", strcasecmp(str1,s2));
     printf("%d\n", Strcasecmp(s1,str2));
     printf("%d\n", strcasecmp(s1,str2));
	 
     
		   
   
     printf("testing for Strchr function:\n");
     printf("%s\n", Strchr("abba",'b'));
	  assert(NULL == Strchr("abba",'z'));
	  
     printf("%s\n", Strchr("abba",'a'));
     printf("%s\n", Strchr("abba",'b'));
   
	printf("testing for Strcat function:\n");
	printf("%s\n",Strcat(for_cat,for_cat2));

	printf("testing for Strncat function:\n");
	printf("%s\n",Strncat(for_ncat,for_ncat2,1));


	printf("testing for Strstr function:\n");
	printf("%s\n",Strstr("abbcccdddd","ccd"));
}

