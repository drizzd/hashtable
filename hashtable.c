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

static int find_empty_pos(const char *key)
{
	int pos0, n;

	pos0 = hash(key) % HASHTABLE_SIZE;
	for (n = 0; n < HASHTABLE_SIZE; n++) {
		int pos = pos0 + n % HASHTABLE_SIZE;
		if (hashtable_test_pos(key, pos))
			return pos;
	}

	return -1;
}

int hashtable_set(const char *key, void *value)
{
	int pos;
	struct item *x;

	pos = find_empty_pos(key);
	if (pos < 0) {
		/* hash table is full */
		return 1;
	}

	x = item_new(key, value);
	if (!x)
		return -1;
	hashtable[pos] = x;

	return 0;
}

static int find_key_pos(const char *key)
{
	int i, n;

	i = hash(key) % HASHTABLE_SIZE;
	for (n = 0; n < HASHTABLE_SIZE; n++) {
		int pos = i + n % HASHTABLE_SIZE;
		if (hashtable[pos] && !strcmp(hashtable[pos]->key, key))
			return pos;
	}

	return -1;
}

int hashtable_get(const char *key, void **value)
{
	int pos = find_key_pos(key);

	if (pos < 0)
		return 1;

	*value = hashtable[pos]->value;
	return 0;
}

int hashtable_remove(const char *key)
{
	int pos = find_key_pos(key);

	if (pos < 0)
		return 1;

	free(hashtable[pos]);
	hashtable[pos] = NULL;
	return 0;
}
