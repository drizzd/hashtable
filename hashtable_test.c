#include "hash.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

struct item {
	void *value;
	char key[];
};

#define HASHTABLE_SIZE 5

static struct item *hashtable[HASHTABLE_SIZE];

static inline int hashtable_test_pos(const char *key, int pos)
{
	return !hashtable[pos] || !strcmp(key, hashtable[pos]->key);
}

struct item *item_new(const char *key, void *value)
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

int inc_key(char *key, int n)
{
	int i;

	for (i = n-1; i >= 0; i--) {
		key[i]++;
		if (key[i] <= 'z')
			return 0;
		key[i] = 'a';
	}

	return 1;
}

int hashtable_test_key_at_pos(const char *key, int pos)
{
	return hashtable[pos] && !strcmp(hashtable[pos]->key, key);
}

int find_next_collision(int h, char *key, int n)
{
	while (!inc_key(key, n))
		if (hash(key) % HASHTABLE_SIZE == h)
			return 0;

	return 1;
}

int main()
{
	char key[] = "aaaaaaaa";
	int i;
	int pos = 0;

	for (i = 0; i < HASHTABLE_SIZE; i++) {
		assert(!find_next_collision(pos, key, strlen(key)));
		assert(!hashtable_set(key, NULL + i));
		assert(hashtable_test_key_at_pos(key, pos + i % HASHTABLE_SIZE));
	}

	assert(!find_next_collision(pos, key, strlen(key)));
	/* table is full */
	assert(hashtable_set(key, NULL) == 1);

	return 0;
}
