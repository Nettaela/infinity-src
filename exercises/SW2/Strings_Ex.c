#include <stdio.h>		/*for printf function*/
#include <stdlib.h>		/*for exit success*/
#include <ctype.h>		/*remove this*/
#include <assert.h> 	/*for asserting*/
#include <string.h>		/*remove this*/
#include <strings.h>	/*remove this*/
#define IS_UPPERCASE(c) ('A' <= (c) && (c) <= 'Z') /*macro for strcasecmp*/


size_t Strlen(const char *str);
int Strcmp(const char *str1, const char *str2);
char * Strcpy (char *dest, const char *src);
char * Strncpy (char *dest, const char *src, size_t n);
int Strcasecmp(const char *str1, const char *str2);
char *Strchr(const char *str, int c);
char *Strdup(const char *s);
char *Strcat(char *dest, const char *src);
char *Strncat(char *dest, const char *src, size_t n);
char *Strstr(const char *haystack, const char *needle);
size_t Strspn(const char *s, const char *accept);

void UniTest(void);


int main()
{
	UniTest();
	return EXIT_SUCCESS;
}

size_t Strlen(const char *str) /*do this with pointer*/
{
	const char *start_ptr = str;
	
	assert(str); 
	
	while (*str != '\0') /* while pointer to str array (incremented 
									by 1 in each cycle) is not a null terminator*/
	{
		++str;
	}
	return (str-start_ptr);	

}


int Strcmp(const char *str1, const char *str2)
{
	int result;
		
	assert(str1 && str2);
	
	while ((*str1 != '\0') || (*str2 != '\0'))
	{
		result = *str1 - *str2;
		
		if (result == 0)
		{
			++str1;
			++str2;
			continue;
		}
		else 
		{
			return result;
		}
		
		
	}

	return result;
}

char * Strcpy (char *dest, const char *src) /*returns pointer to dest */
{
	char *runner = dest;
	
	assert (dest && src);
		
	while (*src != '\0')
	{
		*runner=*src;
		++src;
		++runner;
	}
	return dest;
}

char * Strncpy (char *dest, const char *src, size_t n) /*returns pointer to dest */
{

	char *runner = dest;
	size_t src_len = Strlen(src);
	int counter = n;
	
	assert(dest && src && n);
	
	while (counter > 0)/*????*/
	{
		*runner = *src;
		++src;
		++runner;
		--counter;
	}
	if (n < src_len)
	{
		while ((src_len - n) > 0)
		{
			*runner = '\0';
			++runner;
			++n;
		}
	}  	
		
		
	return dest;
}


int Strcasecmp(const char *str1, const char *str2)
{
	
	char tmp_ch1 = *str1;
	char tmp_ch2 = *str2;

	assert(str1 && str2);

	while (tmp_ch1 != '\0' && tmp_ch2 != '\0')
	{
		IS_UPPERCASE(tmp_ch1)? tmp_ch1 += 32 : tmp_ch1; /*makes everything lower case*/
		
		IS_UPPERCASE(tmp_ch2)? tmp_ch2 += 32 : tmp_ch2;	
		
		if (tmp_ch1 != tmp_ch2)
		{
			break;
		}
		++str1;
		++str2;
		tmp_ch1 = *(str1);
		tmp_ch2 = *(str2);
		
	}
	return (tmp_ch1 - tmp_ch2);

}

char *Strchr(const char *str, int c) 
{
	
	assert(str);
	
	while (*str != c && *str != '\0')
	{
		++str;
	}
	
	if (*str == c)
	{
		return (char *)str;
	}

	return (char *)str;
	

}


char *Strdup(const char *s)
{
	char *dupstr;
	dupstr=calloc(strlen(s)+1, sizeof(char));
	
	assert(dupstr);
	
	Strcpy(dupstr,s);	
	
	return dupstr;

}


char *Strcat(char *dest, const char *src)
{
	unsigned int i=0;
	const char *src_copy = src;	
	size_t dest_len = Strlen(dest);
	size_t src_len = Strlen(dest);
	char *ptr_end_dest = (dest+dest_len);
	
	for (i=0 ; i<src_len ; src_copy++, ptr_end_dest++, i++)
		{	
    		*ptr_end_dest = *src_copy;
		}
	return dest;

}


char *Strncat(char *dest, const char *src, size_t n)
{

	unsigned int i=0;
	const char *src_copy = src;	
	size_t dest_len = Strlen(dest);
	size_t src_len = n;
	char *ptr_end_dest = (dest+dest_len);
	
	for (i=0 ; i<src_len ; src_copy++, ptr_end_dest++, i++)
		{	
    		*ptr_end_dest = *src_copy;
		}
	ptr_end_dest = '\0';
	return dest;


}


char *Strstr(const char *haystack, const char *needle)
{
	char *haystack_needle_ptr = (char *)haystack;
	int needle_size = Strlen(needle);
	char *needle_ptr = (char *)needle;
	char *saved_ptr = NULL; 
	char dest[100]="0";
	int cmp_result=1;

	while (*haystack_needle_ptr != '\0')
	{
		if (*needle_ptr == *haystack_needle_ptr)
		{
			saved_ptr = haystack_needle_ptr;
			/*save the place where suspected needle begins
			and copy the part of haystack starting at that point, 
			up to the size of needle. compare them to see if it 
			fits needle */
			Strncpy(dest,haystack_needle_ptr,needle_size);
			dest[needle_size]='\0';
			cmp_result = Strcmp(dest,needle);
			
		}
		
		if (cmp_result==0)
		{
			return saved_ptr;
		}
		
		++haystack_needle_ptr;
		
	}
	
	
	return saved_ptr;
			
}


size_t Strspn(const char *s, const char *accept)
{
	char *string_ptr = (char *)s;
	int idx_of_accept_char = 0;
	
	
	while (*string_ptr != '\0')
	{
		
		if (*string_ptr != *(Strchr(accept,*string_ptr))) 
		{
			return idx_of_accept_char;
		}
		else
		{
			++idx_of_accept_char;			
			++string_ptr;
		}
	}
	return idx_of_accept_char; 
}



void UniTest(void)
{
	/*Strlen test:	
	printf("%lu\n",Strlen("x"));
	printf("%lu\n",Strlen(" "));
	printf("%lu\n",Strlen("123456"));
	printf("%lu\n",Strlen("123 456"));
	printf("%lu\n",Strlen("\0"));*/ 
	
	/*Strcmp test: 
	char s1[] = "lala";
	char s2[] = "lola";
	printf("%d\n", Strcmp(s1, s2));
	printf("%d\n", Strcmp("l", "dola"));
	printf("%d\n", Strcmp("zzzz", "zzz"));
	printf("%d\n", Strcmp("zzz", "zzz")); */
	
	/*Strcpy test: 
	char src[]="whwheiurhwiehoeijfpoidhgpoqhger";
	char *dest=calloc(sizeof(src),sizeof(src[0]));
	dest = Strcpy(dest, src);
	printf("%s\n", dest);
	free(dest); */

	/*Strncpy test: 
	char src[]="this is my string";
	char *dest=calloc(sizeof(src),sizeof(src[0]));
	dest = Strncpy(dest, src, 6);
	printf("%s\n", dest);
	free(dest); */
	
	/*strcasecmp test
	printf("%d\n", Strcasecmp("sSs","Sss"));*/

	
	/*strchr test
	char c='s';
	char s[]="iamsotired";
	char *result=Strchr(s, c);
	printf("%p\n",result);*/


	/*strdup test
	char *s= "free me";
	char *willy=Strdup(s);	
	printf("%s\n",willy); 
	free(willy);*/
	
	/*Strcat test:
	char *s2=" is";	
	char s1[70]="this";
	printf("%s\n", Strcat(s1,s2));*/
	
	 /*Strncat test:
	char *s2="whatchuwant";	
	char s1[70]="tell me ";
	printf("%s\n", Strncat(s1,s2,6));*/

	/*Strstr test: 
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
	
	printf("1: %s\n", Strstr(haystack,needle));	
	printf("2: %s\n", Strstr(haystack2,needle2));
	printf("3: %s\n", Strstr(haystack3,needle3));
	printf("4: %s\n", Strstr(haystack4,needle4));
	printf("5: %s\n", Strstr(haystack5,needle5));
	printf("6: %s\n", Strstr(haystack6,needle6));
	printf("7: %s\n", Strstr(haystack7,needle7));
	printf("8: %s\n", Strstr(haystack8,needle8));
	printf("9: %s\n", Strstr(haystack9,needle9));*/

	/*Strspn test;
	char *s="trings";
	char *accept = "s";
	size_t size = Strspn(s,accept);
	
	char *s1="ffftrings";
	char *accept1 = "f";
	size_t size1 = Strspn(s1,accept1);
	printf("%lu\n",size);
	printf("%lu\n",size1);*/

	
	
   

}

