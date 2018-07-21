#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{


const char *src = malloc(sizeof(char)*800);
	char *dest = (char*)src+21;
	if (src == NULL)
	{
		perror("allocation 1 for memmove");
		return 1;
	}
	strcpy((char*)src,"this is a string for the memmove function, hopefully, i dont feel like counting it.");
	
	puts("MEMMOVE TEST");
	
	printf("dest before move: %s\n", dest);
	memmove(dest, src, 23);
	printf("dest after move: %s\n", dest);
	/*
	free((char *)src);
	src = NULL;
	free(dest);
	dest = NULL;*/

	return 0;
	
}
