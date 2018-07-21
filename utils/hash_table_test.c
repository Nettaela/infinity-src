#include "hash.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int IsMatch(const void *data, 
					void *param,
					const void *to_find);
void SimpleTest(void);
void InteractiveTest(void);
int FreeWords(void *data, void *params);

int main()
{
	SimpleTest();
	InteractiveTest();
	return 0;
}

size_t HashFunc(const void *data)
{/*http://www.cse.yorku.ca/~oz/hash.html*/
	const char *str = (const char*)data;
	size_t hash = 5381;
    int c;
    
	while ((c = *str++))
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	return hash;
}

void SimpleTest(void)
{
	char *word_to_insert1 = "first";
	char *word_to_insert2 = "second";
	
	hash_t *table = HashCreate(HashFunc, 10, IsMatch, NULL);
	assert(table);
	assert(HashIsEmpty(table) == 1);
	assert(HashSize(table) == 0);
	
	assert(0 == HashInsert(table, word_to_insert1));
	
	assert(HashIsEmpty(table) == 0);
	assert(HashSize(table) == 1);
	
	assert(0 == HashInsert(table, word_to_insert2));
	
	assert(HashSize(table) == 2);
		
	assert(*word_to_insert1 == *(char*)HashFind(table, word_to_insert1));
	assert(*word_to_insert2 == *(char*)HashFind(table, word_to_insert2));
	assert(0 == strcmp(word_to_insert1, HashFind(table, word_to_insert1)));
	assert(0 == strcmp(word_to_insert2, HashFind(table, word_to_insert2)));
		
	assert(0 == strcmp(word_to_insert1, HashErase(table, word_to_insert1)));
	assert(HashSize(table) == 1);
	
	HashDestroy(table);
	
	puts("Simple test passed. check valgrind");
}


int IsMatch(const void *data, 
					void *param,
					const void *to_find)
{
		(void)param;
	return (strcmp(data, to_find) == 0);
}

int FreeWords(void *data, void *params)
{
	(void)params;
	if(data != NULL)
	{
		free(data);
	}
	return 0;
	
}

void InteractiveTest(void)
{
	char user_input[100];
	char *exit_phrase = "exit";
	size_t table_size = 99171;
	char *send_word = NULL;
	char c;
	int i = 0;
	char current_word[100];
	char * filename = "/usr/share/dict/words";
	FILE * fp = fopen(filename, "r");
	
	hash_t *word_table = HashCreate(HashFunc, table_size, IsMatch, NULL);

	assert(HashIsEmpty(word_table));
		
	if (fp == NULL)
	{ 
	/*perror*/
		return;
	}	
	
	/*insert all the dictionary into the hash table*/
	while((c = fgetc(fp)) != EOF)
	{
		if(c == ' ' || c == '\n')
		{
			current_word[i] = '\0';
			send_word = malloc(100);
			strcpy(send_word, current_word);
			assert(0 == HashInsert(word_table, send_word));
			i = 0;
		}
		else
		{
			current_word[i] = c;
			++i;
		}
	}
	fclose(fp);
 
	assert(HashSize(word_table) == table_size);
	puts("\ndictionary loaded successfully");
	printf("load factor: %f\n", HashLoadFactor(word_table));
	printf("variance: %f\n", HashVar(word_table));
	
	
	puts("\nwelcome to spell checker, u can type ""exit"" to leave.\n\nplease insert a word:");
	
	while(1)
	{
		scanf("%s",user_input); 
		if(NULL == HashFind(word_table, user_input))
		{
			puts("Not a word, actually, barely a string...");
		}
		else if(strcmp(user_input, exit_phrase) == 0)
		{
			HashForEach(word_table, FreeWords, NULL);
			HashDestroy(word_table);
			puts("kay, bye!");
			exit(1);
		}
		else if(0 == strcmp(user_input, HashFind(word_table, user_input)))
		{
			puts("This is a word");
		}
		
		
		puts("\nplease insert a word:");
		
	}
}


