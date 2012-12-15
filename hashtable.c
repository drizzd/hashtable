#include "hash.h"
#include "hashtable.h"
#include <string.h>
#include <stdlib.h>

struct item *hashtable[HASHTABLE_SIZE];

static inline int hashtable_test_pos(const char *key, int pos)
{
	return !hashtable[pos] || !strcmp(key, hashtable[pos]->key);
}

static struct item *item_new(const char *key, void *value)
{
	int n = strlen(key);
	struct item *x = malloc(sizeof(struct item) + n + 1);
	if (!x)
		return NULL;
	x->value = value;
	strncpy(x->key, key, n);
	x->key[n] = '\0';

	return x;
}

int hashtable_set(const char *key, void *value)
{
	unsigned i, n;
	struct item *x;

	i = hash(key) % HASHTABLE_SIZE;
	for (n = 0; n < HASHTABLE_SIZE; n++)
		if (hashtable_test_pos(key, i + n % HASHTABLE_SIZE))
			break;

	if (n == HASHTABLE_SIZE) {
		/* hash table is full */
		return 1;
	}

	x = item_new(key, value);
	if (!x)
		return -1;
	hashtable[i+n] = x;

	return 0;
}
