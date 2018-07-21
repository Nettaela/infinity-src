#include "header.h"

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
