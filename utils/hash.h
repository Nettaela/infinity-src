#ifndef HASH_H_
#define HASH_H_

#include <stddef.h>

/*for test: insert words from dictionary /usr/share/dict/words*/

typedef struct hash_table hash_t;

hash_t *HashCreate (
				size_t (*hash_func)(const void *data), 
				size_t size, 
				int (*is_match)(
					const void *data, 
					void *param,
					const void *to_find),
				void *param);

void HashDestroy(hash_t *table);

int HashInsert(hash_t *table, void *data);

void *HashErase(hash_t *table, const void *data);

void *HashFind(const hash_t *table, const void *data);

/*WORNING!!! do not change key values*/
int HashForEach(hash_t *table, int (*action_func)(void *data, void *params), void *params);

double HashLoadFactor(const hash_t *table);

double HashVar(const hash_t *table);

size_t HashSize(const hash_t *table);

int HashIsEmpty(const hash_t *table);

#endif /* HASH_H_ */

