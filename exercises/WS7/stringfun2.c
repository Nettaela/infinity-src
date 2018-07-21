#include "header.h"
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



