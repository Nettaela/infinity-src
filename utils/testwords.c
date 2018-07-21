#include <stdio.h>
 #include <stdlib.h>
 
int main()
{
	char c;
	int i = 0;
	char current_word[50];
	char * filename = "/usr/share/dict/words";
	FILE * fp = fopen(filename, "r");
	if (fp == NULL) return 1;
	
	while((c = fgetc(fp)) != EOF)
	{
		if(c == ' ' || c == '\n')
		{
			current_word[i] = '\0';
			printf("%s\n", current_word);
			i = 0;
		}
		else
		{
			current_word[i] = c;
			++i;
		}
	}
	fclose(fp);
 

	return 0;
}
