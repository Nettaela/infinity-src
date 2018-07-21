#include "hash.h"
#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


struct hash_table
{
	size_t (*hash_func)(const void *data);
	int (*is_match)(const void *data, void *param, const void *to_find);
	dlist_t **list;
	size_t array_size;
	void *param;
};

hash_t *HashCreate (
				size_t (*hash_func)(const void *data), 
				size_t size, 
				int (*is_match)(const void *data, void *param, 
				const void *to_find),
				void *param)
{
	size_t index = 0;
	dlist_t **array_of_lists = NULL; 

	hash_t *new_table = (hash_t *)malloc(sizeof(*new_table));
	if (NULL == new_table)
	{
		return NULL;
	}
	array_of_lists = (dlist_t **)malloc(sizeof(dlist_t *) * size);
	if (NULL == array_of_lists)
	{
		free(new_table);
		return NULL;  
	}
	
	assert(is_match);
	assert(hash_func);
	
	new_table->list = array_of_lists;
	new_table->hash_func = hash_func;
	new_table->is_match = is_match;
	new_table->array_size = size;
	new_table->param = param;
	
	for(index = 0; index < size ; ++index)
	{
		new_table->list[index] = DListCreate(); 
		if(NULL == new_table->list[index])
		{
			size_t destroy_index = 0;
			for(destroy_index = 0 ; destroy_index < index; ++destroy_index)
			{
				free(new_table->list[destroy_index]);
			}
			free(array_of_lists);
			free(new_table);
			return NULL;
		}
	}
		
	return new_table;
}

void HashDestroy(hash_t *table)
{
	size_t array_size = 0;
	dlist_t *current_list = NULL;
	
	assert(table);
	
	array_size = table->array_size;	
	
	while(array_size > 0)
	{
		current_list = table->list[array_size-1];
		DListDestroy(current_list);
		--array_size;  
	}
	free(table->list);
	free(table);
}

int HashInsert(hash_t *table, void *data)
{
	size_t hash_value = 0;
	dlist_t *current_list = NULL;
	
	assert(table);
	
	hash_value = (table->hash_func(data)) % table->array_size;
	current_list = table->list[hash_value];
	
	if(DListIsSameIterator(DListPushBack(current_list, data), DListEnd(current_list)))
	{
		return 1;
	}
	return 0;
}


void *HashErase(hash_t *table, const void *data)
{ 
	dlist_t *current_list = NULL;
	size_t hash_value = 0;
	dlist_iter_t iter = {0};
	void *data_to_return = NULL;
	
	assert(table);
	
	hash_value = (table->hash_func(data)) % table->array_size;
	current_list = table->list[hash_value];
	iter = DListFind(DListBegin(current_list), DListEnd(current_list), 
		table->is_match, table->param, data);

	if(DListIsSameIterator(iter, DListEnd(current_list)))
	{
		return NULL;
	}
	data_to_return = DListGetData(iter);
	
	DListErase(iter);
	
	return data_to_return;
}

void *HashFind(const hash_t *table, const void *data)
{ 
	dlist_t *current_list = NULL;
	size_t hash_value = 0;
	dlist_iter_t iter = {0};
	
	assert(table);
	
	hash_value = (table->hash_func(data)) % table->array_size;
	current_list = table->list[hash_value]; 
	iter = DListFind(DListBegin(current_list), DListEnd(current_list), 
		table->is_match, table->param, data);

	if(DListIsSameIterator(iter, DListEnd(current_list)))
	{
		return NULL;
	}
	return DListGetData(iter);
}

/*WORNING!!! do not change key values*/
int HashForEach(hash_t *table, int (*action_func)(void *data, void *params), void *params)
{
	size_t array_size = 0;
	int result = 0;
	dlist_t *current_list = NULL;
	
	assert(table);
	assert(action_func);
	
	array_size = table->array_size;
	
	while(array_size > 0)
	{
		current_list = table->list[array_size-1]; 
		result = DListForEach(DListBegin(current_list), 
			DListEnd(current_list), action_func, params); 
		if(0 != result)
		{
			return result;
		}
		--array_size;
	}
	return result;
}

double HashLoadFactor(const hash_t *table)
{
	assert(table);
	return HashSize(table)/table->array_size;
}

double HashVar(const hash_t *table)
{
	double sum = 0;
	size_t current_list_size = 0;
	size_t array_size = 0;
	double load_factor = 0;
	double size_minus_ave = 0;
	double power = 0;
	dlist_t *current_list = NULL;
	
	assert(table);
	
	load_factor = HashLoadFactor(table);
	array_size = table->array_size;
	
	while(array_size > 0)
	{
		current_list = table->list[array_size-1];
		current_list_size = DListSize(current_list);
		size_minus_ave = load_factor - current_list_size;
		power = size_minus_ave * size_minus_ave;
		sum += power;
		
		--array_size;
	}
	return sum/table->array_size;
}

size_t HashSize(const hash_t *table)
{
	size_t item_counter = 0;
	size_t array_size = 0;
	
	dlist_t *current_list = NULL;
	
	assert(table);
	
	array_size = table->array_size;
	
	while(array_size > 0)
	{
		current_list = table->list[array_size-1];
		item_counter += DListSize(current_list);
		--array_size;
	}
	return item_counter;
}

int HashIsEmpty(const hash_t *table)
{
	size_t array_size = 0;
	
	dlist_t *current_list = NULL;

	assert(table);
	
	array_size = table->array_size;
	
	while(array_size > 0)
	{
		current_list = table->list[array_size-1];
	
		if(DListIsEmpty(current_list) != 1)
		{
			return 0;
		}
		--array_size;
	}
	return 1;
}
