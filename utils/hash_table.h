#ifndef HASH_H
#define HASH_H

#include <stddef.h>

/*for test: insert words from dictionary /usr/share/dict/words*/

typedef struct hash_table hash_t;

hash_t *Create (
				size_t (*hash_func)(void *data), 
				size_t size, 
				int (*is_match)(const void *data1, const void *data2));

void HashDestroy(hash_t *table);

void *HashInsert(hash_t *table, void *data);

void *HashErase(hash_t *table, const void *data);

void *HashFind(const hash_t *table, const void *data);

/*WORNING!!! do not change key values*/
int HashForEach(hash_t *table, int (*action_func)(void *data, void *params), void *params);

double HashLoadFactor(const hash_t *table);

double HashVar(const hash_t *table);

size_t HashSize(const hash_t *table);

int HashIsEmpty(const hash_t *table);

#endif
