#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

void UniTest (void);
void BackSpace(char * dst, char * src);

void RmSpaces(char *str)
{
	char *dst = str;
	char *src = str;
	
	assert(str);
	
	while (*dst != '\0')
	{

		if (isspace(*dst) && (isspace(*(dst+1))))
		{
			BackSpace(dst,src);
			--src;
			--dst;
		}
		++src;
		++dst;
		
	}
	dst = str;
	src = str;
	if (isspace(*str))
	{
		BackSpace(dst,src);
	}
	if (isspace(*(str+(strlen(str)))))
	{
		*(str+(strlen(str))) = '\0';
	}
	
}

int main()
{
    
    UniTest();
    return EXIT_SUCCESS;
    
}



void BackSpace(char * dst, char * src)
{
    while(*src != '\0')
    {
        dst[0]=src[1];
        src++;
        dst++;
    }
}


void UniTest (void)
{

	char str[] = "  a   5   3 2 d    fd  s   xz  x";
    RmSpaces(str);
    printf("\"%s\"\n",str);
    
}
