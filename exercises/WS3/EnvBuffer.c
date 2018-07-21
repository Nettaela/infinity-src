#include <stdio.h>	/*for printf*/
#include <string.h> /*for strlen*/	
#include <ctype.h>	/*for tolower*/
#include <assert.h> /*for assert*/
#include <stdlib.h> /*for EXIT SUCCESS */

/*function declarations*/
static char *Strdup(const char *s);
static char *Strcpy(char *dest, const char *src); 
static size_t SizeOfEnv(char **env);	
static void PrintEnv(char **env);
static void CleanStrings(char **env);

/* PSEUDO-CODE:

duplicate structure: size of env, malloc **buffer, save pointer.

content of env: duplicate env - string by string. using strdup (uses malloc)
use tolower (char by char). 
put each string pointer in the pointer array of buffer.

print env.

de-allocate memory - free everything */

int main(int argc, char *argv[], char *env[])
{

	char **buffer_runner1;
	char **buffer_runner2;
	size_t env_size = SizeOfEnv(env);
	/*allocate memory for buffer of the same size*/
	char **buffer = (char **)malloc((env_size+1)*sizeof(char*)); /*env_size plus one for the NULL*/
	(void)argc;
	(void)argv;
	buffer_runner1 = buffer;
	buffer_runner2 = buffer;

	/*check that buffer was allocated*/
	if (buffer == NULL)
	{
		printf("buffer was not allocated\n");
		return EXIT_FAILURE;
	}
	else
	{
		printf("buffer allocation successful\n");
	}
	/*duplicate and put in buffer*/
		
	while (*env != NULL)
	{
		*buffer_runner1 = Strdup(*env); /*Strdup uses Strcpy, Strcpy makes everything lowercase*/
		if (*buffer_runner1 == NULL)
		{
			CleanStrings(buffer_runner2);
			return EXIT_FAILURE;
		}
			
		++buffer_runner1;
		++env;

	}
	
	*buffer_runner1 = NULL;
	
	/*print buffer from the start*/
	PrintEnv(buffer_runner2);
	
	/*de-allocate strings*/
	CleanStrings(buffer_runner2);
	
	/*de-allocate buffer*/
	free(buffer);
	buffer = NULL;
	
	return EXIT_SUCCESS;
}

static size_t SizeOfEnv(char **env)	/*check env size*/
{
	size_t count = 0;
	
	while (*env != NULL)
	{
		++count;
		++env;
	}
	return count;
}

static void PrintEnv(char **env)
{
	while (*env != NULL)
	{
		puts(*env);

		++env;
	}
}

static void CleanStrings(char **env)
{
	while (*env != NULL)
	{
		free(*env);
		*env=NULL;
		++env;
	}
		
}

static char *Strdup(const char *s)
{
	char *dupstr = malloc((strlen(s) + 1) * sizeof(char)); /*using malloc gives an error in valgrind
													 due to using the uninitialized string in strcpy?*/
	
	if (dupstr == NULL)
	{
		printf("buffer in dupstr was not allocated\n");
		dupstr = NULL;
		return 0;
	}
	
	Strcpy(dupstr,s);	
	return dupstr;
}

static char * Strcpy (char *dest, const char *src) 
{
	char *runner = dest;
	
	assert (dest && src);
		
	while (*src != '\0')
	{
		*runner = *src;
		*runner = tolower(*runner);
		++src;
		++runner;
	}
	*runner = '\0';
	return dest;
}


